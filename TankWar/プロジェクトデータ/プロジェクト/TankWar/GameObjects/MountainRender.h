//*********************************************************************
//			�T�v	�F�R�N���X
// 
//			�����	�F5��8��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/TaskManager.h"

class MountainRender : public Task
{
private:

	// �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
	ID3D11DeviceContext* m_context;

	// �R�����X�e�[�g�ւ̃|�C���^
	DirectX::CommonStates* m_states;

	DirectX::SimpleMath::Matrix m_view, m_proj;

	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	// �R���f��
	std::shared_ptr<DirectX::Model> m_mountainModel[5];

public:
	// �R���X�g���N�^
	MountainRender(ID3D11DeviceContext* context,
		DirectX::CommonStates* states
	);

	// �`��
	void Render() override;

	void SetViewProjectionMatrix(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
};