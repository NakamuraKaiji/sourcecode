#include "pch.h"
#include "SoundManager.h"

using namespace DirectX;

// �R���X�g���N�^
SoundManager::SoundManager()
{
}

// �T�E���h�G�t�F�N�g�C���X�^���X�쐬�֐�
DirectX::SoundEffect* SoundManager::CreateSoundEffectInstance(const wchar_t* name, DirectX::AudioEngine* audioEngine)
{
    auto it = m_soundEffectCache.find(name);

    // �L���b�V���ɑ��݂��Ȃ�����
    if (it == m_soundEffectCache.end())
    {
        // �T�E���h�G�t�F�N�g�̍쐬
        std::unique_ptr<DirectX::SoundEffect> sound = std::make_unique<DirectX::SoundEffect>(audioEngine, name);
        SoundEffectCache::value_type v(name, std::move(sound));
        // �L���b�V���Ɋi�[����
        m_soundEffectCache.insert(std::move(v));
    }

    return m_soundEffectCache.at(name).get();
}
