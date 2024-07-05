//*********************************************************************
//			�T�v	�F�^�C�g���V�[���N���X
// 
//			�����	�F11��29��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/SceneManager.h"
#include "UserResources.h"
#include "GameObjects/PlayerCamera.h"
#include "GameObjects/GameParameter.h"

class TitleScene : public Scene<UserResources>
{
public:

	// �R�X�g���N�^
	TitleScene();

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

	// �^�C�g���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleTexture;

	// PushEnter�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushTexture;

	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();

	// �X�J�C�h�[�����f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_skydomeModel;

	// �ԑ̃��f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_tankBodyModel;

	// �C�g���f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_tankTurretModel;

	// �C�e���f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_bulletModel;

	// �n�ʃ��f���ւ̃|�C���^
	std::shared_ptr<DirectX::Model> m_groundModel;

	// �J����
	PlayerCamera m_playerCamera;

private:

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;

	// �p�x
	DirectX::SimpleMath::Quaternion m_rotate;

	// �J�E���g
	float m_count;

	// �C�e�̈ʒu
	DirectX::SimpleMath::Vector3 m_bulletPos;

	// �C�e�̊p�x
	float m_angle;

	// �C�e���
	float m_bulletRecovery;

	// �X�J�C�h�[���̉�]
	float m_skydomeRotate;
};