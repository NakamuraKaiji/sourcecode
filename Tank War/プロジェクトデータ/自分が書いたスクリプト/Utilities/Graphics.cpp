#include "pch.h"
#include "Graphics.h"

std::unique_ptr<Graphics> Graphics::m_graphics = nullptr;

// DirectX Graphics�N���X�̃C���X�^���X���擾
Graphics* const Graphics::GetInstance()
{
	if (m_graphics == nullptr)
	{
		// DirectX Graphics�N���X�̃C���X�^���X�𐶐�
		m_graphics.reset(new Graphics());
	}
	// DirectX Graphics�N���X�̃C���X�^���X��Ԃ�
	return m_graphics.get();
}

// �R���X�g���N�^
Graphics::Graphics()
	:
	m_deviceResources(nullptr),			                // �f�o�C�X���\�[�X
	m_commonStates(nullptr),				            // �R�����X�e�[�g
	m_spriteBatch(nullptr),					            // �X�v���C�g�o�b�`
	m_spriteFont(nullptr),						        // �X�v���C�g�t�H���g
	m_basicEffect(nullptr),					            // �x�[�V�b�N�G�t�F�N�g
	m_primitiveBatch(nullptr),				            // �v���~�e�B�u�o�b�`
	m_rasterrizerState(nullptr),				        // ���X�^���C�U�[�X�e�[�g
	m_effectFactory(nullptr),				            // �G�t�F�N�g�t�@�N�g��
	m_inputLayout(nullptr),					            // ���̓��C�A�E�g
	m_screenW(0),								        // �X�N���[����
	m_screenH(0),									    // �X�N���[����
	m_view{},											// �r���[�s��
	m_projection{},								        // �ˉe�s��
	m_device(nullptr),							        // �f�o�C�X
	m_context(nullptr)							        // �f�o�C�X�R���e�L�X�g
{
	// DeviceResources�N���X�̃C���X�^���X�𐶐�
	//m_deviceResources = std::make_unique<DX::DeviceResources>();
}

// �f�X�g���N�^
Graphics::~Graphics()
{
}

// ������
void Graphics::Initialize()
{
	// �X�N���[���T�C�Y��ݒ�
	//SetScreenSize(width, height);
	// �f�o�C�X���\�[�X��ݒ�
	//m_deviceResources = deviceResources;
	// �f�o�C�X���擾
	m_device = m_deviceResources->GetD3DDevice();
	// �f�o�C�X�R���e�L�X�g���擾
	m_context = m_deviceResources->GetD3DDeviceContext();

	// �R�����X�e�[�g�𐶐�
	//m_commonStates = std::make_unique<DirectX::CommonStates>(m_device);
	// �X�v���C�g�o�b�`�𐶐�
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context);
	// �x�[�V�b�N�G�t�F�N�g�𐶐�
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(m_device);
	// �X�v���C�g�t�H���g�𐶐�
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device, L"resources\\font\\SegoeUI_18.spritefont");
	// �v���~�e�B�u�o�b�`�𐶐�
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_context);
	// ���̓��C�A�E�g�𐶐�
	m_basicEffect->SetVertexColorEnabled(true);
	// �e�N�X�`����L��
	m_basicEffect->SetTextureEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	//// ���̓��C�A�E�g�𐶐�
	//m_device->CreateInputLayout(
	//	DirectX::VertexPositionColor::InputElements,
	//	DirectX::VertexPositionColor::InputElementCount,
	//	shaderByteCode, byteCodeLength,
	//	m_inputLayout.ReleaseAndGetAddressOf()
	//);
	// ���̓��C�A�E�g�𐶐�
	m_device->CreateInputLayout(
		DirectX::VertexPositionColorTexture::InputElements,
		DirectX::VertexPositionColorTexture::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.ReleaseAndGetAddressOf()
	);
	CD3D11_RASTERIZER_DESC rasterizerStateDesc(
		D3D11_FILL_SOLID, D3D11_CULL_NONE, FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, FALSE, TRUE
	);
	// ���X�^���C�Y�X�e�[�g�𐶐�
	m_device->CreateRasterizerState(&rasterizerStateDesc, m_rasterrizerState.ReleaseAndGetAddressOf());
	// �G�t�F�N�g�t�@�N�g���𐶐�
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_device);
	// ���\�[�X�f�B���N�g����ݒ�
	m_effectFactory->SetDirectory(L"Resources/cmo");
}

// �������`��
void Graphics::DrawString(const float& x, const float& y, const wchar_t* str)
{
	// �������`��
	m_spriteFont->DrawString(m_spriteBatch.get(), str, DirectX::SimpleMath::Vector2(x, y));
}

// �`��v���~�e�B�u���J�n
void Graphics::DrawPrimitiveBegin(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_context->OMSetBlendState(m_commonStates->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);
	m_context->RSSetState(m_commonStates->CullCounterClockwise());
	//m_context->RSSetState(m_rasterrizeState.Get());

	// �r���[�s���ݒ�
	m_basicEffect->SetView(view);
	// �v���W�F�N�V�����s���ݒ�
	m_basicEffect->SetProjection(projection);
	// ���[���h�s���ݒ�
	//m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	// ���_�J���[��L��
	m_basicEffect->SetVertexColorEnabled(true);
	// �e�N�X�`����L��
	m_basicEffect->SetTextureEnabled(true);
	// ���̓��C�A�E�g��ݒ�
	m_basicEffect->Apply(m_context);
	// ���̓��C�A�E�g��ݒ�
	m_context->IASetInputLayout(m_inputLayout.Get());
	// �v���~�e�B�u�o�b�`���J�n
	m_primitiveBatch->Begin();
}

// �`��v���~�e�B�u���I��
void Graphics::DrawPrimitiveEnd()
{
	// �v���~�e�B�u�o�b�`���I��
	m_primitiveBatch->End();
}

// ���f����`��
void Graphics::DrawModel(const DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const bool& depthBuffer)
{
	if (depthBuffer)
	{
		// ���f����`��
		model->Draw(m_context, *m_commonStates, world, m_view, m_projection);
	}
	else
	{
		// ���f����`��
		model->Draw(
			m_context,
			*m_commonStates,
			world,
			m_view,
			m_projection,
			false,
			[&]() { 	m_context->OMSetDepthStencilState(m_commonStates->DepthNone(), 0); }
		);
	}
}
