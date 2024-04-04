#include "pch.h"
#include "SoundCreate.h"

std::unique_ptr<SoundCreate> SoundCreate::m_soundCreate = nullptr;

SoundCreate* const SoundCreate::GetInstance()
{
	// SoundCreate��nullptr�Ȃ珈������
	if (m_soundCreate == nullptr)
	{
		// SoundCreate�N���X�̃C���X�^���X�𐶐�����
		m_soundCreate.reset(new SoundCreate());
	}

	// SoundManager�N���X�̃C���X�^���X��Ԃ�
	return m_soundCreate.get();
}