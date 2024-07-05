//*********************************************************************
//			�T�v	�F�Q�[���I�u�W�F�N�g�N���X
// 
//			�����	�F11��2��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/TaskManager.h"
#include "GameParameter.h"

class GameObject : public Task
{
private:

	// �I�u�W�F�N�g����ID
	int m_id;

	// ���a
	float m_radius;

	// ����
	float m_weight;

	// ���Ƃ̖��C�W��
	float m_friction;

	// �����x
	DirectX::SimpleMath::Vector3 m_acceleration;

	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// ��]
	DirectX::SimpleMath::Quaternion m_rotate;

public:

	// �R���X�g���N�^
	GameObject(
		int id,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotate,
		float radius,
		float friction,
		float weight
	);

	// �X�V
	bool Update(float elapsedTime) override;

	// �I�u�W�F�N�g����ID��ݒ�
	void SetID(int id) { m_id = id; }

	// �I�u�W�F�N�g����ID���擾
	int GetID() { return m_id; }

	// �Փ˂�����Ă΂��֐�
	virtual void OnHit(GameObject* object) = 0;

	// ���a���擾����֐�
	float GetRadius() { return m_radius; }

	// ���x��ݒ肷��֐�
	void SetVelocity(DirectX::SimpleMath::Vector3 velocity) { m_velocity = velocity; }

	// ���x���擾����֐�
	const DirectX::SimpleMath::Vector3& GetVelocity() { return m_velocity; }

	// �ʒu��ݒ肷��֐�
	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	// �ʒu���擾����֐�
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	// ��]��ݒ肷��֐�
	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_rotate = rotate; }

	// ��]���擾����֐�
	const DirectX::SimpleMath::Quaternion& GetRotate() { return m_rotate; }

	// �͂�������֐�
	void AddForce(DirectX::SimpleMath::Vector3 dir, float force);

	// ���C�W����ݒ肷��֐�
	void SetFriction(float friction) { m_friction = friction; }

	// �d����ݒ肷��֐�
	void SetWeight(float weight) { m_weight = weight; }

	// �����𐧌�����֐�
	void LimitSpeed(float speed);

	// �Փˎ��̗͂��擾����
	float GetHitForce();

};
