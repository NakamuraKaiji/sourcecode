//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	ResultScene
//		結果
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"

class ResultScene : public BaseScene
{
private:
	bool p1Ready;		//	P1準備
	bool p2Ready;		//	P2準備

public:
	ResultScene();
	~ResultScene();

	void Initialize()	override;   //	初期化
	void Update()       override;   //	更新
	void Render()       override;   //	描画
	void Finalize()     override;	//	終了
};
