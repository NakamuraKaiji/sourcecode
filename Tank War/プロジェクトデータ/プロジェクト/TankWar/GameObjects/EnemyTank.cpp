#include "pch.h"
#include "EnemyTank.h"
#include "Utilities/Resources.h"
#include "Bullet.h"
#include "SmokeEffect.h"
#include <random>

using namespace DirectX;

// �R���X�g���N�^
EnemyTank::EnemyTank(const GameResources& gameResources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate)
	: GameObject(static_cast<int>(ObjectID::Enemy), position, rotate, ENEMY_RADIUS, ENEMY_FRICTION, PLAYER_WEIGHT)
	, m_gameResources(gameResources)
	, m_bodyModel{}
	, m_turretModel{}
	, m_bodyRotate{}
	, m_turretRotate{}
	, m_bulletTime(0.0f)
	, m_velocity{}
	, m_mass(1.0f)
	, m_wanderOrientation(0.0f)
	, m_target(nullptr)
	, m_enemyState(EnemyState::Normal)
	, m_invincibleTime(0.0f)
	, m_smokeTime(0.0f)
	, m_shotFlag(false)
{
}

// ������
void EnemyTank::Initialize()
{
	// �ԑ̃��f�����擾
	m_bodyModel = Resources::GetInstance()->GetEnemyTankBody();
	// �C�g���f�����擾
	m_turretModel = Resources::GetInstance()->GetEnemyTankTurret();

	// �e�p�[�c�̍쐬
	m_parts[ROOT]   = std::make_unique<ModelPart>();
	m_parts[BODY]   = std::make_unique<ModelPart>(m_bodyModel.get());
	m_parts[TURRET] = std::make_unique<ModelPart>(m_turretModel.get());
	// �e�p�[�c��A������
	// ROOT����ԑ̂̐e�q�֌W
	m_parts[ROOT]->SetChild(m_parts[BODY].get());
	// �ԑ̂���C�g�̐e�q�֌W
	m_parts[BODY]->SetChild(m_parts[TURRET].get());

	// ������
	m_wanderOrientation = 0.0f;

	// �`�揇�̐ݒ�
	SetOt(static_cast<int>(OT_Priority::OT_Object));
}

// �X�V
bool EnemyTank::Update(float elapsedTime)
{
	// ��Ԃɂ���ď����𕪊򂳂���
	switch (m_enemyState)
	{
	case EnemyState::Normal:
		Normal(elapsedTime);
		break;
	case EnemyState::Hit:
		Hit();
		break;
	default:
		break;
	}

	m_invincibleTime += elapsedTime;

	// ���N���X�̍X�V�֐����Ăяo���Ĉړ�����
	GameObject::Update(elapsedTime);

	// �����𐧌�����
	LimitSpeed(ENEMY_MAX_SPEED);

	// �Փ˔���}�l�[�W���[�ɓo�^
	m_gameResources.pCollisionManager->AddObject(this);

	return true;
}

// �`��
void EnemyTank::Render()
{
	auto context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_graphics->GetCommonStates();

	// �r���[�s��Ǝˉe�s����擾
	SimpleMath::Matrix view, proj;
	view = m_graphics->GetViewMatrix();
	proj = m_graphics->GetProjectionMatrix();


	// �C�g�̉�]
	m_parts[TURRET]->SetTransformMatrix(SimpleMath::Matrix::CreateFromQuaternion(m_turretRotate));
	// ��Ԃ̈ړ��Ɖ�]
	SimpleMath::Matrix mat = SimpleMath::Matrix::CreateFromQuaternion(m_bodyRotate) 
						   * SimpleMath::Matrix::CreateTranslation(GetPosition());
	m_parts[BODY]->SetTransformMatrix(mat);

	// ��Ԃ̕`��
	m_parts[ROOT]->UpdateMatrix();
	m_parts[ROOT]->Draw(context, *states, view, proj);
}

// �Փ˂�����Ă΂��֐�
void EnemyTank::OnHit(GameObject* object)
{
	// �Փ˂�������ɂ���ď�����ς���
	switch (static_cast<ObjectID>(object->GetID()))
	{
	case ObjectID::Bullet:			// �C�e
		OnHit_Bullet();
		break;
	case ObjectID::Player:
		OnHit_Player();
	default:
		break;
	}
}

