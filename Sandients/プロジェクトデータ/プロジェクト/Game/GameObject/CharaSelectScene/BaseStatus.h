#pragma once
#include <string>
#include <vector>

using namespace std;

class BaseStatus
{
public:
	int HP;						//�q�b�g�|�C���g
	int ATK;					//�A�^�b�N
	int DEF;					//�f�B�t�F���X
	int WEI;					//�E�F�C�g
	std::vector<int> SKILLID;
	int CD;						//�N�[���_�E��
	int TextureHandle;			//�e�N�X�`��
};