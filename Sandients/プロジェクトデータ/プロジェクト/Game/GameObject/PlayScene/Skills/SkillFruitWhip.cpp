#include <DxLib.h>
#include "SkillFruitWhip.h"
#include "../Player.h"

SkillFruitWhip::SkillFruitWhip() :
	Attack()
{
}

SkillFruitWhip::~SkillFruitWhip()
{
}

void SkillFruitWhip::Initialize()
{
	scale = Vector2{ SKILL_FRUIT_WHIP_SIZE ,SKILL_FRUIT_WHIP_SIZE };
	hit = false;
	countTime = 0.0f;
}

void SkillFruitWhip::Update(float deltaTime)
{
	countTime -= deltaTime;
	if (countTime < 0.0f)
	{
		hit = false;
	}

	if (hit)
	{
		PlayerCondition p = ePlayer->GetCondition();
		p.spdRate = SKILL_FRUIT_WHIP_SLOW_RATE;
		ePlayer->SetCondition(p);
	}
	if (vanish && !hit) isDelete = true;
	if (vanish) return;

	time += deltaTime;
	//	ŽžŠÔ‚ª‚½‚Â‚ÆÁ–Å
	if (time > SKILL_FRUIT_WHIP_REMAINTIME)
	{
		vanish = true;
	}

	//	’n–ÊÚG‚µ‚Ä‚¢‚È‚¯‚ê‚Î
	if (!(pos.y + scale.x > ground * screen.y))
	{
		pos.x += vel.x * deltaTime;
		pos.y += vel.y * deltaTime;
	}

	vel.y += SKILL_FRUIT_WHIP_DROP_SPD * deltaTime;
}

void SkillFruitWhip::Render()
{
	DrawRotaGraphF(pos.x, pos.y, 0.7f, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Whip)), 1);
	//DrawCircle(pos.x, pos.y, scale.x, 0xffffff);
}

void SkillFruitWhip::Finalize()
{
}

void SkillFruitWhip::HitPlayerCheck()
{
	//	“–‚½‚Á‚½‚ç
	if (vanish) return;
	if (HitCircle(pos, scale.x, ePlayer->GetPosition(), ePlayer->GetScale().x))
	{
		PlayerCondition p = ePlayer->GetCondition();
		p.spdRate = SKILL_FRUIT_WHIP_SLOW_RATE;
		ePlayer->SetCondition(p);
		hit = true;
		countTime = SKILL_FRUIT_WHIP_SLOW_TIME;
	}
}

void SkillFruitWhip::HitAttackCheck()
{
}

void SkillFruitWhip::Hited()
{
	isDelete = true;
}