// ���Z�b�g
void EnemyTank::Reset()
{
}

// �ʏ펞�̊֐�
void EnemyTank::Normal(float elapsedTime)
{
	// ���Ǘ͂̒�`
	SimpleMath::Vector3 steeringforce = SimpleMath::Vector3::Zero;

	// �p�j�s��
	steeringforce += Wander(&m_wanderOrientation, 1.0f, 2.0f, 0.2f);

	// �^�[�Q�b�g�܂ł̋���
	SimpleMath::Vector3 toTarget = m_target->GetPosition() - GetPosition();

	// �͈͊O�ɏo����߂�
	if (toTarget.Length() > ENEMY_SEEK_RANGE)
	{
		steeringforce -= Seek(m_target->GetPosition());
	}
	// �ߕt���������痣���
	if (toTarget.Length() <= ENEMY_FLEE_RANGE)
	{
		steeringforce -= Flee(m_target->GetPosition());
	}

	// ���̂ɗ^����ꂽ��[m/s2]
	SimpleMath::Vector3 force = steeringforce / elapsedTime;

	// ���i�^���̎��s
	// �͂̒���
	force = Truncate(force, ENEMY_MOVE_FORCE);

	// �����x�̎Z�o(�����x = �� / ����)
	SimpleMath::Vector3 acceleration = force / m_mass;

	// ���x�̍X�V����ђ���
	m_velocity += acceleration * elapsedTime;
	m_velocity = Truncate(m_velocity, ENEMY_MAX_SPEED);

	AddForce(SimpleMath::Vector3::Transform(-OBJECT_FORWARD, m_bodyRotate), ENEMY_MOVE_FORCE);

	// ���W�̍X�V
	SetPosition(GetPosition() - (m_velocity * elapsedTime));

	// �i�s����������
	TurnHeading(m_velocity);

	// ��]�p���v�Z����
	float targetRotation = std::atan2f(toTarget.x, toTarget.z);
	m_turretRotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, targetRotation);
	m_turretRotate = XMQuaternionMultiply(m_turretRotate, XMQuaternionInverse(m_bodyRotate));

	// �C�e�̔��ˊԊu
	m_bulletTime += elapsedTime;
	m_shotFlag = false;
	// 2�b�Ԋu�Ŕ���
	if (m_bulletTime >= 3.0f)
	{
		// �e�𔭎˂���
		Bullet* bulletTask = this->GetTaskManager()->AddTask<Bullet>(m_gameResources, GetPosition(), m_bodyRotate * m_turretRotate);
		// �e��ύX����
		bulletTask->ChangeParent(this->GetTaskManager()->GetRootTask());
		SetVelocity(SimpleMath::Vector3::Zero);
		m_bulletTime = 0.0f;

		m_shotFlag = true;
	}

	// ���̑��x�x�N�g��
	SimpleMath::Vector3 velocity = WHITE_SMOKE_SPEED;
	m_smokeTime += elapsedTime;
	// ���̃G�t�F�N�g�𔭐�������
	if (m_smokeTime > 1.0f)
	{
		SimpleMath::Vector3 position = SimpleMath::Vector3(GetPosition().x, GetPosition().y - 0.2f, GetPosition().z);
		GetTaskManager()->AddTask<SmokeEffect>(position, velocity);
		m_smokeTime = 0.0f;
	}

}

// �Փ˒��֐�
void EnemyTank::Hit()
{
	// ���C�ɂ���~������
	if (GetVelocity() == SimpleMath::Vector3::Zero)
	{
		// �����ւ̃x�N�g�������߂�
		SimpleMath::Vector3 v = GetPosition() - m_target->GetPosition();
		v.Normalize();
		// �����x�N�g�����쐬
		SimpleMath::Vector3 dir;
		dir = SimpleMath::Vector3::Transform(-v, m_bodyRotate);
		// �m�b�N�o�b�N����
		AddForce(dir, m_target->GetHitForce());

		// �ʏ�
		m_enemyState = EnemyState::Normal;
	}
}

