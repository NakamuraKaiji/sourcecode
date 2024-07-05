#include "pch.h"
#include "Bullet.h"
#include "Utilities/Resources.h"
#include "GameParameter.h"

using namespace DirectX;

// �R���X�g���N�^
Bullet::Bullet(const GameResources& gameResources,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotate
)
	: GameObject(static_cast<int>(ObjectID::Bullet), position, rotate, BULLET_RADIUS, BULLET_FRICTION, BULLET_WEIGHT)
	, m_gameResources(gameResources)
	, m_context{}
	, m_num(0.0f)
{
}

// ������
void Bullet::Initialize()
{
	// �f�o�C�X�R���e�L�X�g���擾
	m_context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	// �C�e���f�����擾
	m_bulletModel = Resources::GetInstance()->GetBullet();

	// �`�揇�̐ݒ�
	SetOt(static_cast<int>(OT_Priority::OT_Object));
}

// �X�V
bool Bullet::Update(float elapsedTime)
{
	// ���N���X�̍X�V�֐����Ăяo���Ĉړ�����
	GameObject::Update(elapsedTime);

	// ��]
	SimpleMath::Matrix rotation = SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	// ���x���v�Z
	SimpleMath::Vector3 velocity = SimpleMath::Vector3::TransformNormal(BULLET_SPEED, rotation);
	// �ړ�
	SetPosition(GetPosition() + velocity);

	// �Փ˔���p�I�u�W�F�N�g
	m_num += elapsedTime;
	if (m_num > 0.3f)
	{
		m_gameResources.pCollisionManager->AddObject(this);
	}

	return true;
}

// �`��
void Bullet::Render()
{
	// ���[���h�s���������
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
 	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	// �v���~�e�B�u�`����J�n
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �C�e��`��
	m_graphics->DrawModel(m_bulletModel.get(), world);
	// �v���~�e�B�u�`����I��
	m_graphics->DrawPrimitiveEnd();
}

// ���Z�b�g
void Bullet::Reset()
{
}

// �Փ˂�����Ă΂��֐�
void Bullet::OnHit(GameObject* object)
{
	UNREFERENCED_PARAMETER(object);

	this->Kill();
}

