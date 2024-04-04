#include "pch.h"
#include "UserInterface.h"
#include "Utilities/Resources.h"

// �R���X�g���N�^
UserInterface::UserInterface()
	: m_lifeTexture{}
	, m_life(nullptr)
	, m_enemyHP(nullptr)
{
	m_lifeTexture = Resources::GetInstance()->GetLife();
}

// ������
void UserInterface::Initialize()
{
	// �c�@���^�X�N�o�^
	m_life = GetTaskManager()->AddTask<Life>(
		m_lifeTexture.Get(), 10, 10
		);

	// �GHP�^�X�N�o�^
	m_enemyHP = GetTaskManager()->AddTask<EnemyHP>();
}