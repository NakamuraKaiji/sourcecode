//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	Game.h
//		�Q�[���ōs�����ۂ̏������Ăяo�����߁A���ۂɃN���X���֏������L�q���邽�߂̃t�@�C���B
//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#include <DxLib.h>
#include "Game.h"
#include "GameDatas/ControllerInput.h"
#include "GameScene/LogoScene.h"
#include "GameScene/TitleScene.h"
#include "GameScene/ModeSelectScene.h"
#include "GameScene/CharaSelectScene.h"
#include "GameScene/PlayScene.h"
#include "GameScene/ResultScene.h"


const SceneID DEF_SCENE = SceneID::Logo;	//	�ŏ��̃V�[���ݒ�

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �R���X�g���N�^
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Game::Game() :
	screenWidth(0),
	screenHeight(0),
	system(nullptr),
	nowScene(nullptr),
	endGameFlag(false),
	score(),
	padSetting(),
	padSetP1(),
	padSetP2()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �f�X�g���N�^
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Game::~Game()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ����������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::Initialize(int screenwidth, int screenheight)
{
	screenWidth = screenwidth;
	screenHeight = screenheight;
	endGameFlag = false;
	padSetting = true;
	padSetP1 = false;
	padSetP2 = false;
	fontData.Initialize();
	ChangeScene(DEF_SCENE);
	changeSceneDirection.BaseInitialize(screenWidth, screenHeight, system, &fontData, &textureManager, &sound, &score);

	system->GetTimerSystem().UpdateFrameTimer();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �X�V����
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::Update()
{
	//	�R���g���[���[���ڑ����ꂽ���ؒf���ꂽ���ǂ���
	if (system->GetInputSystem().GetNewConectedPad() || system->GetInputSystem().GetDisconectedPad())
	{
		padSetting = true;
		padSetP1 = false;
		padSetP2 = false;
	}

	//	�p�b�h�ݒ胂�[�h
	if (padSetting)
	{
		//------------------------------------------------------------------------------------------------
		//	�f�o�b�O�p�L�[�������Ƌ����I������
		if (system->GetInputSystem().IsKeyPressed(KEY_INPUT_ESCAPE))	ChangeScene(SceneID::EndGame);
		//------------------------------------------------------------------------------------------------
		PadSettingsUpdate();
		return;
	}

	//	�V�[���؂�ւ�����������������ʏ�ʂ�X�V
	if (!changeSceneDirection.GetNowSceneDirection())	nowScene->Update();
	//	�V�[���؂�ւ����邩�ǂ���
	SceneID changeSceneID = nowScene->GetChangeSceneID();
	//	�V�[���؂�ւ��̍X�V
	changeSceneDirection.Update();

	//	�V�[���؂�ւ����邩�ǂ������f����
	if (changeSceneID == SceneID::None) return;
	//	�؂�ւ����o�������Ă���Ƃ��͉��̏������X�L�b�v
	if (changeSceneDirection.GetNowSceneDirection())		return;
	//	�V�[���؂�ւ�
	else if (changeSceneDirection.GetReadyChangeScene())	ChangeScene(changeSceneID);
	//	�t�F�[�h�A�E�g�����J�n
	else													changeSceneDirection.StartSceneDirection(false);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �`�揈��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::Render()
{
	//	�e�V�[���̕`�揈��
	nowScene->Render();
	//	�V�[���؂�ւ����o
	changeSceneDirection.Render();
	//	�p�b�h�ݒ�`��
	if(padSetting) PadSettingsRender();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ��������Ō�ɍs����
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::Finalize()
{
	fontData.Finalize();
	changeSceneDirection.Finalize();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// Reserve Data(�K�v�ȃf�[�^���󂯎�� Initialize����ɌĂяo�����)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::SetSystemObject(GameSystemObjects* system)
{
	this->system = system;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ChangeScene(�V�[���؂�ւ�����)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::ChangeScene(SceneID scene)
{
	//	���̃V�[�������݂���Ƃ������V�[���̉���������s��
	if (nowScene != nullptr)
	{
		//	Finalize
		nowScene->BaseFinalize();
		textureManager.DeleteSceneGraph();
		delete nowScene;
	}

	//	�V�[���؂�ւ�����
	switch (scene)
	{
	case SceneID::Logo:
		nowScene = new LogoScene;
		break;
	case SceneID::Title:
		nowScene = new TitleScene;
		break;
	case SceneID::ModeSelect:
		nowScene = new ModeSelectScene;
		break;
	case SceneID::CharaSelect:
		nowScene = new CharaSelectScene;
		break;
	case SceneID::Play:
		nowScene = new PlayScene;
		break;
	case SceneID::Result:
		nowScene = new ResultScene;
		break;
	case SceneID::EndGame:
		endGameFlag = true;
		return;
		break;
	}
	//	������
	textureManager.LoadSceneGraph(scene);
	nowScene->BaseInitialize(screenWidth, screenHeight, system, &fontData, &textureManager, &sound, &score);
	//	�؂�ւ����o�J�n
	changeSceneDirection.StartSceneDirection(true);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// End Game Flag(�Q�[���I���t���O��n)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
bool Game::GetEndGameFlag()
{
	return endGameFlag;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �p�b�h�ݒ�X�V
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::PadSettingsUpdate()
{
	int id;
	if (!padSetP1)
	{
		id = system->GetInputSystem().GetIsButtonPressedPadID(DualShock4Input::PS);
		if (id == -1) return;
		system->GetInputSystem().SetPlayerInputNum(0, id);
		padSetP1 = true;
	}
	else if (!padSetP2)
	{
		id = system->GetInputSystem().GetIsButtonPressedPadID(DualShock4Input::PS);
		if (id == -1) return;
		system->GetInputSystem().SetPlayerInputNum(1, id);
		padSetP2 = true;
	}
	else
	{
		if (system->GetInputSystem().IsButtonPressed(DualShock4Input::PS))
			padSetting = false;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �p�b�h�ݒ�`��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Game::PadSettingsRender()
{
	//	�t�H���g�n���h���ꎞ�ۑ��p
	int drawFontHandle;
	//	�����̒����p�擾�p
	int drawWidth;
	//	�����̑傫���擾�p
	int drawFontSize;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 210);
	DrawBox(0, 0, screenWidth, screenHeight, 0x000000, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	drawFontHandle = fontData.GetFontHandle(FontID::SuperBigEdgeMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "�ڑ�����Ă���R���g���[���[�̐����ς��܂���");
	DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, 1 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "�ڑ�����Ă���R���g���[���[�̐����ς��܂���");
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "(ESC�ŏI��)");
	DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, 1 * screenHeight / 5 + drawFontSize / 2, 0xffffff, drawFontHandle, "(ESC�ŏI��)");

	drawFontHandle = fontData.GetFontHandle(FontID::BigMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);

	if (!padSetP1)
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1�ɐڑ��������R���g���[���[��PS�������Ă�������");
		DrawFormatStringToHandle(1 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P1�ɐڑ��������R���g���[���[��PS�������Ă�������");
	}
	else if (!padSetP2)
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1�ڑ������I");
		DrawFormatStringToHandle(1 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P1�ڑ������I");
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P2�ɐڑ��������R���g���[���[��PS�������Ă�������");
		DrawFormatStringToHandle(2 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P2�ɐڑ��������R���g���[���[��PS�������Ă�������");
	}
	else
	{
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1�ڑ������I");
		DrawFormatStringToHandle(1 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P1�ڑ������I");
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P2�ڑ������I");
		DrawFormatStringToHandle(2 * screenWidth / 3 - drawWidth / 2, 3 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "P2�ڑ������I");
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "PS�{�^���ŊJ�n�I");
		DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, 4 * screenHeight / 5 - drawFontSize / 2, 0xffffff, drawFontHandle, "PS�{�^���ŊJ�n�I");
	}
}
