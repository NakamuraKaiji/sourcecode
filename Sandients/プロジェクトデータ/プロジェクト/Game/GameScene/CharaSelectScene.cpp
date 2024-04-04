//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	CharaSelectScene
//		具材選択
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#include <DxLib.h>
#include "CharaSelectScene.h"
#include "../GameDatas/ControllerInput.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// コンストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
CharaSelectScene::CharaSelectScene() :
	BaseScene(),
	back()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// デストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
CharaSelectScene::~CharaSelectScene()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 初期化
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void CharaSelectScene::Initialize()
{
	//breadSelect.Initialize(system);
	ingredientsSelect.Initialize(system, tdata, fdata, sdata);
	back = false;
	sdata->SelectBGM();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 更新処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void CharaSelectScene::Update()
{
	if (system->GetInputSystem().IsButtonPressed(DualShock4Input::OPTIONS))
	{
		sdata->Select();
		if (back) back = false;
		else back = true;
	}

	if (back)
	{
		if (system->GetInputSystem().IsButtonPressed(DualShock4Input::CIRCLE))
		{
			sdata->Decision();
			ChangeScene(SceneID::Title);
		}
		if (system->GetInputSystem().IsButtonPressed(DualShock4Input::CROSS))
		{
			sdata->Select();
			back = false;
		}
		return;
	}
	float deltatime = system->GetTimerSystem().GetFrameDeltaTime();
	//breadSelect.Update(deltatime);
	//if (breadSelect.GetFlg(0) && breadSelect.GetFlg(1))
	//{
	bool Flg[2][3];
		ingredientsSelect.Update(deltatime);

		for (int i = 0; i < 3; i++)
		{
			for (int h = 0; h < 2; h++)
			{
				Flg[h][i] = ingredientsSelect.GetFlg(h, i);
			}
		}
		if (Flg[0][0] && Flg[0][1] && Flg[0][2] && Flg[1][0] && Flg[1][1] && Flg[1][2])
		{
			ChangeScene(SceneID::Play);
			ingredientsSelect.GetStatas()[0];
			score->SetStatas(0, Statas{ ingredientsSelect.GetStatas()[0].HP,ingredientsSelect.GetStatas()[0].ATK,ingredientsSelect.GetStatas()[0].DEF,ingredientsSelect.GetStatas()[0].WEI,ingredientsSelect.GetStatas()[0].SKILLID });
			score->SetStatas(1, Statas{ ingredientsSelect.GetStatas()[1].HP,ingredientsSelect.GetStatas()[1].ATK,ingredientsSelect.GetStatas()[1].DEF,ingredientsSelect.GetStatas()[1].WEI,ingredientsSelect.GetStatas()[1].SKILLID });
		}
	//}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 描画処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void CharaSelectScene::Render()
{
	//breadSelect.Render();
	//if (breadSelect.GetFlg(0) && breadSelect.GetFlg(1))
	//{
		ingredientsSelect.Render();
	//}
		int fontHandle = fdata->GetFontHandle(FontID::BigMainFont);
		int fontSize = GetFontSizeToHandle(fontHandle);
		int drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "具材を3つまで選んで！");
		DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, 0, 0xffffff, fontHandle, "具材を3つまで選んで！");

		if (back)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawBox(0, 0, screenWidth, screenHeight, 0x000000, 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			int fontHandle = fdata->GetFontHandle(FontID::SuperUltraBigEdgeMainFont);
			int fontSize = GetFontSizeToHandle(fontHandle);
			int drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "タイトルへ戻りますか？");
			DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, screenHeight / 2 - fontSize / 2, 0xffffff, fontHandle, "タイトルへ戻りますか？");

			drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "×：閉じる");
			DrawFormatStringToHandle(1 * screenWidth / 4 - drawWidth / 2, 2 * screenHeight / 3 - fontSize / 2, 0xffffff, fontHandle, "×：閉じる");
			drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "○：タイトルへ");
			DrawFormatStringToHandle(3 * screenWidth / 4 - drawWidth / 2, 2 * screenHeight / 3 - fontSize / 2, 0xffffff, fontHandle, "○：タイトルへ");
		}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 解放処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void CharaSelectScene::Finalize()
{
	sdata->StopSelectBGM();
}

