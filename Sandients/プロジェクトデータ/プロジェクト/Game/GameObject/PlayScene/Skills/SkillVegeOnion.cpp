#include <DxLib.h>
#include "SkillVegeOnion.h"
#include "../Player.h"

SkillVageOnion::SkillVageOnion()
{
}

SkillVageOnion::~SkillVageOnion()
{
}

void SkillVageOnion::Initialize()
{
}

void SkillVageOnion::Update(float deltaTime)
{
	time += deltaTime;
	//	���Ԃ����Ə���
	if (time > SKILL_VEGE_ONION_REMAINTIME)
	{
		isDelete = true;
	}

	//	�N�[���^�C����ݒ�
	mPlayer->SetCoolTime(pSkillID, SKILL[ID].ct);

	//	�X�e�[�^�X�㏸
	PlayerCondition con = mPlayer->GetCondition();
	con.atkRate *= SKILL_VEGE_ONION_ATK_RATE;
	con.defRate *= SKILL_VEGE_ONION_DEF_RATE;
	con.knockRate *= SKILL_VEGE_ONION_KNOCK_RATE;
	mPlayer->SetCondition(con);
}

void SkillVageOnion::Render()
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawRotaGraphF(mPlayer->GetPosition().x, mPlayer->GetPosition().y - 5.0f, 0.7, 0.0, tdata->GetTextureHandle(static_cast<int>(GameSceneTexture::Onion)), 1);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SkillVageOnion::Finalize()
{
}

void SkillVageOnion::HitPlayerCheck()
{
}

void SkillVageOnion::HitAttackCheck()
{
}

void SkillVageOnion::Hited()
{
}
