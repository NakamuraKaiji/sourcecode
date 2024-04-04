//----------------------------------------------------------------------------------------------------
//	WinMain�E�E�E	�v���O�����̃G���g���[�|�C���g�ƁA�Q�[���̃��C�����[�v���`����t�@�C���B
// 
//----------------------------------------------------------------------------------------------------
#include <DxLib.h>							//	DxLib�G���W�����g�����߂ɕK�v�ȃC���N���[�h
#include <windows.h>
#include "Game/Game.h"						//	Game�N���X���g�p���邽�߂ɕK�v�ȃC���N���[�h
#include "ExtendLib/MemoryLeakDetector.h"
#include "ExtendLib/GameSystemObject/GameSystemObjects.h"

#define SCREEN_WIDTH						1280		//	��ʂ̉��T�C�Y
#define SCREEN_HEIGHT						 720		//	��ʂ̏c�T�C�Y
//	�E�B���h�E�^�C�g���ɕ\�����镶��
#define GAME_TITLE							"Sandients"

//	�v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//	���g�p�����̌x���΍�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nShowCmd);

	SetMainWindowText(GAME_TITLE);    // �E�C���h�E�^�C�g���̐ݒ�
#if defined(_DEBUG)
	//	�������[���[�N���o�@�\�̃Z�b�g�A�b�v
	SetUpMemoryLeakDetector();
#endif

	SetOutApplicationLogValidFlag(FALSE);	//	�f�o�b�O���p���O�t�@�C���͏o�͂��Ȃ�

	//	�N�����[�h�̐ݒ�
	ChangeWindowMode(TRUE);					//	�E�C���h�E���[�h�Ŏ��s

	//	��ʂ̉𑜓x���擾
	int screenWidth;
	int screenHeight;
	//	��ʏ��擾
	GetDefaultState(&screenWidth, &screenHeight, NULL);

	//	�Q�[����ʂ̃T�C�Y�ݒ�
	int gameWidth = screenWidth;
	int gameHeight = screenHeight;

	//	�`�惂�[�h�ύX�i�𑜓xx,y,�F�j
	SetGraphMode(screenWidth, screenHeight, 32);	

	//	�E�B���h�E�T�C�Y�ύX
	SetWindowSize(screenWidth, screenHeight);

	// �E�C���h�E�̏����ʒu�̓f�X�N�g�b�v��ʂ̒��S�ɂ���
	SetWindowPosition(screenWidth / 2 - gameWidth / 2, (screenHeight - gameHeight) / 2);

	//	������Ԃ̉�ʃ��[�h�̐ݒ�
	SetWindowStyleMode(4);							//	�E�B���h�E���[�h���t�`�Ȃ���
	SetAlwaysRunFlag(true);	                        //	�o�b�N�O���E���h�ł����s����悤��

	//	DX���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;							//	DxLib�̏����������Ɏ��s����
	}

	SetDrawScreen(DX_SCREEN_BACK);			//	��ʂ̕`����ݒ�

	//	���C�����[�v���Ŏg�p����ϐ���錾����
	GameSystemObjects	systemObject;		//	�Q�[�����̃^�C�}�[�ƃL�[���͂̏���
	Game gameJobObject;						//	�Q�[���̏��������ۂɋL�q���Ă���N���X�I�u�W�F�N�g

	//	�錾�����ϐ��̏��������K�v�ł���΁A�ȉ��ōs��
	systemObject.Initialize();
	gameJobObject.SetSystemObject(&systemObject);
	gameJobObject.Initialize(screenWidth, screenHeight);				//	�Q�[���̏������s���O�ɁA�������������s��

	//	���C�����[�v�B
	while (ProcessMessage() == 0)
	{
		//	�X�V����
		//	���͌n���̍X�V
		systemObject.Update();

		//	Game�̍X�V
		gameJobObject.Update();						

		//	�I���w��������ΏI��
		if (gameJobObject.GetEndGameFlag())	break;

		//	�`�揈���B�Q�[���̕`�揈���͂����������ŏ���
		//	��ʂ�����������B					�`�揈���̊J�n
		ClearDrawScreen();
		
		//	���Ɏw�����Ȃ���΁AGame::Render()�֐����ɕ`�揈��������
		gameJobObject.Render();

		//	����ʂ̓��e��\��ʂɔ��f������B	�`�揈���̏I��
		ScreenFlip();

		//	�t���[�����̏����I���I
	}
	systemObject.Finalize();
	gameJobObject.Finalize();				//	�v���O�������I������O�ɁA�Q�[���̏I���������s��

	//	DX���C�u�����̏I������
	if (DxLib_End() == -1)
	{
		return -1;							//	DxLib�̏I�������Ɏ��s����
	}

	return 0;								//	����I��
}
