//*********************************************************************
//			�T�v	�F���̃G�t�F�N�g�N���X
// 
//			�����	�F12��15��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/TaskManager.h"
#include "GameResources.h"

class SmokeEffect : public Task
{
public:

	// �R���X�g���N�^
	SmokeEffect(DirectX::SimpleMath::Vector3 position, 
		DirectX::SimpleMath::Vector3 velocity
	);
		
	// �X�V
	bool Update(float elapsedTime) override;

	// �`��
	void Render() override;

private:

	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// �ړ����x
	DirectX::SimpleMath::Vector3 m_velocity;

	// �\�����ԃJ�E���^
	float m_timer;

	// �����x
	float m_alpha;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_smokeTexture;
};