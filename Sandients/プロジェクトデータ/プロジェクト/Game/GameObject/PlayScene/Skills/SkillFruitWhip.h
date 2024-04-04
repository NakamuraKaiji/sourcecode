#pragma once
#include "../Attack.h"

class SkillFruitWhip : public Attack
{
private:
	bool vanish;
	bool hit;
	float countTime;

public:
	SkillFruitWhip();
	~SkillFruitWhip();

	void Initialize()				override;	//	‰Šú‰»
	void Update(float deltaTIme)	override;	//	XV
	void Render()					override;	//	•`‰æ
	void Finalize()					override;	//	I—¹
	void HitPlayerCheck()			override;	//	“–‚½‚è”»’è
	void HitAttackCheck()			override;	//	“–‚½‚èUŒ‚”»’è
	void Hited()					override;	//	Õ“Ë
};
