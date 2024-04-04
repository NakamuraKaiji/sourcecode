//*********************************************************************
//			�T�v	�F�`��֌W�̃N���X
// 
//			�����	�F6��7��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#ifndef GRAPHICS_DEFINED
#define GRAPHICS_DEFINED

#include "DeviceResources.h"

class Graphics final
{
public:
	// DirectX Graphics�N���X�̃C���X�^���X���擾
	static Graphics* const GetInstance();

	// �X�N���[���T�C�Y���擾
	void GetScreenSize(int& width, int& height) const { width = m_screenW; height = m_screenH; }
	// �X�N���[���T�C�Y��ݒ�
	void SetScreenSize(const int& width, const int& height) { m_screenW = width; m_screenH = height; }
	// �f�o�C�X���\�[�X���擾
	DX::DeviceResources* GetDeviceResources() const { return m_deviceResources; }
	// �f�o�C�X���\�[�X��ݒ�
	void SetDeviceResources(DX::DeviceResources* pDR) { m_deviceResources = (pDR); }
	// PrimitiveBatch�N���X�̃C���X�^���X���擾
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* GetPrimitiveBatch() const { return m_primitiveBatch.get(); }
	// InputLayout�N���X�̃C���X�^���X���擾
	ID3D11InputLayout* GetInputLayout() const { return m_inputLayout.Get(); }
	// BasicEffect�N���X�̃C���X�^���X�擾
	DirectX::BasicEffect* GetBasicEffect() { return m_basicEffect.get(); }
	// CommonStates�N���X�̃C���X�^���X���擾
	DirectX::CommonStates* GetCommonStates() const { return m_commonStates; }
	// CommonStates�N���X�̃C���X�^���X��ݒ�
	void SetCommonStates(DirectX::CommonStates* pCS) { m_commonStates = pCS; }
	// SpriteBatch�N���X�̃C���X�^���X���擾
	DirectX::SpriteBatch* GetSpriteBatch() { return m_spriteBatch.get(); }
	// SpriteFont�N���X�̃C���X�^���X���擾
	DirectX::SpriteFont* GetFont() { return m_spriteFont.get(); }
	// EffectFactory�N���X�̃C���X�^���X���擾
	DirectX::EffectFactory* GetFX() const { return m_effectFactory.get(); }
	// �r���[�s���ݒ�
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// �r���[�s����擾
	const DirectX::SimpleMath::Matrix& GetViewMatrix() { return m_view; };
	// �ˉe�s���ݒ�
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection) { m_projection = projection; }
	// �ˉe�s����擾
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() { return m_projection; };

public:
	// �f�X�g���N�^
	~Graphics();
	// ������
	void Initialize();
	// �������`��
	void DrawString(const float& x, const float& y, const wchar_t* str);
	// �v���~�e�B�u�`����J�n
	void DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	// �v���~�e�B�u�`����I��
	void DrawPrimitiveEnd();
	// ���f����`��
	void DrawModel(const DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const bool& depthBuffer = true);

private:
	// �R���X�g���N�^
	Graphics();

	// ����͋��e���Ȃ�
	void operator=(const Graphics& object) = delete;
	// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
	Graphics(const Graphics& object) = delete;

private:
	// Graphics�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Graphics> m_graphics;
	// �f�o�C�X���\�[�X�ւ̃|�C���^
	 DX::DeviceResources* m_deviceResources;
	// �R�����X�e�[�g
	DirectX::CommonStates* m_commonStates;
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
	// �G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;
	// ���X�^���C�U�[�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterrizerState;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �X�N���[���T�C�Y
	int m_screenW;
	int m_screenH;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
	// �f�o�C�X
	ID3D11Device* m_device;
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;
};
#endif		// GRAPHICS_DEFINED