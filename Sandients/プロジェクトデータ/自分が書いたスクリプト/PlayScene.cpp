//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	PlayScene
//		�v���C�V�|��
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#include <DxLib.h>
#include "PlayScene.h"
#include "../GameObject/PlayScene/Skills/Skills.h"

#define GROUND		0.78f		//	��ʂɑ΂���n�ʂ̈ʒu

//	������
#define MATCH_WIN				2	//	�K�v������

//	��������
#define MATCH_TIME				99.0f

//	�J�E���g�_�E��
#define COUNT_DOWN				3.0f

//	���E���h�I�����Ԋu			
#define ROUND_END_TIME			2.0f

//	�ŏI�q�b�g�X�g�b�v
#define LAST_HIT_STOP			1.0f

//	UI
//	�^�C�}�[
#define TIMER_Y						80
#define TIMER_COLOR					0xFF3333
#define COUNT_COLOR					0xff3333

//	������
#define VIC_TEXT					"V"
#define VIC_ICON_Y					145
#define VIC_ICON_P1X				960 - 100
#define VIC_ICON_P2X				960 + 100
#define VIC_ICON_OFFSET				30
#define VIC_ICON_R					20
#define VIC_ICON_COLOR_DEF			0xffffff
#define VIC_ICON_COLOR_WIN			0xffd700
#define VIC_ICON_COLOR_V			0xFF3333

//	HP�ASP�o�[
#define	P1_BAR_POS_X			700	
#define	P2_BAR_POS_X			1220
#define HP_BAR_POS_Y			100
#define SP_BAR_POS_Y			140
#define HP_BAR_WIDTH_MAX		600
#define SP_BAR_WIDTH_MAX		550
#define HP_BAR_HEIGHT			30
#define SP_BAR_HEIGHT			15
#define HP_BAR_OUT_WIDTH		3
#define SP_BAR_OUT_WIDTH		2
#define HP_BAR_COLOR			0x00ff00
#define HP_BAR_EMPTY_COLOR		0x222222
#define HP_BAR_RED_COLOR		0xff0000
#define HP_BAR_OUT_COLOR		0xffffff
#define SP_BAR_COLOR			0xdd5500
#define SP_BAR_EMPTY_COLOR		0x222222
#define SP_BAR_MAX_COLOR		0xffff33
#define SP_BAR_OUT_COLOR		0xffffff
#define HP_BAR_RED_LINE			0.25f
#define SP_BAR_MAX_LINE			1.00f

//	�X�L���̈ʒu
#define P1_SKILL_POS_X				150
#define P2_SKILL_POS_X				1770
#define SKILL_POS_Y					950
#define SKILL_BOX_WIDTH				100
#define SKILL_BOX_HEIGHT			100
#define SKILL_BOX_OUT_WIDTH			5
#define SKILL_BOX_OFFSET			50
#define SKILL_BOX_COLOR				0xffffff
#define SKILL_BOX_OUT_COLOR			0x00ffff
#define SKILL_CIRCLE_R				20
#define SKILL_CIRCLE_COLOR			0xFF3333
#define SKILL_CIRCLE_RENGE			100
#define SKILL_STOCK_COLOR			0x33FFFF

//	������
#define BLENDMODE_MAX			210
#define BLENDMODE_MIN			0

