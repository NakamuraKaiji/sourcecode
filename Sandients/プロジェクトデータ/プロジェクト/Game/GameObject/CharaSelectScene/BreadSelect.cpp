#include "BreadSelect.h"
#include "../../GameDatas/ControllerInput.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>

#define COLUMN			5
#define RAW				9

BreadSelect::BreadSelect()
{
}

BreadSelect::~BreadSelect()
{
	
}

void BreadSelect::Initialize(GameSystemObjects* system)
{
	this->system = system;

	std::ifstream ifs;
	//ファイルを読み取り専用で開く
	ifs.open("Resources/csv/BreadState.csv", std::ios::in | std::ios::binary);
	//ファイルが開けなかった場合はエラーメッセージを出す
	if (!ifs)
	{
		MessageBoxA(0, "ファイルを開けませんでした。", NULL, MB_OK);
	}

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
				break;
			case 1:
				SBread[x].HP = num;
				break;
			case 2:
				SBread[x].ATK = num;
				break;
			case 3:
				SBread[x].DEF = num;
				break;
			case 4:
				SBread[x].WEI = num;
				break;
			case 5:
				SBread[x].CD = num;
			default:
				break;
			}
		}
	}
	//開いたファイルを閉じる
	ifs.close();

	Bread[0] = new Square(SBread[0], 0);
	Bread[1] = new Mountain(SBread[1], 1);
	Bread[2] = new France(SBread[2], 2);
	Bread[3] = new Koppe(SBread[3], 3);
	Bread[4] = new Waffle(SBread[4], 4);
	Bread[5] = new Tortilla(SBread[5], 5);
	Bread[6] = new Vans(SBread[6], 6);
	Bread[7] = new Muffin(SBread[7], 7);
	Bread[8] = new Bagel(SBread[8], 8);

	B_flg[0] = false;
	B_flg[1] = false;

	bread_Id[0] = 0;
	bread_Id[1] = 0;

	BreadTextures[0] = LoadGraph("Resources/Textures/Vege1_pumpkin.png");
	BreadTextures[1] = LoadGraph("Resources/Textures/Vege2_cabbage.png");
	BreadTextures[2] = LoadGraph("Resources/Textures/Vege3_cucumber.png");
	BreadTextures[3] = LoadGraph("Resources/Textures/Vege4_radish.png");
	BreadTextures[4] = LoadGraph("Resources/Textures/Vege5_tomato.png");
	BreadTextures[5] = LoadGraph("Resources/Textures/Vege6_greenbellpepper.png");
	BreadTextures[6] = LoadGraph("Resources/Textures/Vege7_pickles.png");
	BreadTextures[7] = LoadGraph("Resources/Textures/Vege8_lettuce1.png");
	BreadTextures[8] = LoadGraph("Resources/Textures/Vege9_onion.png");

	Chara_Cooltime[0] = 0.0f;
	Chara_Cooltime[1] = 0.0f;
}

void BreadSelect::Update(float deltatime)
{
	for (int i = 0; i < 2; i++)
	{
		Chara_Cooltime[i] -= deltatime;
		if (Chara_Cooltime[i] < 0.0f)
		{
			Chara_Cooltime[i] = 0.0f;
		}

	}
		//プレーヤー1のパン選択
		if (!B_flg[0])
		{
			if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::RIGHT) && Chara_Cooltime[0] <= 0.0f)
			{
				Chara_Cooltime[0] = 0.3f;
				bread_Id[0] += 1;
				if (bread_Id[0] > 8)
				{
					bread_Id[0] = 0;
				}
			}
			if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::LEFT) && Chara_Cooltime[0] <= 0.0f)
			{
				Chara_Cooltime[0] = 0.3f;
				bread_Id[0] -= 1;
				if (bread_Id[0] < 0)
				{
					bread_Id[0] = 8;
				}
			}

		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::CIRCLE))
		{
			B_flg[0] = true;
		}
		if (B_flg[0] == true)
		{
			if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::CROSS))
			{
				B_flg[0] = false;
			}
		}
		if (!B_flg[1])
		{
			if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::RIGHT) && Chara_Cooltime[1] <= 0.0f)
			{
				Chara_Cooltime[1] = 0.3f;
				bread_Id[1] += 1;
				if (bread_Id[1] > 8)
				{
					bread_Id[1] = 0;
				}
			}
			if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::LEFT) && Chara_Cooltime[1] <= 0.0f)
			{
				Chara_Cooltime[1] = 0.3f;
				bread_Id[1] -= 1;
				if (bread_Id[1] < 0)
				{
					bread_Id[1] = 8;
				}
			}

		}
		if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::CIRCLE))
		{
			B_flg[1] = true;
		}
		if (B_flg[1] == true)
		{
			if (system->GetInputSystem().IsButtonDown(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::CROSS))
			{
				B_flg[1] = false;
			}
		}

}

void BreadSelect::Render()
{
	// 透過色を変更
	SetTransColor(255, 255, 255);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "パン番号：%d", bread_Id[0]);
	DrawFormatString(100, 200, GetColor(255, 255, 255), "HP：%d", Bread[bread_Id[0]]->GetHP());
	DrawFormatString(100, 300, GetColor(255, 255, 255), "ATK：%d", Bread[bread_Id[0]]->GetATK());
	DrawFormatString(100, 400, GetColor(255, 255, 255), "ATK：%d", Bread[bread_Id[0]]->GetDEF());
	DrawFormatString(100, 500, GetColor(255, 255, 255), "ATK：%d", Bread[bread_Id[0]]->GetWEI());
	DrawGraph(100,600,BreadTextures[bread_Id[0]],FALSE);
	DrawFormatString(800, 100, GetColor(255, 255, 255), "パン番号：%d", bread_Id[1]);
	DrawFormatString(800, 200, GetColor(255, 255, 255), "HP：%d", Bread[bread_Id[1]]->GetHP());
	DrawFormatString(800, 300, GetColor(255, 255, 255), "ATK：%d", Bread[bread_Id[1]]->GetATK());
	DrawFormatString(800, 400, GetColor(255, 255, 255), "ATK：%d", Bread[bread_Id[1]]->GetDEF());
	DrawFormatString(800, 500, GetColor(255, 255, 255), "ATK：%d", Bread[bread_Id[1]]->GetWEI());
	DrawGraph(800, 600, BreadTextures[bread_Id[1]], FALSE);

}

void BreadSelect::Finalize()
{
	delete[] Bread;
}

int BreadSelect::GetFlg(int id)
{
	return B_flg[id];
}
