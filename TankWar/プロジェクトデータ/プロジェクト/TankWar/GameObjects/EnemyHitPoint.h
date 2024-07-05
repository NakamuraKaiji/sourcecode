//*********************************************************************
//			�T�v	�F�G�̗̑̓N���X
// 
//			�����	�F5��14��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/TaskManager.h"

class EnemyHitPoint :public Task
{
private:

	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hpTexture_a;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hpTexture_b;

	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// �J�����̈ʒu��ݒ�
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	// �r���{�[�h
	DirectX::SimpleMath::Matrix m_billboard;

	// �̗�
	float m_hp;

public:
	// �R���X�g���N�^
	EnemyHitPoint();

	// ������
	void Initialize();

	// �`��
	void Render() override;

public:
	// �̗͂�ݒ�
	void SetHP(float hp);
	// �̗͂��擾
	float GetHP() { return m_hp; }

	// �G�̈ʒu��ݒ�
	void SetEnemyPosition(DirectX::SimpleMath::Vector3 position);

	// �J�����̈ʒu��ݒ�
	void SetCameraPosition(DirectX::SimpleMath::Vector3 cameraposition);
};
