#include "pch.h"
#include "StartCount.h"
#include "Utilities/Resources.h"

using namespace DirectX;

// �R���X�g���N�^
StartCount::StartCount(int x, int y, int windowWidth, int windowHeight)
	: m_count(3.0f)
	, m_x(x)
	, m_y(y)
	, m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_startFlag(false)
	, m_texture1{}
	, m_texture2{}
	, m_texture3{}
{
	m_texture1 = Resources::GetInstance()->GetNumber1();
	m_texture2 = Resources::GetInstance()->GetNumber2();
	m_texture3 = Resources::GetInstance()->GetNumber3();
}

// �X�V
bool StartCount::Update(float elapsedTime)
{
	m_count -= elapsedTime;

	if (m_count <= 0.0f) m_startFlag = true;

	return true;
}

// �`��
void StartCount::Render()
{
	if (m_count <= 3.0f && m_count > 2.0f)
	{
		m_graphics->GetSpriteBatch()->Draw(m_texture3,
			SimpleMath::Vector2(float((m_windowWidth / 2) - (m_x / 2)), float((m_windowHeight / 2) - (m_y / 2))));
	}
	else if (m_count <= 2.0f && m_count > 1.0f)
	{
		m_graphics->GetSpriteBatch()->Draw(m_texture2,
			SimpleMath::Vector2(float((m_windowWidth / 2) - (m_x / 2)), float((m_windowHeight / 2) - (m_y / 2))));
	}
	else if (m_count <= 1.0f && m_count > 0.0f)
	{
		m_graphics->GetSpriteBatch()->Draw(m_texture1,
			SimpleMath::Vector2(float((m_windowWidth / 2) - (m_x / 2)), float((m_windowHeight / 2) - (m_y / 2))));
	}
	else if (m_count <= 0.0f)
	{
	}
}

// �J�E���g��ݒ�
void StartCount::SetCount(float count)
{
	m_count = count;
}

// �e�N�X�`����ݒ�i�P�̃e�N�X�`���j
void StartCount::SetTexture1(ID3D11ShaderResourceView* number1)
{
	m_texture1 = number1;
}

// �e�N�X�`����ݒ�i�Q�̃e�N�X�`���j
void StartCount::SetTexture2(ID3D11ShaderResourceView* number2)
{
	m_texture2 = number2;
}

// �e�N�X�`����ݒ�i�R�̃e�N�X�`���j
void StartCount::SetTexture3(ID3D11ShaderResourceView* number3)
{
	m_texture3 = number3;
}
