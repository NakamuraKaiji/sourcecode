//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	ModeSelectScene
//		モード選択
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"

class ModeSelectScene : public BaseScene
{
private:

public:
	ModeSelectScene();
	~ModeSelectScene();

	void Initialize()	override;   //	初期化
	void Update()       override;   //	更新
	void Render()       override;   //	描画
	void Finalize()     override;	//	終了
};
