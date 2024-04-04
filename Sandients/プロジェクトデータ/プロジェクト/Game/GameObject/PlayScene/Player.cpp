//----------------------------------------------------------------------------------------------------
//	Player�E�E�E�T���h�E�B�b�`�B
// 
//----------------------------------------------------------------------------------------------------
#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "../../GameDatas/ControllerInput.h"

#define DEF_HP		600			//	��b�̗�
#define DEF_ATK		80			//	��b�U����
#define DEF_DEF		10			//	��b�h���
#define DEF_WEI		1			//	��b�d��

#define PLAYER_SCALE 100		//	�傫��

#define ACCELE		50.0f		//	������
#define SPEED		400.0f		//	���x
#define COLISION	0.91f		//	���C	
#define JUMP		1000.0f		//	������
#define GRABITY		55.0f		//	�d��

#define MAX_COMBO_PUNNISH	2.5f		//	�R���{�ő厞�̌㌄
#define HITED_RATE			5000

#define GUARD_VAL			0.3f		//	�K�[�h���̃_���[�W�{��
#define SP_POWER			1.5f		//	SP�U��������
#define	SP_ADD				15.0f		//	SP������
#define	SP_G_ADD			8.0f		//	SP�K�[�h������
#define	SP_DEC				10.0f		//	SP������
#define SP_TIME				10.0f		//	SP����

#define DROP_ANI_TIME		0.15f		//	�������[�V�������Ԑ���
#define STAND_ANI_TIME		0.1f		//	�ҋ@���[�V�������Ԑ���
#define INVI_ANI_TIME		0.1f		//	�_�ŊԊu

Player::Player():
	system(nullptr),
	tdata(nullptr),
	sdata(nullptr),
	screenSize{},
	statas(),
	pos(),
	scale(),
	right(),
	padNum(),
	pID(),
	jumpVal(),
	standbyTime(),
	maxJumpVal(),
	dropTime(),
	fly(),
	attack(),
	charge(),
	defPos(),
	special(),
	skillPunishTime(),
	attackPunishTime(),
	attackComboRemainTime(),
	cantMoveTime(),
	invincibleTime(),
	guard(),
	nowSkillNum(),
	nowAtkNum()
{
}

