#pragma once
#include "../Attack.h"

class SkillMeatTuna : public Attack
{
private:


public:
	SkillMeatTuna();
	~SkillMeatTuna();

	void Initialize()				override;	//	������
	void Update(float deltaTime)	override;	//	�X�V
	void Render()					override;	//	�`��
	void Finalize()					override;	//	�I��
	void HitPlayerCheck()			override;	//	�����蔻��
	void HitAttackCheck()			override;	//	������U������
	void Hited()					override;	//	�Փˎ�
};
