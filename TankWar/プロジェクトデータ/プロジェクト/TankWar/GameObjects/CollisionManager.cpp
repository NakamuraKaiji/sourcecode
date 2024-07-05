#include "pch.h"
#include "CollisionManager.h"

using namespace DirectX;

// �X�V
void CollisionManager::Update()
{
	// ��������ŏՓ˔��肷��
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		GameObject* a = m_objects[i];
		for (size_t j = i + 1; j < m_objects.size(); j++)
		{
			GameObject* b = m_objects[j];
			// ���Ƌ��̏Փ˔���
			SimpleMath::Vector3 distance = a->GetPosition() - b->GetPosition();
			float r = a->GetRadius() + b->GetRadius();
			if (distance.LengthSquared() <= r * r)
			{
				// �Փ˂���
				a->OnHit(b);
				b->OnHit(a);
			}
		}
	}
	// �o�^���X�g���N���A�ɂ���
	m_objects.clear();
}

// �o�^�֐�
void CollisionManager::AddObject(GameObject* object)
{
	// �Փ˔��胊�X�g�ɓo�^
	m_objects.push_back(object);
}
