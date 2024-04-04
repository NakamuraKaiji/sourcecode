//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	Game.h
//		ゲームで行う実際の処理を呼び出すため、実際にクラス内へ処理を記述するためのファイル。
//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#include <DxLib.h>
#include "Game.h"
#include "GameDatas/ControllerInput.h"
#include "GameScene/LogoScene.h"
#include "GameScene/TitleScene.h"
#include "GameScene/ModeSelectScene.h"
#include "GameScene/CharaSelectScene.h"
#include "GameScene/PlayScene.h"
#include "GameScene/ResultScene.h"


const SceneID DEF_SCENE = SceneID::Logo;	//	最初のシーン設定

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// コンストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Game::Game() :
	screenWidth(0),
	screenHeight(0),
	system(nullptr),
	nowScene(nullptr),
	endGameFlag(false),
	score(),
	padSetting(),
	padSetP1(),
	padSetP2()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// デストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Game::~Game()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 初期化処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::Initialize(int screenwidth, int screenheight)
{
	screenWidth = screenwidth;
	screenHeight = screenheight;
	endGameFlag = false;
	padSetting = true;
	padSetP1 = false;
	padSetP2 = false;
	fontData.Initialize();
	ChangeScene(DEF_SCENE);
	changeSceneDirection.BaseInitialize(screenWidth, screenHeight, system, &fontData, &textureManager, &sound, &score);

	system->GetTimerSystem().UpdateFrameTimer();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 更新処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::Update()
{
	//	コントローラーが接続されたか切断されたかどうか
	if (system->GetInputSystem().GetNewConectedPad() || system->GetInputSystem().GetDisconectedPad())
	{
		padSetting = true;
		padSetP1 = false;
		padSetP2 = false;
	}

	//	パッド設定モード
	if (padSetting)
	{
		//------------------------------------------------------------------------------------------------
		//	デバッグ用キーを押すと強制終了する
		if (system->GetInputSystem().IsKeyPressed(KEY_INPUT_ESCAPE))	ChangeScene(SceneID::EndGame);
		//------------------------------------------------------------------------------------------------
		PadSettingsUpdate();
		return;
	}

	//	シーン切り替え処理が無かったら通常通り更新
	if (!changeSceneDirection.GetNowSceneDirection())	nowScene->Update();
	//	シーン切り替えするかどうか
	SceneID changeSceneID = nowScene->GetChangeSceneID();
	//	シーン切り替えの更新
	changeSceneDirection.Update();

	//	シーン切り替えするかどうか判断する
	if (changeSceneID == SceneID::None) return;
	//	切り替え演出処理しているときは下の処理をスキップ
	if (changeSceneDirection.GetNowSceneDirection())		return;
	//	シーン切り替え
	else if (changeSceneDirection.GetReadyChangeScene())	ChangeScene(changeSceneID);
	//	フェードアウト処理開始
	else													changeSceneDirection.StartSceneDirection(false);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 描画処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::Render()
{
	//	各シーンの描画処理
	nowScene->Render();
	//	シーン切り替え演出
	changeSceneDirection.Render();
	//	パッド設定描画
	if(padSetting) PadSettingsRender();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 解放処理最後に行われる
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::Finalize()
{
	fontData.Finalize();
	changeSceneDirection.Finalize();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// Reserve Data(必要なデータを受け取る Initializeより先に呼び出される)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::SetSystemObject(GameSystemObjects* system)
{
	this->system = system;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ChangeScene(シーン切り替え処理)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::ChangeScene(SceneID scene)
{
	//	今のシーンが存在するときだけシーンの解放処理を行う
	if (nowScene != nullptr)
	{
		//	Finalize
		nowScene->BaseFinalize();
		textureManager.DeleteSceneGraph();
		delete nowScene;
	}

	//	シーン切り替え処理
	switch (scene)
	{
	case SceneID::Logo:
		nowScene = new LogoScene;
		break;
	case SceneID::Title:
		nowScene = new TitleScene;
		break;
	case SceneID::ModeSelect:
		nowScene = new ModeSelectScene;
		break;
	case SceneID::CharaSelect:
		nowScene = new CharaSelectScene;
		break;
	case SceneID::Play:
		nowScene = new PlayScene;
		break;
	case SceneID::Result:
		nowScene = new ResultScene;
		break;
	case SceneID::EndGame:
		endGameFlag = true;
		return;
		break;
	}
	//	初期化
	textureManager.LoadSceneGraph(scene);
	nowScene->BaseInitialize(screenWidth, screenHeight, system, &fontData, &textureManager, &sound, &score);
	//	切り替え演出開始
	changeSceneDirection.StartSceneDirection(true);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// End Game Flag(ゲーム終了フラグ受渡)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
bool Game::GetEndGameFlag()
{
	return endGameFlag;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// パッド設定更新
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::PadSettingsUpdate()
{
	int id;
	if (!padSetP1)
	{
		id = system->GetInputSystem().GetIsButtonPressedPadID(DualShock4Input::PS);
		if (id == -1) return;
		system->GetInputSystem().SetPlayerInputNum(0, id);
		padSetP1 = true;
	}
	else if (!padSetP2)
	{
		id = system->GetInputSystem().GetIsButtonPressedPadID(DualShock4Input::PS);
		if (id == -1) return;
		system->GetInputSystem().SetPlayerInputNum(1, id);
		padSetP2 = true;
	}
	else
	{
		if (system->GetInputSystem().IsButtonPressed(DualShock4Input::PS))
			padSetting = false;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// パッド設定描画
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::PadSettingsRender()
{
	//	フォントハンドル一時保存用
	int drawFontHandle;
	//	文字の長さ用取得用
	int drawWidth;
	//	文字の大きさ取得用
	int drawFontSize;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 210);
	DrawBox(0, 0, screenWidth, screenHeight, 0x000000, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	drawFontHandle = fontData.GetFontHandle(FontID::SuperBigEdgeMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "接続されているコントローラーの数が変わりました");
	DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, 1 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "接続されているコントローラーの数が変わりました");
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "(ESCで終了)");
	DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, 1 * screenHeight / 5 + drawFontSize / 2, 0xffffff, drawFontHandle, "(ESCで終了)");

	drawFontHandle = fontData.GetFontHandle(FontID::BigMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);

	if (!padSetP1)
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1に接続したいコントローラーのPSを押してください");
		DrawFormatStringToHandle(1 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P1に接続したいコントローラーのPSを押してください");
	}
	else if (!padSetP2)
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1接続完了！");
		DrawFormatStringToHandle(1 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P1接続完了！");
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P2に接続したいコントローラーのPSを押してください");
		DrawFormatStringToHandle(2 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P2に接続したいコントローラーのPSを押してください");
	}
	else
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1接続完了！");
		DrawFormatStringToHandle(1 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P1接続完了！");
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P2接続完了！");
		DrawFormatStringToHandle(2 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P2接続完了！");
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "PSボタンで開始！");
		DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, 4 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "PSボタンで開始！");
	}
}