PlayerStatas defstatas
{
	10,10,10,10,0
};
PlayerStatas defP1Statas
{
	10,10,10,10,0,{ static_cast<int>(SkillName::Tuna),static_cast<int>(SkillName::Whip),static_cast<int>(SkillName::Banana)},100
};
PlayerStatas defP2Statas
{
	10,10,10,10,0,{ static_cast<int>(SkillName::Salmon),static_cast<int>(SkillName::Onion),static_cast<int>(SkillName::Bacon)},100
};
Vector2 defP1Pos
{
	400,750
};
Vector2 defP2Pos
{
	1500,750
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �R���X�g���N�^
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
PlayScene::PlayScene() :
	BaseScene(),
	Timer(),
	P1WinNum(0),
	P2WinNum(0),
	P1Win(),
	P2Win(),
	countDown(),
	countTime(),
	roundEnd(),
	matchEnd(),
	debug(),
	pause()
{
	CoolTimeH = LoadGraph("Resources/Textures/Circle.png");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �f�X�g���N�^
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
PlayScene::~PlayScene()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::Initialize()
{
	Vector2 screen = { screenWidth,screenHeight };
	PlayerStatas p1Statas;
	PlayerStatas p2Statas;
	Statas p1 = score->GetStatas(0);
	Statas p2 = score->GetStatas(1);
	p1Statas.hp      = p1.HP;
	p1Statas.atk     = p1.ATK;
	p1Statas.def     = p1.DEF;
	p1Statas.weight  = p1.WEI;
	p1Statas.skillID = p1.skillID;

	p2Statas.hp      = p2.HP;
	p2Statas.atk     = p2.ATK;
	p2Statas.def     = p2.DEF;
	p2Statas.weight  = p2.WEI;
	p2Statas.skillID = p2.skillID;

	player1.Initialize(system, tdata, sdata, &attackManager, 0, screen, GROUND, p1Statas, defP1Pos);
	player2.Initialize(system, tdata, sdata, &attackManager, 1, screen, GROUND, p2Statas, defP2Pos);
	attackManager.Initialize(tdata, sdata, screen, GROUND, &player1, &player2);
	Timer = MATCH_TIME;
	countTime = COUNT_DOWN;
	debug = false;
	countDown = true;
	roundEnd = false;
	matchEnd = false;
	P1Win = false;
	P2Win = false;

	if (P1WinNum == 0 && P2WinNum == 0)		sound.Round1();
	else if ((P1WinNum == 1 && P2WinNum == 0) || (P1WinNum == 0 && P2WinNum == 1))	sound.Round2();
	else if (P1WinNum == 1 && P2WinNum == 1)	sound.Round3();

	JugeRight();

	sdata->PlayBGM();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �X�V����
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::Update()
{
	//	�O�̃t���[������̌o�ߎ��Ԏ擾
	float deltaTime = system->GetTimerSystem().GetFrameDeltaTime();

	//	�R���g���[���[���ڑ����ꂽ���ؒf���ꂽ���ǂ���
	if (system->GetInputSystem().GetNewConectedPad() || system->GetInputSystem().GetDisconectedPad())
	{
		pause = true;
	}

	//	�|�[�Y���邩�ǂ���
	if (system->GetInputSystem().IsButtonPressed(DualShock4Input::OPTIONS))
	{
		sdata->Select();
		if (pause)pause = false;
		else pause = true;
	}

	//	�|�[�Y��
	if (pause)
	{
		PauseUpdate();
		return;
	}

	//	�J�E���g�_�E������
	if (countDown)
	{
		countTime -= deltaTime;
		if (countTime < 0.0f)
		{
			countTime = 0.0f;
			countDown = false;
			sound.Fight();
		}
		return;
	}

	//	�}�b�`�I���Ȃ�
	if (P1WinNum >= MATCH_WIN || P2WinNum >= MATCH_WIN)
	{
		roundEnd = true;
		matchEnd = true;
	}

	//	�����I����
	if (matchEnd)
	{
		countTime -= deltaTime;
		if (countTime < 0.0f)
		{
			countTime = 0.0f;
			ChangeScene(SceneID::Result);
			score->SetScore(0, player1.GetScore());
			score->SetScore(1, player2.GetScore());
			if (P1Win > P2Win)
				score->SetWinPID(0);
			else
				score->SetWinPID(1);
		}
		return;
	}

	//	���E���h�I������
	if (roundEnd)
	{
		countTime -= deltaTime;
		if (countTime < 0.0f)
		{
			countTime = 0.0f;
			roundEnd = false;
			Reset();
		}
	}

	//	�p�b�h�ԍ��ݒ�
	player1.SetPadNum(system->GetInputSystem().GetPlayerInputNum()[0]);
	player2.SetPadNum(system->GetInputSystem().GetPlayerInputNum()[1]);

	//	�^�C�}�[�X�V
	Timer -= deltaTime;
	if (Timer < 0.0f)
	{
		if (!roundEnd)
		{
			if (player1.GetStatas().hp / player1.GetStatas().maxHp > player2.GetStatas().hp / player2.GetStatas().maxHp)
			{
				P1WinNum++;
				P1Win = true;
			}
			else
			{
				P2WinNum++;
				P2Win = true;
			}
			sound.L_Attack();
			Timer = 0.0f;
			roundEnd = true;
			countTime = ROUND_END_TIME;
		}
	}

	//	�R���f�B�V�������Z�b�g
	player1.ResetCondition();
	player2.ResetCondition();

	//	�E�����f
	JugeRight();

	//	�e�U���̍X�V 
	attackManager.Update(deltaTime);

	//	�e�I�u�W�F�N�g�̍X�V
	player1.Update(deltaTime);
	player2.Update(deltaTime);

	//	�e�U���̍쐬
	attackManager.CreateUpdate();

	//	�����蔻��̍X�V
	HitUpdate();

	//	�����J�E���g
	if (player1.GetStatas().hp == 0 && !roundEnd)
	{
		P2WinNum++;
		P2Win = true;
		roundEnd = true;
		countTime = ROUND_END_TIME;
		sound.L_Attack();
	}
	if (player2.GetStatas().hp == 0 && !roundEnd)
	{
		P1WinNum++;
		P1Win = true;
		roundEnd = true;
		countTime = ROUND_END_TIME;
		sound.L_Attack();
	}

	//	�f�o�b�O�p
	if (system->GetInputSystem().IsButtonPressed(DualShock4Input::PS))
	{
		ChangeScene(SceneID::EndGame);
	}
	if (system->GetInputSystem().IsButtonPressed(DualShock4Input::PAD))
	{
		if (debug) debug = false;
		else debug = true;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �`�揈��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::Render()
{
	DrawGraph(0, 0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Back)),1);
	attackManager.Render();
	player1.Render();
	player2.Render();
	UIRender();
	if (pause) PauseRender();

	//	�e�v���C���[�̏��(�f�o�b�O)
	if (debug)
	{
		DrawFormatString(0, 00, 0xffffff, "p1 Pos x:%.2f y:%.2f", player1.GetPosition().x, player1.GetPosition().y);
		DrawFormatString(0, 20, 0xffffff, "skill1:%d %.2f skill2:%d %.2f skill3:%d %.2f", player1.GetSkillStock()[0], player1.GetSkillCoolTime()[0], player1.GetSkillStock()[1], player1.GetSkillCoolTime()[1], player1.GetSkillStock()[2], player1.GetSkillCoolTime()[2]);
		DrawFormatString(0, 40, 0xffffff, "atk:%.1f def:%.1f spd:%.1f knock:%.1f ", player1.GetCondition().atkRate, player1.GetCondition().defRate, player1.GetCondition().spdRate, player1.GetCondition().knockRate);

		DrawFormatString(screenWidth / 2, 00, 0xffffff, "Pos x:%.2f y:%.2f", player1.GetPosition().x, player1.GetPosition().y);
		DrawFormatString(screenWidth / 2, 20, 0xffffff, "skill1:%d %.2f skill2:%d %.2f skill3:%d %.2f", player2.GetSkillStock()[0], player2.GetSkillCoolTime()[0], player2.GetSkillStock()[1], player2.GetSkillCoolTime()[1], player2.GetSkillStock()[2], player2.GetSkillCoolTime()[2]);
		DrawFormatString(screenWidth / 2, 40, 0xffffff, "atk:%.1f def:%.1f spd:%.1f knock:%.1f ", player2.GetCondition().atkRate, player2.GetCondition().defRate, player2.GetCondition().spdRate, player2.GetCondition().knockRate);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::Finalize()
{
	player1.Finalize();
	player2.Finalize();
	attackManager.Finalize();
	sdata->StopPlayBGM();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ���Z�b�g
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::Reset()
{
	Vector2 screen = { screenWidth,screenHeight };
	player1.Reset();
	player2.Reset();
	attackManager.Initialize(tdata, sdata, screen, GROUND, &player1, &player2);
	Timer = MATCH_TIME;
	countTime = COUNT_DOWN;
	countDown = true;
	roundEnd = false;
	matchEnd = false;
	P1Win = false;
	P2Win = false;

	if (P1WinNum == 0 && P2WinNum == 0)		sound.Round1();
	else if ((P1WinNum == 1 && P2WinNum == 0) || (P1WinNum == 0 && P2WinNum == 1))	sound.Round2();
	else if (P1WinNum == 1 && P2WinNum == 1)	sound.Round3();

	JugeRight();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �����蔻��X�V
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::HitUpdate()
{
	attackManager.HitUpdate(player1.GetPosition(), player1.GetScale().x, 0, &player1);
	attackManager.HitUpdate(player2.GetPosition(), player2.GetScale().x, 1, &player2);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �E���f
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::JugeRight()
{
	//	P1�����Ȃ��
	if (player1.GetPosition().x > player2.GetPosition().x)
	{
		player1.SetRight(false);
		player2.SetRight(true);
	}
	//	�t�Ȃ��
	else
	{
		player1.SetRight(true);
		player2.SetRight(false);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// UI�`��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::UIRender()
{
	//	�t�H���g�n���h���ꎞ�ۑ��p
	int drawFontHandle;
	//	�����̒����p�擾�p
	int drawWidth;
	//	�����̑傫���擾�p
	int drawFontSize;

	//	�v���C���[ID�\��
	drawFontHandle = fdata->GetFontHandle(FontID::MainFont);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "P1");
	drawFontSize = GetFontSizeToHandle(drawFontHandle);

	DrawFormatStringToHandle(player1.GetPosition().x - drawWidth / 2, player1.GetPosition().y - player1.GetScale().x - drawFontSize, 0xffffff, drawFontHandle, "P1");
	DrawFormatStringToHandle(player2.GetPosition().x - drawWidth / 2, player2.GetPosition().y - player2.GetScale().x - drawFontSize, 0xffffff, drawFontHandle, "P2");

	//	�^�C���\��
	drawFontHandle = fdata->GetFontHandle(FontID::SuperBigMainFont);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "%.0f", Timer);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, TIMER_Y - drawFontSize / 2, TIMER_COLOR, drawFontHandle, "%.0f", Timer);

	//	�������\��
	drawFontHandle = fdata->GetFontHandle(FontID::BigMainFont);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, VIC_TEXT);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	for (int i = 0; i < MATCH_WIN; i++)
	{
		// (P1)
		DrawCircle(VIC_ICON_P1X - (VIC_ICON_OFFSET + VIC_ICON_R) * i, VIC_ICON_Y, VIC_ICON_R, VIC_ICON_COLOR_DEF, true);
		if (P1WinNum > i)	DrawCircle(VIC_ICON_P1X - (VIC_ICON_OFFSET + VIC_ICON_R) * i, VIC_ICON_Y, VIC_ICON_R, VIC_ICON_COLOR_WIN, true);
		DrawFormatStringToHandle(VIC_ICON_P1X - (VIC_ICON_OFFSET + VIC_ICON_R) * i - drawWidth / 2, VIC_ICON_Y - drawFontSize / 2, VIC_ICON_COLOR_V, drawFontHandle, VIC_TEXT);
		//	(P2)
		DrawCircle(VIC_ICON_P2X + (VIC_ICON_OFFSET + VIC_ICON_R) * i, VIC_ICON_Y, VIC_ICON_R, VIC_ICON_COLOR_DEF, true);
		if (P2WinNum > i)	DrawCircle(VIC_ICON_P2X + (VIC_ICON_OFFSET + VIC_ICON_R) * i, VIC_ICON_Y, VIC_ICON_R, VIC_ICON_COLOR_WIN, true);
		DrawFormatStringToHandle(VIC_ICON_P2X + (VIC_ICON_OFFSET + VIC_ICON_R) * i - drawWidth / 2, VIC_ICON_Y - drawFontSize / 2, VIC_ICON_COLOR_V, drawFontHandle, VIC_TEXT);
	}

	//	HP�o�[�\��
	//	�O�g
	DrawBox(P1_BAR_POS_X + HP_BAR_OUT_WIDTH, HP_BAR_POS_Y - HP_BAR_OUT_WIDTH, P1_BAR_POS_X - HP_BAR_OUT_WIDTH - HP_BAR_WIDTH_MAX, HP_BAR_POS_Y + HP_BAR_HEIGHT + HP_BAR_OUT_WIDTH, HP_BAR_OUT_COLOR, true);
	DrawBox(P2_BAR_POS_X - HP_BAR_OUT_WIDTH, HP_BAR_POS_Y - HP_BAR_OUT_WIDTH, P2_BAR_POS_X + HP_BAR_OUT_WIDTH + HP_BAR_WIDTH_MAX, HP_BAR_POS_Y + HP_BAR_HEIGHT + HP_BAR_OUT_WIDTH, HP_BAR_OUT_COLOR, true);
	//	��\��
	DrawBox(P1_BAR_POS_X, HP_BAR_POS_Y, P1_BAR_POS_X - HP_BAR_WIDTH_MAX, HP_BAR_POS_Y + HP_BAR_HEIGHT, HP_BAR_EMPTY_COLOR, true);
	DrawBox(P2_BAR_POS_X, HP_BAR_POS_Y, P2_BAR_POS_X + HP_BAR_WIDTH_MAX, HP_BAR_POS_Y + HP_BAR_HEIGHT, HP_BAR_EMPTY_COLOR, true);
	//	���l�\��
	if ((player1.GetStatas().hp / player1.GetStatas().maxHp) >= HP_BAR_RED_LINE)
		DrawBox(P1_BAR_POS_X, HP_BAR_POS_Y, P1_BAR_POS_X - HP_BAR_WIDTH_MAX * (player1.GetStatas().hp / player1.GetStatas().maxHp), HP_BAR_POS_Y + HP_BAR_HEIGHT, HP_BAR_COLOR, true);
	else
		DrawBox(P1_BAR_POS_X, HP_BAR_POS_Y, P1_BAR_POS_X - HP_BAR_WIDTH_MAX * (player1.GetStatas().hp / player1.GetStatas().maxHp), HP_BAR_POS_Y + HP_BAR_HEIGHT, HP_BAR_RED_COLOR, true);
	if ((player2.GetStatas().hp / player2.GetStatas().maxHp) >= HP_BAR_RED_LINE)
		DrawBox(P2_BAR_POS_X, HP_BAR_POS_Y, P2_BAR_POS_X + HP_BAR_WIDTH_MAX * (player2.GetStatas().hp / player2.GetStatas().maxHp), HP_BAR_POS_Y + HP_BAR_HEIGHT, HP_BAR_COLOR, true);
	else
		DrawBox(P2_BAR_POS_X, HP_BAR_POS_Y, P2_BAR_POS_X + HP_BAR_WIDTH_MAX * (player2.GetStatas().hp / player2.GetStatas().maxHp), HP_BAR_POS_Y + HP_BAR_HEIGHT, HP_BAR_RED_COLOR, true);
	//	SP�o�[�\��
	//	�O�g
	DrawBox(P1_BAR_POS_X + SP_BAR_OUT_WIDTH, SP_BAR_POS_Y - SP_BAR_OUT_WIDTH, P1_BAR_POS_X - SP_BAR_OUT_WIDTH - SP_BAR_WIDTH_MAX, SP_BAR_POS_Y + SP_BAR_HEIGHT + SP_BAR_OUT_WIDTH, SP_BAR_OUT_COLOR, true);
	DrawBox(P2_BAR_POS_X - SP_BAR_OUT_WIDTH, SP_BAR_POS_Y - SP_BAR_OUT_WIDTH, P2_BAR_POS_X + SP_BAR_OUT_WIDTH + SP_BAR_WIDTH_MAX, SP_BAR_POS_Y + SP_BAR_HEIGHT + SP_BAR_OUT_WIDTH, SP_BAR_OUT_COLOR, true);
	//	��\��
	DrawBox(P1_BAR_POS_X, SP_BAR_POS_Y, P1_BAR_POS_X - SP_BAR_WIDTH_MAX, SP_BAR_POS_Y + SP_BAR_HEIGHT, SP_BAR_EMPTY_COLOR, true);
	DrawBox(P2_BAR_POS_X, SP_BAR_POS_Y, P2_BAR_POS_X + SP_BAR_WIDTH_MAX, SP_BAR_POS_Y + SP_BAR_HEIGHT, SP_BAR_EMPTY_COLOR, true);
	//	���l�\��
	if ((player1.GetStatas().sp / player1.GetStatas().maxSp >= SP_BAR_MAX_LINE))
		DrawBox(P1_BAR_POS_X, SP_BAR_POS_Y, P1_BAR_POS_X - SP_BAR_WIDTH_MAX * (player1.GetStatas().sp / player1.GetStatas().maxSp), SP_BAR_POS_Y + SP_BAR_HEIGHT, SP_BAR_MAX_COLOR, true);
	else
		DrawBox(P1_BAR_POS_X, SP_BAR_POS_Y, P1_BAR_POS_X - SP_BAR_WIDTH_MAX * (player1.GetStatas().sp / player1.GetStatas().maxSp), SP_BAR_POS_Y + SP_BAR_HEIGHT, SP_BAR_COLOR, true);
	if ((player2.GetStatas().sp / player2.GetStatas().maxSp >= SP_BAR_MAX_LINE))
		DrawBox(P2_BAR_POS_X, SP_BAR_POS_Y, P2_BAR_POS_X + SP_BAR_WIDTH_MAX * (player2.GetStatas().sp / player2.GetStatas().maxSp), SP_BAR_POS_Y + SP_BAR_HEIGHT, SP_BAR_MAX_COLOR, true);
	else
		DrawBox(P2_BAR_POS_X, SP_BAR_POS_Y, P2_BAR_POS_X + SP_BAR_WIDTH_MAX * (player2.GetStatas().sp / player2.GetStatas().maxSp), SP_BAR_POS_Y + SP_BAR_HEIGHT, SP_BAR_COLOR, true);

	//	P1�̌��݃X�L���\��
	DrawBox(
		P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * player1.GetNowSkillNum() - SKILL_BOX_WIDTH / 2 - SKILL_BOX_OUT_WIDTH,
		SKILL_POS_Y - SKILL_BOX_HEIGHT / 2 - SKILL_BOX_OUT_WIDTH,
		P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * player1.GetNowSkillNum() + SKILL_BOX_WIDTH / 2 + SKILL_BOX_OUT_WIDTH,
		SKILL_POS_Y + SKILL_BOX_HEIGHT / 2 + SKILL_BOX_OUT_WIDTH,
		SKILL_BOX_OUT_COLOR, true);
	//	P2�̌��݃X�L���\��
	DrawBox(
		P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * (player2.GetStatas().skillID.size() - 1 - player2.GetNowSkillNum()) - SKILL_BOX_WIDTH / 2 - SKILL_BOX_OUT_WIDTH,
		SKILL_POS_Y - SKILL_BOX_HEIGHT / 2 - SKILL_BOX_OUT_WIDTH,
		P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * (player2.GetStatas().skillID.size() - 1 - player2.GetNowSkillNum()) + SKILL_BOX_WIDTH / 2 + SKILL_BOX_OUT_WIDTH,
		SKILL_POS_Y + SKILL_BOX_HEIGHT / 2 + SKILL_BOX_OUT_WIDTH,
		SKILL_BOX_OUT_COLOR, true);

	drawFontHandle = fdata->GetFontHandle(FontID::MainFont);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "0");
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	//	P1���X�L��
	for (int i = 0; i < player1.GetStatas().skillID.size(); i++)
	{
		//	�X�L���\��
		DrawBox(
			P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i - SKILL_BOX_WIDTH / 2,
			SKILL_POS_Y - SKILL_BOX_HEIGHT / 2,
			P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i + SKILL_BOX_WIDTH / 2,
			SKILL_POS_Y + SKILL_BOX_HEIGHT / 2,
			SKILL_BOX_COLOR, true);
		DrawExtendGraph(
			P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i - SKILL_BOX_WIDTH / 2,
			SKILL_POS_Y - SKILL_BOX_HEIGHT / 2,
			P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i + SKILL_BOX_WIDTH / 2,
			SKILL_POS_Y + SKILL_BOX_HEIGHT / 2,
			tdata->GetTextureHandle(player1.GetStatas().skillID[i]), true);
		DrawCircle(P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i + SKILL_BOX_WIDTH / 2, SKILL_POS_Y + SKILL_BOX_HEIGHT / 2, SKILL_CIRCLE_R, SKILL_CIRCLE_COLOR, true);
		DrawFormatStringToHandle(P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i + SKILL_BOX_WIDTH / 2 - drawWidth / 2, SKILL_POS_Y + SKILL_BOX_HEIGHT / 2 - drawFontSize / 2, SKILL_STOCK_COLOR, drawFontHandle, "%d", player1.GetSkillStock()[i]);

		//	�X�L���N�[���^�C���\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, BLENDMODE_MAX);
		DrawCircleGauge(P1_SKILL_POS_X + (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i, SKILL_POS_Y, player1.GetSkillCoolTime()[i] / SKILL[player1.GetStatas().skillID[i]].ct * 100.0f, CoolTimeH);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BLENDMODE_MIN);

	}
	//	P2���X�L��
	for (int i = 0; i < player2.GetStatas().skillID.size(); i++)
	{
		//	�X�L���\��
		DrawBox(
			P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i - SKILL_BOX_WIDTH / 2,
			SKILL_POS_Y - SKILL_BOX_HEIGHT / 2,
			P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i + SKILL_BOX_WIDTH / 2,
			SKILL_POS_Y + SKILL_BOX_HEIGHT / 2,
			SKILL_BOX_COLOR, true);
		DrawExtendGraph(
			P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i - SKILL_BOX_WIDTH / 2,
			SKILL_POS_Y - SKILL_BOX_HEIGHT / 2,
			P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i + SKILL_BOX_WIDTH / 2,
			SKILL_POS_Y + SKILL_BOX_HEIGHT / 2,
			tdata->GetTextureHandle(player2.GetStatas().skillID[player2.GetStatas().skillID.size() - 1 - i]), true);
		DrawCircle(P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i + SKILL_BOX_WIDTH / 2, SKILL_POS_Y + SKILL_BOX_HEIGHT / 2, SKILL_CIRCLE_R, SKILL_CIRCLE_COLOR, true);
		DrawFormatStringToHandle(P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i + SKILL_BOX_WIDTH / 2 - drawWidth / 2, SKILL_POS_Y + SKILL_BOX_HEIGHT / 2 - drawFontSize / 2, SKILL_STOCK_COLOR, drawFontHandle, "%d", player2.GetSkillStock()[player2.GetStatas().skillID.size() - 1 - i]);

		//	�X�L���N�[���^�C���\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, BLENDMODE_MAX);
		DrawCircleGauge(P2_SKILL_POS_X - (SKILL_BOX_WIDTH + SKILL_BOX_OFFSET) * i, SKILL_POS_Y, player2.GetSkillCoolTime()[player2.GetStatas().skillID.size() - 1 - i] / SKILL[player2.GetStatas().skillID[player2.GetStatas().skillID.size() - 1 - i]].ct * 100.0f, CoolTimeH);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, BLENDMODE_MIN);
	}

	//	�J�E���g�_�E���\��
	if (countDown)
	{
		//	�^�C���\��
		drawFontHandle = fdata->GetFontHandle(FontID::SuperBigMainFont);
		drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "%.0f", countTime);
		drawFontSize = GetFontSizeToHandle(drawFontHandle);
		DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, screenHeight / 2 - drawFontSize / 2, TIMER_COLOR, drawFontHandle, "%.0f", countTime);
	}

	//	���E���h�I���\��
	if (roundEnd)
	{
		if (P1Win)
		{
			drawFontHandle = fdata->GetFontHandle(FontID::SuperBigMainFont);
			drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "Player1WIN!");
			drawFontSize = GetFontSizeToHandle(drawFontHandle);
			DrawFormatStringToHandle(1 * screenWidth / 4 - drawWidth / 2, screenHeight / 3 - drawFontSize / 2, TIMER_COLOR, drawFontHandle, "Player1WIN!");
		}
		else if (P2Win)
		{
			drawFontHandle = fdata->GetFontHandle(FontID::SuperBigMainFont);
			drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "Player2WIN!");
			drawFontSize = GetFontSizeToHandle(drawFontHandle);
			DrawFormatStringToHandle(3 * screenWidth / 4 - drawWidth / 2, screenHeight / 3 - drawFontSize / 2, TIMER_COLOR, drawFontHandle, "Player2WIN!");
		}
	}

	//	�}�b�`�I��
	if (matchEnd)
	{

	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �|�[�Y�X�V
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::PauseUpdate()
{
	if (system->GetInputSystem().IsButtonPressed(DualShock4Input::CIRCLE))
	{
		sound.Decision();
		ChangeScene(SceneID::CharaSelect);
	}
	if (system->GetInputSystem().IsButtonPressed(DualShock4Input::CROSS))
	{
		sound.Select();
		pause = false;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �|�[�Y�`��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void PlayScene::PauseRender()
{
	//	�t�H���g�n���h���ꎞ�ۑ��p
	int drawFontHandle;
	//	�����̑傫���擾�p
	int drawFontSize;
	//	�����̒����p�擾�p
	int drawWidth;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, screenWidth, screenHeight, 0x000000, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	drawFontHandle = fdata->GetFontHandle(FontID::SuperBigEdgeMainFont);
	drawFontSize = GetFontSizeToHandle(drawFontHandle);
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "�|�[�Y��");
	DrawFormatStringToHandle(screenWidth / 2 - drawWidth / 2, screenHeight / 2 - drawFontSize / 2, 0xffffff, drawFontHandle, "�|�[�Y��");

	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "�~�F����");
	DrawFormatStringToHandle(1 * screenWidth / 4 - drawWidth / 2, 2 * screenHeight / 3 - drawFontSize / 2, 0xffffff, drawFontHandle, "�~�F����");
	drawWidth = GetDrawFormatStringWidthToHandle(drawFontHandle, "���F�I����");
	DrawFormatStringToHandle(3 * screenWidth / 4 - drawWidth / 2, 2 * screenHeight / 3 - drawFontSize / 2, 0xffffff, drawFontHandle, "���F�I����");
}
