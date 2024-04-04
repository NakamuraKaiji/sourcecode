#include <DxLib.h>
#include "Attack0.h"
#include "../Player.h"

Attack0::Attack0() :
	Attack()
{
}

Attack0::~Attack0()
{
}

void Attack0::Initialize()
{
	scale = Vector2{ ATTACK[0].hitSize, ATTACK[0].hitSize };
	if (right)
		pos.x += pScale;
	else
		pos.x -= pScale;
}

void Attack0::Update(float deltaTime)
{
	time += deltaTime;

	//	Œü‚«ŒÅ’è
	mPlayer->SetRight(right);

	//	À•W’²®
	pos = mPlayer->GetPosition();
	if (right)
		pos.x += pScale;
	else
		pos.x -= pScale;

	//	ŽžŠÔ‚ª‚½‚Â‚ÆÁ–Å
	if (time > 0.3f)
	{
		isDelete = true;
	}
}

void Attack0::Render()
{
}

void Attack0::Finalize()
{
}

void Attack0::HitPlayerCheck()
{
	//	“–‚½‚Á‚½‚ç
	if (HitCircle(pos, scale.x, ePlayer->GetPosition(), ePlayer->GetScale().x))
	{
		float power;
		float deg;
		if (right) deg = ATTACK[ID].knockDeg;
		else       deg = 180.0 - ATTACK[ID].knockDeg;
		if (attackNum >= ATTACK[ID].maxConbo) power = ATTACK[ID].power * ATTACK[ID].maxConboRate;
		else                                  power = ATTACK[ID].power;

		ePlayer->Hited(
			atk,
			power,
			ATTACK[ID].knockBack,
			deg
		);
		Hited();
	}
}

void Attack0::HitAttackCheck()
{
}

void Attack0::Hited()
{
	isDelete = true;
}
