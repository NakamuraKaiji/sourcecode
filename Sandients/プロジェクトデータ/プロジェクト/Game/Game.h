//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	Game.h
//		�Q�[���ōs�����ۂ̏������Ăяo�����߁A�N���X���`����t�@�C���B
//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "GameDatas/FontHandle.h"
#include "GameDatas/ChangeSceneDirection.h"
#include "GameDatas/TextureManager.h"
#include "GameDatas/Sound.h"
#include "GameScene/Scenes.h"
#include "GameScene/BaseScene.h"

#include "GameObject/PlayerScore.h"

class Game
{
private:
	int screenWidth;				            //	��ʕ�
	int screenHeight;				            //	��ʍ���

	GameSystemObjects* system;		            //	���͏����p
	FontHandle fontData;			            //	�t�H���g�f�[�^�N���X
	TextureManger textureManager;				//	�e�N�X�`���f�[�^�N���X
	Sound sound;								//	�T�E���h�f�[�^�N���X

	bool endGameFlag;				            //	�Q�[���I���p

	BaseScene* nowScene;			            //	���݂̃V�[��
	ChangeSceneDirection changeSceneDirection;	//	�؂�ւ����o

	PlayerScore score;								//	�X�R�A�ݒ�

	bool padSetting;							//	�p�b�h�ݒ蒆
	bool padSetP1;
	bool padSetP2;
		
public:
	Game();													//	�R���X�g���N�^
	~Game();												//	�f�X�g���N�^

	void Initialize(int screenwidth, int screenheight);		//	������
	void Update();											//	�X�V
	void Render();											//	�`��
	void Finalize();										//	�I��

	void SetSystemObject(GameSystemObjects* system);		//	�V�[���Ƀf�[�^���󂯓n��
	void ChangeScene(SceneID scene);						//	�V�[���؂�ւ�
	bool GetEndGameFlag();									//	�Q�[���I���t���O

	void PadSettingsUpdate();								//	�p�b�h�ݒ�X�V
	void PadSettingsRender();								//	�p�b�h�ݒ�`��
};

