#pragma once
#include <vector>
#include "../../../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "../../GameDatas/TextureManager.h"
#include "../../GameDatas/Sound.h"
#include "../../GameDatas/FontHandle.h"
#include "Ingredients.h"

class IngredientsSelect
{
private:
	bool I_flg[2][3];						//��ތ���t���O
	GameSystemObjects* system;
	TextureManger* tdata;
	Sound* sdata;
	FontHandle* fdata;

	//Ingredients* Vegetable[9];		//��؂̃N���X�̂܂Ƃ�
	//Ingredients* Meat[14];			//�^���p�N���̃N���X�̂܂Ƃ�
	//Ingredients* Fruits[10];		//�O���[�̃N���X�̂܂Ƃ�
	//Ingredients* Other[8];			//���̑��̃N���X�̂܂Ƃ�

	//BaseStatus SVegetable[9];		//��؂̃X�e�[�^�X�ۑ��p
	//BaseStatus SMeat[14];			//�^���p�N���̃X�e�[�^�X�ۑ��p
	//BaseStatus SFruits[10];			//�t���[�c�̃X�e�[�^�X�ۑ��p
	//BaseStatus SOther[8];			//���̑��̃X�e�[�^�X�ۑ��p

	//Ingredients* Ingredient[4][9];


	Ingredients* Ingredient[9];		//��ނ̌��N���X
	BaseStatus IngredientState[9];	//��ނ̃X�e-�^�X
	BaseStatus baseStatus[2];		//HP3,ATK2,DEF1


	//int Vegetable_Id;				//��؂�ID�ۑ�
	//int Meat_Id;					//�^���p�N����ID�ۑ�
	//int Fruits_Id;					//�t���[�c��ID�ۑ�
	//int Other_Id;					//���̑���ID�ۑ�

	int Ingredient_X[2];
	int Ingredient_Y[2];

	float Chara_Cooltime[2];
	float decideCooltime[2];

	bool decideFlg[2][3];
	int flgFor[2];
	int decidePositionX[2][3];
	int decidePositionY[2][3];

	int BackGround;

	bool sideFlg[2][3];

	int Texture1P;
	int Texture2P;

	int SaveID[2][3];

public:
	IngredientsSelect();
	~IngredientsSelect();

	void Initialize(GameSystemObjects* system, TextureManger* tdata, FontHandle* fdata, Sound* sdata);			//������
	void Update(float deltatime);		                                        //�X�V
	void Render();		                                                        //�`��
	void Finalize();															//�I��

	int GetFlg(int id,int kind);													//�I���t���O��߂�

	BaseStatus* GetStatas();
};