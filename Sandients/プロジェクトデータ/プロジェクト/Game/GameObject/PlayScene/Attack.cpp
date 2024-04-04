#include "Attack.h"
#include "Player.h"

Attack::Attack():
	tdata(),
	sdata(),
	isDelete(),
	screen(),
	ground(),
	pos(),
	scale(),
	vel(),
	ePos(),
	pScale(),
	atk(),
	ID(),
	pSkillID(),
	attackNum(),
	pID(),
	right(),
	skill(),
	time(),
	mPlayer(),
	ePlayer(),
	attack()
{
}

Attack::~Attack()
{
}

void Attack::BaseInitialize(TextureManger* tdata, Sound* sdata, Vector2 screen, float ground, Player* mPlayer, Vector2 ePos, int ID, int attackNum)
{
	this->tdata = tdata;
	this->sdata = sdata;
	isDelete = false;
	this->mPlayer = mPlayer;
	this->screen = screen;
	this->ground = ground;
	this->pos = mPlayer->GetPosition();
	this->ePos = ePos;
	this->pScale = mPlayer->GetScale().x;
	if (attackNum < 0)
	{
		this->skill = true;
	}
	else
	{
		this->skill = false;
	}
	this->atk = mPlayer->GetStatas().atk * mPlayer->GetCondition().atkRate;
	this->pID = mPlayer->GetPID();
	this->pSkillID = mPlayer->GetNowSkillNum();
	this->right = mPlayer->GetIsRight();
	this->ID = ID;
	this->attackNum = attackNum;
	time = 0.0f;
	Initialize();
}

void Attack::BaseFinalize()
{
	Finalize();
}

void Attack::BaseHitPlayerCheck(Player* ePlayer)
{
	this->ePlayer = ePlayer;
	HitPlayerCheck();
}

void Attack::BaseHitAttackCheck(Attack* attack)
{
	this->attack = attack;
	HitAttackCheck();
}

void Attack::BaseHited()
{
	Hited();
}

bool Attack::GetDelete()
{
	return isDelete;
}

Vector2 Attack::GetPos()
{
	return pos;
}

Vector2 Attack::GetScale()
{
	return scale;
}

float Attack::GetAtk()
{
	return atk;
}

bool Attack::GetRight()
{
	return right;
}

int Attack::GetSkillID()
{
	return ID;
}

int Attack::GetPID()
{
	return pID;
}

bool Attack::GetIsSkill()
{
	return skill;
}
