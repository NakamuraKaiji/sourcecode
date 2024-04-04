#include <DxLib.h>
#include "AttackManager.h"
#include "Skills/Skills.h"
#include "Player.h"

#include "Attacks/Attack0.h"

#include "Skills/SkillVegeLettuce.h"
#include "Skills/SkillVegeTomato.h"
#include "Skills/SkillVegeOnion.h"
#include "Skills/SkillMeatBacon.h"
#include "Skills/SkillMeatChicken.h"
#include "Skills/SkillMeatSalmon.h"
#include "Skills/SkillMeatTuna.h"
#include "Skills/SkillFruitBanana.h"
#include "Skills/SkillFruitWhip.h"

AttackManager::AttackManager():
	tdata(),
	sdata(),
	ground(),
	screen(),
	player1(),
	player2()
{
}

AttackManager::~AttackManager()
{
}

void AttackManager::Initialize(TextureManger* tdata, Sound* sdata, Vector2 screen, float ground, Player* p1, Player* p2)
{
	this->tdata = tdata;
	this->sdata = sdata;
	this->screen = screen;
	this->ground = ground;
	this->player1 = p1;
	this->player2 = p2;
	prepareAttack.clear();
	attack.clear();
}

void AttackManager::Update(float deltaTime)
{
	std::vector<size_t> deleteID;

	for (size_t i = 0; i < attack.size(); i++)
	{
		attack[i]->Update(deltaTime);
		if (attack[i]->GetDelete()) deleteID.push_back(i);
	}
	for (size_t i = 0; i < deleteID.size(); i++)
	{
		attack.erase(attack.begin() + deleteID[i] - i);
	}
}

void AttackManager::Render()
{
	for (size_t i = 0; i < attack.size(); i++)
	{
		attack[i]->Render();
	}
}

void AttackManager::Finalize()
{
	for (size_t i = 0; i < attack.size(); i++)
	{
		attack[i]->Finalize();
	}
	attack.clear();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �����蔻��̍X�V
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void AttackManager::HitUpdate(Vector2 pos, float scale, int pID, Player* player)
{
	for (size_t i = 0; i < attack.size(); i++)
	{
		//	�����ŕ��������̂̓X�L�b�v
		if (attack[i]->GetPID() == pID) continue;
		//	�����蔻��`�F�b�N
		attack[i]->BaseHitPlayerCheck(player);
		//	�����蔻��`�F�b�N
		for (size_t j = 0; j < attack.size(); j++)
		{
			if (j == i) continue;
			attack[i]->BaseHitAttackCheck(attack[j]);
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �U���쐬
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void AttackManager::CreateUpdate()
{
	for (size_t i = 0; i < prepareAttack.size(); i++)
	{
		switch (prepareAttack[i].pID)
		{
		case 0:
			if (prepareAttack[i].attackNum < 0)
				CreateAttack(player1, player2->GetPosition(), prepareAttack[i].SorAID);
			else
				CreateAttack(player1, player2->GetPosition(), prepareAttack[i].SorAID, prepareAttack[i].attackNum);
			break;
		case 1:
			if (prepareAttack[i].attackNum < 0)
				CreateAttack(player2, player1->GetPosition(), prepareAttack[i].SorAID);
			else
				CreateAttack(player2, player1->GetPosition(), prepareAttack[i].SorAID, prepareAttack[i].attackNum);
			break;
		}
	}
	prepareAttack.clear();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �U����������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void AttackManager::CreatePrepareAttack(int pID, int skillID)
{
	prepareAttack.push_back({ pID, skillID, -99 });
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �U����������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void AttackManager::CreatePrepareAttack(int pID, int attackID, int attackNum)
{
	prepareAttack.push_back({ pID, attackID, attackNum });
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �U������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void AttackManager::CreateAttack(Player* player,Vector2 ePos, int skillID)
{
	Attack *a = nullptr;
	//	ID�ɉ����čU������
	switch (static_cast<SkillName>(skillID))
	{
	case SkillName::Lettuce:
		a = new SkillVegeLettuce;
		break;
	case SkillName::Onion:
		a = new SkillVageOnion;
		break;
	case SkillName::Tomato:
		a = new SkillVegeTomato;
		break;
	case SkillName::Bacon:
		a = new SkillMeatBacon;
		break;
	case SkillName::Chicken:
		a = new SkillMeatChicken;
		break;
	case SkillName::Salmon:
		a = new SkillMeatSalmon;
		break;
	case SkillName::Tuna:
		a = new SkillMeatTuna;
		break;
	case SkillName::Banana:
		a = new SkillFruitBanana;
		break;
	case SkillName::Whip:
		a = new SkillFruitWhip;
		break;
	}
	//	����������
	a->BaseInitialize(tdata, sdata, screen, ground, player, ePos, skillID, -99);
	attack.push_back(a);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �U������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void AttackManager::CreateAttack(Player* player, Vector2 ePos, int attackID, int attackNum)
{
	Attack* a = nullptr;
	//	ID�ɉ����čU������
	switch (attackID)
	{
	case 0:
		a = new Attack0;
		break;
	}
	//	����������
	a->BaseInitialize(tdata, sdata, screen, ground, player, ePos, attackID, attackNum);
	attack.push_back(a);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �A�^�b�N�N���X���󂯓n��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
Attack* AttackManager::GetAttack(int i)
{
	return attack[i];
}
