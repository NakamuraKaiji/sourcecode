#pragma once
#include "../Attack.h"

class Attack0 : public Attack
{
private:


public:
	Attack0();
	~Attack0();

	void Initialize()				override;	//	������
	void Update(float deltaTIme)	override;	//	�X�V
	void Render()					override;	//	�`��
	void Finalize()					override;	//	�I��
	void HitPlayerCheck()			override;	//	�����蔻��
	void HitAttackCheck()			override;	//	������U������
	void Hited()					override;	//	�Փˎ�
};
