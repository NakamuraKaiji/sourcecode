#pragma once
#include "../Attack.h"

class SkillVegeTomato : public Attack
{
private:


public:
	SkillVegeTomato();
	~SkillVegeTomato();

	void Initialize()				override;	//	������
	void Update(float deltaTIme)	override;	//	�X�V
	void Render()					override;	//	�`��
	void Finalize()					override;	//	�I��
	void HitPlayerCheck()			override;	//	�����蔻��
	void HitAttackCheck()			override;	//	������U������
	void Hited()					override;	//	�Փˎ�
};
