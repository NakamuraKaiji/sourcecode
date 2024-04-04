#pragma once
#include "../Attack.h"

struct Salmon
{
	bool right;
	Vector2 pos;
	Vector2 scale = Vector2{ SKILL_MEAT_SALMON_SCALE,SKILL_MEAT_SALMON_SCALE };
};

class SkillMeatSalmon : public Attack
{
private:
	int shotCount;
	float coolTime;
	std::vector<Salmon> salmon;

public:
	SkillMeatSalmon();
	~SkillMeatSalmon();

	void Initialize()				override;	//	‰Šú‰»
	void Update(float deltaTime)	override;	//	XV
	void Render()					override;	//	•`‰æ
	void Finalize()					override;	//	I—¹
	void HitPlayerCheck()			override;	//	“–‚½‚è”»’è
	void HitAttackCheck()			override;	//	“–‚½‚èUŒ‚”»’è
	void Hited()					override;	//	Õ“Ë
};
