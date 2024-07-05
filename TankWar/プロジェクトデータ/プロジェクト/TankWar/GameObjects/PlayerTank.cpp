#include "pch.h"
#include "PlayerTank.h"
#include "Utilities/Resources.h"
#include "Bullet.h"
#include "SmokeEffect.h"

using namespace DirectX;


// �R���X�g���N�^
PlayerTank::PlayerTank(const GameResources& gameResources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate)
	: GameObject(static_cast<int>(ObjectID::Player), position, rotate, PLAYER_RADIUS, PLAYER_FRICTION, PLAYER_WEIGHT)
	, m_gameResources(gameResources)
	, m_bodyModel{}
	, m_turretModel{}
	, m_bodyRotate{}
	, m_turretRotate{}
	, m_playerState(PlayerState::Normal)
	, m_smokeTime(0.0f)
	, m_bulletTime(0.0f)
	, m_shotFlag(false)
	, m_target(nullptr)
	, m_start(false)

{
}

// ������
void PlayerTank::Initialize()
{
	// �ԑ̃��f�����擾
	m_bodyModel = Resources::GetInstance()->GetTankBody();
	// �C�g���f�����擾
	m_turretModel = Resources::GetInstance()->GetTankTurret();

	// ��Ԃ̊e�p�[�c�̍쐬
	m_parts[ROOT]   = std::make_unique<ModelPart>();
	m_parts[BODY]   = std::make_unique<ModelPart>(m_bodyModel.get());
	m_parts[TURRET] = std::make_unique<ModelPart>(m_turretModel.get());
	// �e�p�[�c��A������
	// ROOT����ԑ̂̐e�q�֌W
	m_parts[ROOT]->SetChild(m_parts[BODY].get());
	// �ԑ̂���C�g�̐e�q�֌W
	m_parts[BODY]->SetChild(m_parts[TURRET].get());

	// �`�揇�̐ݒ�
	SetOt(static_cast<int>(OT_Priority::OT_Object));
}

// �X�V
bool PlayerTank::Update(float elapsedTime)
{
	// �X�^�[�g������X�V
	if (m_start)
	{
		// ��Ԃɂ���ď��������߂�
		switch (m_playerState)
		{
		case PlayerState::Hit:
			Hit();
			break;
		default:
			break;
		}

		// �s���͈�
		// �͈͊O�ɏo����~�߂�
		SimpleMath::Vector3 distance = GetPosition() - SimpleMath::Vector3::Zero;
		if (distance.Length() > PLAYER_ACTION_RANGE)
		{
			SetVelocity(SimpleMath::Vector3::Zero);
			SetPosition(distance - SimpleMath::Vector3(0.0f, 0.0f, 0.001f));
		}

		// ���N���X�̍X�V�֐����Ăяo���Ĉړ�����
		GameObject::Update(elapsedTime);

		// �����𐧌�����
		LimitSpeed(PLAYER_MAX_SPEED);

		// �Փ˔���}�l�[�W���[�ɓo�^
		m_gameResources.pCollisionManager->AddObject(this);
	}

	return true;
}

// �`��
void PlayerTank::Render()
{
	auto context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_graphics->GetCommonStates();

	// �r���[�s��Ǝˉe�s����擾
	SimpleMath::Matrix view, proj;
	view = m_graphics->GetViewMatrix();
	proj = m_graphics->GetProjectionMatrix();

	//view = SimpleMath::Matrix::CreateLookAt(SimpleMath::Vector3(5, 5, 0), SimpleMath::Vector3(0, 0, 0), SimpleMath::Vector3::UnitY);
	//proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(XMConvertToRadians(45.0f), 1280 / 720.0f, 0.1, 100.0f);

	// ��Ԃ̉�]
	m_parts[BODY]->SetTransformMatrix(SimpleMath::Matrix::CreateFromQuaternion(m_bodyRotate));
	// �C�g�̉�]
	m_parts[TURRET]->SetTransformMatrix(SimpleMath::Matrix::CreateFromQuaternion(m_turretRotate));
	// ��Ԃ̈ړ�
	SimpleMath::Matrix mat = SimpleMath::Matrix::CreateFromQuaternion(m_bodyRotate) * 
		SimpleMath::Matrix::CreateTranslation(GetPosition());
	m_parts[BODY]->SetTransformMatrix(mat);

	// ��Ԃ̕`��
	m_parts[ROOT]->UpdateMatrix();
	m_parts[ROOT]->Draw(context, *states, view, proj);
}

// ���Z�b�g
void PlayerTank::Reset()
{
}

