#pragma once
#include "../Attack.h"

class SkillFruitBanana : public Attack
{
private:

public:
	SkillFruitBanana();
	~SkillFruitBanana();

	void Initialize()				override;	//	������
	void Update(float deltaTIme)	override;	//	�X�V
	void Render()					override;	//	�`��
	void Finalize()					override;	//	�I��
	void HitPlayerCheck()			override;	//	������v���C���[����
	void HitAttackCheck()			override;	//	������U������
	void Hited()					override;	//	�Փˎ�
};
