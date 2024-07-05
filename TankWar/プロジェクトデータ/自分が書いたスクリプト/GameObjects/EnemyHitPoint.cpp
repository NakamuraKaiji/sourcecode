#include "pch.h"
#include "EnemyHitPoint.h"
#include "Utilities/Resources.h"

using namespace DirectX;

//�R���X�g���N�^
EnemyHitPoint::EnemyHitPoint()
	: m_hp(100.0f)
{
}

// ������
void EnemyHitPoint::Initialize()
{
	auto device = m_graphics->GetDeviceResources()->GetD3DDevice();
	auto context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	
	// �x�[�V�b�N�G�t�F�N�g�̍쐬
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetLightingEnabled(false);
	m_basicEffect->SetVertexColorEnabled(false);
	m_basicEffect->SetTextureEnabled(true);

	// ���̓��C�A�E�g�̍쐬
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf())
	);

	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(context);

	// �e�N�X�`�����擾����
	m_hpTexture_a = Resources::GetInstance()->GetHP_A();
	m_hpTexture_b = Resources::GetInstance()->GetHP_B();
}

// �`��
void EnemyHitPoint::Render()
{
	auto context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_graphics->GetCommonStates();

	// �r���[�s����擾
	SimpleMath::Matrix view = m_graphics->GetViewMatrix();
	// �ˉe�s����擾
	SimpleMath::Matrix proj = m_graphics->GetProjectionMatrix();

	// �̗̓o�[�̈ʒu�i��Ԃ̈ʒu����Y����1�グ���ꏊ�Ɉʒu���Ă���j
	SimpleMath::Vector3 objectPosition = m_position + SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	// �r���{�[�h�s��̍쐬
	SimpleMath::Matrix billboardMatrix = SimpleMath::Matrix::CreateBillboard(
		objectPosition,
		m_cameraPosition,
		SimpleMath::Vector3::Up,
		nullptr
	);

	// �G�t�F�N�g�̐ݒ�
	m_basicEffect->SetWorld(billboardMatrix);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);

	// �������̐ݒ�i�ʏ�̔������j
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�̐ݒ�i�[�x�o�b�t�@���g�p���Ȃ��j
	context->OMSetDepthStencilState(states->DepthNone(), 0);
	// �J�����O�̐ݒ�i�J�����O���Ȃ��j
	context->RSSetState(states->CullNone());

	// ���̓��C�A�E�g�̐ݒ�
	context->IASetInputLayout(m_inputLayout.Get());

	// �e�N�X�`���T���v���[�̐ݒ�
	ID3D11SamplerState* samplers[] = { states->LinearClamp() };
	context->PSSetSamplers(0, 1, samplers);

	//	-----�̗̓o�[�̉��n�̕`��-----
	m_basicEffect->SetTexture(m_hpTexture_a.Get());
	m_basicEffect->Apply(context);

	// �̗̓o�[�̑傫���̓��[���h��Ԃ̍��W�n�ɑ΂��ĉ摜�T�C�Y��150����1�ɂ��Ă���
	float scale = 1.0f / 150.0f;

	// �̗̓o�[�̕��ƍ���
	float w = 224.0f * scale;
	float h = 32.0f * scale;

	// ���_���W
	VertexPositionTexture v[4] = {
		{ SimpleMath::Vector3(0.0f,  0.0f, 0.0f), SimpleMath::Vector2(0.0f, 0.0f) },
		{ SimpleMath::Vector3(   w,  0.0f, 0.0f), SimpleMath::Vector2(1.0f, 0.0f) },
		{ SimpleMath::Vector3(   w,    -h, 0.0f), SimpleMath::Vector2(1.0f, 1.0f) },
		{ SimpleMath::Vector3(0.0f,    -h, 0.0f), SimpleMath::Vector2(0.0f, 1.0f) },
	};

	// �̗̓o�[�̃Z���^�[�̈ʒu���������̂ݒ��S�ɒ�������
	v[0].position.x -= w / 2.0f;
	v[1].position.x -= w / 2.0f;
	v[2].position.x -= w / 2.0f;
	v[3].position.x -= w / 2.0f;

	// �v���~�e�B�u�̕`��
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(v[0], v[1], v[2], v[3]);
	m_primitiveBatch->End();

	// ----�̗̓o�[�i�I�����W�F�̃o�[�j�̕`�� ----
	m_basicEffect->SetTexture(m_hpTexture_b.Get());
	m_basicEffect->Apply(context);

	// m_hp�̗͑́i0�`100�j
	float hp = m_hp / 100.0f;

	// �̗̓o�[�̉��n�̍��ォ��̃I�t�Z�b�g�i�z�u�ʒu�j
	float off_x = 10.0f * scale;
	float off_y = 10.0f * scale;
	// �̗̓o�[�̕��ƍ���
	float w2 = 204.0f * scale * hp;
	float h2 = 12.0f * scale;

	// ���_���
	VertexPositionTexture v2[4] = {
		{ SimpleMath::Vector3(     off_x,  0.0f - off_y, 0.0f), SimpleMath::Vector2(0.0f, 0.0f) },
		{ SimpleMath::Vector3(w2 + off_x,  0.0f - off_y, 0.0f), SimpleMath::Vector2(  hp, 0.0f) },
		{ SimpleMath::Vector3(w2 + off_x,   -h2 - off_y, 0.0f), SimpleMath::Vector2(  hp, 1.0f) },
		{ SimpleMath::Vector3(     off_x,   -h2 - off_y, 0.0f), SimpleMath::Vector2(0.0f, 1.0f) },
	};

	// �̗̓o�[�̃Z���^�[�̈ʒu���������̂ݒ��S�ɒ�������
	v2[0].position.x -= w / 2.0f;
	v2[1].position.x -= w / 2.0f;
	v2[2].position.x -= w / 2.0f;
	v2[3].position.x -= w / 2.0f;

	// �v���~�e�B�u�̕`��
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(v2[0], v2[1], v2[2], v2[3]);
	m_primitiveBatch->End();
}

// HP��ݒ肷��
void EnemyHitPoint::SetHP(float hp)
{
	m_hp = hp;
}

// �ʒu��ݒ肷��
void EnemyHitPoint::SetEnemyPosition(DirectX::SimpleMath::Vector3 position)
{
	m_position = position;
}

void EnemyHitPoint::SetCameraPosition(DirectX::SimpleMath::Vector3 cameraposition)
{
	m_cameraPosition = cameraposition;
}
