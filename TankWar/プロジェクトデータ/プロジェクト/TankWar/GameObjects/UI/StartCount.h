//*********************************************************************
//			�T�v	�F�Q�[�����n�܂�܂ł̃J�E���g�N���X
// 
//			�����	�F5��15��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/TaskManager.h"

class StartCount : public Task
{
private:
	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	// �e�N�X�`���n���h��
	ID3D11ShaderResourceView* m_texture1;
	ID3D11ShaderResourceView* m_texture2;
	ID3D11ShaderResourceView* m_texture3;

	// �\���ʒu
	int m_x, m_y;

	// ��ʃT�C�Y
	int m_windowWidth, m_windowHeight;

	// �J�E���g
	float m_count;

	bool m_startFlag;

public:
	// �R���X�g���N�^
	StartCount(int x, int y, int windowWidth, int windowHeight);

	// �X�V
	bool Update(float elapsedTime) override;

	// �`��
	void Render() override;

public:

	// �J�E���g���擾
	float GetCount() { return m_count; }
	// �J�E���g��ݒ�
	void SetCount(float count);

	//	�摜��ݒ肷��
	void SetTexture1(ID3D11ShaderResourceView* number1);
	void SetTexture2(ID3D11ShaderResourceView* number2);
	void SetTexture3(ID3D11ShaderResourceView* number3);

	// �X�^�[�g�t���O
	bool GetStartFlag() { return m_startFlag; }


};
