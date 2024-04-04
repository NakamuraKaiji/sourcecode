#include <DxLib.h>
#include "SkillFruitBanana.h"
#include "../Player.h"

SkillFruitBanana::SkillFruitBanana() :
	Attack()
{
}

SkillFruitBanana::~SkillFruitBanana()
{
}

void SkillFruitBanana::Initialize()
{
	scale = Vector2{ SKILL_FRUIT_BANANA_SIZE ,SKILL_FRUIT_BANANA_SIZE };
	if (right)
		vel.x = SKILL_FRUIT_BANANA_DEF_VELX;
	else
		vel.x = -SKILL_FRUIT_BANANA_DEF_VELX;
	vel.y = -SKILL_FRUIT_BANANA_DEF_VELY;
}

void SkillFruitBanana::Update(float deltaTime)
{
	time += deltaTime;
	//	ŽžŠÔ‚ª‚½‚Â‚ÆÁ–Å
	if (time > SKILL_FRUIT_BANANA_REMAINTIME)
	{
		isDelete = true;
	}

	//	’n–ÊÚG‚µ‚Ä‚¢‚È‚¯‚ê‚Î
	if (!(pos.y + scale.x > ground * screen.y))
	{
		pos.x += vel.x * deltaTime;
		pos.y += vel.y * deltaTime;
	}

	vel.y += SKILL_FRUIT_BANANA_DROP_SPD * deltaTime;
}

void SkillFruitBanana::Render()
{
	DrawRotaGraphF(pos.x, pos.y, 0.7f, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Banana)),1);
	//DrawCircle(pos.x, pos.y, scale.x, 0x00ff00);
	//DrawFormatString(pos.x, pos.y, 0x000000, "%d", ID);
}

void SkillFruitBanana::Finalize()
{
}

void SkillFruitBanana::HitPlayerCheck()
{
	//	“–‚½‚Á‚½‚ç
	if (HitCircle(pos, scale.x, ePlayer->GetPosition(), ePlayer->GetScale().x))
	{
		ePlayer->SetCantMoveTime(SKILL_FRUIT_BANANA_CANTMOVE_TIME);
		Hited();
	}
}

void SkillFruitBanana::HitAttackCheck()
{
}

void SkillFruitBanana::Hited()
{
	isDelete = true;
	sdata->HitedSkill();
}