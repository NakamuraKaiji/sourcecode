#include "IngredientsSelect.h"
#include <DxLib.h>
#include "../../GameDatas/ControllerInput.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>

#define CIRCLE_R				70
#define CIRCLE_START_POS_X		320		
#define CIRCLE_START_POS_Y		800		

#define CIRCLE_SECOND_POS_X		400		
#define CIRCLE_SECOND_POS_Y		800		

#define BOX_START_POS_X		400		
#define BOX_START_POS_Y		50		

#define BOX_END_POS_X		1400		
#define BOX_END_POS_Y		700	



#define STATE_BOX_P1_HP_POS_X		850		
#define STATE_BOX_P1_HP_POS_Y		250

#define STATE_BOX_P1_ATK_POS_X		850		
#define STATE_BOX_P1_ATK_POS_Y		350

#define STATE_BOX_P1_DEF_POS_X		850		
#define STATE_BOX_P1_DEF_POS_Y		450

#define STATE_BOX_P1_WEI_POS_X		850		
#define STATE_BOX_P1_WEI_POS_Y		550



#define STATE_BOX_P2_HP_POS_X		940		
#define STATE_BOX_P2_HP_POS_Y		250

#define STATE_BOX_P2_ATK_POS_X		940		
#define STATE_BOX_P2_ATK_POS_Y		350

#define STATE_BOX_P2_DEF_POS_X		940		
#define STATE_BOX_P2_DEF_POS_Y		450

#define STATE_BOX_P2_WEI_POS_X		940		
#define STATE_BOX_P2_WEI_POS_Y		550


#define STATE_SCALE_BOX_X		10		
#define STATE_SCALE_BOX_Y		80

#define BOX_WHILE				20

#define STATE_BOX_P2_POS_X		400		
#define STATE_BOX_P2_POS_Y		50

#define SELECT_P1_CIRCLE_X		480
#define SELECT_P2_CIRCLE_X		1290
#define SELECT_CIRCLE_Y			260
#define SELECT_CIRCLE_R			80
#define SELECT_CIRCLE_OFFSET	160

#define NAME_POS		BOX_START_POS_Y + 100	

#define POS_2P_X		(BOX_START_POS_X + BOX_END_POS_X) / 2 + LINE_WHILE	
#define POS_2P_Y		50		



#define LINE_WHILE		10		

#define CIRCLE_BETWEEN			150

#define CIRCLE_R_ORIGIN			60

#define COLUMN			5
#define RAW				9

#define MAX_INGREDIENTS	3

IngredientsSelect::IngredientsSelect()
{
	Texture1P = LoadGraph("Resources/Textures/1P.png");
	Texture2P = LoadGraph("Resources/Textures/2P.png");
	std::ifstream ifs;
	//ファイルを読み取り専用で開く
	ifs.open("Resources/State.csv");
	//一行分(横方向)のデータを列数分(縦方向)入れる配列
	std::string s[RAW];

	for (int x = 0; x < RAW; x++)
	{
		//一行分のデータを読み込む
		ifs >> s[x];
		//読み込んだデータの区切り文字(,)を半角スペース( )に置き換える
		std::string tmp = std::regex_replace(s[x], std::regex(","), " ");
		//処理しやすくするためにストリーム形式にする
		std::istringstream iss(tmp);
		for (int z = 0; z < COLUMN; z++)
		{
			int num = -1;
			//空白までのデータ（１つ分のデータ）を読み込む
			iss >> num;

			//読み込んだデータを格納する
			switch (z)
			{
			case 0:
				IngredientState[x].HP = num;
				break;
			case 1:
				IngredientState[x].ATK = num;
				break;
			case 2:
				IngredientState[x].DEF = num;
				break;
			case 3:
				IngredientState[x].WEI = num;
				break;
			case 4:
				IngredientState[x].CD = num;
				break;
			default:
				break;
			}
		}
	}

//開いたファイルを閉じる
	ifs.close();

	IngredientState[0].TextureHandle = LoadGraph("Resources/Textures/Vege8_lettuce.png");	//レタス
	IngredientState[1].TextureHandle = LoadGraph("Resources/Textures/Vege5_tomato.png.png");	//トマト
	IngredientState[2].TextureHandle = LoadGraph("Resources/Textures/Vege9_onion.png");	//玉ねぎ
	IngredientState[3].TextureHandle = LoadGraph("Resources/Textures/ベーコン.png");	//ベーコン
	IngredientState[4].TextureHandle = LoadGraph("Resources/Textures/サラダチキン.png");	//チキン
	IngredientState[5].TextureHandle = LoadGraph("Resources/Textures/サーモン.png");	//サーモン
	IngredientState[6].TextureHandle = LoadGraph("Resources/Textures/ツナ.png");	//ツナ缶
	IngredientState[7].TextureHandle = LoadGraph("Resources/Textures/banana.png");	//バナナ
	IngredientState[8].TextureHandle = LoadGraph("Resources/Textures/");	//ホイップ

	for (int i = 0; i < 2; i++)
	{
		baseStatus[i].HP = 3;
		baseStatus[i].ATK = 2;
		baseStatus[i].DEF = 1;
		baseStatus[i].WEI = 2;
	}

	Ingredient[0] = new Lettuce(IngredientState[0], 0);
	Ingredient[1] = new Tomato(IngredientState[1], 1);
	Ingredient[2] = new Onion(IngredientState[2], 2);
	Ingredient[3] = new Bacon(IngredientState[3], 3);
	Ingredient[4] = new Chicken(IngredientState[4], 4);
	Ingredient[5] = new Salmon(IngredientState[5], 5);
	Ingredient[6] = new Tuna(IngredientState[6], 6);
	Ingredient[7] = new Banana(IngredientState[7], 7);
	Ingredient[8] = new Whip(IngredientState[8], 8);

}

