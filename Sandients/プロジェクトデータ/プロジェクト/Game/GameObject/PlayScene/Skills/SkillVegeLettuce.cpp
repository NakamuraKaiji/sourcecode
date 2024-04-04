#include <DxLib.h>
#include "SkillVegeLettuce.h"
#include "../Player.h"

SkillVegeLettuce::SkillVegeLettuce() :
	Attack()
{
}

SkillVegeLettuce::~SkillVegeLettuce()
{
}

void SkillVegeLettuce::Initialize()
{
	atk = mPlayer->GetStatas().atk * mPlayer->GetCondition().atkRate;
	scale = Vector2{ SKILL_VEGE_LETTUCE_SIZE ,SKILL_VEGE_LETTUCE_SIZE };
	if (fabsf(static_cast<float>(pos.x - ePos.x)) < SKILL_VEGE_LETTUCE_MAX_RENGE)
	{
		pos.x = ePos.x;
	}
	else
	{
		if (right) pos.x += SKILL_VEGE_LETTUCE_MAX_RENGE;
		else pos.x -= SKILL_VEGE_LETTUCE_MAX_RENGE;
	}
	pos.y = SKILL_VEGE_LETTUCE_HEIGHT;
}

void SkillVegeLettuce::Update(float deltaTime)
{
	time += deltaTime;
	//	ŽžŠÔ‚ª‚½‚Â‚ÆÁ–Å
	if (time > SKILL_VEGE_LETTUCE_REMAINTIME)
	{
		isDelete = true;
	}

	//	ˆÚ“®
	pos.y += static_cast<double>(SKILL_VEGE_LETTUCE_SPD) * deltaTime;
	//	’n–ÊÚG
	if (pos.y + scale.x > ground * screen.y)
	{
		isDelete = true;
		pos.y = ground * screen.y - scale.x;
	}
}

void SkillVegeLettuce::Render()
{
	if (right) DrawRotaGraphF(pos.x, pos.y, 0.7, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Lettuce)), 1);
	else DrawRotaGraphF(pos.x, pos.y, 0.7, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Lettuce)), 1, 1);
	//DrawCircle(pos.x, pos.y, scale.x, 0x00ff00);
	//DrawFormatString(pos.x, pos.y, 0x000000, "%.1f", atk);
}

void SkillVegeLettuce::Finalize()
{
}

void SkillVegeLettuce::HitPlayerCheck()
{
	//	“–‚½‚Á‚½‚ç
	if (HitCircle(pos, scale.x, ePlayer->GetPosition(), ePlayer->GetScale().x))
	{
		float deg;
		if (right) deg = SKILL_VEGE_LETTUCE_KNOCKDEG;
		else       deg = 180.0f - SKILL_VEGE_LETTUCE_KNOCKDEG;
		ePlayer->Hited(
			atk,
			SKILL_VEGE_LETTUCE_POWER,
			SKILL_VEGE_LETTUCE_KNOCKBUCK,
			deg
		);
		Hited();
	}
}

void SkillVegeLettuce::HitAttackCheck()
{
}

void SkillVegeLettuce::Hited()
{
	isDelete = true;
}
