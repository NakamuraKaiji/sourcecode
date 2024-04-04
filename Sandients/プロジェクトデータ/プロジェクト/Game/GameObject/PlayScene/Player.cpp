//----------------------------------------------------------------------------------------------------
//	Player・・・サンドウィッチ達
// 
//----------------------------------------------------------------------------------------------------
#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "../../GameDatas/ControllerInput.h"

#define DEF_HP		600			//	基礎体力
#define DEF_ATK		80			//	基礎攻撃力
#define DEF_DEF		10			//	基礎防御力
#define DEF_WEI		1			//	基礎重量

#define PLAYER_SCALE 100		//	大きさ

#define ACCELE		50.0f		//	加速力
#define SPEED		400.0f		//	速度
#define COLISION	0.91f		//	摩擦	
#define JUMP		1000.0f		//	跳躍力
#define GRABITY		55.0f		//	重力

#define MAX_COMBO_PUNNISH	2.5f		//	コンボ最大時の後隙
#define HITED_RATE			5000

#define GUARD_VAL			0.3f		//	ガード中のダメージ倍率
#define SP_POWER			1.5f		//	SP攻撃増加量
#define	SP_ADD				15.0f		//	SP増加量
#define	SP_G_ADD			8.0f		//	SPガード増加量
#define	SP_DEC				10.0f		//	SP減少量
#define SP_TIME				10.0f		//	SP時間

