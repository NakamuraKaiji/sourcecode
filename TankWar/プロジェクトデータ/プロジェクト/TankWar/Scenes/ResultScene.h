//*********************************************************************
//			�T�v	�F���U���g�V�[���N���X
// 
//			�����	�F1��9��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/SceneManager.h"
#include "UserResources.h"
#include "MyLib/TaskManager.h"
#include "GameObjects/PlayerCamera.h"
#include "GameObjects/GameParameter.h"
#include "GameObjects/SmokeParticle.h"

class ResultScene : public Scene<UserResources>
{
public:

	// �R���X�g���N�^
	ResultScene();

	// ������
	void Initialize() override;

	// �X�V
	void Update(const DX::StepTimer& timer) override;

	// �`��
	void Render() override;

	// �I��
	void Finalize() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateWindowSizeDependentResources() override;

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	void OnDeviceLost() override;

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();

	// PushEnter�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushTexture;

	// �����e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_victoryTexture;

	// �s�k�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_defeatTexture;

	// �J����
	PlayerCamera m_playerCamera;

	// �^�X�N�}�l�[�W���[
	TaskManager m_taskManager;

	// �X�J�C�h�[�����f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_skydomeModel;
	// �ԑ̃��f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_tankBodyModel;
	// �C�g���f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_tankTurretModel;
	// �������̐��̐�ԃ��f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_loseTankModel;
	// �n�ʃ��f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_groundModel;

	// ���̃p�[�e�B�N��
	std::unique_ptr<SmokeParticle> m_smokeParticle;

	// BGM
	std::unique_ptr<DirectX::SoundEffectInstance> m_bgm;
	// �����̉�
	std::unique_ptr<DirectX::SoundEffectInstance> m_victorySound;
	// �s�k�̉�
	std::unique_ptr<DirectX::SoundEffectInstance> m_defeatSound;


private:

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;

	// �J�E���g
	float m_count;

	// �C�g�̉�]
	float m_turretRotate;

	// �X�J�C�h�[���̉�]
	float m_skydomeRotate;

	// �ԑ̂̈ʒu
	DirectX::SimpleMath::Vector3 m_tankPosition;

	// ��������
	bool m_victoryFlag;

};