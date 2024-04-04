//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	CharaSelectScene
//		��ޑI�����
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

	void Initialize()	override;   //	������
	void Update()       override;   //	�X�V
	void Render()       override;   //	�`��
	void Finalize()     override;	//	�I��
};
