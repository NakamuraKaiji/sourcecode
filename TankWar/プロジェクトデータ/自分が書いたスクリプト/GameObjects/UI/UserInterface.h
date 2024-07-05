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
#include "StartCount.h"

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

	// �X�^�[�g�J�E���g�ɃA�N�Z�X����֐�
	StartCount* GetStartCount(){return m_startCount;}

public:

	// ��ʃT�C�Y
	static const int SCREEN_W = 1280;
	static const int SCREEN_H = 720;

private:

	// �c�@�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_lifeTexture;

	// �����e�N�X�`���i�P�j
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture1;
	// �����e�N�X�`���i�Q�j
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
	// �����e�N�X�`���i�R�j
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture3;

	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	// �c�@
	Life* m_life;

	// �X�^�[�g�J�E���g
	StartCount* m_startCount;
};