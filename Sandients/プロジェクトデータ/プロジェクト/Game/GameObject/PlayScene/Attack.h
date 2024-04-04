#pragma once
#include <vector>
#include "../../GameDatas/Vector.h"
#include "Skills/Skills.h"
#include "Attacks/Attacks.h"
#include "../../GameDatas/HitJudge.h"
#include "../../GameDatas/TextureManager.h"
#include "../../GameDatas/Sound.h"

class Player;

class Attack
{
protected:
	bool isDelete;		//	�������邩�ǂ���

	Vector2 screen;		//	�摜���
	float ground;		//	�n��
	Vector2 pos;		//	���W
	Vector2 scale;		//	�傫��
	Vector2 vel;		//	�ړ�
	Vector2 ePos;		//	�G�̍��W
	float pScale;		//	�v���C���[�̑傫��
	float atk;			//	�U����
	int ID;				//	�X�L��ID
	int pSkillID;		//	�v���C���[�ɂƂ��ẴX�L��ID
	int attackNum;		//	�U��
	int pID;			//	�ǂ̃v���C���[�̂��̂�
	bool right;			//	�E�����ʂ�
	bool skill;			//	�X�L�����ǂ���

	float time;			//	����

	Player* mPlayer;
	Player* ePlayer;
	Attack* attack;

	TextureManger* tdata;
	Sound* sdata;

public:
	Attack();
	~Attack();

	virtual void Initialize() = 0;				//	������
	virtual void Update(float deltaTime) = 0;	//	�X�V
	virtual void Render() = 0;					//	�`��
	virtual void Finalize() = 0;				//	�I��

	virtual void HitPlayerCheck() = 0;			//	�����蔻��v�Z
	virtual void HitAttackCheck() = 0;			//	�����蔻��v�Z
	virtual void Hited() = 0;					//	�Փ˂�����

	void BaseInitialize(TextureManger* tdata, Sound* sdata, Vector2 screen, float ground, Player* mPlayer, Vector2 ePos, int skillID, int attackNum = 1);	//	��{������
	void BaseFinalize();																								//	��{���
	void BaseHitPlayerCheck(Player* ePlayer);
	void BaseHitAttackCheck(Attack* attack);
	void BaseHited();

	bool GetDelete();
	Vector2 GetPos();
	Vector2 GetScale();
	float GetAtk();
	bool GetRight();
	int GetSkillID();
	int GetPID();
	bool GetIsSkill();
};
