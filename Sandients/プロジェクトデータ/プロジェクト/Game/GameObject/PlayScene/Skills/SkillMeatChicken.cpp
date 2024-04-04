#include <DxLib.h>
#include "SkillMeatChicken.h"
#include "../Player.h"

SkillMeatChicken::SkillMeatChicken():
	coolTime(),
	eggcount(),
	deadChiken()
{
}

SkillMeatChicken::~SkillMeatChicken()
{
}

void SkillMeatChicken::Initialize()
{
	coolTime = SKILL_MEAT_CHICKEN_CREATE_TIME;
	scale = Vector2{ SKILL_MEAT_CHICKEN_SCALE,SKILL_MEAT_CHICKEN_SCALE };
	eggcount = 0;
	egg.clear();
	deadChiken = false;
}

void SkillMeatChicken::Update(float deltaTime)
{
	//	—‘ˆÚ“®
	for (size_t i = 0; i < egg.size(); i++)
	{
		egg[i].pos.y += static_cast<double>(SKILL_MEAT_CHICKEN_EGG_DROP_SPD) * deltaTime;
		//	’n–ÊÚG
		if (egg[i].pos.y + egg[i].scale.x > ground * screen.y)
		{
			egg[i].pos.y = ground * screen.y - egg[i].scale.x;
		}
	}

	if (deadChiken) return;

	coolTime -= deltaTime;
	SKILL_MEAT_CHICKEN_MOVE_RAND* deltaTime;
	if (GetRand(99) < SKILL_MEAT_CHICKEN_MOVE_RAND * deltaTime * 100)
	{
		if (right) right = false;
		else right = true;
	}
	//	¶¬
	if (coolTime < 0.0f)
	{
		egg.push_back(Egg{ pos });
		eggcount++;
		coolTime = SKILL_MEAT_CHICKEN_CREATE_TIME;
		if (eggcount >= SKILL_MEAT_CHICKEN_EGG_NUM)
		{
			deadChiken = true;
		}
		sdata->EggDrop();
	}
	if (right)
		pos.x += SKILL_MEAT_CHICKEN_SPEED * deltaTime;
	else
		pos.x -= SKILL_MEAT_CHICKEN_SPEED * deltaTime;
	pos.y += static_cast<double>(SKILL_MEAT_CHICKEN_EGG_DROP_SPD) * deltaTime;
	//	’n–ÊÚG
	if (pos.y + scale.x > ground * screen.y)
	{
		pos.y = ground * screen.y - scale.x;
	}
	//	•Ç”»’èˆ—
	if (pos.x + scale.x > screen.x) pos.x = screen.x - scale.x;
	else if (pos.x - scale.x < 0.0f) pos.x = scale.x;
}

void SkillMeatChicken::Render()
{
	if (!deadChiken)
	{
		if(right) DrawRotaGraphF(pos.x, pos.y, 0.5f, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Chicken)), 1,1);
		else DrawRotaGraphF(pos.x, pos.y, 0.5f, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Chicken)), 1);
	}
	for (size_t i = 0; i < egg.size(); i++)
	{
		DrawRotaGraphF(egg[i].pos.x, egg[i].pos.y, 0.3f, 0.0f, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Egg)), 1);
		//DrawCircle(egg[i].pos.x, egg[i].pos.y, egg[i].scale.x, 0xffffff);
	}
}

void SkillMeatChicken::Finalize()
{
}

void SkillMeatChicken::HitPlayerCheck()
{
	//	—‘“–‚½‚Á‚½‚ç
	for (size_t i = 0; i < egg.size(); i++)
	{
		if (HitCircle(egg[i].pos, egg[i].scale.x, mPlayer->GetPosition(), mPlayer->GetScale().x))
		{
			PlayerStatas p = mPlayer->GetStatas();
			p.hp += p.maxHp * SKILL_MEAT_CHICKEN_HEAL;
			if (p.hp > p.maxHp) p.hp = p.maxHp;
			mPlayer->SetStatas(p);
			egg.erase(egg.begin() + i);
			i--;
			sdata->EggHeal();
		}
		else if (HitCircle(egg[i].pos, egg[i].scale.x, ePlayer->GetPosition(), ePlayer->GetScale().x))
		{
			PlayerStatas p = ePlayer->GetStatas();
			p.hp += p.maxHp * SKILL_MEAT_CHICKEN_HEAL;
			if (p.hp > p.maxHp) p.hp = p.maxHp;
			ePlayer->SetStatas(p);
			egg.erase(egg.begin() + i);
			i--;
			sdata->EggHeal();
		}
	}
	if (deadChiken && egg.size() <= 0)
	{
		isDelete = true;
	}
}

void SkillMeatChicken::HitAttackCheck()
{
}

void SkillMeatChicken::Hited()
{
}
