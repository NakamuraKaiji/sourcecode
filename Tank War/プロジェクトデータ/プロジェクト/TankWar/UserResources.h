#pragma once
#include "StepTimer.h"
#include "DeviceResources.h"
#include "MyLib/TransitionMask.h"

class UserResources
{
private:

	// �X�e�b�v�^�C�}�[
	DX::StepTimer* m_timer;

	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_deviceResources;

	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardTracker;

	// �}�E�X�X�e�[�g�g���b�J�[
	DirectX::Mouse::ButtonStateTracker* m_mouseTracker;

	// ���ʃX�e�[�g
	DirectX::CommonStates* m_states;

	// ��ʑJ�ڃ}�X�N�ւ̃|�C���^
	TransitionMask* m_transitionMask;

	// ��������
	bool m_victoryFlag;

	// �I�[�f�B�I�G���W��
	DirectX::AudioEngine* m_audioEngine;

public:

	// �R���X�g���N�^
	UserResources()
		: m_timer(nullptr)
		, m_deviceResources(nullptr)
		, m_keyboardTracker(nullptr)
		, m_mouseTracker(nullptr)
		, m_states(nullptr)
		, m_transitionMask(nullptr)
		, m_audioEngine(nullptr)
		, m_victoryFlag(false)
	{
	}

	// ------------------------------------------ //
	// �X�e�b�v�^�C�}�[	
	// ------------------------------------------ //

	// �X�e�b�v�^�C�}�[��ݒ肷��֐�
	void SetStepTimerStates(DX::StepTimer* timer) { m_timer = timer; }

	// �X�e�b�v�^�C�}�[���擾����֐�
	DX::StepTimer* GetStepTimer() { return m_timer; }

	// ------------------------------------------ //
	// �f�o�C�X���\�[�X	
	// ------------------------------------------ //

	// �f�o�C�X���\�[�X��ݒ肷��֐�
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_deviceResources = deviceResources; }

	// �f�o�C�X���\�[�X���擾����֐�
	DX::DeviceResources* GetDeviceResources() { return m_deviceResources; }

	// ------------------------------------------ //
	// �L�[�{�[�h�X�e�[�g�g���b�J�[	
	// ------------------------------------------ //

	// �L�[�{�[�h�X�e�[�g�g���b�J�[��ݒ肷��֐�
	void SetKeyboardStateTracker(DirectX::Keyboard::KeyboardStateTracker* tracker) { m_keyboardTracker = tracker; }

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����֐�
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker() { return m_keyboardTracker; }

	// ------------------------------------------ //
	// �}�E�X�X�e�[�g�g���b�J�[	
	// ------------------------------------------ //

	// �}�E�X�X�e�[�g�g���b�J�[��ݒ肷��֐�
	void SetMouseStateTracker(DirectX::Mouse::ButtonStateTracker* tracker) { m_mouseTracker = tracker; }

	// �}�E�X�X�e�[�g�g���b�J�[���擾����֐�
	DirectX::Mouse::ButtonStateTracker* GetMouseStateTracker() { return m_mouseTracker; }

	// ------------------------------------------ //
	// ���ʃX�e�[�g	
	// ------------------------------------------ //

	// ���ʃX�e�[�g��ݒ肷��֐�
	void SetCommonStates(DirectX::CommonStates* states) { m_states = states; }

	// ���ʃX�e�[�g���擾����֐�
	DirectX::CommonStates* GetCommonStates() { return m_states; }

	// ------------------------------------------ //
	// ��ʑJ�ڃ}�X�N	
	// ------------------------------------------ //

	// ��ʑJ�ڃ}�X�N��ݒ肷��֐�
	void SetTransitionMask(TransitionMask* transitionMask) { m_transitionMask = transitionMask; }

	// ��ʑJ�ڃ}�X�N���擾����֐�
	TransitionMask* GetTransitionMask() { return m_transitionMask; }

	// ------------------------------------------ //
	// ��������	
	// ------------------------------------------ //

	// ���������ݒ肷��֐�
	void SetVictoryFlag(bool victoryFlag) { m_victoryFlag = victoryFlag; }

	// ����������擾����֐�
	bool GetVictoryFlag() { return m_victoryFlag; }


	// ------------------------------------------ //
	// �I�[�f�B�I�G���W��
	// ------------------------------------------ //

	// �I�[�f�B�I�G���W����ݒ肷��֐�
	void SetAudioEngine(DirectX::AudioEngine* audioEngine) { m_audioEngine = audioEngine; }

	// �I�[�f�B�I�G���W�����擾����֐�
	DirectX::AudioEngine* GetAudioEngine() { return m_audioEngine; }

};

