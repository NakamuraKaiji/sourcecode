#include "pch.h"
#include "PlayScene.h"
#include "Utilities/Resources.h"
#include "GameObjects/GameResources.h"
#include "MyLib/SoundCreate.h"
#include "ResultScene.h"

using namespace DirectX;

// �R���X�g���N�^
PlayScene::PlayScene()
	: m_view{}
	, m_proj{}
	, m_skydomeModel{}
	, m_skydomeRotate(0.0f)
	, m_moutainRender{}
	, m_treeRender{}
	, m_stage{}
	, m_userInterface{}
	, m_life(0)
	, m_ratio(1.0)
	, m_explosionPlayerFlag(false)
	, m_explosionEnemyFlag(false)
	, m_explosionPlayerTime(0.0f)
	, m_explosionEnemyTime(0.0f)
	, m_countSoundFlag(false)
{
}

// ������
void PlayScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	// �c�@����ݒ�
	m_life = PLAYER_CNT;
	m_userInterface->GetLife()->SetLife(m_life);

	// �G��HP��ݒ�
	m_ratio = ENEMY_HP;

	// BGM�Đ�
	m_bgm->Play(true);

	// �X�^�[�g�܂ł̎��Ԃ�ݒ�
	m_userInterface->GetStartCount()->SetCount(START_COUNT);
}

