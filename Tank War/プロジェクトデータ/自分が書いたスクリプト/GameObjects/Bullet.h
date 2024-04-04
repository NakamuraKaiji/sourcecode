//*********************************************************************
//			�T�v	�F�C�e�N���X
// 
//			�����	�F10��18��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "CollisionManager.h"
#include "GameParameter.h"
#include "GameResources.h"

class Bullet : public GameObject
{
public:
	// �R���X�g���N�^
	Bullet(const GameResources& gameResources,
		DirectX::SimpleMath::Vector3 position, 
		DirectX::SimpleMath::Quaternion rotate
	);

	// ������
	void Initialize();

	// �X�V 
	bool Update(float elapsedTime) override;

	// �`��
	void Render() override;

	// ���Z�b�g
	void Reset();

	// �Փ˂�����Ă΂��֐�
	void OnHit(GameObject* object) override;

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance(); 

	// DeviceContext�N���X�̃C���X�^���X
	ID3D11DeviceContext* m_context;

	// �C�e���f��
	std::shared_ptr<DirectX::Model> m_bulletModel;

	// Collision�ō쐬�������\�[�X
	GameResources m_gameResources;

	float m_num;

};

