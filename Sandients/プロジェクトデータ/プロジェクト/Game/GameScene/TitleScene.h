//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	TitleScene
//		�^�C�g����`�悷��V�[��
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

	void Initialize()	override;   //	������
	void Update()       override;   //	�X�V
	void Render()       override;   //	�`��
	void Finalize()     override;	//	�I��
};