// �X�V
void PlayScene::Update(const DX::StepTimer& timer)
{
	auto kbTracker = GetUserResources()->GetKeyboardStateTracker();

	// �J�����̐ݒ�
	m_playerCamera.SetType(PlayerCamera::Type::TYPE_A);
	m_playerCamera.SetPlayer(m_stage->GetPlayer()->GetPosition(), m_stage->GetPlayer()->GetBodyRotate() * m_stage->GetPlayer()->GetTurretRotate());

	// �J�����̍X�V
	m_playerCamera.Update((float)timer.GetElapsedSeconds());

	// �R���f����view��proj��ݒ肷��
	m_moutainRender->SetViewProjectionMatrix(m_view, m_proj);
	// �؃��f����view��proj��ݒ肷��
	m_treeRender->SetViewProjectionMatrix(m_view, m_proj);

	// �J�����̏���HP�ɓn��
	m_stage->GetEnemy()->GetEnemyHitPoint()->SetCameraPosition(m_playerCamera.GetEyePosition());

	// �X�J�C�h�[���̉�]
	m_skydomeRotate += (float)timer.GetElapsedSeconds() * 0.05f;

	// �J�E���g���Ԃɓn��
	m_stage->GetPlayer()->SetStartFlag(m_userInterface->GetStartCount()->GetStartFlag());
	m_stage->GetEnemy()->SetStartFlag(m_userInterface->GetStartCount()->GetStartFlag());

	// �J�E���g���ɉ���炷
	if (!m_userInterface->GetStartCount()->GetStartFlag())
	{
		float count = m_userInterface->GetStartCount()->GetCount();
		if (count <= 3.0f && count > 2.9f) m_countSoundFlag = true;
		if (count <= 2.1f && count > 2.0f) m_countSoundFlag = true;
		if (count <= 1.1f && count > 1.0f) m_countSoundFlag = true;
		if (m_countSoundFlag)
		{
			m_countSound->Stop();
			m_countSound->Play();
			m_countSoundFlag = false;
		}
		if (count <= 0.02f)
		{
			m_explosionSound->Stop();
			m_explosionSound->Play();
		}
	}

	// �^�X�N�̍X�V
	m_taskManager.Update((float)timer.GetElapsedSeconds());

	// �v���C���[�̈ړ�����
	m_stage->GetPlayer()->Move(kbTracker, (float)timer.GetElapsedSeconds());

	// �Փ˔���̍X�V
	m_collisionManager.Update();

	// �C�e�𔭎˂����特��炷
	if (m_stage->GetPlayer()->GetShotFlag() || m_stage->GetEnemy()->GetShotFlag())
	{
		m_shotSound->Stop();
		m_shotSound->Play();
	}

	// ����������c�@�����炷
	if (m_stage->GetPlayer()->GetState() == PlayerTank::PlayerState::Hit)
	{
		m_life--;
		m_userInterface->GetLife()->SetLife(m_life);

		// ��������炷
		m_explosionSound->Stop();
		m_explosionSound->Play();

		// �����̃p�[�e�B�N���̈ʒu�̐ݒ�
		m_explosionParticle[0]->SetPosition(m_stage->GetPlayer()->GetPosition());
		m_explosionPlayerFlag = true;

		if (m_life == 0)
		{
			// �}�X�N���I�[�v������
			auto transitionMask = GetUserResources()->GetTransitionMask();
			transitionMask->SetCreateMaskRequest(TransitionMask::CreateMaskRequest::NONE);
			transitionMask->Open();

			// ���U���g�V�[���ɐ؂�ւ�
			ChangeScene<ResultScene>();
			GetUserResources()->SetVictoryFlag(false);
		}
	}

	// �G���C�e�ɓ���������HP�����炷
	if (m_stage->GetEnemy()->GetState() == EnemyTank::EnemyState::Hit)
	{
		m_ratio = m_ratio - ENEMY_REDUCE_HP;
		m_stage->GetEnemy()->GetEnemyHitPoint()->SetHP(m_ratio);

		// ��������炷
		m_explosionSound->Stop();
		m_explosionSound->Play();

		// �����̃p�[�e�B�N���̈ʒu��ݒ�
		m_explosionParticle[1]->SetPosition(m_stage->GetEnemy()->GetPosition());
		m_explosionEnemyFlag = true;

		if (m_ratio <= 0.0f)
		{
			// �}�X�N���I�[�v������
			auto transitionMask = GetUserResources()->GetTransitionMask();
			transitionMask->SetCreateMaskRequest(TransitionMask::CreateMaskRequest::NONE);
			transitionMask->Open();

			// ���U���g�V�[���ɐ؂�ւ�
			ChangeScene<ResultScene>();
			GetUserResources()->SetVictoryFlag(true);
		}
	}

	// 0.4�b�o�߂��������
	if (m_explosionPlayerFlag == true)
	{
		m_explosionPlayerTime += (float)timer.GetElapsedSeconds();
		m_explosionParticle[0]->SetScale(SimpleMath::Vector3::One);
		if (m_explosionPlayerTime >= EXPLOSION_DISPLAY_TIME)
		{
			m_explosionPlayerFlag = false;
			m_explosionPlayerTime = 0.0f;
		}
	}
	if (m_explosionEnemyFlag == true)
	{
		m_explosionEnemyTime += (float)timer.GetElapsedSeconds();
		m_explosionParticle[1]->SetScale(SimpleMath::Vector3::One);
		if (m_explosionEnemyTime >= EXPLOSION_DISPLAY_TIME)
		{
			m_explosionEnemyFlag = false;
			m_explosionEnemyTime = 0.0f;
		}
	}
	// �X�P�[���̐ݒ�
	if (m_explosionPlayerFlag == false) m_explosionParticle[0]->SetScale(SimpleMath::Vector3::Zero);
	if (m_explosionEnemyFlag == false) m_explosionParticle[1]->SetScale(SimpleMath::Vector3::Zero);

	// �����̍X�V
	m_explosionParticle[0]->Update((float)timer.GetElapsedSeconds());
	m_explosionParticle[1]->Update((float)timer.GetElapsedSeconds());

}

// �`��
void PlayScene::Render()
{
	auto context = GetUserResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	m_view = SimpleMath::Matrix::CreateLookAt(
		m_playerCamera.GetEyePosition(),
		m_playerCamera.GetTargetPosition(),
		SimpleMath::Vector3::UnitY
	);

	// �r���[�s���ݒ�
	m_graphics->SetViewMatrix(m_view);

	// �C���v�b�g���C�A�E�g��o�^
	m_graphics->GetDeviceResources()->GetD3DDeviceContext()->IASetInputLayout(m_graphics->GetInputLayout());

	// �n�ʂ�`��
	SimpleMath::Matrix groundWorld;
	groundWorld *= SimpleMath::Matrix::CreateTranslation(SimpleMath::Vector3(0.0f, -0.5f, 0.0f));
	m_groundModel->Draw(context, *states, groundWorld, m_view, m_proj);

	// �X�J�C�h�[���̕`��
	SimpleMath::Matrix skyWorld;
	skyWorld *= SimpleMath::Matrix::CreateRotationY(m_skydomeRotate);
	skyWorld *= SimpleMath::Matrix::CreateTranslation(m_stage->GetPlayer()->GetPosition());
	m_skydomeModel->Draw(context, *states, skyWorld, m_view, m_proj);

	if (m_graphics->GetSpriteBatch()) m_graphics->GetSpriteBatch()->Begin();

	// �^�X�N�̕`��
	m_taskManager.Render();

	if (m_graphics->GetSpriteBatch()) m_graphics->GetSpriteBatch()->End();

	// �����̃p�[�e�B�N���̕`��
	if (m_explosionPlayerFlag == true)
	{
		m_explosionParticle[0]->CreateBillboard(m_stage->GetEnemy()->GetPosition(), m_playerCamera.GetEyePosition(), SimpleMath::Vector3::Up);
		m_explosionParticle[0]->Render();
	}
	if (m_explosionEnemyFlag == true)
	{
		m_explosionParticle[1]->CreateBillboard(m_playerCamera.GetTargetPosition(), m_playerCamera.GetEyePosition(), SimpleMath::Vector3::Up);
		m_explosionParticle[1]->Render();
	}
}

