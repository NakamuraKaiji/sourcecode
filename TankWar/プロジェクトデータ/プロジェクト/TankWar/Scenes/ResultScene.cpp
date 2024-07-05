#include "pch.h"
#include "ResultScene.h"
#include "Utilities/Resources.h"
#include "TitleScene.h"
#include "GameObjects/SmokeEffect.h"
#include "MyLib/SoundCreate.h"

using namespace DirectX;

// �R���X�g���N�^
ResultScene::ResultScene()
	: m_view{}
	, m_proj{}
	, m_count(0.0f)
	, m_skydomeModel{}
	, m_skydomeRotate(0.0f)
	, m_tankBodyModel{}
	, m_tankTurretModel{}
	, m_loseTankModel{}
	, m_groundModel{}
	, m_tankPosition{}
	, m_victoryFlag(false)
	, m_turretRotate(0.0f)
{
}

// ������
void ResultScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	// �J�����̈ʒu�ݒ�
	m_playerCamera.SetPlayer(SimpleMath::Vector3::Zero, SimpleMath::Quaternion::Identity);
	// �J�����̐ݒ�
	m_playerCamera.SetType(PlayerCamera::Type::TYPE_C);

	// ��Ԃ̏����ʒu
	m_tankPosition = SimpleMath::Vector3(0.5f, 0.0f, -0.5f);

	//	���s�ɍ��킹�������Đ�
	if (m_victoryFlag == true) m_victorySound->Play(false);
	else m_defeatSound->Play(false);

	// BGM�Đ�
	m_bgm->Play(true);
}

// �X�V
void ResultScene::Update(const DX::StepTimer& timer)
{
	// �L�[�{�[�h�擾
	auto keyState = GetUserResources()->GetKeyboardStateTracker();

	// �J�����X�V
	m_playerCamera.Update((float)timer.GetElapsedSeconds());

	// �^�X�N�̍X�V
	m_taskManager.Update((float)timer.GetElapsedSeconds());

	// ���̃p�[�e�B�N���̍X�V
	m_smokeParticle->SetPosition(m_tankPosition);
	m_smokeParticle->Update((float)timer.GetElapsedSeconds());
	// ���̃r���{�[�h���X�V
	m_smokeParticle->CreateBillboard(m_playerCamera.GetTargetPosition(), m_playerCamera.GetEyePosition(), SimpleMath::Vector3::Up);

	// �V�[���؂�ւ�
	if (keyState->pressed.Enter)
	{
		// �}�X�N���I�[�v������
		auto transitionMask = GetUserResources()->GetTransitionMask();
		transitionMask->SetCreateMaskRequest(TransitionMask::CreateMaskRequest::NONE);
		transitionMask->Open();

		ChangeScene<TitleScene>();
	}

	// PushEnter�̓_��
	m_count += (float)timer.GetElapsedSeconds();
	if (m_count >= 2.0f)	m_count = 0.0f;

	// �C�g�̉�]
	m_turretRotate += (float)timer.GetElapsedSeconds();

	// �X�J�C�h�[���̉�]
	m_skydomeRotate += (float)timer.GetElapsedSeconds() * 0.05f;
}

// �`��
void ResultScene::Render()
{
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	//auto debugFont = GetUserResources()->GetDebugFont();
	//debugFont->AddString(L"ResultScene", SimpleMath::Vector2(0.0f, debugFont->GetFontHeight() / 2.0f));

	// �r���[�s���ݒ�
	m_view = SimpleMath::Matrix::CreateLookAt(
		m_playerCamera.GetEyePosition(),
		m_playerCamera.GetTargetPosition(),
		SimpleMath::Vector3::UnitY);

	// �r���[�s���ݒ�
	m_graphics->SetViewMatrix(m_view);

	// �C���v�b�g���C�A�E�g��o�^
	m_graphics->GetDeviceResources()->GetD3DDeviceContext()->IASetInputLayout(m_graphics->GetInputLayout());

	// �^�X�N�̕`��
	m_taskManager.Render();

	// �n�ʂ�`��
	SimpleMath::Matrix groundWorld;
	groundWorld *= SimpleMath::Matrix::CreateTranslation(SimpleMath::Vector3(0.0f, -0.5f, 0.0f));
	m_groundModel->Draw(context, *states, groundWorld, m_view, m_proj);

	// �X�J�C�h�[���̕`��
	SimpleMath::Matrix skyWorld;
	skyWorld *= SimpleMath::Matrix::CreateRotationY(m_skydomeRotate);
	m_skydomeModel->Draw(context, *states, skyWorld, m_view, m_proj);

	m_graphics->GetSpriteBatch()->Begin();

	// ��Ԃ̕`��
	SimpleMath::Matrix bodyWorld, turretWorld;
	bodyWorld	*= SimpleMath::Matrix::CreateRotationY(-90.0f);
	bodyWorld	*= SimpleMath::Matrix::CreateTranslation(m_tankPosition);
	turretWorld *= SimpleMath::Matrix::CreateRotationY(m_turretRotate);
	turretWorld *= bodyWorld;
	if (m_victoryFlag == true)
	{
		m_tankBodyModel->Draw(context, *states, bodyWorld, m_view, m_proj);
		m_tankTurretModel->Draw(context, *states, turretWorld, m_view, m_proj);

		// �����e�N�X�`����`�悷��
		m_graphics->GetSpriteBatch()->Draw(m_victoryTexture.Get(), SimpleMath::Vector2(-50.0f, 75.0f));
	}

	// ��������Ԃ̕`��
	if (m_victoryFlag == false)
	{
		m_loseTankModel->Draw(context, *states, bodyWorld, m_view, m_proj);

		// �s�k�e�N�X�`����`�悷��
		m_graphics->GetSpriteBatch()->Draw(m_defeatTexture.Get(), SimpleMath::Vector2(-50.0f, 75.0f));

		// ���̃p�[�e�B�N���̕`��
		m_smokeParticle->Render();
	}



	// Push�e�N�X�`���̕`��
	if (m_count <= 1.0f)
	{
		m_graphics->GetSpriteBatch()->Draw(m_pushTexture.Get(), SimpleMath::Vector2(0.0, 550.0f));
	}

	m_graphics->GetSpriteBatch()->End();

}

