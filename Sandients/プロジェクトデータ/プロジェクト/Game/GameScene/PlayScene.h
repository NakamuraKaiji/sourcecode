//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	PlayScene
//		�v���C�V�[��
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"

#include "../GameDatas/Vector.h"
#include "../GameDatas/Sound.h"
#include "../GameObject/PlayScene/Player.h"
#include "../GameObject/PlayScene/AttackManager.h"

class PlayScene : public BaseScene
{
private:
	Player player1;
	Player player2;
	AttackManager attackManager;
	Sound sound;

	float Timer;		//	����
	float countTime;	//	�J�E���g�_�E���p

	int P1WinNum;       //	1P������
	int P2WinNum;       //	2P������

	bool P1Win;			//	1P����
	bool P2Win;			//	2P����

	int CoolTimeH;		//	�X�L���̃N�[���^�C��

	bool countDown;		//	�J�E���g�_�E��
	bool roundEnd;		//	���E���h�I��
	bool matchEnd;		//	�����I��
	bool pause;			//	�|�[�Y
	bool debug;			//	�f�o�b�O

public:
	PlayScene();
	~PlayScene();

	void Initialize()	override;   //	������
	void Update()       override;   //	�X�V
	void Render()       override;   //	�`��
	void Finalize()     override;	//	�I��

	void Reset();					//	���E���h���Z�b�g

	void HitUpdate();				//	�����蔻��̍X�V
	void JugeRight();				//	�ǂ������E�����f����

	void UIRender();				//	UI�`��

	void PauseUpdate();				//	�|�[�Y�X�V
	void PauseRender();				//	�|�[�Y�`��

	void RoundEnd();				//	���E���h�I������
};
