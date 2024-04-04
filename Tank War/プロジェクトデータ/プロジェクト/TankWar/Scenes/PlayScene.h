//*********************************************************************
//			�T�v	�F�v���C�V�[���N���X
// 
//			�����	�F10��3��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/SceneManager.h"
#include "UserResources.h"
#include "MyLib/TaskManager.h"
#include "GameObjects/PlayerCamera.h"
#include "GameObjects/Stage.h"
#include "GameObjects/CollisionManager.h"
#include "GameObjects/UI/UserInterface.h"
#include "GameObjects/ExplosionParticle.h"

class PlayScene :public Scene<UserResources>
{
public:

	// �R���X�g���N�^
	PlayScene();

	// ������
	void Initialize() override;

	// �X�V
	void Update(const DX::StepTimer& timer) override;

	// �`��
	void Render() override;

	// �I������
	void Finalize() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateWindowSizeDependentResources() override;

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	void OnDeviceLost() override;

private:

	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	// �v���C���[�J����
	PlayerCamera m_playerCamera;

	// �X�J�C�h�[�����f��
	std::shared_ptr<DirectX::Model> m_skydomeModel;

	// �n�ʃ��f��
	std::shared_ptr<DirectX::Model> m_groundModel;

	// �R���f��
	std::shared_ptr<DirectX::Model> m_mountainModel[5];

	// �^�X�N�}�l�[�W���[
	TaskManager m_taskManager;

	// �X�e�[�W
	Stage* m_stage;

	// �Փ˔���p�I�u�W�F�N�g
	CollisionManager m_collisionManager;
	
	// UI
	UserInterface* m_userInterface;

	// �����̃p�[�e�B�N��
	std::unique_ptr<ExplosionParticle> m_explosionParticle[2];

	// BGM
	std::unique_ptr<DirectX::SoundEffectInstance> m_bgm;
	// ������
	std::unique_ptr<DirectX::SoundEffectInstance> m_explosionSound;
	// ���ˉ�
	std::unique_ptr<DirectX::SoundEffectInstance> m_shotSound;

private:

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;

	// �c�@��
	int m_life;

	// �G��HP
	float m_ratio;

	// �X�J�C�h�[���̉�]
	float m_skydomeRotate;

	// �����t���O
	bool m_explosionPlayerFlag, m_explosionEnemyFlag;

	// �����\������
	float m_explosionPlayerTime, m_explosionEnemyTime;
};