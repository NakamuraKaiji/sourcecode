//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	CharaSelectScene
//		具材選択画面
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"
#include "../GameObject/CharaSelectScene/BreadSelect.h"
#include "../GameObject/CharaSelectScene/IngredientsSelect.h"

class CharaSelectScene : public BaseScene
{
private:

	BreadSelect breadSelect;
	IngredientsSelect ingredientsSelect;

	bool back;

public:
	CharaSelectScene();
	~CharaSelectScene();

	void Initialize()	override;   //	初期化
	void Update()       override;   //	更新
	void Render()       override;   //	描画
	void Finalize()     override;	//	終了
};
