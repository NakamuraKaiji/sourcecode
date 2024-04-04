#include <DxLib.h>
#include "SkillMeatBacon.h"
#include "../Player.h"

SkillMeatBacon::SkillMeatBacon() :
	Attack()
{
}

SkillMeatBacon::~SkillMeatBacon()
{
}

void SkillMeatBacon::Initialize()
{
	scale = Vector2{ SKILL_MEAT_BACON_SIZE,SKILL_MEAT_BACON_SIZE };
}

void SkillMeatBacon::Update(float deltaTime)
{
	time += deltaTime;
	//	ŽžŠÔ‚ª‚½‚Â‚ÆÁ–Å
	if (time > SKILL_MEAT_BACON_REMAINTIME)
	{
		isDelete = true;
	}

	if (right)
		pos.x += SKILL_MEAT_BACON_SPD_X * deltaTime;
	else 
		pos.x -= SKILL_MEAT_BACON_SPD_X * deltaTime;
	
	//	’n–ÊÚG
	if (!(pos.y + scale.x > ground * screen.y))
	{
		pos.y += SKILL_MEAT_BACON_SPD_Y * deltaTime;
	}

}

void SkillMeatBacon::Render()
{
	if(right) DrawRotaGraphF(pos.x, pos.y, 0.7, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Bacon)), 1);
	else DrawRotaGraphF(pos.x, pos.y, 0.7, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Bacon)), 1,1);
}

void SkillMeatBacon::Finalize()
{
}

void SkillMeatBacon::HitPlayerCheck()
{
	//	“–‚½‚Á‚½‚ç
	if (HitCircle(pos, scale.x, ePlayer->GetPosition(), ePlayer->GetScale().x))
	{
		float deg;
		if (right) deg = SKILL_MEAT_BACON_KNOCKDEG;
		else       deg = 180.0f - SKILL_MEAT_BACON_KNOCKDEG;
		ePlayer->Hited(
			atk,
			SKILL_MEAT_BACON_POWER,
			SKILL_MEAT_BACON_KNOCKBUCK,
			deg
		);
		Hited();
	}
}

void SkillMeatBacon::HitAttackCheck()
{
}

void SkillMeatBacon::Hited()
{
	isDelete = true;
}