//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	TitleScene
//		タイトルを描画するシーン
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#include <DxLib.h>
#include "TitleScene.h"

#define		VEGE_POP			1.5f
#define		LOGO_POS_X			460
#define		LOGO_POS_Y			200

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// コンストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
TitleScene::TitleScene() :
	Back(0),
	VegePos_Y(0),
	L_VegePos_X(0),
	R_VegePos_X(0),
	Yellow(0),
	Logo(0),
	Matte(0),
	L_fall(0),
	L_fall2(0),
	L_fall3(0),
	L_rand(0),
	L_rand2(0),
	L_rand3(0),
	R_fall(0),
	R_fall2(0),
	R_fall3(0),
	R_rand(0),
	R_rand2(0),
	R_rand3(0),
	counter(0.0f),
	count(0),
	alpha(0),
	back(),
	Vegetables{},
	BaseScene()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// デストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
TitleScene::~TitleScene()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 初期化
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void TitleScene::Initialize()
{
	Vegetables[0] = NULL;
	Vegetables[1] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege1));
	Vegetables[2] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege2));
	Vegetables[3] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege3));
	Vegetables[4] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege4));
	Vegetables[5] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege5));
	Vegetables[6] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege6));
	Vegetables[7] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege7));
	Vegetables[8] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege8));
	Vegetables[9] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege9));
	Vegetables[10] = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Vege10));

	Back = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Back));
	Yellow = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Yellow));
	Logo = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Logo));
	Matte = tdata->GetTextureHandle(static_cast<int>(TitleSceneTexture::Matto));

	L_rand = 0;
	L_rand2 = 0;
	L_rand3 = 0;

	R_rand = 0;
	R_rand2 = 0;
	R_rand3 = 0;

	counter = 0.0f;

	L_VegePos_X = 25;
	R_VegePos_X = 1395;

	VegePos_Y = -400;

	L_fall = 0;
	L_fall2 = 0;
	L_fall3 = 0;

	R_fall = 0;
	R_fall2 = 0;
	R_fall3 = 0;

	count = 0;

	alpha = 150;

	back = false;

	sdata->TitleBGM();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 更新処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void TitleScene::Update()
{
	if (back)
	{
		if (system->GetInputSystem().IsButtonPressed(DualShock4Input::CIRCLE))
		{
			sdata->Decision();
			ChangeScene(SceneID::EndGame);
		}

		if (system->GetInputSystem().IsButtonPressed(DualShock4Input::CROSS))
		{
			sdata->Select();
			back = false;
		}

		return;
	}
	//	シーン切り替えデバッグ用
	if (system->GetInputSystem().IsButtonPressed(DualShock4Input::CIRCLE))
	{
		sdata->Decision();
		ChangeScene(SceneID::CharaSelect);
	}
	if (system->GetInputSystem().IsButtonPressed(DualShock4Input::CROSS) || system->GetInputSystem().IsButtonPressed(DualShock4Input::OPTIONS))
	{
		sdata->Select();
		back = true;
	}

	counter += 0.016;
	count++;
	if (count >= 100)	count -= 100;

	if (L_fall == 3 || L_fall + VegePos_Y >= 1180)		L_rand = GetRand(9) + 1;
	if (L_fall2 == 3 || L_fall2 + VegePos_Y >= 1180)	L_rand2 = GetRand(9) + 1;
	if (L_fall3 == 3 || L_fall3 + VegePos_Y >= 1180)	L_rand3 = GetRand(9) + 1;

	if (R_fall == 3 || R_fall + VegePos_Y >= 1180)		R_rand = GetRand(9) + 1;
	if (R_fall2 == 3 || R_fall2 + VegePos_Y >= 1180)	R_rand2 = GetRand(9) + 1;
	if (R_fall3 == 3 || R_fall3 + VegePos_Y >= 1180)	R_rand3 = GetRand(9) + 1;


	while (1)
	{
		if (L_rand == L_rand2)			L_rand2 = GetRand(9) + 1;
		else if (L_rand2 == L_rand3)	L_rand3 = GetRand(9) + 1;
		else if (L_rand3 == L_rand)		L_rand  = GetRand(9) + 1;
		else break;
	}

	while (1)
	{
		if (R_rand == R_rand2)			R_rand2 = GetRand(9) + 1;
		else if (R_rand2 == R_rand3)	R_rand3 = GetRand(9) + 1;
		else if (R_rand3 == R_rand)		R_rand  = GetRand(9) + 1;
		else break;
	}



	L_fall += 3;
	if (counter >= 3.0f)	L_fall2 += 3;
	if (counter >= 6.0f)	L_fall3 += 3;
	if (counter >= 1.5f)	R_fall += 3;
	if (counter >= 4.5f)	R_fall2 += 3;
	if (counter >= 7.5f)	R_fall3 += 3;


	if (L_fall + VegePos_Y >= 1180)		L_fall = 0;
	if (L_fall2 + VegePos_Y >= 1180)	L_fall2 = 0;
	if (L_fall3 + VegePos_Y >= 1180)	L_fall3 = 0;
	if (R_fall + VegePos_Y >= 1180)		R_fall = 0;
	if (R_fall2 + VegePos_Y >= 1180)	R_fall2 = 0;
	if (R_fall3 + VegePos_Y >= 1180)	R_fall3 = 0;

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 描画処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void TitleScene::Render()
{
	DrawExtendGraph(0, 0, screenWidth, screenHeight, Back, 1);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, alpha);
	DrawExtendGraph(0, 0, screenWidth, screenHeight, Yellow, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawExtendGraph(screenWidth / 2 - 600, screenHeight / 2 - 300, screenWidth / 2 + 600, screenHeight / 2 + 300, Matte, 1);


	DrawFormatString(0, 0, 0xffffff, "TitleScene");

	DrawGraph(LOGO_POS_X, LOGO_POS_Y, Logo, 1);

	DrawGraph(L_VegePos_X, VegePos_Y  + L_fall, Vegetables[L_rand] , 1);
	DrawGraph(L_VegePos_X, VegePos_Y + L_fall2, Vegetables[L_rand2], 1);
	DrawGraph(L_VegePos_X, VegePos_Y + L_fall3, Vegetables[L_rand3], 1);

	DrawGraph(R_VegePos_X, VegePos_Y + R_fall,  Vegetables[R_rand], 1);
	DrawGraph(R_VegePos_X, VegePos_Y + R_fall2, Vegetables[R_rand2], 1);
	DrawGraph(R_VegePos_X, VegePos_Y + R_fall3, Vegetables[R_rand3], 1);

	//	デフォルトサイズ
	int defaultFontSize = GetFontSize();
	SetFontSize(64);
	int drawwidth = GetDrawFormatStringWidth("");
	//DrawBox(screenWidth / 2 - drawwidth / 2, 800, screenWidth / 2 + drawwidth / 2, 850, 0xffffff, true);
	if (count >= 50) DrawFormatString(screenWidth / 2 - drawwidth / 2, 800, 0xFF3333, "");
	//	デフォルトサイズに戻す
	SetFontSize(defaultFontSize);

	int fontHandle = fdata->GetFontHandle(FontID::SuperUltraBigEdgeMainFont);
	int fontSize = GetFontSizeToHandle(fontHandle);
	int drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "○でスタート");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
	DrawBox(
		screenWidth / 2 - drawWidth / 2,
		3 * screenHeight / 4 - fontSize / 2, 
		screenWidth / 2 + drawWidth / 2,
		3 * screenHeight / 4 + fontSize / 2,
		0x000000, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, 3 * screenHeight / 4 - fontSize / 2, 0xffffff, fontHandle,"○でスタート");

	if (back)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, screenWidth, screenHeight, 0x000000, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		int fontHandle = fdata->GetFontHandle(FontID::SuperUltraBigEdgeMainFont);
		int fontSize = GetFontSizeToHandle(fontHandle);
		int drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "ゲームを終了しますか？");
		DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, screenHeight / 2 - fontSize / 2, 0xffffff, fontHandle, "ゲームを終了しますか？");

		drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "×：タイトル");
		DrawFormatStringToHandle(1 * screenWidth / 4 - drawWidth / 2, 2 * screenHeight / 3 - fontSize / 2, 0xffffff, fontHandle, "×：タイトル");
		drawWidth = GetDrawFormatStringWidthToHandle(fontHandle, "○：終了");
		DrawFormatStringToHandle(3 * screenWidth / 4 - drawWidth / 2, 2 * screenHeight / 3 - fontSize / 2, 0xffffff, fontHandle, "○：終了");
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 解放処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void TitleScene::Finalize()
{
	sdata->StopTitleBGM();
}