#include <DxLib.h>
#include "SkillMeatTuna.h"
#include "../Player.h"

SkillMeatTuna::SkillMeatTuna()
{
}

SkillMeatTuna::~SkillMeatTuna()
{
}

void SkillMeatTuna::Initialize()
{
}

void SkillMeatTuna::Update(float deltaTime)
{
	time += deltaTime;
	//	時間がたつと消滅
	if (time > SKILL_VEGE_ONION_REMAINTIME)
	{
		isDelete = true;
	}

	//	クールタイムを設定
	mPlayer->SetCoolTime(pSkillID, SKILL[ID].ct);

	//	ステータス上昇
	PlayerCondition con = mPlayer->GetCondition();
	con.spdRate *= SKILL_VEGE_ONION_ATK_RATE;
	mPlayer->SetCondition(con);
}

void SkillMeatTuna::Render()
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawRotaGraphF(mPlayer->GetPosition().x, mPlayer->GetPosition().y - 5.0f, 0.7, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Tuna)), 1);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SkillMeatTuna::Finalize()
{
}

void SkillMeatTuna::HitPlayerCheck()
{
}

void SkillMeatTuna::HitAttackCheck()
{
}

void SkillMeatTuna::Hited()
{
}