IngredientsSelect::~IngredientsSelect()
{

}

void IngredientsSelect::Initialize(GameSystemObjects* system, TextureManger* tdata, FontHandle* fdata, Sound* sdata)
{
	this->system = system;
	this->tdata = tdata;
	this->fdata = fdata;
	this->sdata = sdata;



	/*
	SVegetable[0].TextureHandle = LoadGraph("Resources/Textures/Vege8_lettuce.png");
	SVegetable[1].TextureHandle = LoadGraph("Resources/Textures/Vege5_tomato.png");
	SVegetable[2].TextureHandle = LoadGraph("Resources/Textures/Vege4_radish.png");
	SVegetable[3].TextureHandle = LoadGraph("Resources/Textures/Vege9_onion.png");
	SVegetable[4].TextureHandle = LoadGraph("Resources/Textures/Vege6_greenbellpepper.png");
	SVegetable[5].TextureHandle = LoadGraph("Resources/Textures/Vege7_pickles.png");
	SVegetable[6].TextureHandle = LoadGraph("Resources/Textures/Vege3_cucumber.png");
	SVegetable[7].TextureHandle = LoadGraph("Resources/Textures/Vege10_carrot.png");
	SVegetable[8].TextureHandle = LoadGraph("Resources/Textures/Vege1_pumpkin.png");

	BackGround = LoadGraph("Resources/Textures/SelectSceneBackGround");

	Ingredient[0][0] = new Lettuce(SVegetable[0], 0);
	Ingredient[0][1] = new Tomato(SVegetable[1], 1);
	Ingredient[0][2] = new Takuan(SVegetable[2], 2);
	Ingredient[0][3] = new Onion(SVegetable[3], 3);
	Ingredient[0][4] = new Pepper(SVegetable[4], 4);
	Ingredient[0][5] = new Pickles(SVegetable[5], 5);
	Ingredient[0][6] = new Cucumber(SVegetable[6], 6);
	Ingredient[0][7] = new Carrot(SVegetable[7], 7);
	Ingredient[0][8] = new Squash(SVegetable[8], 8);

	Meat[0] = new Ham(SMeat[0], 0);
	Meat[1] = new Chicken(SMeat[1], 1);
	Meat[2] = new Hamburger(SMeat[2], 2);
	Meat[3] = new Scrambled(SMeat[3], 3);
	Meat[4] = new Boiled(SMeat[4], 4);
	Meat[5] = new Sausage(SMeat[5], 5);
	Meat[6] = new Cheese(SMeat[6], 6);
	Meat[7] = new Bacon(SMeat[7], 7);
	Meat[8] = new Tuna(SMeat[8], 8);
	Meat[9] = new Prawn(SMeat[9], 9);
	Meat[10] = new Fish(SMeat[10], 10);
	Meat[11] = new Pork(SMeat[11], 11);
	Meat[12] = new Salmon(SMeat[12], 12);
	Meat[13] = new Roast(SMeat[13], 13);


	Fruits[0] = new Avocado(SFruits[0], 0);
	Fruits[1] = new Strawberry(SFruits[1], 1);
	Fruits[2] = new Kiwi(SFruits[2], 2);
	Fruits[3] = new Grape(SFruits[3], 3);
	Fruits[4] = new Banana(SFruits[4], 4);
	Fruits[5] = new Orange(SFruits[5], 5);
	Fruits[6] = new Blueberry(SFruits[6], 6);
	Fruits[7] = new Pineapple(SFruits[7], 7);
	Fruits[8] = new Peach(SFruits[8], 8);

	Other[0] = new Yakisoba(SOther[0], 0);
	Other[1] = new Whip(SOther[1], 1);
	Other[2] = new PotatoSalad(SOther[2], 2);
	Other[3] = new KeemaCurry(SOther[3], 3);
	Other[4] = new Gratin(SOther[4], 4);
	Other[5] = new Kimpira(SOther[5], 5);
	Other[6] = new Bean(SOther[6], 6);
	Other[7] = new Chocolate(SOther[7], 7);
	*/
	Ingredient_X[0] = 0;
	Ingredient_Y[0] = 0;

	Ingredient_X[1] = 0;
	Ingredient_Y[1] = 0;

	Chara_Cooltime[0] = 0.0f;
	Chara_Cooltime[1] = 0.0f;

	decideCooltime[0] = 0.0f;
	decideCooltime[1] = 0.0f;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			decidePositionX[i][j] = 0;
			decidePositionY[i][j] = 0;
			decideFlg[i][j] = false;
			I_flg[i][j] = false;
			sideFlg[i][j] = false;
			SaveID[i][j] = 0;

		}
		
		flgFor[i] = 0;
		flgFor[i] = 0;
	}

}

