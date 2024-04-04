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

	void Initialize()				override;	//	������
	void Update(float deltaTime)	override;	//	�X�V
	void Render()					override;	//	�`��
	void Finalize()					override;	//	�I��
	void HitPlayerCheck()			override;	//	�����蔻��
	void HitAttackCheck()			override;	//	������U������
	void Hited()					override;	//	�Փˎ�
};
