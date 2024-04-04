//----------------------------------------------------------------------------------------------------
//	BaseScene
//			各シーンの元となる継承元クラス
// 
//----------------------------------------------------------------------------------------------------
#pragma once
#include "../../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "../GameScene/Scenes.h"
#include "../GameDatas/FontHandle.h"
#include "../GameDatas/TextureManager.h"
#include "../GameDatas/Sound.h"
#include "../GameObject/PlayerScore.h"
#include "../GameDatas/ControllerInput.h"

class BaseScene
{
protected:
	SceneID changeSceneID;		//	シーンID

	int screenWidth;			//	画面幅
	int screenHeight;			//	画面高さ

	GameSystemObjects* system;	//	入力用
	FontHandle* fdata;			//	フォントデータ
	TextureManger* tdata;		//	テクスチャデータ
	Sound* sdata;				//	サウンドデータ

	PlayerScore* score;

public:
	BaseScene();
	~BaseScene();

	void ChangeScene(SceneID sceneID);	//	シーン切り替え処理
	SceneID GetChangeSceneID();			//	どのシーンに遷移するか渡す

	void BaseInitialize(int screenWidth, int screenHeight, GameSystemObjects* system, FontHandle* fdata, TextureManger* tdata, Sound* sdata, PlayerScore* score);	//	基本的な初期化
	void BaseFinalize();				//	基本的な解放処理

	virtual void Initialize() = 0;	//	初期化
	virtual void Update()     = 0;	//	更新
	virtual void Render()     = 0;	//	描画
	virtual void Finalize()   = 0;	//	終了
};