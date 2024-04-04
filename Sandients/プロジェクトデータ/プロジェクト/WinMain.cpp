//----------------------------------------------------------------------------------------------------
//	WinMain・・・	プログラムのエントリーポイントと、ゲームのメインループを定義するファイル。
// 
//----------------------------------------------------------------------------------------------------
#include <DxLib.h>							//	DxLibエンジンを使うために必要なインクルード
#include <windows.h>
#include "Game/Game.h"						//	Gameクラスを使用するために必要なインクルード
#include "ExtendLib/MemoryLeakDetector.h"
#include "ExtendLib/GameSystemObject/GameSystemObjects.h"

#define SCREEN_WIDTH						1280		//	画面の横サイズ
#define SCREEN_HEIGHT						 720		//	画面の縦サイズ
//	ウィンドウタイトルに表示する文字
#define GAME_TITLE							"Sandients"

//	プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//	未使用引数の警告対策
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nShowCmd);

	SetMainWindowText(GAME_TITLE);    // ウインドウタイトルの設定
#if defined(_DEBUG)
	//	メモリーリーク検出機構のセットアップ
	SetUpMemoryLeakDetector();
#endif

	SetOutApplicationLogValidFlag(FALSE);	//	デバッグ情報用ログファイルは出力しない

	//	起動モードの設定
	ChangeWindowMode(TRUE);					//	ウインドウモードで実行

	//	画面の解像度を取得
	int screenWidth;
	int screenHeight;
	//	画面情報取得
	GetDefaultState(&screenWidth, &screenHeight, NULL);

	//	ゲーム画面のサイズ設定
	int gameWidth = screenWidth;
	int gameHeight = screenHeight;

	//	描画モード変更（解像度x,y,色）
	SetGraphMode(screenWidth, screenHeight, 32);	

	//	ウィンドウサイズ変更
	SetWindowSize(screenWidth, screenHeight);

	// ウインドウの初期位置はデスクトップ画面の中心にする
	SetWindowPosition(screenWidth / 2 - gameWidth / 2, (screenHeight - gameHeight) / 2);

	//	初期状態の画面モードの設定
	SetWindowStyleMode(4);							//	ウィンドウモードをフチなしに
	SetAlwaysRunFlag(true);	                        //	バックグラウンドでも実行するように

	//	DXライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;							//	DxLibの初期化処理に失敗した
	}

	SetDrawScreen(DX_SCREEN_BACK);			//	画面の描画先を設定

	//	メインループ内で使用する変数を宣言する
	GameSystemObjects	systemObject;		//	ゲーム内のタイマーとキー入力の処理
	Game gameJobObject;						//	ゲームの処理を実際に記述しているクラスオブジェクト

	//	宣言した変数の初期化が必要であれば、以下で行う
	systemObject.Initialize();
	gameJobObject.SetSystemObject(&systemObject);
	gameJobObject.Initialize(screenWidth, screenHeight);				//	ゲームの処理を行う前に、初期化処理を行う

	//	メインループ。
	while (ProcessMessage() == 0)
	{
		//	更新処理
		//	入力系統の更新
		systemObject.Update();

		//	Gameの更新
		gameJobObject.Update();						

		//	終了指示があれば終了
		if (gameJobObject.GetEndGameFlag())	break;

		//	描画処理。ゲームの描画処理はもう少し下で書く
		//	画面を初期化する。					描画処理の開始
		ClearDrawScreen();
		
		//	特に指示がなければ、Game::Render()関数内に描画処理を書く
		gameJobObject.Render();

		//	裏画面の内容を表画面に反映させる。	描画処理の終了
		ScreenFlip();

		//	フレーム内の処理終了！
	}
	systemObject.Finalize();
	gameJobObject.Finalize();				//	プログラムを終了する前に、ゲームの終了処理を行う

	//	DXライブラリの終了処理
	if (DxLib_End() == -1)
	{
		return -1;							//	DxLibの終了処理に失敗した
	}

	return 0;								//	正常終了
}
