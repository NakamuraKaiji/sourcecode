//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	TitleScene
//		タイトルを描画するシーン
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"

class TitleScene : public BaseScene
{
private:
	int Vegetables[11];

	int Back;
	int Yellow;
	int Logo;
	int Matte;

	int L_rand;
	int L_rand2;
	int L_rand3;

	int R_rand;
	int R_rand2;
	int R_rand3;


	float counter;

	int count;

	int L_VegePos_X;
	int R_VegePos_X;
	int VegePos_Y;

	int L_fall;
	int L_fall2;
	int L_fall3;

	int R_fall;
	int R_fall2;
	int R_fall3;

	int alpha;

	bool back;


public:
	TitleScene();
	~TitleScene();

	void Initialize()	override;   //	初期化
	void Update()       override;   //	更新
	void Render()       override;   //	描画
	void Finalize()     override;	//	終了
};