// �I��
void ResultScene::Finalize()
{
	m_pushTexture.Reset();
}

// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
void ResultScene::CreateDeviceDependentResources()
{
	auto states  = GetUserResources()->GetCommonStates();

	// ����������擾����
	m_victoryFlag = GetUserResources()->GetVictoryFlag();

	// �O���t�B�b�N�X�̐���
	m_graphics->SetDeviceResources(GetUserResources()->GetDeviceResources());
	m_graphics->SetCommonStates(states);
	m_graphics->Initialize();

	// ���\�[�X�����[�h
	Resources::GetInstance()->LoadResource();

	// PushEnter�e�N�X�`�����擾����
	m_pushTexture    = Resources::GetInstance()->GetPush();
	// �����e�N�X�`�����擾����
	m_victoryTexture = Resources::GetInstance()->GetVictory();
	// �s�k�e�N�X�`�����擾����
	m_defeatTexture  = Resources::GetInstance()->GetDefeat();
	
	// �X�J�C�h�[�����f���̍쐬
	m_skydomeModel = Resources::GetInstance()->GetSkydome();
	m_skydomeModel->UpdateEffects([](IEffect* effect)
		{
			auto lights = dynamic_cast<IEffectLights*>(effect);
			if (lights)
			{
				lights->SetAmbientLightColor(Colors::Black);
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	// �ԑ̃��f���̍쐬
	m_tankBodyModel   = Resources::GetInstance()->GetTankBody();
	// �C�g���f���̍쐬
	m_tankTurretModel = Resources::GetInstance()->GetTankTurret();
	// �������̐����f���̍쐬
	m_loseTankModel   = Resources::GetInstance()->GetLoseTank();
	// �n�ʃ��f���̍쐬
	m_groundModel     = Resources::GetInstance()->GetGround();

	// �p�[�e�B�N���̐���
	m_smokeParticle = std::make_unique<SmokeParticle>();

	// BGM�̍쐬
	m_bgm = SoundCreate::GetInstance()->GetSoundManager()->CreateSoundEffectInstance(
		L"Resources/Sounds/bgm.wav",
		GetUserResources()->GetAudioEngine())->CreateInstance();
	m_bgm->SetVolume(0.2f);

	// �����̉��쐬
	m_victorySound = SoundCreate::GetInstance()->GetSoundManager()->CreateSoundEffectInstance(
		L"Resources/Sounds/victory.wav",
		GetUserResources()->GetAudioEngine())->CreateInstance();
	m_victorySound->SetVolume(0.5f);

	// �s�k�̉��쐬
	m_defeatSound = SoundCreate::GetInstance()->GetSoundManager()->CreateSoundEffectInstance(
		L"Resources/Sounds/defeat.wav",
		GetUserResources()->GetAudioEngine())->CreateInstance();
	m_defeatSound->SetVolume(0.5f);

}

// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
void ResultScene::CreateWindowSizeDependentResources()
{
	// �ˉe�s����쐬
	RECT rect = GetUserResources()->GetDeviceResources()->GetOutputSize();
	m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 200.0f
	);

	// �ˉe�s���ݒ�
	m_graphics->SetProjectionMatrix(m_proj);
}

// �f�o�C�X���X�g�������ɌĂяo�����֐�
void ResultScene::OnDeviceLost()
{
	Finalize();
}
