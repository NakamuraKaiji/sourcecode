#include "pch.h"
#include "GameObject.h"
#include "GameParameter.h"

using namespace DirectX;

GameObject::GameObject(
	int id, 
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotate,
	float radius, 
	float friction, 
	float weight
)
	: m_id(id)
	, m_radius(radius)
	, m_friction(friction)
	, m_weight(weight)
	, m_position(position)
	, m_rotate(rotate)
{
}

// �X�V
bool GameObject::Update(float elapsedTime)
{
	// ���C�� = ���C�W�� �~ ���� �~ �d�͉����x
	float frictionForce = m_friction * m_weight * 9.8f * elapsedTime;

	// ���C�͂ɂ���đ��x�𗎂Ƃ�
	float v = m_velocity.Length() - (frictionForce / m_weight);
	if (v < 0.0f) v = 0.0f;
	m_velocity.Normalize();
	m_velocity *= v;

	// �ʒu�ɑ��x�𑫂�
	m_position += m_velocity;

	return true;
}

// �͂�������֐�
void GameObject::AddForce(DirectX::SimpleMath::Vector3 dir, float force)
{
	// �����x
	m_acceleration = dir * (force / m_weight);

	// ���x�ɉ����x�𑫂�
	m_velocity += m_acceleration;
}

// �����𐧌�����֐�
void GameObject::LimitSpeed(float speed)
{
	// �ő呬�x�ȏ�ɂȂ�Ȃ��悤����
	if (m_velocity.LengthSquared() > speed * speed)
	{
		m_velocity.Normalize();
		m_velocity *= speed;
	}
}

// �Փˎ��̗͂��擾����
float GameObject::GetHitForce()
{
	float force = HIT_FORCE_MIN;

	// �A���q�b�g���̑��x�̉e�����傫������̂ő��x��}����
	float v = m_velocity.Length();
	if (v > 0.1f) v = 0.1f;
	force += m_weight * v;

	return force;
}
