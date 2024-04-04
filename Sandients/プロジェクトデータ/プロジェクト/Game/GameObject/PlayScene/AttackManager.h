#pragma once
#include <vector>
#include "../../GameDatas/Vector.h"
#include "../../GameDatas/TextureManager.h"
#include "../../GameDatas/Sound.h"
#include "Attack.h"

class Player;

struct PrepareAttack
{
	int pID;		//	�v���C���[ID
	int SorAID;		//	�X�L�����U����ID
	int attackNum;	//	�U���R���{��
};


class AttackManager
{
private:
	Vector2 screen;								//	��ʃT�C�Y
	float   ground;								//	�n�ʈʒu
	std::vector<Attack*> attack;				//	�U��
	std::vector<PrepareAttack> prepareAttack;	//	�U������

	Player* player1;
	Player* player2;
	TextureManger* tdata;
	Sound* sdata;

public:
	AttackManager();
	~AttackManager();

	void Initialize(TextureManger* tdata, Sound* sdata, Vector2 screen, float ground, Player* p1, Player* p2);	//	������
	void Update(float deltaTime);											//	�X�V
	void Render();															//	�`��
	void Finalize();														//	�I��

	void HitUpdate(Vector2 pos, float scale, int pID, Player* player);
	void CreateUpdate();
	void CreatePrepareAttack(int pID, int skillID);
	void CreatePrepareAttack(int pID, int attackID, int attackNum);
	void CreateAttack(Player* player, Vector2 ePos, int skillID);
	void CreateAttack(Player* player, Vector2 ePos, int attackID, int attackNum);
	Attack* GetAttack(int i);
};
