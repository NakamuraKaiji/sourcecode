//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ChangeSceneDirection
//				�V�[���؂�ւ����̃t�F�[�h�C���A�A�E�g�������s���N���X
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/BaseScene.h"

class ChangeSceneDirection :public BaseScene
{
private:

	bool in;					//	�t�F�[�h�C���������ǂ���
	bool nowDirection;			//	�`�撆���ǂ���
	bool readyChangeScene;		//	�V�[���J�ڂł��邩�ǂ���

	float timeCount;			//	���ԃJ�E���g

public:
	ChangeSceneDirection();
	~ChangeSceneDirection();

	void Initialize()	override;			//	������
	void Update()		override;			//	�X�V
	void Render()		override;			//	�`��
	void Finalize()		override;			//	���

	void StartSceneDirection(bool in);		//	���o�J�n���ɌĂяo������������
	bool GetNowSceneDirection();			//	�؂�ւ����o�����ǂ�����n��
	bool GetReadyChangeScene();				//	�V�[���؂�ւ��\���ǂ�����n��
};