// �I��
void PlayScene::Finalize()
{
}

// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
void PlayScene::CreateDeviceDependentResources()
{
	auto states = GetUserResources()->GetCommonStates();

	// �O���t�B�b�N�X�̐���
	m_graphics->GetInstance()->SetDeviceResources(GetUserResources()->GetDeviceResources());
	m_graphics->GetInstance()->SetCommonStates(states);
	m_graphics->Initialize();

	// ���\�[�X�����[�h
	Resources::GetInstance()->LoadResource();

	// �n�ʃ��f�����쐬
	m_groundModel   = Resources::GetInstance()->GetGround();
	// �X�J�C�h�[�����쐬
	m_skydomeModel  = Resources::GetInstance()->GetSkydome();

	// �R���f�����쐬
	if (m_moutainRender) m_moutainRender->Kill();
	m_moutainRender = m_taskManager.AddTask<MountainRender>(
		m_graphics->GetDeviceResources()->GetD3DDeviceContext(),
		m_graphics->GetCommonStates());

	// �؃��f�����쐬
	if (m_treeRender) m_treeRender->Kill();
	m_treeRender = m_taskManager.AddTask<TreeRender>(
		m_graphics->GetDeviceResources()->GetD3DDeviceContext(),
		m_graphics->GetCommonStates());

	// �X�e�[�W���쐬 
	GameResources gameResources = {&m_collisionManager};
	if (m_stage) m_stage->Kill();
	m_stage = m_taskManager.AddTask<Stage>(gameResources);
	
	// �X�e�[�W�f�[�^�̐ݒ�
	m_stage->SetStageData();

	// UI�̍쐬
	if (m_userInterface) m_userInterface->Kill();
	m_userInterface = m_taskManager.AddTask<UserInterface>();

	// �����̃p�[�e�B�N������
	for (int i = 0; i < 2; i++)
	{
		m_explosionParticle[i] = std::make_unique<ExplosionParticle>();
	}

	// BGM�̍쐬
	m_bgm = SoundCreate::GetInstance()->GetSoundManager()->CreateSoundEffectInstance(
		L"Resources/Sounds/bgm.wav",
		GetUserResources()->GetAudioEngine())->CreateInstance();
	m_bgm->SetVolume(0.3f);

	// �������̍쐬
	m_explosionSound = SoundCreate::GetInstance()->GetSoundManager()->CreateSoundEffectInstance(
		L"Resources/Sounds/explosion.wav",
		GetUserResources()->GetAudioEngine())->CreateInstance();
	m_explosionSound->SetVolume(0.6f);

	// ���ˉ��̍쐬
	m_shotSound = SoundCreate::GetInstance()->GetSoundManager()->CreateSoundEffectInstance(
		L"Resources/Sounds/shot.wav",
		GetUserResources()->GetAudioEngine())->CreateInstance();
	m_shotSound->SetVolume(0.8f);

	// �J�E���g�I���̍쐬
	m_countSound = SoundCreate::GetInstance()->GetSoundManager()->CreateSoundEffectInstance(
		L"Resources/Sounds/Count.wav",
		GetUserResources()->GetAudioEngine())->CreateInstance();
	m_countSound->SetVolume(1.0f);
}

// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
void PlayScene::CreateWindowSizeDependentResources()
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
void PlayScene::OnDeviceLost()
{
	Finalize();
}
