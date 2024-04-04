//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	ResultScene
//		結果
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#include <DxLib.h>
#include "ResultScene.h"
#include "../GameDatas/ControllerInput.h"

//	UI
//	勝利者表示
#define P1_WINNER_X				350
#define WINNER_TEXT_COLOR		0xffffff
#define NO_WINNER_BOX_COLOR		0xdddddd
#define P1_WINNER_BOX_COLOR		0xff9999
#define P2_WINNER_BOX_COLOR		0x99ff99
#define WINNER_GRAPH_Y			490

//	スコア
#define P1_SCORE_BOX_X			350
#define P2_SCORE_BOX_X			1570
#define SCORE_BOX_MAX_Y			950
#define SCORE_BOX_WIDTH			600
#define SCORE_BOX_OUT_WIDTH		5
#define SCORE_BOX_COLOR	        0xffffff
#define SCORE_BOX_OUT_COLOR	    0x44ff44
#define SCORE_BOX_TEXT_COLOR	0xffffff

//	準備
#define P1_READY_BOX_COLOR		0xff0000
#define P2_READY_BOX_COLOR		0x00ff00
#define READY_BOX_WIDTH			550
#define READY_BOX_HEIGHT		100
#define READY_BOX_TEXT_COLOR	0xffffff

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// コンストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
ResultScene::ResultScene() :
	BaseScene(),
	p1Ready(),
	p2Ready()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// デストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
