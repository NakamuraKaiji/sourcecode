#include "pch.h"
#include "ParticleUtility.h"

using namespace DirectX;

// �R���X�g���N�^
ParticleUtility::ParticleUtility(
	float life, 
	DirectX::SimpleMath::Vector3 pos, 
	DirectX::SimpleMath::Vector3 velocity, 
	DirectX::SimpleMath::Vector3 accele, 
	DirectX::SimpleMath::Vector3 startScale, 
	DirectX::SimpleMath::Vector3 endScale,
	DirectX::SimpleMath::Color startColor,
	DirectX::SimpleMath::Color endColor
)
{
	// �l����
	m_startLife =
		m_life = life;

	m_position = pos;
	m_velocity = velocity;
	m_accele = accele;

	m_startScale = 
		m_nowScale = startScale;
	m_endScale = endScale;

	m_startColor = 
		m_nowColor = startColor;
	m_endColor = endColor;

}

// �X�V
bool ParticleUtility::Update(float elapsedTime)
{
	// �X�P�[��
	m_nowScale = SimpleMath::Vector3::Lerp(m_startScale, m_endScale, 1.0f - m_life / m_startLife);
	// �F
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, 1.0f - m_life / m_startLife);
	// ���x�̌v�Z
	m_velocity += m_accele * elapsedTime;
	// ���W�̌v�Z
	m_position += m_velocity * elapsedTime;
	m_life -= elapsedTime;
	// ���C�t���O�Ŏ��g�������Ă��炤
	if (m_life < 0.0f)
	{
		return false;
	}

	return true;
}