Player::~Player()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Initialize(GameSystemObjects* system, TextureManger* tdata, Sound* sdata, AttackManager* attackManager, int pID, Vector2 screen, float ground, PlayerStatas statas, Vector2 defpos)
{
	this->system = system;
	this->tdata = tdata;
	this->sdata = sdata;
	this->attackManager = attackManager;
	this->pID = pID;
	this->screenSize = screen;
	this->ground = ground;

	this->statas = statas;
	this->statas.hp = DEF_HP + (statas.hp / 10) * DEF_HP;
	this->statas.atk = DEF_ATK + (statas.atk / 10) * DEF_ATK;
	this->statas.def = DEF_DEF + (statas.def / 10) * DEF_DEF;
	this->statas.weight = DEF_WEI + (statas.weight / 20) * DEF_WEI;
	this->statas.maxHp = this->statas.hp;
	this->statas.maxSp = this->statas.sp;
	this->statas.sp = 0.0f;

	pos = defpos;
	this->defPos = defpos;
	scale = { 100.0f,100.0f };
	vel = {};
	jumpVal = 0.0f;
	maxJumpVal = 0.0f;
	dropTime = 0.0f;
	standbyTime = 0.0f;

	guard = false;
	right = false;
	fly = false;
	special = false;
	charge = false;
	attack = false;

	attackPunishTime = 9999.9f;
	skillPunishTime = 9999.9f;
	cantMoveTime = 0.0f;
	attackComboRemainTime = 0.0f;
	invincibleTime = 0.0f;

	nowAtkNum = 0;
	nowSkillNum = 0;
	skillCoolTime.clear();
	skillStock.clear();
	for (size_t i = 0; i < statas.skillID.size(); i++)
	{
		skillCoolTime.push_back(0.0f);
		skillStock.push_back(SKILL[statas.skillID[i]].stock);
		score.useSkillNum.push_back(0);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �X�V
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	charge = false;
	//	SPUP
	if (special)
	{
		conditoin.atkRate = SP_POWER;
	}
	//	�X�L���̃N�[���^�C������
	for (size_t i = 0; i < statas.skillID.size(); i++)
	{
		skillCoolTime[i] -= deltaTime;

		//	SP��ԂȂ猸���ʏ㏸
		if (special) skillCoolTime[i] -= deltaTime;

		if (skillCoolTime[i] < 0.0f)
		{
			skillCoolTime[i] = 0.0f;
			//	�X�g�b�N�ǉ�����
			if (skillStock[i] < SKILL[statas.skillID[i]].stock)
			{
				skillStock[i]++;

				//	�X�g�b�N�����߂���Ȃ璙�߂�
				if (skillStock[i] < SKILL[statas.skillID[i]].stock)
					skillCoolTime[i] = SKILL[statas.skillID[i]].ct;
			}
		}
	}

	//	�O��
	skillPunishTime -= deltaTime;
	if (skillPunishTime < 0.0f)
	{
		skillPunishTime = 9999.0f;
		UseSkill();
	}

	//	�O���i�U���j
	attackPunishTime -= deltaTime;
	if (attackPunishTime < 0.0f)
	{
		attackPunishTime = 9999.9f;
		UseAttack();
	}

	//	�U���R���{�����c�莞��
	attackComboRemainTime -= deltaTime;
	if (attackComboRemainTime < 0.0f)
	{
		nowAtkNum = 0;
		attackComboRemainTime = 0.0f;
	}

	//	�����Ȃ����Ԍv�Z
	cantMoveTime -= deltaTime;
	if (cantMoveTime < 0.0f)
	{
		cantMoveTime = 0.0f;
		attack = false;
	}

	//	���G���Ԍ���
	invincibleTime -= deltaTime;
	if (invincibleTime < 0.0f) invincibleTime = 0.0f;

	//	SP���Ԍ���
	if (special)
	{
		statas.sp -= SP_DEC * deltaTime;
		if (statas.sp <= 0.0f)
		{
			statas.sp = 0.0f;
			special = false;
		}
	}

	guard = false;
	//	�v���C���[�̑���
	if (cantMoveTime <= 0.0f && statas.hp > 0)
	{
		PlayerControll();
	}

	//	�n��ɂ���Ƃ�
	if (!fly)
	{
		//	���C����
		vel.x *= COLISION;
	}

	//	�d�͏���
	vel.y -= GRABITY;
	jumpVal -= GRABITY;
	//	�W�����v�̃x�N�g���������Ȃ�����
	if (jumpVal <= 0.0f)
	{
		jumpVal = 0.0f;
		//	�������Ă�����
		if (cantMoveTime <= 0.0f)
		{
			dropTime += deltaTime;
		}
	}
	else
	{
		standbyTime = 0.0f;
	}

	//	�ҋ@����
	standbyTime += deltaTime;
	if (standbyTime > STAND_ANI_TIME * 10)
	{
		standbyTime = 0.0f;
	}


	//	�ʒu����ύX
	pos.x += vel.x * deltaTime;
	pos.y += -vel.y * deltaTime;

	//	���̔��菈��
	if (pos.y + scale.y > screenSize.y * ground)
	{
		vel.y = 0.0f;
		pos.y = screenSize.y * ground - scale.y;
		fly = false;
		dropTime = 0.0f;
	}
	else
	{
		fly = true;
	}

	//	�ǔ��菈��
	if (pos.x > screenSize.x) pos.x = screenSize.x;
	else if (pos.x < 0.0f) pos.x = 0.0f;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �`��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Render()
{
	//	���G����
	if (invincibleTime > 0.0f)
	{
		inviTime += deltaTime;
		if (inviTime > INVI_ANI_TIME)
		{
			return;
		}
		else if (inviTime > INVI_ANI_TIME * 2)
		{
			inviTime = 0.0f;
		}
	}

	//	�K�[�h��
	if (guard)
	{
		DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerGuard)), 1, !right);
		DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerBarrier)), 1, !right);
	}
	//	�U����
	else if (attack)
	{
		if (attackPunishTime <= 4 * maxAttackTime / 4.0f)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerAttack1)), 1, !right);
		else if (attackPunishTime <= 3 * maxAttackTime / 4.0f)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerAttack2)), 1, !right);
		else if (attackPunishTime <= 2 * maxAttackTime / 4.0f)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerAttack3)), 1, !right);
		else
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerAttack4)), 1, !right);
	}
	//	�q�b�g��
	else if (cantMoveTime)
	{
		DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerGuard)), 1, !right);
	}
	//	�`���[�W��
	else if (charge)
	{
		DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerGuard)), 1, !right);
	}
	//	�W�����v��
	else if (jumpVal)
	{
		if (jumpVal > maxJumpVal * 0.75)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerJump1)), 1, !right);
		else if (jumpVal > maxJumpVal * 0.5)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerJump2)), 1, !right);
		else if (jumpVal > maxJumpVal * 0.25)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerJump3)), 1, !right);
		else
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerJump4)), 1, !right);
	}
	//	������
	else if (dropTime)
	{
		if (dropTime < DROP_ANI_TIME)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerDrop1)), 1, !right);
		else if (dropTime < DROP_ANI_TIME * 2)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerDrop2)), 1, !right);
		else
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerDrop3)), 1, !right);
	}
	//	���̑�
	else
	{
		if (standbyTime < STAND_ANI_TIME)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby1)), 1, !right);
		else if (standbyTime < STAND_ANI_TIME * 2)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby2)), 1, !right);
		else if (standbyTime < STAND_ANI_TIME * 3)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby3)), 1, !right);
		else if (standbyTime < STAND_ANI_TIME * 4)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby4)), 1, !right);
		else if (standbyTime < STAND_ANI_TIME * 5)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby5)), 1, !right);
		else if (standbyTime < STAND_ANI_TIME * 6)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby6)), 1, !right);
		else if (standbyTime < STAND_ANI_TIME * 7)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby7)), 1, !right);
		else if (standbyTime < STAND_ANI_TIME * 8)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby8)), 1, !right);
		else if (standbyTime < STAND_ANI_TIME * 9)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby9)), 1, !right);
		else
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerStandby10)), 1, !right);
	}
	int color = 0xffffff;
	if (special) color = 0xffff00;
	//DrawCircle(pos.x, pos.y, scale.x, color);
	//DrawCircle(pos.x, pos.y, scale.x, 0xff0000, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 190);
	if (special)
		DrawOval(pos.x, pos.y, scale.x, scale.y / 2, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Finalize()
{
	skillCoolTime.clear();
	skillStock.clear();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �v���C���[�̑���
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::PlayerControll()
{
	//	PAD�̍��X�e�B�b�N�擾
	int x;
	int y;
	GetJoypadAnalogInput(&x, &y, padNum);

	//	�󒆂ɂ��Ȃ��Ƃ�
	if (!fly)
	{
		//	�K�[�h������
		if (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::RIGHT2) || (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::LEFT2)))
		{
			guard = true;
			return;
		}

		//	�Q�[�W�𒙂߂�
		if (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::SQUARE) && !special)
		{
			charge = true;
			statas.sp += SP_ADD * deltaTime;
			if (statas.sp >= statas.maxSp) statas.sp = statas.maxSp;
			return;
		}

		//	�W�����v
		if (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::CROSS) || system->GetInputSystem().IsTipPressed(padNum, DualShock4Input::LS_Y, DualShock4Input::LS_UP))
		{
			vel.y = JUMP * statas.weight * conditoin.spdRate;
			sdata->Jump();
			jumpVal = vel.y;
			maxJumpVal = jumpVal;
		}
	}

	//	��������
	if (x > 0)      x = 1;
	else if (x < 0) x = -1;
	if (fly)
		vel.x += ACCELE * statas.weight * conditoin.spdRate * x * 0.4f;
	else
		vel.x += ACCELE * statas.weight * conditoin.spdRate * x;

	//	�ړ����x����
	if (vel.x < -SPEED * statas.weight * conditoin.spdRate)
	{
		if (fly) vel.x = -SPEED * statas.weight * conditoin.spdRate * 0.4f;
		else    vel.x = -SPEED * statas.weight * conditoin.spdRate;
	}
	else if (vel.x > SPEED * statas.weight * conditoin.spdRate)
	{
		if (fly) vel.x = SPEED * statas.weight * conditoin.spdRate * 0.4f;
		else    vel.x = SPEED * statas.weight * conditoin.spdRate;
	}

	//	�X�L���I��
	if (system->GetInputSystem().IsTipPressed(padNum, DualShock4Input::RS_X, DualShock4Input::RS_LEFT) || system->GetInputSystem().IsPOVPressed(padNum, DualShock4Input::ARROW_POV, DualShock4Input::ARROW_LEFT))
	{
		nowSkillNum--;
		if (nowSkillNum < 0) nowSkillNum = 0;
	}
	if (system->GetInputSystem().IsTipPressed(padNum, DualShock4Input::RS_X, DualShock4Input::RS_RIGHT) || system->GetInputSystem().IsPOVPressed(padNum, DualShock4Input::ARROW_POV, DualShock4Input::ARROW_RIGHT))
	{
		nowSkillNum++;
		if (nowSkillNum > statas.skillID.size() - 1) nowSkillNum = statas.skillID.size() - 1;
	}

	//	�ʏ�U��
	if (system->GetInputSystem().IsButtonPressed(padNum, DualShock4Input::CIRCLE))
	{
		attack = true;
		attackPunishTime = ATTACK[statas.atkID].beforePunishTime;
		maxAttackTime = attackPunishTime;
		cantMoveTime = ATTACK[statas.atkID].beforePunishTime;
	}
	
	//	�X�L���g�p
	if(system->GetInputSystem().IsButtonPressed(padNum, DualShock4Input::TRIANGLE))
	{
		if (skillStock[nowSkillNum] > 0)
		{
			skillPunishTime = SKILL[statas.skillID[nowSkillNum]].beforePunishTime;
			cantMoveTime    = SKILL[statas.skillID[nowSkillNum]].beforePunishTime;
		}
	}

	//	SP�g�p
	if (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::RIGHT1) && (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::LEFT1)))
	{
		if (statas.sp >= statas.maxSp)
		{
			//	SP��Ԉڍs
			special = true;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �U��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::UseAttack()
{
	sdata->Blow();
	//	�R���{�ǉ�
	nowAtkNum++;

	//	�U���쐬
	attackManager->CreatePrepareAttack(pID, statas.atkID, nowAtkNum);

	//	�ő�R���{�o�Ȃ���Βʏ�U��
	if (nowAtkNum < ATTACK[statas.atkID].maxConbo)
	{
		//	�㌄�ݒ�
		cantMoveTime = ATTACK[statas.atkID].afterPunishTime;
		//	�R���{���Ԑݒ�
		attackComboRemainTime = ATTACK[statas.atkID].afterPunishTime * ATTACK[statas.atkID].maxConboRate;
	}
	//	�ő�Ȃ�
	else
	{
		//	�㌄�ݒ�
		cantMoveTime = ATTACK[statas.atkID].afterPunishTime * ATTACK[statas.atkID].maxConboPunishRate;
		nowAtkNum = 0;
	}

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �X�L���g�p
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::UseSkill()
{
	sdata->useSkill();
	//	�N�[���^�C���ݒ�
	if (skillStock[nowSkillNum] == SKILL[statas.skillID[nowSkillNum]].stock)
		skillCoolTime[nowSkillNum] = SKILL[statas.skillID[nowSkillNum]].ct;
	skillStock[nowSkillNum]--;
	cantMoveTime = SKILL[statas.skillID[nowSkillNum]].afterPunishTime;

	//	�U���쐬
	attackManager->CreatePrepareAttack(pID, statas.skillID[nowSkillNum]);

	score.useSkillNum[nowSkillNum]++;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �U��������������(�U����^��������A�U���̈З́A�m�b�N�o�b�N�ʁA�p�x�i�E��90���j)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Hited(float atk, float power, float knock, float deg)
{
	float guardVal = 1.0f;

	//	���G���ԂȂ�v�Z���Ȃ�
	if (invincibleTime > 0.0f) return;

	//	�K�[�h���̏���
	if (guard)
	{
		guardVal = GUARD_VAL;
	}

	//	�Z���Z�b�g
	attackPunishTime = 9999.9f;
	skillPunishTime = 9999.9f;
	attackComboRemainTime = 0.0f;

	// HP����
	float dmg = 0.0f;
	dmg = ((atk * power) - statas.def) * guardVal;
	if (dmg < 1.0f) dmg = 1.0f;
	this->statas.hp -= dmg;
	score.hitedDamage += dmg;
	if (this->statas.hp < 0.0f) this->statas.hp = 0.0f;

	//	�p�x�v�Z
	float radian = deg * (static_cast<float>(DX_PI) / 180);

	float x = cosf(radian);
	float y = sinf(radian);

	vel.x += knock * statas.weight * x * guardVal;
	vel.y += knock * statas.weight * y * guardVal;

	//	����
	if (knock > 0.0f)
	{
		jumpVal = 0.0f;
		dropTime = 0.0f;
		standbyTime = 0.0f;
		attack = false;
	}

	//	�����Ȃ����Ԓǉ�
	if (!guard)
	{
		cantMoveTime = knock / HITED_RATE;
		invincibleTime = knock / HITED_RATE;
		sdata->S_Attack();
	}
	else
	{
		cantMoveTime = knock / HITED_RATE * guardVal;
		sdata->Guard();
		if (!special)
			statas.sp += SP_G_ADD;
		if (statas.sp > statas.maxSp) statas.sp = statas.maxSp;

	}
	return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ���Z�b�g
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Reset()
{
	this->statas.hp = this->statas.maxHp;
	this->statas.sp = 0.0f;

	this->conditoin = PlayerCondition();
	pos = defPos;
	scale = { PLAYER_SCALE,PLAYER_SCALE };
	vel = { 0.0f,0.0f };

	guard = false;
	right = false;
	fly = false;
	special = false;

	attackPunishTime = 9999.9f;
	skillPunishTime = 9999.9f;
	cantMoveTime = 0.0f;
	attackComboRemainTime = 0.0f;
	invincibleTime = 0.0f;
	standbyTime = 0.0f;
	jumpVal = 0.0f;
	dropTime = 0.0f;

	nowAtkNum = 0;
	nowSkillNum = 0;
	for (size_t i = 0; i < statas.skillID.size(); i++)
	{
		skillCoolTime[i] = 0.0f;
		skillStock[i] = SKILL[statas.skillID[i]].stock;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ���ʂ�ݒ�
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetRight(bool right)
{
	this->right = right;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �p�b�h�ԍ����Z�b�g
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetPadNum(int padNum)
{
	this->padNum = padNum;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ��Ԉُ�ݒ�
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetCondition(PlayerCondition condition)
{
	this->conditoin = condition;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ��Ԉُ탊�Z�b�g
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::ResetCondition()
{
	this->conditoin = PlayerCondition();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �s���s�\���Ԑݒ�
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetCantMoveTime(float time)
{
	cantMoveTime = time;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �N�[���^�C���ݒ�
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetCoolTime(int id, float ct)
{
	skillCoolTime[id] = ct;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �X�e�[�^�X�ݒ�
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetStatas(PlayerStatas p)
{
	statas = p;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �ʒu�ݒ�
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetPosition(Vector2 pos)
{
	this->pos = pos;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �X�e�[�^�X��n
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
PlayerStatas Player::GetStatas()
{
	return statas;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ��Ԉُ��n
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
PlayerCondition Player::GetCondition()
{
	return conditoin;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ���W�ʒu��n
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Vector2 Player::GetPosition()
{
	return pos;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �傫����n
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Vector2 Player::GetScale()
{
	return scale;
}

bool Player::GetIsRight()
{
	return right;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �p�b�h�ԍ���n��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int Player::GetPadNum()
{
	return padNum;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �v���C���[ID��Ԃ�
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int Player::GetPID()
{
	return pID;
}

Score Player::GetScore()
{
	return score;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ���݂̃X�L���ԍ���n
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int Player::GetNowSkillNum()
{
	return nowSkillNum;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �X�L���̃N�[���^�C����n��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
std::vector<float> Player::GetSkillCoolTime()
{
	return skillCoolTime;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �X�L���̃X�g�b�N����n��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
std::vector<int> Player::GetSkillStock()
{
	return skillStock;
}
