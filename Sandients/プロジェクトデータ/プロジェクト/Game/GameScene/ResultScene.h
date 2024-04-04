//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	ResultScene
//		����
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"

class ResultScene : public BaseScene
{
private:
	bool p1Ready;		//	P1����
	bool p2Ready;		//	P2����

public:
	ResultScene();
	~ResultScene();

	void Initialize()	override;   //	������
	void Update()       override;   //	�X�V
	void Render()       override;   //	�`��
	void Finalize()     override;	//	�I��
};