void IngredientsSelect::Update(float deltatime)
{
	for (int i = 0; i < 2; i++)
	{
		Chara_Cooltime[i] -= deltatime;
		decideCooltime[i] -= deltatime;
		if (Chara_Cooltime[i] < 0.0f)
		{
			Chara_Cooltime[i] = 0.0f;
		}
		if (decideCooltime[i] < 0.0f)
		{
			decideCooltime[i] = 0.0f;
		}
	}
	//----------------------//
	//		プレイヤー1		//	
	//----------------------//
	if (!I_flg[0][0] || !I_flg[0][1] || !I_flg[0][2])
	{
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::RIGHT) && Chara_Cooltime[0] <= 0.0f)
		{
			sdata->Select();
			Chara_Cooltime[0] = 0.3f;
			Ingredient_X[0] += 1;
			if (Ingredient_Y[0] == 1 || Ingredient_Y[0] == 3)
			{
				if (Ingredient_X[0] > 7)
				{
					Ingredient_X[0] = 0;
				}
			}
			else if (Ingredient_X[0] > 8)
			{
				Ingredient_X[0] = 0;
			}
		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::LEFT) && Chara_Cooltime[0] <= 0.0f)
		{
			sdata->Select();
			Chara_Cooltime[0] = 0.3f;
			Ingredient_X[0] -= 1;
			if (Ingredient_Y[0] == 1 || Ingredient_Y[0] == 3)
			{
				if (Ingredient_X[0] < 0)
				{
					Ingredient_X[0] = 7;
				}
			}
			else if (Ingredient_X[0] < 0)
			{
				Ingredient_X[0] = 8;
			}
		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::UP) && Chara_Cooltime[0] <= 0.0f)
		{
			sdata->Select();
			Chara_Cooltime[0] = 0.3f;
			Ingredient_Y[0] -= 1;
			if (Ingredient_X[0] == 8)
			{
				Ingredient_X[0] = 7;
			}
			if (Ingredient_Y[0] < 0)
			{
				Ingredient_Y[0] = 1;
			}
		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::DOWN) && Chara_Cooltime[0] <= 0.0f)
		{
			sdata->Select();
			Chara_Cooltime[0] = 0.3f;
			Ingredient_Y[0] += 1;
			if (Ingredient_X[0] == 8)
			{
				Ingredient_X[0] = 7;
			}
			if (Ingredient_Y[0] > 1)
			{
				Ingredient_Y[0] = 0;
			}
		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::CIRCLE) && Chara_Cooltime[0] <= 0.0f)
		{
			sdata->Decision();
			baseStatus[0].HP += IngredientState[Ingredient_X[0]].HP;
			baseStatus[0].ATK += IngredientState[Ingredient_X[0]].ATK;
			baseStatus[0].DEF += IngredientState[Ingredient_X[0]].DEF;
			baseStatus[0].WEI += IngredientState[Ingredient_X[0]].WEI;
			baseStatus[0].SKILLID.push_back(Ingredient_X[0]);
			//baseStatus[0].SKILLID.push_back(Ingredient[flgFor[0]]->GetId());

			SaveID[1][flgFor[0]] = Ingredient[flgFor[0]]->GetId();

			Chara_Cooltime[0] = 0.3f;
			I_flg[0][flgFor[0]] = true;
			flgFor[0] += 1;
		}
	}
	//if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::CIRCLE) && decideCooltime[0] <= 0.0f)
	if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::CROSS) && Chara_Cooltime[0] <= 0.0f && flgFor[0] > 0)
	{
		flgFor[0] -= 1;
		I_flg[0][flgFor[0]] = false;

		sdata->Select();
		baseStatus[0].HP -= IngredientState[baseStatus[0].SKILLID[flgFor[0]]].HP;
		baseStatus[0].ATK -= IngredientState[baseStatus[0].SKILLID[flgFor[0]]].ATK;
		baseStatus[0].DEF -= IngredientState[baseStatus[0].SKILLID[flgFor[0]]].DEF;
		baseStatus[0].WEI -= IngredientState[baseStatus[0].SKILLID[flgFor[0]]].WEI;
		baseStatus[0].SKILLID.pop_back();


		Chara_Cooltime[0] = 0.3f;
	}
	/*if (!I_flg[0][flgFor[0]- 1])
	{
		baseStatus[0].HP -= IngredientState[Ingredient_X[0]].HP;
		baseStatus[0].ATK -= IngredientState[Ingredient_X[0]].ATK;
		baseStatus[0].DEF -= IngredientState[Ingredient_X[0]].DEF;
		baseStatus[0].WEI -= IngredientState[Ingredient_X[0]].WEI;
	}*/

	//if (I_flg[0][flgFor[0] - 1] == true)
	//{
	//	if (system->GetInputSystem().IsButtonDown(DX_INPUT_PAD1, DualShock4Input::CROSS) && Chara_Cooltime[0] <= 0.0f)
	//	{
	//		Chara_Cooltime[0] = 0.3f;
	//		I_flg[0][flgFor[0]] = false;
	//		flgFor[0] -= 1;
	//		decideFlg[0][flgFor[0] - 1] = false;
	//		sideFlg[0] = false;
	//	}
	//}
	//if (flgFor[0] == 2)
	//{
	//	if (I_flg[0][flgFor[0]] == true)
	//	{
	//		I_flg[0][flgFor[0]] = false;
	//	}
	//	else
	//	{
	//		I_flg[0][flgFor[0]] = true;
	//	}
	//}
	
	//----------------------//
	//		プレイヤー2		//	
	//----------------------//

	if (!I_flg[1][0] || !I_flg[1][1] || !I_flg[1][2])
	{
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::RIGHT) && Chara_Cooltime[1] <= 0.0f)
		{
			sdata->Select();
			Chara_Cooltime[1] = 0.3f;
			Ingredient_X[1] += 1;
			if (Ingredient_Y[1] == 1 || Ingredient_Y[1] == 3)
			{
				if (Ingredient_X[1] > 7)
				{
					Ingredient_X[1] = 0;
				}
			}
			else if (Ingredient_X[1] > 8)
			{
				Ingredient_X[1] = 0;
			}
		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::LEFT) && Chara_Cooltime[1] <= 0.0f)
		{
			sdata->Select();
			Chara_Cooltime[1] = 0.3f;
			Ingredient_X[1] -= 1;
			if (Ingredient_Y[1] == 1 || Ingredient_Y[1] == 3)
			{
				if (Ingredient_X[1] < 0)
				{
					Ingredient_X[1] = 7;
				}
			}
			else if (Ingredient_X[1] < 0)
			{
				Ingredient_X[1] = 8;
			}
		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::UP) && Chara_Cooltime[1] <= 0.0f)
		{
			sdata->Select();
			Chara_Cooltime[1] = 0.3f;
			Ingredient_Y[1] -= 1;
			if (Ingredient_X[1] == 8)
			{
				Ingredient_X[1] = 7;
			}
			if (Ingredient_Y[1] < 0)
			{
				Ingredient_Y[1] = 1;
			}
		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::DOWN) && Chara_Cooltime[1] <= 0.0f)
		{
			sdata->Select();
			Chara_Cooltime[1] = 0.3f;
			Ingredient_Y[1] += 1;
			if (Ingredient_X[1] == 8)
			{
				Ingredient_X[1] = 7;
			}
			if (Ingredient_Y[1] > 1)
			{
				Ingredient_Y[1] = 0;
			}
		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::CIRCLE) && Chara_Cooltime[1] <= 0.0f)
		{
			sdata->Decision();
			Chara_Cooltime[1] = 0.3f;
			I_flg[1][flgFor[1]] = true;
			SaveID[1][flgFor[1]] = Ingredient[flgFor[1]]->GetId();
			flgFor[1] += 1;


			baseStatus[1].HP += IngredientState[Ingredient_X[1]].HP;
			baseStatus[1].ATK += IngredientState[Ingredient_X[1]].ATK;
			baseStatus[1].DEF += IngredientState[Ingredient_X[1]].DEF;
			baseStatus[1].WEI += IngredientState[Ingredient_X[1]].WEI;
			baseStatus[1].SKILLID.push_back(Ingredient_X[1]);
			//baseStatus[1].SKILLID.push_back(Ingredient[flgFor[1]]->GetId());

		}
		//else if (I_flg[1][flgFor[1]] == true)
		//{
		//	if (system->GetInputSystem().IsButtonDown(DX_INPUT_PAD2, DualShock4Input::CROSS))
		//	{
		//		I_flg[1][flgFor[1]] = false;
		//		flgFor[1] -= 1;
		//		decideFlg[0][flgFor[1] - 1] = false;
		//		sideFlg[0] = false;

		//	}
		//}

	}
	if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::CROSS) && Chara_Cooltime[1] <= 0.0f && flgFor[1] > 0)
	{
		flgFor[1] -= 1;
		I_flg[1][flgFor[1]] = false;

		sdata->Select();
		baseStatus[1].HP -= IngredientState[baseStatus[1].SKILLID[flgFor[1]]].HP;
		baseStatus[1].ATK -= IngredientState[baseStatus[1].SKILLID[flgFor[1]]].ATK;
		baseStatus[1].DEF -= IngredientState[baseStatus[1].SKILLID[flgFor[1]]].DEF;
		baseStatus[1].WEI -= IngredientState[baseStatus[1].SKILLID[flgFor[1]]].WEI;
		baseStatus[1].SKILLID.pop_back();


		Chara_Cooltime[1] = 0.3f;
	}
}

