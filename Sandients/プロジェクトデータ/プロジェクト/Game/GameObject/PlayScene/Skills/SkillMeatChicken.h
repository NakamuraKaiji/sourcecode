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

	void Initialize()				override;	//	������
	void Update(float deltaTime)	override;	//	�X�V
	void Render()					override;	//	�`��
	void Finalize()					override;	//	�I��
	void HitPlayerCheck()			override;	//	�����蔻��
	void HitAttackCheck()			override;	//	������U������
	void Hited()					override;	//	�Փˎ�
};
