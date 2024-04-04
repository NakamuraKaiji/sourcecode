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
	bool I_flg[2][3];						//具材決定フラグ
	GameSystemObjects* system;
	TextureManger* tdata;
	Sound* sdata;
	FontHandle* fdata;

	//Ingredients* Vegetable[9];		//野菜のクラスのまとめ
	//Ingredients* Meat[14];			//タンパク質のクラスのまとめ
	//Ingredients* Fruits[10];		//グルーつのクラスのまとめ
	//Ingredients* Other[8];			//その他のクラスのまとめ

	//BaseStatus SVegetable[9];		//野菜のステータス保存用
	//BaseStatus SMeat[14];			//タンパク質のステータス保存用
	//BaseStatus SFruits[10];			//フルーツのステータス保存用
	//BaseStatus SOther[8];			//その他のステータス保存用

	//Ingredients* Ingredient[4][9];


	Ingredients* Ingredient[9];		//具材の元クラス
	BaseStatus IngredientState[9];	//具材のステ-タス
	BaseStatus baseStatus[2];		//HP3,ATK2,DEF1


	//int Vegetable_Id;				//野菜のID保存
	//int Meat_Id;					//タンパク質のID保存
	//int Fruits_Id;					//フルーツのID保存
	//int Other_Id;					//その他のID保存

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

	void Initialize(GameSystemObjects* system, TextureManger* tdata, FontHandle* fdata, Sound* sdata);			//初期化
	void Update(float deltatime);		                                        //更新
	void Render();		                                                        //描画
	void Finalize();															//終了

	int GetFlg(int id,int kind);													//選択フラグを戻す

	BaseStatus* GetStatas();
};