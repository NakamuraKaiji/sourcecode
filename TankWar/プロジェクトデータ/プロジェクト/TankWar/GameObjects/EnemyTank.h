//*********************************************************************
//			�T�v	�F�G�^���N�̃N���X
// 
//			�����	�F10��17��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "GameObject.h"
#include "MyLib/ModelPart.h"
#include "CollisionManager.h"
#include "GameResources.h"
#include "EnemyHitPoint.h"

class EnemyTank : public GameObject
{
public:
	// �G�̏��
	enum class EnemyState
	{
		Normal,			// �ʏ�
		Hit,			// ������΂�����
		Stop,           // ��~
	};

public:

	// �^�[�Q�b�g��ݒ�
	void SetTarget(GameObject* target) { m_target = target; }

	// ��Ԃ��擾����֐�
	EnemyState GetState() { return m_enemyState; }

	// �e�𔭎˂����ǂ������擾����֐�
	bool GetShotFlag() { return m_shotFlag; }

	// �X�^�[�g�������ǂ�����ݒ肷��֐�
	void SetStartFlag(bool start);

	// �G�̗̑͂ɃA�N�Z�X����֐�
	EnemyHitPoint* GetEnemyHitPoint() { return m_enemyHP; }

private:

	// �ʏ펞�̊֐�
	void Normal(float elapsedTime);

	// �Փ˒��֐�
	void Hit();

	// �C�e�Ƃ̏Փˊ֐�
	void OnHit_Bullet();

	// �v���C���[�Ƃ̓����蔻��
	void OnHit_Player();

public:

	// �R���X�g���N�^
	EnemyTank(const GameResources& gameResources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate);

	// ������
	void Initialize();

	// �X�V
	bool Update(float elapsedTime) override;

	// �`��
	void Render() override;

	// �Փ˂�����Ă΂��֐�
	void OnHit(GameObject* object) override;

	//	���Z�b�g
	void Reset();

	// �w��̕���������
	void TurnHeading(const DirectX::SimpleMath::Vector3& direction);

public:
	// ���Ǎs��
	// �T��
	DirectX::SimpleMath::Vector3 Seek(const DirectX::SimpleMath::Vector3& targetPosition);

	// �����s��		
	DirectX::SimpleMath::Vector3 Flee(const DirectX::SimpleMath::Vector3& targetPosition);

	// �p�j
	DirectX::SimpleMath::Vector3 Wander(float* wanderOriantation, float wanderRadius, float wanderDistance, float wanderRotate);


	// �x�N�g���̒����̐؂�̂�
	static DirectX::SimpleMath::Vector3 Truncate(const DirectX::SimpleMath::Vector3& v, float maxLength);

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();

	// �^�[�Q�b�g
	GameObject* m_target;

	// ��Ԃ̊e�p�[�c�ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_bodyModel;
	std::shared_ptr<DirectX::Model> m_turretModel;
	enum { ROOT, BODY, TURRET, PARTS_CNT };
	// ��Ԋe�p�[�c�ւ̃|�C���^
	std::unique_ptr<ModelPart> m_parts[PARTS_CNT];

	// �G�̏��
	EnemyState m_enemyState;

	// Collision�ō쐬�������\�[�X
	GameResources m_gameResources;

	// �G��HP
	EnemyHitPoint* m_enemyHP;

private:
	// �ԑ̂̊p�x
	DirectX::SimpleMath::Quaternion m_bodyRotate;

	// �C�g�̊p�x
	DirectX::SimpleMath::Quaternion m_turretRotate;

	// ���x[m/s]
	DirectX::SimpleMath::Vector3 m_velocity;

	// ����[kg]
	float m_mass;    

	// �p�j�s���Ŏg�p�������
	float m_wanderOrientation;   

	// �C�e�̔��ˊԊu
	float m_bulletTime;

	// ���G����
	float m_invincibleTime;

	// ���̏o��Ԋu
	float m_smokeTime;

	// ���˂������ǂ���
	bool m_shotFlag;

	// �X�^�[�g�������ǂ���
	bool m_start;
};