void IngredientsSelect::Render()
{
	unsigned int white = GetColor(255, 255, 255);    // 白色の値を取得
	unsigned int black = GetColor(0, 0, 0);    // 白色の値を取得
	unsigned int blue = GetColor(0, 0, 255);		// 青色の値を取得
	unsigned int Selblue = GetColor(0, 130, 255);    // 青色の値を取得
	unsigned int red = GetColor(255, 0, 0);			// 青色の値を取得
	unsigned int Selred = GetColor(255, 130, 0);    // 青色の値を取得
	unsigned int BOX = GetColor(100, 100, 100);    // 色の値を取得

	//	背景
	DrawBox(0, 0, 1920, 1080, 0x000000, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
	DrawExtendGraph(0, 0, 1920, 1080, tdata->GetTextureHandle(static_cast<int>(CharaSelectSceneTexture::Back)), 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 円
	for (int j = 0; j < 2; j++)
	{
		if (j % 2 == 0)
		{
			for (int i = 0; i < 9; i++)
			{
				if (i == Ingredient_X[0] && j == Ingredient_Y[0])
				{
					DrawCircle(CIRCLE_START_POS_X + i * CIRCLE_BETWEEN, CIRCLE_START_POS_Y + j * CIRCLE_BETWEEN, CIRCLE_R + 5, red, TRUE);
					for (int n = 0; n < 3; n++)
					{
						if (I_flg[0][n] && !decideFlg[0][n])
						{
							decidePositionX[0][n] = i;
							decidePositionY[0][n] = j;

							decideFlg[0][n] = true;
							sideFlg[0][n] = true;
						}

					}
				}

				if (i == Ingredient_X[1] && j == Ingredient_Y[1])
				{
					DrawCircle(CIRCLE_START_POS_X + i * CIRCLE_BETWEEN, CIRCLE_START_POS_Y + j * CIRCLE_BETWEEN, CIRCLE_R, blue, TRUE);
					for (int n = 0; n < 3; n++)
					{
						if (I_flg[1][n] && !decideFlg[1][n])
						{
							decidePositionX[1][n] = i;
							decidePositionY[1][n] = j;

							decideFlg[1][n] = true;
							sideFlg[1][n] = true;
						}

					}
				}
				DrawCircle(CIRCLE_START_POS_X + i * CIRCLE_BETWEEN, CIRCLE_START_POS_Y + j * CIRCLE_BETWEEN, CIRCLE_R_ORIGIN, white, TRUE);
			}
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				if (i == Ingredient_X[0] && j == Ingredient_Y[0])
				{
					DrawCircle(CIRCLE_SECOND_POS_X + i * CIRCLE_BETWEEN, CIRCLE_SECOND_POS_Y + j * CIRCLE_BETWEEN, CIRCLE_R + 5, red, TRUE);
					for (int n = 0; n < 3; n++)
					{
						if (I_flg[0][n] && !decideFlg[0][n])
						{
							decidePositionX[0][n] = i;
							decidePositionY[0][n] = j;

							decideFlg[0][n] = true;
						}

					}


				}
				if (i == Ingredient_X[1] && j == Ingredient_Y[1])
				{
					DrawCircle(CIRCLE_SECOND_POS_X + i * CIRCLE_BETWEEN, CIRCLE_SECOND_POS_Y + j * CIRCLE_BETWEEN, CIRCLE_R, blue, TRUE);
					for (int n = 0; n < 3; n++)
					{
						if (I_flg[1][n] && !decideFlg[1][n])
						{
							decidePositionX[1][n] = i;
							decidePositionY[1][n] = j;

							decideFlg[1][n] = true;
						}
					}
				}
				DrawCircle(CIRCLE_SECOND_POS_X + i * CIRCLE_BETWEEN, CIRCLE_SECOND_POS_Y + j * CIRCLE_BETWEEN, CIRCLE_R_ORIGIN, white, TRUE);
			}

		}
	}
	//元の白いボックス
	DrawBox(BOX_START_POS_X, BOX_START_POS_Y, BOX_END_POS_X, BOX_END_POS_Y, white, TRUE);
	//ボックスの真ん中の線
	DrawBox((BOX_START_POS_X + BOX_END_POS_X) / 2 - LINE_WHILE, BOX_START_POS_Y, (BOX_START_POS_X + BOX_END_POS_X) / 2 + LINE_WHILE, BOX_END_POS_Y, black, TRUE);
	//名前のやつ
	DrawBox(BOX_START_POS_X, NAME_POS - LINE_WHILE, BOX_END_POS_X, NAME_POS + LINE_WHILE, black, TRUE);
	//1Pと2Pのアイコン
	DrawGraph(BOX_START_POS_X, BOX_START_POS_Y, Texture1P, TRUE);
	DrawGraph(POS_2P_X, POS_2P_Y, Texture2P, TRUE);

	//選択後の円
	for (int k = 0; k < 3; k++)
	{
		if (decideFlg[0][k] && I_flg[0][k])
		{
			if (baseStatus[0].SKILLID.size() <= k) continue;
			if (sideFlg[0][k] == false)
			{
				DrawCircle(CIRCLE_SECOND_POS_X + baseStatus[0].SKILLID[k] * CIRCLE_BETWEEN, CIRCLE_SECOND_POS_Y + decidePositionY[0][k] * CIRCLE_BETWEEN, CIRCLE_R_ORIGIN + 5, Selred, TRUE);
			}
			else
			{
				DrawCircle(CIRCLE_START_POS_X + baseStatus[0].SKILLID[k] * CIRCLE_BETWEEN, CIRCLE_START_POS_Y + decidePositionY[0][k] * CIRCLE_BETWEEN, CIRCLE_R_ORIGIN + 5, Selred, TRUE);
			}

			DrawExtendGraphF(
				SELECT_P1_CIRCLE_X - SELECT_CIRCLE_R,
				SELECT_CIRCLE_Y + (k * SELECT_CIRCLE_OFFSET) - SELECT_CIRCLE_R,
				SELECT_P1_CIRCLE_X + SELECT_CIRCLE_R,
				SELECT_CIRCLE_Y + (k * SELECT_CIRCLE_OFFSET) + SELECT_CIRCLE_R,
				tdata->GetTextureHandle(baseStatus[0].SKILLID[k]),
				1);
		}
		if (decideFlg[1][k] && I_flg[1][k])
		{
			if (baseStatus[1].SKILLID.size() <= k) continue;
			if (sideFlg[1][k] == false)
			{
				DrawCircle(CIRCLE_SECOND_POS_X + baseStatus[1].SKILLID[k] * CIRCLE_BETWEEN , CIRCLE_SECOND_POS_Y + decidePositionY[1][k] * CIRCLE_BETWEEN, CIRCLE_R_ORIGIN, Selblue, TRUE);
			}
			else
			{
				DrawCircle(CIRCLE_START_POS_X + baseStatus[1].SKILLID[k] * CIRCLE_BETWEEN , CIRCLE_START_POS_Y + decidePositionY[1][k] * CIRCLE_BETWEEN, CIRCLE_R_ORIGIN, Selblue, TRUE);
			}
			DrawExtendGraphF(
				SELECT_P2_CIRCLE_X - SELECT_CIRCLE_R,
				SELECT_CIRCLE_Y + (k * SELECT_CIRCLE_OFFSET) - SELECT_CIRCLE_R,
				SELECT_P2_CIRCLE_X + SELECT_CIRCLE_R,
				SELECT_CIRCLE_Y + (k * SELECT_CIRCLE_OFFSET) + SELECT_CIRCLE_R,
				tdata->GetTextureHandle(baseStatus[1].SKILLID[k]),
				1);
		}
	}

	//	アイテム画像
	for (int j = 0; j < 2; j++)
	{
		if (j % 2 == 0)
		{
			for (int i = 0; i < 9; i++)
			{
				DrawExtendGraphF(
					CIRCLE_START_POS_X + i * CIRCLE_BETWEEN - CIRCLE_R_ORIGIN,
					CIRCLE_START_POS_Y + j * CIRCLE_BETWEEN - CIRCLE_R_ORIGIN,
					CIRCLE_START_POS_X + i * CIRCLE_BETWEEN + CIRCLE_R_ORIGIN,
					CIRCLE_START_POS_Y + j * CIRCLE_BETWEEN + CIRCLE_R_ORIGIN,
					tdata->GetTextureHandle(i),
					1);
			}
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				DrawExtendGraphF(
					CIRCLE_SECOND_POS_X + i * CIRCLE_BETWEEN - CIRCLE_R_ORIGIN,
					CIRCLE_SECOND_POS_Y + j * CIRCLE_BETWEEN - CIRCLE_R_ORIGIN,
					CIRCLE_SECOND_POS_X + i * CIRCLE_BETWEEN + CIRCLE_R_ORIGIN,
					CIRCLE_SECOND_POS_Y + j * CIRCLE_BETWEEN + CIRCLE_R_ORIGIN,
					tdata->GetTextureHandle(i),
					1);
			}
		}
	}


	////デバック用のステータス１
	//DrawFormatString(BOX_START_POS_X + 100, 250 + 100, black, "%d", baseStatus[0].HP);
	//DrawFormatString(BOX_START_POS_X + 100, 250 + 200, black, "%d", baseStatus[0].ATK);
	//DrawFormatString(BOX_START_POS_X + 100, 250 + 300, black, "%d", baseStatus[0].DEF);
	//DrawFormatString(BOX_START_POS_X + 100, 250 + 400, black, "%d", baseStatus[0].WEI);
	////デバック用のステータス２
	//DrawFormatString(BOX_START_POS_X + 700, 250 + 100, black, "%d", baseStatus[1].HP);
	//DrawFormatString(BOX_START_POS_X + 700, 250 + 200, black, "%d", baseStatus[1].ATK);
	//DrawFormatString(BOX_START_POS_X + 700, 250 + 300, black, "%d", baseStatus[1].DEF);
	//DrawFormatString(BOX_START_POS_X + 700, 250 + 400, black, "%d", baseStatus[1].WEI);




	if (flgFor[0] != 3)
	{
		//------------------------------//
		//--ステータスのボックス選択前--//
		//------------------------------//
		for (int i = baseStatus[0].HP; i < baseStatus[0].HP + IngredientState[Ingredient_X[0]].HP; i++)
		{
			DrawBox(STATE_BOX_P1_HP_POS_X - BOX_WHILE * i, STATE_BOX_P1_HP_POS_Y, STATE_BOX_P1_HP_POS_X + STATE_SCALE_BOX_X - BOX_WHILE * i, STATE_BOX_P1_HP_POS_Y + STATE_SCALE_BOX_Y, red, TRUE);
		}
		for (int i = 0; i < baseStatus[0].ATK + IngredientState[Ingredient_X[0]].ATK; i++)
		{
			DrawBox(STATE_BOX_P1_ATK_POS_X - BOX_WHILE * i, STATE_BOX_P1_ATK_POS_Y, STATE_BOX_P1_ATK_POS_X + STATE_SCALE_BOX_X - BOX_WHILE * i, STATE_BOX_P1_ATK_POS_Y + STATE_SCALE_BOX_Y, red, TRUE);
		}
		for (int i = 0; i < baseStatus[0].DEF + IngredientState[Ingredient_X[0]].DEF; i++)
		{
			DrawBox(STATE_BOX_P1_DEF_POS_X - BOX_WHILE * i, STATE_BOX_P1_DEF_POS_Y, STATE_BOX_P1_DEF_POS_X + STATE_SCALE_BOX_X - BOX_WHILE * i, STATE_BOX_P1_DEF_POS_Y + STATE_SCALE_BOX_Y, red, TRUE);
		}
		for (int i = 0; i < baseStatus[0].WEI + IngredientState[Ingredient_X[0]].WEI; i++)
		{
			DrawBox(STATE_BOX_P1_WEI_POS_X - BOX_WHILE * i, STATE_BOX_P1_WEI_POS_Y, STATE_BOX_P1_WEI_POS_X + STATE_SCALE_BOX_X - BOX_WHILE * i, STATE_BOX_P1_WEI_POS_Y + STATE_SCALE_BOX_Y, red, TRUE);
		}
	}
	//------------------------------//
	//--ステータスのボックス選択前--//
	//------------------------------//
	if (flgFor[1] != 3)
	{
		for (int i = 0; i < baseStatus[1].HP + IngredientState[Ingredient_X[1]].HP; i++)
		{
			DrawBox(STATE_BOX_P2_HP_POS_X + BOX_WHILE * i, STATE_BOX_P2_HP_POS_Y, STATE_BOX_P2_HP_POS_X + STATE_SCALE_BOX_X + BOX_WHILE * i, STATE_BOX_P2_HP_POS_Y + STATE_SCALE_BOX_Y, red, TRUE);
		}
		for (int i = 0; i < baseStatus[1].ATK + IngredientState[Ingredient_X[1]].ATK; i++)
		{
			DrawBox(STATE_BOX_P2_ATK_POS_X + BOX_WHILE * i, STATE_BOX_P2_ATK_POS_Y, STATE_BOX_P2_ATK_POS_X + STATE_SCALE_BOX_X + BOX_WHILE * i, STATE_BOX_P2_ATK_POS_Y + STATE_SCALE_BOX_Y, red, TRUE);
		}
		for (int i = 0; i < baseStatus[1].DEF + IngredientState[Ingredient_X[1]].DEF; i++)
		{
			DrawBox(STATE_BOX_P2_DEF_POS_X + BOX_WHILE * i, STATE_BOX_P2_DEF_POS_Y, STATE_BOX_P2_DEF_POS_X + STATE_SCALE_BOX_X + BOX_WHILE * i, STATE_BOX_P2_DEF_POS_Y + STATE_SCALE_BOX_Y, red, TRUE);
		}
		for (int i = 0; i < baseStatus[1].WEI + IngredientState[Ingredient_X[1]].WEI; i++)
		{
			DrawBox(STATE_BOX_P2_WEI_POS_X + BOX_WHILE * i, STATE_BOX_P2_WEI_POS_Y, STATE_BOX_P2_WEI_POS_X + STATE_SCALE_BOX_X + BOX_WHILE * i, STATE_BOX_P2_WEI_POS_Y + STATE_SCALE_BOX_Y, red, TRUE);
		}
	}

	int fontHandle = fdata->GetFontHandle(FontID::BigMainFont);
	int fontSize = GetFontSizeToHandle(fontHandle);
	int drawWidth;

	//ステータスのボックスP1
	for (int i = 0; i < baseStatus[0].HP; i++)
	{
		DrawBox(STATE_BOX_P1_HP_POS_X - BOX_WHILE * i, STATE_BOX_P1_HP_POS_Y, STATE_BOX_P1_HP_POS_X + STATE_SCALE_BOX_X - BOX_WHILE * i, STATE_BOX_P1_HP_POS_Y + STATE_SCALE_BOX_Y , BOX, TRUE);
	}
	for (int i = 0; i < baseStatus[0].ATK; i++)
	{
		DrawBox(STATE_BOX_P1_ATK_POS_X - BOX_WHILE * i, STATE_BOX_P1_ATK_POS_Y, STATE_BOX_P1_ATK_POS_X + STATE_SCALE_BOX_X - BOX_WHILE * i, STATE_BOX_P1_ATK_POS_Y + STATE_SCALE_BOX_Y, BOX, TRUE);
	}
	for (int i = 0; i < baseStatus[0].DEF; i++)
	{
		DrawBox(STATE_BOX_P1_DEF_POS_X - BOX_WHILE * i, STATE_BOX_P1_DEF_POS_Y, STATE_BOX_P1_DEF_POS_X + STATE_SCALE_BOX_X - BOX_WHILE * i, STATE_BOX_P1_DEF_POS_Y + STATE_SCALE_BOX_Y, BOX, TRUE);
	}
	for (int i = 0; i < baseStatus[0].WEI; i++)
	{
		DrawBox(STATE_BOX_P1_WEI_POS_X - BOX_WHILE * i, STATE_BOX_P1_WEI_POS_Y, STATE_BOX_P1_WEI_POS_X + STATE_SCALE_BOX_X - BOX_WHILE * i, STATE_BOX_P1_WEI_POS_Y + STATE_SCALE_BOX_Y, BOX, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "HP");
	DrawFormatStringToHandle(STATE_BOX_P1_HP_POS_X - drawWidth, STATE_BOX_P1_HP_POS_Y + STATE_SCALE_BOX_Y / 2 - fontSize / 2, 0x000000, fontHandle, "HP");
	drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "ATK");
	DrawFormatStringToHandle(STATE_BOX_P1_HP_POS_X - drawWidth, STATE_BOX_P1_ATK_POS_Y + STATE_SCALE_BOX_Y / 2 - fontSize / 2, 0x000000, fontHandle, "ATK");
	drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "DEF");
	DrawFormatStringToHandle(STATE_BOX_P1_HP_POS_X - drawWidth, STATE_BOX_P1_DEF_POS_Y + STATE_SCALE_BOX_Y / 2 - fontSize / 2, 0x000000, fontHandle, "DEF");
	drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "WEIGHT");
	DrawFormatStringToHandle(STATE_BOX_P1_HP_POS_X - drawWidth, STATE_BOX_P1_WEI_POS_Y + STATE_SCALE_BOX_Y / 2 - fontSize / 2, 0x000000, fontHandle, "WEIGHT");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ステータスのボックスP2
	for (int i = 0; i < baseStatus[1].HP; i++)
	{
		DrawBox(STATE_BOX_P2_HP_POS_X + BOX_WHILE * i, STATE_BOX_P2_HP_POS_Y, STATE_BOX_P2_HP_POS_X + STATE_SCALE_BOX_X + BOX_WHILE * i, STATE_BOX_P2_HP_POS_Y + STATE_SCALE_BOX_Y, BOX, TRUE);
	}
	for (int i = 0; i < baseStatus[1].ATK; i++)
	{
		DrawBox(STATE_BOX_P2_ATK_POS_X + BOX_WHILE * i, STATE_BOX_P2_ATK_POS_Y, STATE_BOX_P2_ATK_POS_X + STATE_SCALE_BOX_X + BOX_WHILE * i, STATE_BOX_P2_ATK_POS_Y + STATE_SCALE_BOX_Y, BOX, TRUE);
	}
	for (int i = 0; i < baseStatus[1].DEF; i++)
	{
		DrawBox(STATE_BOX_P2_DEF_POS_X + BOX_WHILE * i, STATE_BOX_P2_DEF_POS_Y, STATE_BOX_P2_DEF_POS_X + STATE_SCALE_BOX_X + BOX_WHILE * i, STATE_BOX_P2_DEF_POS_Y + STATE_SCALE_BOX_Y, BOX, TRUE);
	}
	for (int i = 0; i < baseStatus[1].WEI; i++)
	{
		DrawBox(STATE_BOX_P2_WEI_POS_X + BOX_WHILE * i, STATE_BOX_P2_WEI_POS_Y, STATE_BOX_P2_WEI_POS_X + STATE_SCALE_BOX_X + BOX_WHILE * i, STATE_BOX_P2_WEI_POS_Y + STATE_SCALE_BOX_Y, BOX, TRUE);
	}

	for (int i = 0; i < 9; i++)
	{
		DrawGraph(CIRCLE_START_POS_X + (i * CIRCLE_BETWEEN), CIRCLE_START_POS_Y * CIRCLE_BETWEEN, Ingredient[i]->GetTexture(), TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "HP");
	DrawFormatStringToHandle(STATE_BOX_P2_HP_POS_X, STATE_BOX_P2_HP_POS_Y + STATE_SCALE_BOX_Y / 2 - fontSize / 2, 0x000000, fontHandle, "HP");
	drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "ATK");
	DrawFormatStringToHandle(STATE_BOX_P2_HP_POS_X, STATE_BOX_P2_ATK_POS_Y + STATE_SCALE_BOX_Y / 2 - fontSize / 2, 0x000000, fontHandle, "ATK");
	drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "DEF");
	DrawFormatStringToHandle(STATE_BOX_P2_HP_POS_X, STATE_BOX_P2_DEF_POS_Y + STATE_SCALE_BOX_Y / 2 - fontSize / 2, 0x000000, fontHandle, "DEF");
	drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "WEIGHT");
	DrawFormatStringToHandle(STATE_BOX_P2_HP_POS_X, STATE_BOX_P2_WEI_POS_Y + STATE_SCALE_BOX_Y / 2 - fontSize / 2, 0x000000, fontHandle, "WEIGHT");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void IngredientsSelect::Finalize()
{
	delete[] Ingredient;
}

int IngredientsSelect::GetFlg(int id,int kind)
{
	return I_flg[id][kind];
}

BaseStatus* IngredientsSelect::GetStatas()
{
	return baseStatus;
}