// �ړ��֐�
void PlayerTank::Move(DirectX::Keyboard::KeyboardStateTracker* tracker, float elapsedTime)
{
	if (m_start)
	{
		// �ʏ펞�݈̂ړ�����
		if (m_playerState != PlayerState::Normal) return;

		// �L�[���͂��擾
		auto kb = Keyboard::Get().GetState();

		// �����Ă�������ɗ͂������Ĉړ�����
		float force = PLAYER_MOVE_FORCE;

		// ���̑��x�x�N�g��
		SimpleMath::Vector3 velocity = WHITE_SMOKE_SPEED;

		// W�L�[�őO�i
		if (kb.W)
		{
			AddForce(SimpleMath::Vector3::Transform(OBJECT_FORWARD, m_bodyRotate), -force);
			m_smokeTime += elapsedTime;
			// ���̃G�t�F�N�g�𔭐�������
			if (m_smokeTime > 0.5f)
			{
				SimpleMath::Vector3 position = SimpleMath::Vector3(GetPosition().x, GetPosition().y - 0.2f, GetPosition().z);
				GetTaskManager()->AddTask<SmokeEffect>(position, velocity);
				m_smokeTime = 0.0f;
			}
		}
		// S�L�[�Ō�i
		if (kb.S)
		{
			AddForce(SimpleMath::Vector3::Transform(OBJECT_FORWARD, m_bodyRotate), force);
		}
		// D�L�[�ŉE��]
		if (kb.D)
		{
			// ��]�p���v�Z
			m_bodyRotate *= SimpleMath::Quaternion::CreateFromAxisAngle(
				SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-PLAYER_BODY_ROTATE)
			);
		}
		// A�L�[�ō���]
		if (kb.A)
		{
			// ��]�p���v�Z
			m_bodyRotate *= SimpleMath::Quaternion::CreateFromAxisAngle(
				SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(PLAYER_BODY_ROTATE)
			);
		}
		// ���ŖC�g���E��]
		if (kb.Right)
		{
			// ��]�p���v�Z
			m_turretRotate *= SimpleMath::Quaternion::CreateFromAxisAngle(
				SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-PLAYER_TURRET_ROTATE)
			);
		}
		// ���ŖC�g���E��]
		if (kb.Left)
		{
			// ��]�p���v�Z
			m_turretRotate *= SimpleMath::Quaternion::CreateFromAxisAngle(
				SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(PLAYER_TURRET_ROTATE)
			);
		}

		// �X�y�[�X�Ŕ���
		m_bulletTime += elapsedTime;
		m_shotFlag = false;
		if (m_bulletTime > 1.0f)
			if (tracker->pressed.Space)
			{
				// �e�𔭎˂���
				Bullet* bulletTask = this->GetTaskManager()->AddTask<Bullet>(m_gameResources, GetPosition(), m_bodyRotate * m_turretRotate);
				// �e��ύX����
				bulletTask->ChangeParent(this->GetTaskManager()->GetRootTask());
				SetVelocity(SimpleMath::Vector3::Zero);
				m_bulletTime = 0.0f;
				// ���˂���
				m_shotFlag = true;
			}
	}
}

// �Փ˒��֐�
void PlayerTank::Hit()
{
	// ���C�ɂ���~������
	if (GetVelocity() == SimpleMath::Vector3::Zero)
	{
		// �����ւ̃x�N�g�������߂�
		SimpleMath::Vector3 v = m_target->GetPosition() - GetPosition();
		v.Normalize();
		// �����x�N�g�����쐬
		SimpleMath::Vector3 dir;
		dir = SimpleMath::Vector3::Transform(-v, m_bodyRotate);
		// �m�b�N�o�b�N����
		AddForce(dir, m_target->GetHitForce());

		// �ʏ�
		m_playerState = PlayerState::Normal;
	}
}

// �Փˎ��ɌĂяo�����֐�
void PlayerTank::OnHit(GameObject* object)
{
	// �Փ˂�������ɂ���ď�����ς���
	switch (static_cast<ObjectID>(object->GetID()))
	{
	case ObjectID::Bullet:			// �C�e
		OnHit_Bullet();
		break;
	case ObjectID::Enemy:			// �G
		OnHit_Player();
	default:
		break;
	}
}

// �C�e�Ƃ̏Փˊ֐�
void PlayerTank::OnHit_Bullet()
{
	SetVelocity(SimpleMath::Vector3::Zero);

	m_playerState = PlayerState::Hit;
}

// �G�Ƃ̓����蔻��
void PlayerTank::OnHit_Player()
{
	SetVelocity(SimpleMath::Vector3::Zero);
}

// �X�^�[�g�������ǂ�����ݒ肷��֐�
void PlayerTank::SetStartFlag(bool start)
{
	m_start = start;
}
