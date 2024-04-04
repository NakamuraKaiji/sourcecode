//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	Game.h
//		ゲームで行う実際の処理を呼び出すため、クラスを定義するファイル。
//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "GameDatas/FontHandle.h"
#include "GameDatas/ChangeSceneDirection.h"
#include "GameDatas/TextureManager.h"
#include "GameDatas/Sound.h"
#include "GameScene/Scenes.h"
#include "GameScene/BaseScene.h"

#include "GameObject/PlayerScore.h"

class Game
{
private:
	int screenWidth;				            //	画面幅
	int screenHeight;				            //	画面高さ

	GameSystemObjects* system;		            //	入力処理用
	FontHandle fontData;			            //	フォントデータクラス
	TextureManger textureManager;				//	テクスチャデータクラス
	Sound sound;								//	サウンドデータクラス

	bool endGameFlag;				            //	ゲーム終了用

	BaseScene* nowScene;			            //	現在のシーン
	ChangeSceneDirection changeSceneDirection;	//	切り替え演出

	PlayerScore score;								//	スコア設定

	bool padSetting;							//	パッド設定中
	bool padSetP1;
	bool padSetP2;
		
public:
	Game();													//	コンストラクタ
	~Game();												//	デストラクタ

	void Initialize(int screenwidth, int screenheight);		//	初期化
	void Update();											//	更新
	void Render();											//	描画
	void Finalize();										//	終了

	void SetSystemObject(GameSystemObjects* system);		//	シーンにデータを受け渡す
	void ChangeScene(SceneID scene);						//	シーン切り替え
	bool GetEndGameFlag();									//	ゲーム終了フラグ

	void PadSettingsUpdate();								//	パッド設定更新
	void PadSettingsRender();								//	パッド設定描画
};

