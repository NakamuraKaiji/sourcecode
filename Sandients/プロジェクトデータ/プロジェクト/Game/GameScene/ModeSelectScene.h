//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	ModeSelectScene
//		���[�h�I��
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

	void Initialize()	override;   //	������
	void Update()       override;   //	�X�V
	void Render()       override;   //	�`��
	void Finalize()     override;	//	�I��
};
