//*********************************************************************
//			�T�v	�F�v���C���[�̃J�����N���X
// 
//			�����	�F7��03��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "Camera.h"

// �v���C���[�J����
class PlayerCamera : public Camera
{
public:
	// �J�����^�C�v
	enum class Type
	{
		TYPE_A,
		TYPE_B,
		TYPE_C,
	};
private:
	// ���݂̃J�����^�C�v
	Type m_type;
	// ��]�p
	float m_angle;
	// �v���C���[�̈ʒu
	DirectX::SimpleMath::Vector3 m_playerPos;
	// �v���C���[�̉�]
	DirectX::SimpleMath::Quaternion m_playerRotate;
public:
	// �R���X�g���N�^
	PlayerCamera();
	// �X�V
	void Update(float elapsedTime);
	// �v���C���[�̈ʒu�Ɖ�]�p��ݒ�	
	void SetPlayer(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotate
	)
	{
		m_playerPos = position;
		m_playerRotate = rotate;
	}
	// �J�����̃^�C�v��ݒ肷��֐�
	void SetType(Type type)
	{
		// �J�����̏��������Ă�
		//InitializeCamera();
		m_type = type;
	}
};