//*********************************************************************
//			�T�v	�F�T�E���h�}�l�[�W���[�𐶐�����N���X
// 
//			�����	�F1��29��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/SoundManager.h"

class SoundCreate
{
private:

	// �T�E���h�}�l�[�W���[
	std::unique_ptr<SoundManager> m_soundManager;

	// �T�E���h����
	static std::unique_ptr<SoundCreate> m_soundCreate;

	SoundCreate()
	{
		// �T�E���h�}�l�[�W���[�̐���
		m_soundManager = std::make_unique<SoundManager>();
	}

public:

	// SoundCreate�N���X�̃C���X�^���X���擾����
	static SoundCreate* const GetInstance();

	// �T�E���h�}�l�[�W���[���擾����
	SoundManager* GetSoundManager() { return m_soundManager.get(); }
};