ResultScene::~ResultScene()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 初期化
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void ResultScene::Initialize()
{
	sdata->resultSE();
	p1Ready = false;
	p2Ready = false;
	switch (score->GetWinPID())
	{
	case -1:
		sdata->You_Lose();
		break;
	default:
		sdata->You_Win();
		break;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 更新処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void ResultScene::Update()
{
	if (system->GetInputSystem().IsButtonPressed(system->GetInputSystem().GetPlayerInputNum()[0], DualShock4Input::CIRCLE))
	{
		sdata->Ready();
		p1Ready = true;
	}
	if (system->GetInputSystem().IsButtonPressed(system->GetInputSystem().GetPlayerInputNum()[1], DualShock4Input::CIRCLE))
	{
		sdata->Ready();
		p2Ready = true;
	}


	//	シーン切り替え
	if (p1Ready && p2Ready)
	{
		ChangeScene(SceneID::CharaSelect);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 描画処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void ResultScene::Render()
{
	//	フォントハンドル一時保存用
	int drawFontHandle;
	//	文字の長さ用取得用
	int drawWidth;
	//	文字の大きさ取得用
	int drawFontSize;

	DrawGraph(0, 0, tdata->GetTextureHandle(static_cast<int>(ResultSceneTexture::Back)), 1);
	
	//	勝利者表示
	drawFontHandle = fdata->GetFontHandle(FontID::SuperUltraBigEdgeMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);

	switch (score->GetWinPID())
	{
	case -1:
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "Draw");
		DrawOvalAA(screenWidth / 2 , drawFontSize, drawWidth / 2 , drawFontSize / 2 * 1.7, 30, NO_WINNER_BOX_COLOR, 1);
		DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, drawFontSize / 2, WINNER_TEXT_COLOR, drawFontHandle, "Draw");
		break;
	case 0:
		DrawRotaGraphF(1 * screenWidth / 3, WINNER_GRAPH_Y, 3.0, 210.0f * 180.0f / DX_PI_F, tdata->GetTextureHandle(static_cast<int>(ResultSceneTexture::Player)), 1);
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "WINNER!");
		DrawOvalAA(drawWidth / 2, drawFontSize, drawWidth / 2, drawFontSize / 2 * 1.7, 30, P1_WINNER_BOX_COLOR, 1);
		DrawFormatStringToHandle(0, drawFontSize / 2, WINNER_TEXT_COLOR ,drawFontHandle, "WINNER!");
		break;																						  
	case 1:		
		DrawRotaGraphF(2 * screenWidth / 3, WINNER_GRAPH_Y, 3.0, 210.0f * 180.0f / DX_PI_F, tdata->GetTextureHandle(static_cast<int>(ResultSceneTexture::Player)), 1, 1);
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "WINNER!");				 
		DrawOvalAA(screenWidth - drawWidth / 2, drawFontSize, drawWidth / 2, drawFontSize / 2 * 1.7, 30, P2_WINNER_BOX_COLOR, 1);
		DrawFormatStringToHandle(screenWidth - drawWidth, drawFontSize / 2, WINNER_TEXT_COLOR ,drawFontHandle, "WINNER!");
		break;
	}

	//	スコア表示
	drawFontHandle = fdata->GetFontHandle(FontID::SuperBigEdgeMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	int p1ScoreBoxHeight = drawFontSize * 1.5;
	int p2ScoreBoxHeight = drawFontSize * 1.5;

	drawFontHandle = fdata->GetFontHandle(FontID::BigMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	p1ScoreBoxHeight += drawFontSize * (score->GetScore(0).useSkillNum.size() + 1);
	p2ScoreBoxHeight += drawFontSize * (score->GetScore(1).useSkillNum.size() + 1);

	DrawBox(P1_SCORE_BOX_X - SCORE_BOX_WIDTH / 2 - SCORE_BOX_OUT_WIDTH, SCORE_BOX_MAX_Y - p1ScoreBoxHeight - SCORE_BOX_OUT_WIDTH, P1_SCORE_BOX_X + SCORE_BOX_WIDTH / 2 + SCORE_BOX_OUT_WIDTH, SCORE_BOX_MAX_Y + SCORE_BOX_OUT_WIDTH, SCORE_BOX_OUT_COLOR, 1);
	DrawBox(P2_SCORE_BOX_X - SCORE_BOX_WIDTH / 2 - SCORE_BOX_OUT_WIDTH, SCORE_BOX_MAX_Y - p2ScoreBoxHeight - SCORE_BOX_OUT_WIDTH, P2_SCORE_BOX_X + SCORE_BOX_WIDTH / 2 + SCORE_BOX_OUT_WIDTH, SCORE_BOX_MAX_Y + SCORE_BOX_OUT_WIDTH, SCORE_BOX_OUT_COLOR, 1);
	DrawBox(P1_SCORE_BOX_X - SCORE_BOX_WIDTH / 2, SCORE_BOX_MAX_Y - p1ScoreBoxHeight, P1_SCORE_BOX_X + SCORE_BOX_WIDTH / 2, SCORE_BOX_MAX_Y, SCORE_BOX_COLOR, 1);
	DrawBox(P2_SCORE_BOX_X - SCORE_BOX_WIDTH / 2, SCORE_BOX_MAX_Y - p2ScoreBoxHeight, P2_SCORE_BOX_X + SCORE_BOX_WIDTH / 2, SCORE_BOX_MAX_Y, SCORE_BOX_COLOR, 1);
	
	drawFontHandle = fdata->GetFontHandle(FontID::SuperBigEdgeMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1スコア");
	DrawFormatStringToHandle(P1_SCORE_BOX_X - SCORE_BOX_WIDTH / 2, SCORE_BOX_MAX_Y - p1ScoreBoxHeight, SCORE_BOX_TEXT_COLOR, drawFontHandle, "P1スコア");
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P2スコア");
	DrawFormatStringToHandle(P2_SCORE_BOX_X - SCORE_BOX_WIDTH / 2, SCORE_BOX_MAX_Y - p2ScoreBoxHeight, SCORE_BOX_TEXT_COLOR, drawFontHandle, "P2スコア");

	int drawP1StartScoreY = SCORE_BOX_MAX_Y - p1ScoreBoxHeight + drawFontSize * 1.5;
	int drawP2StartScoreY = SCORE_BOX_MAX_Y - p2ScoreBoxHeight + drawFontSize * 1.5;

	drawFontHandle = fdata->GetFontHandle(FontID::BigMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "与えたダメージ:%.1f", score->GetScore(1).hitedDamage);
	DrawFormatStringToHandle(P1_SCORE_BOX_X - drawWidth / 2, drawP1StartScoreY - drawFontSize / 2, SCORE_BOX_TEXT_COLOR, drawFontHandle, "与えたダメージ:%.1f", score->GetScore(1).hitedDamage);

	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "与えたダメージ:%.1f", score->GetScore(0).hitedDamage);
	DrawFormatStringToHandle(P2_SCORE_BOX_X - drawWidth / 2, drawP2StartScoreY - drawFontSize / 2, SCORE_BOX_TEXT_COLOR, drawFontHandle, "与えたダメージ:%.1f", score->GetScore(0).hitedDamage);

	for (size_t i = 0; i < score->GetScore(0).useSkillNum.size(); i++)
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "スキル%d使用数:%d回", i + 1, score->GetScore(0).useSkillNum[i]);
		DrawFormatStringToHandle(P1_SCORE_BOX_X - drawWidth / 2, drawP1StartScoreY - drawFontSize / 2 + drawFontSize * (i + 1), SCORE_BOX_TEXT_COLOR, drawFontHandle, "スキル%d使用数:%d回", i, score->GetScore(0).useSkillNum[i]);
	}
	for (size_t i = 0; i < score->GetScore(1).useSkillNum.size(); i++)
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "スキル%d使用数:%d回", i + 1, score->GetScore(1).useSkillNum[i]);
		DrawFormatStringToHandle(P2_SCORE_BOX_X - drawWidth / 2, drawP2StartScoreY - drawFontSize / 2 + drawFontSize * (i + 1), SCORE_BOX_TEXT_COLOR, drawFontHandle, "スキル%d使用数:%d回", i, score->GetScore(1).useSkillNum[i]);
	}

	//	READY!
	DrawBox(0, screenHeight, READY_BOX_WIDTH, screenHeight - READY_BOX_HEIGHT, P1_READY_BOX_COLOR, 1);
	DrawBox(screenWidth, screenHeight, screenWidth - READY_BOX_WIDTH, screenHeight - READY_BOX_HEIGHT, P2_READY_BOX_COLOR, 1);
	drawFontHandle = fdata->GetFontHandle(FontID::BigMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	if (p1Ready)
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1Ready!");
		DrawFormatStringToHandle(READY_BOX_WIDTH / 2 - drawWidth / 2, screenHeight - READY_BOX_HEIGHT / 2 - drawFontSize / 2, READY_BOX_TEXT_COLOR, drawFontHandle, "P1Ready!");
	}
	else
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "Press Circle");
		DrawFormatStringToHandle(READY_BOX_WIDTH / 2 - drawWidth / 2, screenHeight - READY_BOX_HEIGHT / 2 - drawFontSize / 2, READY_BOX_TEXT_COLOR, drawFontHandle, "Press Circle");
	}

	if (p2Ready)
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P2Ready!");
		DrawFormatStringToHandle(screenWidth - READY_BOX_WIDTH / 2 - drawWidth / 2, screenHeight - READY_BOX_HEIGHT / 2 - drawFontSize / 2, READY_BOX_TEXT_COLOR, drawFontHandle, "P2Ready!");
	}
	else
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "Press Circle");
		DrawFormatStringToHandle(screenWidth - READY_BOX_WIDTH / 2 - drawWidth / 2, screenHeight - READY_BOX_HEIGHT / 2 - drawFontSize / 2, READY_BOX_TEXT_COLOR, drawFontHandle, "Press Circle");
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 解放処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void ResultScene::Finalize()
{
}