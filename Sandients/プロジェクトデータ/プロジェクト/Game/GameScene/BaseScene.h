//----------------------------------------------------------------------------------------------------
//	BaseScene
//			�e�V�[���̌��ƂȂ�p�����N���X
// 
//----------------------------------------------------------------------------------------------------
#pragma once
#include "../../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "../GameScene/Scenes.h"
#include "../GameDatas/FontHandle.h"
#include "../GameDatas/TextureManager.h"
#include "../GameDatas/Sound.h"
#include "../GameObject/PlayerScore.h"
#include "../GameDatas/ControllerInput.h"

class BaseScene
{
protected:
	SceneID changeSceneID;		//	�V�[��ID

	int screenWidth;			//	��ʕ�
	int screenHeight;			//	��ʍ���

	GameSystemObjects* system;	//	���͗p
	FontHandle* fdata;			//	�t�H���g�f�[�^
	TextureManger* tdata;		//	�e�N�X�`���f�[�^
	Sound* sdata;				//	�T�E���h�f�[�^

	PlayerScore* score;

public:
	BaseScene();
	~BaseScene();

	void ChangeScene(SceneID sceneID);	//	�V�[���؂�ւ�����
	SceneID GetChangeSceneID();			//	�ǂ̃V�[���ɑJ�ڂ��邩�n��

	void BaseInitialize(int screenWidth, int screenHeight, GameSystemObjects* system, FontHandle* fdata, TextureManger* tdata, Sound* sdata, PlayerScore* score);	//	��{�I�ȏ�����
	void BaseFinalize();				//	��{�I�ȉ������

	virtual void Initialize() = 0;	//	������
	virtual void Update()     = 0;	//	�X�V
	virtual void Render()     = 0;	//	�`��
	virtual void Finalize()   = 0;	//	�I��
};