//----------------------------------------------------------------------------------------------------
//	LogoScene
//		ロゴを描画させるシーン
// 
//----------------------------------------------------------------------------------------------------
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"
#include <vector>

class LogoScene : public BaseScene
{
private:
	float fadeCount;					//	フェード用カウンタ
	float timeCount;					//	時間カウント


	std::vector<int> logoGraph;			//	ロゴ画像用ハンドル
	std::vector<int> logoSound;			//	ロゴ音声用ハンドル
	int logoDrawNum;					//	ロゴ表示回数カウンタ

public:
	LogoScene();
	~LogoScene();

	void Initialize()	override;   //	初期化
	void Update()       override;   //	更新
	void Render()       override;   //	描画
	void Finalize()     override;	//	終了

	void LogoUpdate();				//	ロゴの更新処理
	void LogoDraw(int graph);		//	ロゴの描画処理
};