#define DROP_ANI_TIME		0.15f		//	落下モーション時間推移
#define STAND_ANI_TIME		0.1f		//	待機モーション時間推移
#define INVI_ANI_TIME		0.1f		//	点滅間隔

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
// 初期化
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
// 更新
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
	//	スキルのクールタイム減少
	for (size_t i = 0; i < statas.skillID.size(); i++)
	{
		skillCoolTime[i] -= deltaTime;

		//	SP状態なら減少量上昇
		if (special) skillCoolTime[i] -= deltaTime;

		if (skillCoolTime[i] < 0.0f)
		{
			skillCoolTime[i] = 0.0f;
			//	ストック追加処理
			if (skillStock[i] < SKILL[statas.skillID[i]].stock)
			{
				skillStock[i]++;

				//	ストックが貯められるなら貯める
				if (skillStock[i] < SKILL[statas.skillID[i]].stock)
					skillCoolTime[i] = SKILL[statas.skillID[i]].ct;
			}
		}
	}

	//	前隙
	skillPunishTime -= deltaTime;
	if (skillPunishTime < 0.0f)
	{
		skillPunishTime = 9999.0f;
		UseSkill();
	}

	//	前隙（攻撃）
	attackPunishTime -= deltaTime;
	if (attackPunishTime < 0.0f)
	{
		attackPunishTime = 9999.9f;
		UseAttack();
	}

	//	攻撃コンボ持続残り時間
	attackComboRemainTime -= deltaTime;
	if (attackComboRemainTime < 0.0f)
	{
		nowAtkNum = 0;
		attackComboRemainTime = 0.0f;
	}

	//	動けない時間計算
	cantMoveTime -= deltaTime;
	if (cantMoveTime < 0.0f)
	{
		cantMoveTime = 0.0f;
		attack = false;
	}

	//	無敵時間減少
	invincibleTime -= deltaTime;
	if (invincibleTime < 0.0f) invincibleTime = 0.0f;

	//	SP時間減少
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
	//	プレイヤーの操作
	if (cantMoveTime <= 0.0f && statas.hp > 0)
	{
		PlayerControll();
	}

	//	地上にいるとき
	if (!fly)
	{
		//	摩擦処理
		vel.x *= COLISION;
	}

	//	重力処理
	vel.y -= GRABITY;
	jumpVal -= GRABITY;
	//	ジャンプのベクトルが無くなったら
	if (jumpVal <= 0.0f)
	{
		jumpVal = 0.0f;
		//	落下していたら
		if (cantMoveTime <= 0.0f)
		{
			dropTime += deltaTime;
		}
	}
	else
	{
		standbyTime = 0.0f;
	}

	//	待機時間
	standbyTime += deltaTime;
	if (standbyTime > STAND_ANI_TIME * 10)
	{
		standbyTime = 0.0f;
	}


	//	位置情報を変更
	pos.x += vel.x * deltaTime;
	pos.y += -vel.y * deltaTime;

	//	床の判定処理
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

	//	壁判定処理
	if (pos.x > screenSize.x) pos.x = screenSize.x;
	else if (pos.x < 0.0f) pos.x = 0.0f;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 描画
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Render()
{
	//	無敵時間
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

	//	ガード時
	if (guard)
	{
		DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerGuard)), 1, !right);
		DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerBarrier)), 1, !right);
	}
	//	攻撃時
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
	//	ヒット時
	else if (cantMoveTime)
	{
		DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerGuard)), 1, !right);
	}
	//	チャージ時
	else if (charge)
	{
		DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerGuard)), 1, !right);
	}
	//	ジャンプ時
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
	//	落下時
	else if (dropTime)
	{
		if (dropTime < DROP_ANI_TIME)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerDrop1)), 1, !right);
		else if (dropTime < DROP_ANI_TIME * 2)
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerDrop2)), 1, !right);
		else
			DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::PlayerDrop3)), 1, !right);
	}
	//	その他
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
// 解放処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Finalize()
{
	skillCoolTime.clear();
	skillStock.clear();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// プレイヤーの操作
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::PlayerControll()
{
	//	PADの左スティック取得
	int x;
	int y;
	GetJoypadAnalogInput(&x, &y, padNum);

	//	空中にいないとき
	if (!fly)
	{
		//	ガードをする
		if (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::RIGHT2) || (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::LEFT2)))
		{
			guard = true;
			return;
		}

		//	ゲージを貯める
		if (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::SQUARE) && !special)
		{
			charge = true;
			statas.sp += SP_ADD * deltaTime;
			if (statas.sp >= statas.maxSp) statas.sp = statas.maxSp;
			return;
		}

		//	ジャンプ
		if (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::CROSS) || system->GetInputSystem().IsTipPressed(padNum, DualShock4Input::LS_Y, DualShock4Input::LS_UP))
		{
			vel.y = JUMP * statas.weight * conditoin.spdRate;
			sdata->Jump();
			jumpVal = vel.y;
			maxJumpVal = jumpVal;
		}
	}

	//	加速処理
	if (x > 0)      x = 1;
	else if (x < 0) x = -1;
	if (fly)
		vel.x += ACCELE * statas.weight * conditoin.spdRate * x * 0.4f;
	else
		vel.x += ACCELE * statas.weight * conditoin.spdRate * x;

	//	移動速度制限
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

	//	スキル選択
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

	//	通常攻撃
	if (system->GetInputSystem().IsButtonPressed(padNum, DualShock4Input::CIRCLE))
	{
		attack = true;
		attackPunishTime = ATTACK[statas.atkID].beforePunishTime;
		maxAttackTime = attackPunishTime;
		cantMoveTime = ATTACK[statas.atkID].beforePunishTime;
	}
	
	//	スキル使用
	if(system->GetInputSystem().IsButtonPressed(padNum, DualShock4Input::TRIANGLE))
	{
		if (skillStock[nowSkillNum] > 0)
		{
			skillPunishTime = SKILL[statas.skillID[nowSkillNum]].beforePunishTime;
			cantMoveTime    = SKILL[statas.skillID[nowSkillNum]].beforePunishTime;
		}
	}

	//	SP使用
	if (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::RIGHT1) && (system->GetInputSystem().IsButtonDown(padNum, DualShock4Input::LEFT1)))
	{
		if (statas.sp >= statas.maxSp)
		{
			//	SP状態移行
			special = true;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 攻撃
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::UseAttack()
{
	sdata->Blow();
	//	コンボ追加
	nowAtkNum++;

	//	攻撃作成
	attackManager->CreatePrepareAttack(pID, statas.atkID, nowAtkNum);

	//	最大コンボ出なければ通常攻撃
	if (nowAtkNum < ATTACK[statas.atkID].maxConbo)
	{
		//	後隙設定
		cantMoveTime = ATTACK[statas.atkID].afterPunishTime;
		//	コンボ時間設定
		attackComboRemainTime = ATTACK[statas.atkID].afterPunishTime * ATTACK[statas.atkID].maxConboRate;
	}
	//	最大なら
	else
	{
		//	後隙設定
		cantMoveTime = ATTACK[statas.atkID].afterPunishTime * ATTACK[statas.atkID].maxConboPunishRate;
		nowAtkNum = 0;
	}

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// スキル使用
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::UseSkill()
{
	sdata->useSkill();
	//	クールタイム設定
	if (skillStock[nowSkillNum] == SKILL[statas.skillID[nowSkillNum]].stock)
		skillCoolTime[nowSkillNum] = SKILL[statas.skillID[nowSkillNum]].ct;
	skillStock[nowSkillNum]--;
	cantMoveTime = SKILL[statas.skillID[nowSkillNum]].afterPunishTime;

	//	攻撃作成
	attackManager->CreatePrepareAttack(pID, statas.skillID[nowSkillNum]);

	score.useSkillNum[nowSkillNum]++;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 攻撃をうけた処理(攻撃を与えた相手、攻撃の威力、ノックバック量、角度（右が90°）)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::Hited(float atk, float power, float knock, float deg)
{
	float guardVal = 1.0f;

	//	無敵時間なら計算しない
	if (invincibleTime > 0.0f) return;

	//	ガード中の処理
	if (guard)
	{
		guardVal = GUARD_VAL;
	}

	//	技リセット
	attackPunishTime = 9999.9f;
	skillPunishTime = 9999.9f;
	attackComboRemainTime = 0.0f;

	// HP減少
	float dmg = 0.0f;
	dmg = ((atk * power) - statas.def) * guardVal;
	if (dmg < 1.0f) dmg = 1.0f;
	this->statas.hp -= dmg;
	score.hitedDamage += dmg;
	if (this->statas.hp < 0.0f) this->statas.hp = 0.0f;

	//	角度計算
	float radian = deg * (static_cast<float>(DX_PI) / 180);

	float x = cosf(radian);
	float y = sinf(radian);

	vel.x += knock * statas.weight * x * guardVal;
	vel.y += knock * statas.weight * y * guardVal;

	//	跳躍
	if (knock > 0.0f)
	{
		jumpVal = 0.0f;
		dropTime = 0.0f;
		standbyTime = 0.0f;
		attack = false;
	}

	//	動けない時間追加
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
// リセット
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
// 正面を設定
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetRight(bool right)
{
	this->right = right;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// パッド番号をセット
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetPadNum(int padNum)
{
	this->padNum = padNum;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 状態異常設定
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetCondition(PlayerCondition condition)
{
	this->conditoin = condition;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 状態異常リセット
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::ResetCondition()
{
	this->conditoin = PlayerCondition();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 行動不能時間設定
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetCantMoveTime(float time)
{
	cantMoveTime = time;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// クールタイム設定
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetCoolTime(int id, float ct)
{
	skillCoolTime[id] = ct;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ステータス設定
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetStatas(PlayerStatas p)
{
	statas = p;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 位置設定
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void Player::SetPosition(Vector2 pos)
{
	this->pos = pos;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ステータス受渡
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
PlayerStatas Player::GetStatas()
{
	return statas;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 状態異常受渡
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
PlayerCondition Player::GetCondition()
{
	return conditoin;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 座標位置受渡
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Vector2 Player::GetPosition()
{
	return pos;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 大きさ受渡
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
// パッド番号を渡す
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int Player::GetPadNum()
{
	return padNum;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// プレイヤーIDを返す
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
// 現在のスキル番号受渡
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int Player::GetNowSkillNum()
{
	return nowSkillNum;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// スキルのクールタイムを渡す
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
std::vector<float> Player::GetSkillCoolTime()
{
	return skillCoolTime;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// スキルのストック数を渡す
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
std::vector<int> Player::GetSkillStock()
{
	return skillStock;
}
