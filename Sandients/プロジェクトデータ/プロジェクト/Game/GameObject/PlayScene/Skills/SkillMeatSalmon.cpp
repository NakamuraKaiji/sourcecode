#include <DxLib.h>
#include "SkillMeatSalmon.h"
#include "../Player.h"

SkillMeatSalmon::SkillMeatSalmon():
	shotCount(),
	coolTime()
	
{
}

SkillMeatSalmon::~SkillMeatSalmon()
{
}

void SkillMeatSalmon::Initialize()
{
	shotCount = 0;
	coolTime = 0.0f;
	salmon.clear();
}

void SkillMeatSalmon::Update(float deltaTime)
{
	time += deltaTime;
	//	時間がたつと消滅
	if (time > SKILL_MEAT_SALMON_REMAINTIME)
	{
		isDelete = true;
	}

	for (size_t i = 0; i < salmon.size(); i++)
	{
		if (salmon[i].right)
			salmon[i].pos.x += SKILL_MEAT_SALMON_SPD * deltaTime;
		else
			salmon[i].pos.x -= SKILL_MEAT_SALMON_SPD * deltaTime;
		//	壁判定処理
		if (salmon[i].pos.x - salmon[i].scale.x > screen.x)
		{
			salmon.erase(salmon.begin() + i);
			i--;
		}
	}


	//	クールタイム処理
	if (shotCount >= SKILL_MEAT_SALMON_NUM) return;
	mPlayer->SetPosition(pos);
	coolTime -= deltaTime;
	if (coolTime < 0.0f)
	{
		salmon.push_back(Salmon{ right,pos });
		mPlayer->SetRight(right);
		coolTime = 1.0f / SKILL_MEAT_SALMON_SHOT_COOLTIME;
		shotCount++;
	}
}

void SkillMeatSalmon::Render()
{
	for (size_t i = 0; i < salmon.size(); i++)
	{
		if (salmon[i].right) DrawRotaGraphF(salmon[i].pos.x, salmon[i].pos.y, 0.2, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Salmon)), 1);
		else DrawRotaGraphF(salmon[i].pos.x, salmon[i].pos.y, 0.2, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Salmon)), 1,1);
		//DrawCircle(salmon[i].pos.x, salmon[i].pos.y, salmon[i].scale.x, 0xff3300);
	}
}

void SkillMeatSalmon::Finalize()
{
}

void SkillMeatSalmon::HitPlayerCheck()
{
	//	当たったら
	for (size_t i = 0; i < salmon.size(); i++)
	{
		if (HitCircle(salmon[i].pos, salmon[i].scale.x, ePlayer->GetPosition(), ePlayer->GetScale().x))
		{
			float deg;
			if (salmon[i].right) deg = SKILL_MEAT_SALMON_KNOCKDEG;
			else       deg = 180.0f - SKILL_MEAT_SALMON_KNOCKDEG;
			ePlayer->Hited(
				atk,
				SKILL_MEAT_SALMON_POWER,
				SKILL_MEAT_SALMON_KNOCKBUCK,
				deg
			);
			salmon.erase(salmon.begin() + i);
			i--;
		}
	}
	if (salmon.size() <= 0 && shotCount >= SKILL_MEAT_SALMON_NUM) isDelete = true;
}

void SkillMeatSalmon::HitAttackCheck()
{
}

void SkillMeatSalmon::Hited()
{
}
