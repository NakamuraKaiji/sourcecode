//*********************************************************************
//			�T�v	�F�X�e�[�W�N���X
// 
//			�����	�F11��14��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once

#include <vector>
#include "MyLib/TaskManager.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "GameObjects/GameResources.h"

class Stage : public Task
{
private:

	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();

	// �v���C���[�^�X�N�̃|�C���^
	PlayerTank* m_playerTask;

	// �G�^�X�N�̃|�C���^
	EnemyTank* m_enemyTask;

	// GameScene�ō쐬�������\�[�X�Q
	GameResources m_gameResources;

private:

	// �X�e�[�W��̃I�u�W�F�N�g��S�č폜
	void DeleteStageObjects();


public:

	// �R���X�g���N�^
	Stage(const GameResources& gameResources);

	// ������
	void Initialize() override;

	// �X�e�[�W��ݒ�
	void SetStageData();

	// ���Z�b�g
	void Reset();

	// �v���C���[���擾
	PlayerTank* GetPlayer() { return m_playerTask; }

	// �G���擾
	EnemyTank* GetEnemy() { return m_enemyTask; }

	// �S�Ă̓G������ł��邩�`�F�b�N
	bool IsDeadAllEnemy();

};