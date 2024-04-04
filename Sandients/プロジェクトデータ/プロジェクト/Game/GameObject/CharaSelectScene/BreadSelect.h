#pragma once

#include "../../../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "Ingredients.h"
class BreadSelect
{
private:
	int BreadTextures[9];

	bool B_flg[2];						//�p������t���O

	GameSystemObjects* system;

	Ingredients* Bread[9];			//�p���̃N���X�̂܂Ƃ� 
	BaseStatus SBread[9];			//�p���̃X�e�[�^�X�ۑ��p
	int bread_Id[2];					//�p����ID�ۑ�

	float Chara_Cooltime[2];
public:
	BreadSelect();
	~BreadSelect();

	void Initialize(GameSystemObjects* system);									//������
	void Update(float deltatime);		                                        //�X�V
	void Render();		                                                        //�`��
	void Finalize();															//�I��

	int GetFlg(int id);															//�I���t���O��߂�
};