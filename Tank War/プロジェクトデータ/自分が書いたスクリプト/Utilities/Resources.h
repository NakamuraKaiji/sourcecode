//*********************************************************************
//			�T�v	�F���\�[�X�N���X
// 
//			�����	�F6��14��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED

#include <unordered_map>

class Resources
{
public:
	// �ԑ̃��f�����擾����
	std::shared_ptr<DirectX::Model> GetTankBody() { return m_tankBody; }
	// �C�g���f�����擾����
	std::shared_ptr<DirectX::Model> GetTankTurret() { return m_tankTurret; }
	// �G�̎ԑ̃��f�����擾����
	std::shared_ptr<DirectX::Model> GetEnemyTankBody() { return m_enemyTankBody; }
	// �G�̖C�g���f�����擾����
	std::shared_ptr<DirectX::Model> GetEnemyTankTurret() { return m_enemyTankTurret; }
	// �X�J�C�h�[�����f�����擾����
	std::shared_ptr<DirectX::Model> GetSkydome() { return m_skydome;}
	// �C�e���f�����擾����
	std::shared_ptr<DirectX::Model> GetBullet() { return m_bullet; }
	// ��������ԃ��f�����擾����
	std::shared_ptr<DirectX::Model> GetLoseTank() { return m_loseTank; }
	// �n�ʃ��f�����擾����
	std::shared_ptr<DirectX::Model> GetGround() { return m_ground; }
	// �R���f�����擾����
	std::shared_ptr<DirectX::Model> GetMountain() { return m_mountain; }

	// �p�[�e�B�N���̃e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetParticle() { return m_particleTexture.Get(); }
	// �c�@�̃e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetLife() { return m_life.Get(); }
	// PushEnter�e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetPush() { return m_push.Get(); }
	// �^�C�g���e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetTitle() { return m_title.Get(); }
	// �����e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetVictory() { return m_victory.Get(); }
	// �s�k�e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetDefeat() { return m_defeat.Get(); }

public:
	// Resouces�N���X�̃C���X�^���X���擾����
	static Resources* const GetInstance();

	// ���\�[�X�����[�h����
	void LoadResource();

private:
	Resources() 
		: m_tankBody{}
		, m_tankTurret{}
		, m_enemyTankBody{}
		, m_enemyTankTurret{}
		, m_skydome{}
		, m_bullet{}
		, m_ground{}
		, m_particleTexture{}
		, m_loseTank{}
		, m_push{}
		, m_title{}
		, m_victory{}
		, m_defeat{}
		, m_mountain{}
	{}
	// ����͋��e���Ȃ�
	void operator=(const Resources& object) = delete;
	// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
	Resources(const Resources& object) = delete;

private:
	// Resources�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Resources> m_resources;
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �f�o�C�X
	ID3D11Device* m_device = m_graphics->GetDeviceResources()->GetD3DDevice();

	// �ԑ̃��f��
	std::shared_ptr <DirectX::Model> m_tankBody;
	// �C�g���f��
	std::shared_ptr<DirectX::Model> m_tankTurret;
	// �G�̎ԑ̃��f��
	std::shared_ptr<DirectX::Model> m_enemyTankBody;
	// �G�̖C�g���f��
	std::shared_ptr<DirectX::Model> m_enemyTankTurret;
	// �X�J�C�h�[�����f��
	std::shared_ptr<DirectX::Model> m_skydome;
	// �C�e���f��
	std::shared_ptr<DirectX::Model> m_bullet;
	// �������̐��̐�ԃ��f��
	std::shared_ptr<DirectX::Model> m_loseTank;
	// �n�ʃ��f��
	std::shared_ptr<DirectX::Model> m_ground;
	// �R���f��
	std::shared_ptr<DirectX::Model> m_mountain;

	// �p�[�e�B�N���̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_particleTexture;
	// �c�@�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_life;
	// PushEnter�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_push;
	// �^�C�g���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	// �����e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_victory;
	// �s�k�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_defeat;
};

#endif // RESOURCES_DEFINED
