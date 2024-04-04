//*********************************************************************
//			�T�v	�F���[�U�[�C���^�[�t�F�[�X�N���X
// 
//			�����	�F12��20��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/TaskManager.h"
#include "Life.h"
#include "EnemyHP.h"

class UserInterface : public Task
{
public:

	// �R���X�g���N�^
	UserInterface();

	// ������
	void Initialize() override;

public:

	// �c�@���ɃA�N�Z�X����֐�
	Life* GetLife() { return m_life; }

	// �G��HP�ɃA�N�Z�X����֐�
	EnemyHP* GetEnemyHP() { return m_enemyHP; }

public:

	// ��ʃT�C�Y
	static const int SCREEN_W = 1280;
	static const int SCREEN_H = 720;

private:

	// �c�@�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_lifeTexture;

	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	// �c�@
	Life* m_life;

	// �G��HP
	EnemyHP* m_enemyHP;
};