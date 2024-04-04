#include <DxLib.h>
#include "SkillVegeTomato.h"
#include "../Player.h"

SkillVegeTomato::SkillVegeTomato() :
	Attack()
{
}

SkillVegeTomato::~SkillVegeTomato()
{
}

void SkillVegeTomato::Initialize()
{
	scale = Vector2{ SKILL_VEGE_TOMATO_SIZE,SKILL_VEGE_TOMATO_SIZE };
}

void SkillVegeTomato::Update(float deltaTime)
{
	time += deltaTime;
	//	ŽžŠÔ‚ª‚½‚Â‚ÆÁ–Å
	if (time > SKILL_VEGE_TOMATO_REMAINTIME)
	{
		isDelete = true;
	}

	if (right)
		pos.x += SKILL_VEGE_TOMATO_SPD * deltaTime;
	else
		pos.x -= SKILL_VEGE_TOMATO_SPD * deltaTime;
}

void SkillVegeTomato::Render()
{
	if(right) DrawRotaGraphF(pos.x, pos.y, 0.7, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Tomato)), 1);
	else DrawRotaGraphF(pos.x, pos.y, 0.7, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Tomato)), 1,1);
	//DrawCircle(pos.x, pos.y, scale.x, 0x00ff00);
	//DrawFormatString(pos.x, pos.y, 0x000000, "%d", ID);
}

void SkillVegeTomato::Finalize()
{
}

void SkillVegeTomato::HitPlayerCheck()
{
	//	“–‚½‚Á‚½‚ç
	if (HitCircle(pos, scale.x, ePlayer->GetPosition(), ePlayer->GetScale().x))
	{
		float deg;
		if (right) deg = SKILL_VEGE_TOMATO_KNOCKDEG;
		else       deg = 180.0f - SKILL_VEGE_TOMATO_KNOCKDEG;
		ePlayer->Hited(
			atk,
			SKILL_VEGE_TOMATO_POWER,
			SKILL_VEGE_TOMATO_KNOCKBUCK,
			deg
		);
		Hited();
	}
}

void SkillVegeTomato::HitAttackCheck()
{
}

void SkillVegeTomato::Hited()
{
	isDelete = true;
}
