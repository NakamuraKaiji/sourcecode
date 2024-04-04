/*
	ExtendLibInput.h
	DxLib�𗘗p���āA���͂̏�Ԃ��Ǘ�����N���X�B
	DxLib�ł́A�{�^����������Ă��邩������Ă��Ȃ����͕����邪�A
	�����ꂽ�u�Ԃ��A�����ꂽ�u�Ԃ��A�Ƃ����`�F�b�N���ł��Ȃ����߁A
	���̕������J�o�[���邽�߂̏������T�|�[�g����B
*/
#pragma once
#include <vector>

//	�{�^����
const int MAX_BUTTON_NUM = 32;

//	�X�e�B�b�N
enum class PadTip
{
	X,
	Y,
	Z,
	Rx,
	Ry,
	Rz,

	TipNum
};

//	POV
enum class PadPOV
{
	Arrow,
	none,
	nasi,
	nee,

	POVNum
};

//	�p�b�h�p�\����
struct PadStatas
{
	int PadNum = 0;							//	�p�b�h�ԍ�
	int newPadButtonInput = 0;				//	�W���C�p�b�h�̌��݂̓���
	int oldPadButtonInput = 0;				//	�W���C�p�b�h��1�t���[���O�̓���
	std::vector<char> newPadBtnInput = {};	//	�W���C�p�b�h�̌��݂̓���
	std::vector<char> oldPadBtnInput = {};	//	�W���C�p�b�h��1�t���[���O�̓���
	std::vector<int> newPadPOVInput = {};	//	�W���C�p�b�h�̌��݂̖�����
	std::vector<int> oldPadPOVInput = {};	//	�W���C�p�b�h��1�t���[���O�̖�����
	std::vector<int> newPadTipInput = {};	//	�W���C�p�b�h�̌��݂̃X�e�B�b�N�X��
	std::vector<int> oldPadTipInput = {};	//	�W���C�p�b�h��1�t���[���O�̃X�e�B�b�N�X��
};

enum class PlayerID
{
	player1 = 0,
	player2 = 1
};

class ExtendLibInput
{
private:
	static const int KEY_CODE_MAX;		//	�L�[�̍ő吔
	std::vector<int> playerInputPad;	//	�e�v���C���[�̃p�b�h�ԍ�

	int newConectedPadNum;				//	�p�b�h�ڑ���
	int oldConectedPadNum;				//	1�t���[���O�̃p�b�h�ڑ���

	std::vector<PadStatas> padStatas;	//	�e�p�b�h���

	int nowKeyInput[256];				//	�L�[�R�[�h�̌��݂̓���
	int oldKeyInput[256];				//	�L�[�R�[�h��1�t���[���O�̓���

public:
	ExtendLibInput();					//	�R���X�g���N�^
	~ExtendLibInput();					//	�f�X�g���N�^

	void Initialize();					//	����������
	void Update();						//	�X�V����
	void Finalize();					//	�I������

	int GetPadNum(int padID);						        //	�p�b�hID����ԍ����擾
	
	int IsButtonDown(int padID, int tipID);			        //	����̃W���C�p�b�h�̃{�^����������Ă��邩
	int IsButtonUp(int padID, int tipID);			        //	����̃W���C�p�b�h�̃{�^����������Ă��邩
	int IsButtonPressed(int padID, int tipID);		        //	����̃W���C�p�b�h�̃{�^���������ꂽ�u�Ԃ�
	int IsButtonReleased(int padID, int tipID);		        //	����̃W���C�p�b�h�̃{�^���������ꂽ�u�Ԃ�

	int IsButtonDown(int tipID);					        //	�W���C�p�b�h�̃{�^����������Ă��邩
	int IsButtonUp(int tipID);						        //	�W���C�p�b�h�̃{�^����������Ă��邩
	int IsButtonPressed(int tipID);					        //	�W���C�p�b�h�̃{�^���������ꂽ�u�Ԃ�
	int IsButtonReleased(int tipID);				        //	�W���C�p�b�h�̃{�^���������ꂽ�u�Ԃ�

	int IsPOVDown(int padID, int POVID, int val);		    //	����̃W���C�p�b�h��POV�{�^����������Ă��邩
	int IsPOVUp(int padID, int POVID, int val);			    //	����̃W���C�p�b�h��POV�{�^����������Ă��邩
	int IsPOVPressed(int padID, int POVID, int val);	    //	����̃W���C�p�b�h��POV�{�^���������ꂽ�u�Ԃ�
	int IsPOVReleased(int padID, int POVID, int val);	    //	����̃W���C�p�b�h��POV�{�^���������ꂽ�u�Ԃ�
	int IsPOVVal(int padID, int POVID);						//	����̃W���C�p�b�h�̒l���`�F�b�N

	int IsPOVDown(int POVID, int val);						//	�W���C�p�b�h��POV�{�^����������Ă��邩
	int IsPOVUp(int POVID, int val);			            //	�W���C�p�b�h��POV�{�^����������Ă��邩
	int IsPOVPressed(int POVID, int val);	                //	�W���C�p�b�h��POV�{�^���������ꂽ�u�Ԃ�
	int IsPOVReleased(int POVID, int val);	                //	�W���C�p�b�h��POV�{�^���������ꂽ�u�Ԃ�

	int IsTipDown(int padID, int analogID, bool plass);		//	����̃X�e�B�b�N���|����Ă��邩�`�F�b�N
	int IsTipUp(int padID, int analogID, bool plass);		//	����̃X�e�B�b�N�����ʂ̏�Ԃ��`�F�b�N
	int IsTipPressed(int padID, int analogID, bool plass);  //	����̃X�e�B�b�N���|���ꂽ�u�Ԃ��`�F�b�N
	int IsTipRelesed(int padID, int analogID, bool plass);  //	����̃X�e�B�b�N���߂����u�Ԃ��`�F�b�N
	int IsTipVal(int padID, int analogID);				    //	����̃X�e�B�b�N�̒l�`�F�b�N

	int GetIsButtonPressedPadID(int tipID);			        //	�W���C�p�b�h�̎w��̃{�^����������Ă���p�b�hID���擾

	bool GetNewConectedPad();						        //	�p�b�h���ڑ����ꂽ���ǂ���
	bool GetDisconectedPad();						        //	�p�b�h���ؒf���ꂽ���ǂ���

	bool GetPlayerPadConected(int playerID);		        //	���̃v���C���[�p�̃p�b�h���Ȃ����Ă��邩�ǂ���

	void SetPlayerInputNum(int playerID, int PADID);        //	�p�b�h�ԍ��ݒ�
	std::vector<int> GetPlayerInputNum();			        //	�p�b�h�ԍ��擾

	int IsKeyDown(int keyCode);						        //	�L�[�{�[�h�̃{�^����������Ă��邩�`�F�b�N
	int IsKeyUp(int keyCode);						        //	�L�[�{�[�h�̃{�^����������Ă��邩�`�F�b�N
	int IsKeyPressed(int keyCode);					        //	�L�[�{�[�h�̃{�^���������ꂽ�u�Ԃ��`�F�b�N
	int IsKeyReleased(int keyCode);					        //	�L�[�{�[�h�̃{�^���������ꂽ�u�Ԃ��`�F�b�N
};

