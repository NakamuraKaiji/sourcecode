#pragma once
#include "Vector.h"

//	ŠÛ‚Ì“–‚½‚è”»’è
const static bool HitCircle(Vector2 pos1, float scale1, Vector2 pos2, float scale2)
{
	Vector2 hen = { pos1.x - pos2.x,pos1.y - pos2.y };
	float syahen = scale1 + scale2;
	if ((hen.x * hen.x + hen.y * hen.y) <= (static_cast<double>(syahen) * syahen)) return true;
	return false;
}