#pragma once
#include "../Attack.h"

struct Egg
{
	Vector2 pos;
	Vector2 scale = Vector2{ SKILL_MEAT_CHICKEN_EGG_SCALE, SKILL_MEAT_CHICKEN_EGG_SCALE };
};

class SkillMeatChicken : public Attack
{
private:
	int eggcount;
	std::vector<Egg> egg;
	float coolTime;

	bool deadChiken;

public:
	SkillMeatChicken();
	~SkillMeatChicken();

	void Initialize()				override;	//	‰Šú‰»
	void Update(float deltaTime)	override;	//	XV
	void Render()					override;	//	•`‰æ
	void Finalize()					override;	//	I—¹
	void HitPlayerCheck()			override;	//	“–‚½‚è”»’è
	void HitAttackCheck()			override;	//	“–‚½‚èUŒ‚”»’è
	void Hited()					override;	//	Õ“Ë
};
