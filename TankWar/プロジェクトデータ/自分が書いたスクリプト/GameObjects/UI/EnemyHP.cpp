#include "pch.h"
#include "EnemyHP.h"
#include "MyLib/BinaryFile.h"


using namespace DirectX;

// �C���v�b�g���C�A�E�g	
const std::vector<D3D11_INPUT_ELEMENT_DESC>	EnemyHP::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// �R���X�g���N�^
EnemyHP::EnemyHP()
	: m_texture(nullptr)
	, m_textureHeight(0)
	, m_textureWidth(0)
	, m_res(nullptr)
	, m_ratio(1.0f)
	, m_position{}
{
	//�V�F�[�_�[�̍쐬
	CreateShader();

	//�摜�̓ǂݍ���
	LoadTexture(L"Resources/dds/HP.dds");
}

// �e�N�X�`�����\�[�X�ǂݍ���
void EnemyHP::LoadTexture(const wchar_t* path)
{
	DirectX::CreateDDSTextureFromFile(
		m_graphics->GetDeviceResources()->GetD3DDevice(),
		path, 
		m_res.ReleaseAndGetAddressOf(), 
		m_texture.ReleaseAndGetAddressOf()
	);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(m_res.As(&tex));

	// �摜�T�C�Y���擾
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

// �V�F�[�_���암���������������֐�
void EnemyHP::CreateShader()
{
	// �R���p�C�����ꂽ�V�F�[�_�[�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/HP_VS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/HP_GS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/HP_PS.cso");

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

	//�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	m_graphics->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_CBuffer);
}

// �X�V
bool EnemyHP::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	return true;
}

// �`��
void EnemyHP::Render()
{
	auto context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_graphics->GetCommonStates();

	m_position = SimpleMath::Vector3(m_position.x, 1.0f, m_position.z);

	// ���_���
	VertexPositionColorTexture vertex[1] =
	{
		VertexPositionColorTexture(m_position
		, SimpleMath::Vector4(0.0f, 0.0f, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight))
		, SimpleMath::Vector2(m_ratio, 0))
	};

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
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �`��
	m_graphics->GetPrimitiveBatch()->Begin();
	m_graphics->GetPrimitiveBatch()->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_graphics->GetPrimitiveBatch()->End();

	//�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

// �r���{�[�h
void EnemyHP::CreateBillboard(DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	m_billboard =
		//SimpleMath::Matrix::CreateBillboard(target, eye , up);
		SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero, eye - target, up);

	SimpleMath::Matrix rot = SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	m_billboard = rot * m_billboard;

}

