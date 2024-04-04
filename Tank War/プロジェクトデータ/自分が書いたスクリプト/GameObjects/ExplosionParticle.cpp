#include "pch.h"
#include "ExplosionParticle.h"
#include "Utilities/Resources.h"
#include "MyLib/BinaryFile.h"
#include "GameParameter.h"
#include <random>

using namespace DirectX;

// �C���v�b�g���C�A�E�g	
const std::vector<D3D11_INPUT_ELEMENT_DESC>	ExplosionParticle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,							 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// �R���X�g���N�^
ExplosionParticle::ExplosionParticle()
	: m_timer(0.0f)
	, m_scale(SimpleMath::Vector3::Zero)
{
	// ���\�[�X�����[�h
	Resources::GetInstance()->LoadResource();

	// �V�F�[�_�[�̍쐬
	CreateShader();

	// �e�N�X�`���ǂݍ���
	LoadTexture();
}

// �e�N�X�`�����\�[�X�ǂݍ���
void ExplosionParticle::LoadTexture()
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	texture = Resources::GetInstance()->GetParticle();

	m_texture.push_back(texture);
}

// �V�F�[�_���암���������������֐�
void ExplosionParticle::CreateShader()
{
	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	// �C���v�b�g���C�A�E�g�̍쐬
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(),
		VSData.GetSize(),
		m_inputLayout.GetAddressOf()
	);

	// ���_�V�F�[�_�쐬
	if (FAILED(m_graphics->GetDeviceResources()->GetD3DDevice()->CreateVertexShader(
		VSData.GetData(),
		VSData.GetSize(),
		NULL,
		m_vertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(m_graphics->GetDeviceResources()->GetD3DDevice()->CreateGeometryShader(
		GSData.GetData(),
		GSData.GetSize(),
		NULL,
		m_geometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(m_graphics->GetDeviceResources()->GetD3DDevice()->CreatePixelShader(
		PSData.GetData(),
		PSData.GetSize(),
		NULL,
		m_pixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_CBuffer);
}

// �X�V
void ExplosionParticle::Update(float elapsedTime)
{
	// 0.01�b���Ƃɐ���
	m_timer += elapsedTime;
	if (m_timer >= 0.01f)
	{
		std::random_device seed;
		std::default_random_engine engine(seed());
		std::uniform_real_distribution<> dist(0, XM_2PI);
		float range = BLACK_SMOKE_RANGE;
		float rand = static_cast<float>(dist(engine));
		ParticleUtility pU(
			1.0f,
			SimpleMath::Vector3(m_position.x + range * cosf(rand), 0.5f, m_position.z + range * sinf(rand)),            // ����W
			SimpleMath::Vector3(0.0f, 0.5f, 0.0f),			                                                            // ���x
			SimpleMath::Vector3(0.0f, 0.5f, 0.0f), 					                                                    // �����x
			m_scale, SimpleMath::Vector3::Zero,	                                                                        // �����X�P�[���A�ŏI�X�P�[��
			SimpleMath::Color(0.41f, 0.41f, 0.41, 0.8f), SimpleMath::Color(0.0f, 0.0f, 0.0f, 1.0f)	                    // �����J���[�A  �ŏI�J���[
		);

		m_particleUtility.push_back(pU);
		m_timer = 0.0f;
	}


	//timer��n����m_effect�̍X�V�������s��
	for (std::list<ParticleUtility>::iterator ite = m_particleUtility.begin(); ite != m_particleUtility.end(); ite++)
	{
		// �q�N���X����false�ŏ���
		if (!(ite)->Update(elapsedTime))
		{
			ite = m_particleUtility.erase(ite);
			if (ite == m_particleUtility.end()) break;
		}
	}
}

// �`��
void ExplosionParticle::Render()
{
	auto context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_graphics->GetCommonStates();

	DirectX::SimpleMath::Vector3 cameraDir = m_cameraTarget - m_cameraPosition;
	cameraDir.Normalize();

	m_particleUtility.sort(
		[&](ParticleUtility lhs, ParticleUtility  rhs)
		{
			//�J�������ʂ̋����Ń\�[�g
			return cameraDir.Dot(lhs.GetPosition() - m_cameraPosition) > cameraDir.Dot(rhs.GetPosition() - m_cameraPosition);
		});
	//�o�^����Ă��钸�_�����Z�b�g
	m_vertices.clear();
	for (auto& li : m_particleUtility)
	{
		if (cameraDir.Dot(li.GetPosition() - m_cameraPosition) < 0.0f) {
			//���ς��}�C�i�X�̏ꍇ�̓J�����̌��Ȃ̂ŕ\������K�v�Ȃ�
			continue;
		}
		VertexPositionColorTexture vPCT;
		vPCT.position = XMFLOAT3(li.GetPosition());
		vPCT.color = XMFLOAT4(li.GetNowColor());
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//�\������_���Ȃ��ꍇ�͕`����I���
	if (m_vertices.empty())
	{
		return;
	}

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = m_graphics->GetViewMatrix().Transpose();
	cbuff.matProj = m_graphics->GetProjectionMatrix().Transpose();
	cbuff.matWorld = m_billboard.Transpose();
	cbuff.Diffuse = SimpleMath::Vector4(1, 1, 1, 1);

	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�������`��w��
	ID3D11BlendState* blendstate = states->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	// �J�����O�͍�����
	context->RSSetState(states->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_graphics->GetPrimitiveBatch()->Begin();
	m_graphics->GetPrimitiveBatch()->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());
	m_graphics->GetPrimitiveBatch()->End();

	//�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

// �r���{�[�h
void ExplosionParticle::CreateBillboard(DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	m_billboard =
		SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero, eye - target, up);

	SimpleMath::Matrix rot = SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	m_cameraPosition = eye;
	m_cameraTarget = target;
	m_billboard = rot * m_billboard;
}
