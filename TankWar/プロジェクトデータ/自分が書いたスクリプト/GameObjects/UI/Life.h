//*********************************************************************
//			�T�v	�F�c�@����\������N���X
// 
//			�����	�F12��20��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "MyLib/TaskManager.h"

class Life : public Task
{
private:

	// �O���t�B�b�N�X�ւ̃|�C���^
	Graphics* m_graphics = Graphics::GetInstance();

	// �e�N�X�`���n���h��
	ID3D11ShaderResourceView* m_pTexture;

	// �\���ʒu
	int m_x, m_y;

	// �c�@��
	int m_life;

public:
	// �R���X�g���N�^
	Life(int x, int y);

	// �`��
	void Render() override;

public:

	// �c�@���̎擾
	int GetLife() { return m_life; }

	// �c�@���̐ݒ�
	void SetLife(int life) { m_life = life; }

	//	�摜��ݒ肷��
	void SetTexture(ID3D11ShaderResourceView* texture);


};
