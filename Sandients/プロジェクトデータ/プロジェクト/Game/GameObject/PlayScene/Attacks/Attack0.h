#pragma once
#include "../Attack.h"

class Attack0 : public Attack
{
private:


public:
	Attack0();
	~Attack0();

	void Initialize()				override;	//	‰Šú‰»
	void Update(float deltaTIme)	override;	//	XV
	void Render()					override;	//	•`‰æ
	void Finalize()					override;	//	I—¹
	void HitPlayerCheck()			override;	//	“–‚½‚è”»’è
	void HitAttackCheck()			override;	//	“–‚½‚èUŒ‚”»’è
	void Hited()					override;	//	Õ“Ë
};
