#pragma once
#include "../Attack.h"

class SkillVageOnion : public Attack
{
private:


public:
	SkillVageOnion();
	~SkillVageOnion();

	void Initialize()				override;	//	‰Šú‰»
	void Update(float deltaTime)	override;	//	XV
	void Render()					override;	//	•`‰æ
	void Finalize()					override;	//	I—¹
	void HitPlayerCheck()			override;	//	“–‚½‚è”»’è
	void HitAttackCheck()			override;	//	“–‚½‚èUŒ‚”»’è
	void Hited()					override;	//	Õ“Ë
};
