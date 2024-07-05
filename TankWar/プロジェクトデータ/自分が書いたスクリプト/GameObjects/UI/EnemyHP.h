//*********************************************************************
//			�T�v	�F�G��HP�N���X
// 
//			�����	�F1��15��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/TaskManager.h"

class EnemyHP : public Task
{
public:

	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

private:

	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;


private:

	// �r���{�[�h
	DirectX::SimpleMath::Matrix m_billboard;

	// �\���ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// HP�̊���
	float m_ratio;

	//	�摜�T�C�Y
	int m_textureWidth, m_textureHeight;

	DirectX::Keyboard::KeyboardStateTracker m_tracker;


public:
	
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// �R���X�g���N�^
	EnemyHP();

	// �e�N�X�`�����\�[�X�ǂݍ���
	void LoadTexture(const wchar_t* path);

	// �X�V
	bool Update(float elapsedTime) override;

	// �`��
	void Render() override;

	// �r���{�[�h
	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up);

public:

	// �ʒu�擾
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

	// �ʒu�ݒ�
	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	// HP�̊������擾
	float GetRatio() { return m_ratio; }

	// HP�̊�����ݒ�
	void SetRatio(float ratio) { m_ratio = ratio; }

private:
	// �V�F�[�_���암���������������֐�
	void CreateShader();

};