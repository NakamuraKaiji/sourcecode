#include "pch.h"
#include "SmokeEffect.h"
#include "GameParameter.h"
#include "Utilities/Resources.h"

using namespace DirectX;

// �R���X�g���N�^
SmokeEffect::SmokeEffect(DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Vector3 velocity
)
	:  m_position(position)
	, m_velocity(velocity)
	, m_timer(WHITE_SMOKE_DISPLAY_TIME)
	, m_alpha(0.0f)
{
	// �e�N�X�`�����擾
	m_smokeTexture = Resources::GetInstance()->GetParticle();

	// �`�揇�̐ݒ�
	SetOt(static_cast<int>(OT_Priority::OT_Top));
}

// �X�V
bool SmokeEffect::Update(float elapsedTime)
{
	// ���ԂɂȂ�����^�X�N�͏�����
	m_timer -= elapsedTime;
	if (m_timer <= 0.0f) return false;

	// ���X�ɏ����Ă���
	m_alpha = m_timer / WHITE_SMOKE_DISPLAY_TIME;

	m_position += m_velocity;

	// ���x�𗎂Ƃ��Ă���
	float speed = m_velocity.Length();
	speed *= WHITE_SMOKE_FRICTION;
	m_velocity.Normalize();
	m_velocity *= speed;

	return true;
}

// �`��
void SmokeEffect::Render()
{
	// ���_���
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(XMFLOAT3( 0.5f, 0.0f,  0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, m_alpha), XMFLOAT2(0.0f, 0.0f)),
		VertexPositionColorTexture(XMFLOAT3(-0.5f, 0.0f,  0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, m_alpha), XMFLOAT2(1.0f, 0.0f)),
		VertexPositionColorTexture(XMFLOAT3(-0.5f, 0.0f, -0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, m_alpha), XMFLOAT2(1.0f, 1.0f)),
		VertexPositionColorTexture(XMFLOAT3( 0.5f, 0.0f, -0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, m_alpha), XMFLOAT2(0.0f, 1.0f)),
	};

	auto context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_graphics->GetCommonStates();
	auto effect = m_graphics->GetBasicEffect();

	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states->DepthRead(), 0);
	context->RSSetState(states->CullCounterClockwise());

	// �ݒ�
	float scale = 2.0f * (1.0f - m_timer / WHITE_SMOKE_DISPLAY_TIME);
	SimpleMath::Matrix world = SimpleMath::Matrix::CreateScale(scale) * SimpleMath::Matrix::CreateTranslation(m_position);
	effect->SetWorld(world);
	effect->SetTexture(m_smokeTexture.Get());

	// �\��
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	m_graphics->GetPrimitiveBatch()->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_graphics->DrawPrimitiveEnd();
}
