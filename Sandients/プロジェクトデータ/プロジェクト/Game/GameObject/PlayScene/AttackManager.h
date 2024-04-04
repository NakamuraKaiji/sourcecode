#pragma once
#include <vector>
#include "../../GameDatas/Vector.h"
#include "../../GameDatas/TextureManager.h"
#include "../../GameDatas/Sound.h"
#include "Attack.h"

class Player;

struct PrepareAttack
{
	int pID;		//	プレイヤーID
	int SorAID;		//	スキルか攻撃のID
	int attackNum;	//	攻撃コンボ数
};


class AttackManager
{
private:
	Vector2 screen;								//	画面サイズ
	float   ground;								//	地面位置
	std::vector<Attack*> attack;				//	攻撃
	std::vector<PrepareAttack> prepareAttack;	//	攻撃準備

	Player* player1;
	Player* player2;
	TextureManger* tdata;
	Sound* sdata;

public:
	AttackManager();
	~AttackManager();

	void Initialize(TextureManger* tdata, Sound* sdata, Vector2 screen, float ground, Player* p1, Player* p2);	//	初期化
	void Update(float deltaTime);											//	更新
	void Render();															//	描画
	void Finalize();														//	終了

	void HitUpdate(Vector2 pos, float scale, int pID, Player* player);
	void CreateUpdate();
	void CreatePrepareAttack(int pID, int skillID);
	void CreatePrepareAttack(int pID, int attackID, int attackNum);
	void CreateAttack(Player* player, Vector2 ePos, int skillID);
	void CreateAttack(Player* player, Vector2 ePos, int attackID, int attackNum);
	Attack* GetAttack(int i);
};
