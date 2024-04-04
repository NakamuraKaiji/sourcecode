//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	ResultScene
//		Œ‹‰Ê
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"

class ResultScene : public BaseScene
{
private:
	bool p1Ready;		//	P1€”õ
	bool p2Ready;		//	P2€”õ

public:
	ResultScene();
	~ResultScene();

	void Initialize()	override;   //	‰Šú‰»
	void Update()       override;   //	XV
	void Render()       override;   //	•`‰æ
	void Finalize()     override;	//	I—¹
};
