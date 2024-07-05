#include "pch.h"
#include "Stage.h"

using namespace DirectX;

// �R���X�g���N�^
Stage::Stage(const GameResources& gameResources)
	: m_playerTask{}
	, m_enemyTask{}
	, m_gameResources(gameResources)
{
}

// ������
void Stage::Initialize()
{
}

// �X�e�[�W��̃I�u�W�F�N�g��S�č폜
void Stage::DeleteStageObjects()
{
	// �v���C���[���폜����
	if (m_playerTask)
	{
		m_playerTask->Kill();
		m_playerTask = nullptr;
	}

}

// �X�e�[�W��ݒ�
void Stage::SetStageData()
{
	// �v���C���[�𐶐�
	m_playerTask = GetTaskManager()->AddTask<PlayerTank>(m_gameResources, SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity);

	// �G�𐶐�
	m_enemyTask = GetTaskManager()->AddTask<EnemyTank>(m_gameResources, SimpleMath::Vector3(0.0f, 0.0f, 5.0f), SimpleMath::Quaternion::Identity);

	// �v���C���[�ɓG��n��
	m_playerTask->SetTarget(m_enemyTask);

	// �G�Ƀv���C���[��n��
	m_enemyTask->SetTarget(m_playerTask);
}

// �X�e�[�W�f�[�^�̃��Z�b�g
void Stage::Reset()
{
}

bool Stage::IsDeadAllEnemy()
{
	return false;
}
