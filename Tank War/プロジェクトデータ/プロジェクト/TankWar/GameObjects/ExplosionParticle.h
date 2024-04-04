//*********************************************************************
//			�T�v	�F�����̃G�t�F�N�g�N���X
// 
//			�����	�F2��21��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "ParticleUtility.h"
#include <list>
#include <vector>


class ExplosionParticle
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

	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �e�N�X�`���n���h��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	std::list<ParticleUtility> m_particleUtility;

private:

	// �r���{�[�h
	DirectX::SimpleMath::Matrix m_billboard;

	// �\���ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// �X�P�[��
	DirectX::SimpleMath::Vector3 m_scale;

	DirectX::SimpleMath::Vector3 m_cameraPosition;
	DirectX::SimpleMath::Vector3 m_cameraTarget;

	// �^�C�}�[
	float m_timer;

public:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// �R���X�g���N�^
	ExplosionParticle();

	// �e�N�X�`�����\�[�X�ǂݍ���
	void LoadTexture();

	// �X�V
	void Update(float elapsedTime);

	// �`��
	void Render();

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

	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_scale = scale; }

private:

	// �V�F�[�_���암���������������֐�
	void CreateShader();

};