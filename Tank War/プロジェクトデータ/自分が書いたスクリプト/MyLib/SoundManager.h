//*********************************************************************
//			�T�v	�F�T�E���h���Ǘ�����N���X
// 
//			�����	�F1��29��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include <unordered_map>
#include <string>

class SoundManager
{
private:

	// �T�E���h�L���b�V��
	using SoundEffectCache = std::unordered_map<std::wstring, std::unique_ptr<DirectX::SoundEffect>>;
	SoundEffectCache m_soundEffectCache;

public:

	// �R���X�g���N�^
	SoundManager();

	// �T�E���h�G�t�F�N�g�C���X�^���X�쐬�֐�
	DirectX::SoundEffect* CreateSoundEffectInstance(const wchar_t* name, DirectX::AudioEngine* audioEngine);
};