void EnemyTank::OnHit_Bullet()
{
	// ��~������
	SetVelocity(SimpleMath::Vector3::Zero);

	// ���G���Ԃ��߂�����Փˏ�Ԃ�
	if (m_invincibleTime > INVINCIBILITY_TIME)
	{
		m_enemyState = EnemyState::Hit;
		// ���Ԃ����Z�b�g
		m_invincibleTime = 0.0f;
	}
}

void EnemyTank::OnHit_Player()
{
	SetVelocity(SimpleMath::Vector3::Zero);
}


// �w��̕����Ɍ���
void EnemyTank::TurnHeading(const DirectX::SimpleMath::Vector3& direction)
{
	if (direction.Length() > 0.001f)
	{
		SimpleMath::Quaternion rotation = SimpleMath::Quaternion::FromToRotation(SimpleMath::Vector3::Forward, direction);
		m_bodyRotate = rotation;
	}
}

// �T���s��
DirectX::SimpleMath::Vector3 EnemyTank::Seek(const DirectX::SimpleMath::Vector3& targetPosition)
{
	// �ڕW�ʒu�ւ̕����x�N�g���̎Z�o
	SimpleMath::Vector3 toTarget = targetPosition - GetPosition();

	// ���ґ��x�̎Z�o
	toTarget.Normalize();
	SimpleMath::Vector3 desiredVelocity = toTarget * ENEMY_MAX_SPEED;

	// ���Ǘ͂̎Z�o
	SimpleMath::Vector3 steeringForce = desiredVelocity - m_velocity;

	return steeringForce;
}

// �����s��
DirectX::SimpleMath::Vector3 EnemyTank::Flee(const DirectX::SimpleMath::Vector3& targetPosition)
{
	// �ڕW�ʒu�ւ̕����x�N�g���̎Z�o
	SimpleMath::Vector3 toTarget = targetPosition - GetPosition();

	// ���ґ��x�̎Z�o
	toTarget.Normalize();
	SimpleMath::Vector3 desiredVelocity = -toTarget * ENEMY_MAX_SPEED;

	// ���Ǘ͂̎Z�o
	SimpleMath::Vector3 steeringForce = desiredVelocity - m_velocity;

	// ���Ǘ͂̕ԋp
	return steeringForce;
}

// �p�j�s��
DirectX::SimpleMath::Vector3 EnemyTank::Wander(float* wanderOriantation, float wanderRadius, float wanderDistance, float wanderRotate)
{
	static std::random_device                    seedGenerator;
	static std::mt19937                          randomGenerator{ seedGenerator() };
	static std::uniform_real_distribution<float> distribution{ -1.0, 1.0 };

	// �^�[�Q�b�g�ւ̊p�x��ω�
	*wanderOriantation += (XM_PI * wanderRotate) * distribution(randomGenerator) * wanderDistance;

	// �p�j�s���p�~�̉~����̃^�[�Q�b�g�̈ʒu�̉��o
	SimpleMath::Vector3 targetOriantation = SimpleMath::Vector3{ std::cos(*wanderOriantation), 0.0f, std::sin(*wanderOriantation) };
	SimpleMath::Vector3 toTarget = targetOriantation * wanderRadius;

	// �p�j�s���p�̒��S�̎Z�o
	SimpleMath::Vector3 wanderCenter = GetPosition() + SimpleMath::Vector3::Transform(SimpleMath::Vector3::Forward, m_bodyRotate);

	// �^�[�Q�b�g�̈ʒu�̎Z�o(���[���h���W)
	SimpleMath::Vector3 targetPosition = wanderCenter + toTarget;

	// �T���s���ɂ�鑀�Ǘ͂̎Z�o
	SimpleMath::Vector3 steeringForce = Seek(targetPosition);

	return steeringForce;
}

// �x�N�g���̒����̐؂�̂�
inline DirectX::SimpleMath::Vector3 EnemyTank::Truncate(const DirectX::SimpleMath::Vector3& v, float maxLength)
{
	const float maxLengthSquared = maxLength * maxLength;
	const float vecLengthSquared = v.LengthSquared();
	if (vecLengthSquared <= maxLengthSquared)
		return v;
	else
		return v * (maxLength / v.Length());
}


