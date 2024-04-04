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
	bool isDelete;		//	消去するかどうか

	Vector2 screen;		//	画像情報
	float ground;		//	地面
	Vector2 pos;		//	座標
	Vector2 scale;		//	大きさ
	Vector2 vel;		//	移動
	Vector2 ePos;		//	敵の座標
	float pScale;		//	プレイヤーの大きさ
	float atk;			//	攻撃力
	int ID;				//	スキルID
	int pSkillID;		//	プレイヤーにとってのスキルID
	int attackNum;		//	攻撃
	int pID;			//	どのプレイヤーのものか
	bool right;			//	右が正面か
	bool skill;			//	スキルかどうか

	float time;			//	時間

	Player* mPlayer;
	Player* ePlayer;
	Attack* attack;

	TextureManger* tdata;
	Sound* sdata;

public:
	Attack();
	~Attack();

	virtual void Initialize() = 0;				//	初期化
	virtual void Update(float deltaTime) = 0;	//	更新
	virtual void Render() = 0;					//	描画
	virtual void Finalize() = 0;				//	終了

	virtual void HitPlayerCheck() = 0;			//	当たり判定計算
	virtual void HitAttackCheck() = 0;			//	当たり判定計算
	virtual void Hited() = 0;					//	衝突したら

	void BaseInitialize(TextureManger* tdata, Sound* sdata, Vector2 screen, float ground, Player* mPlayer, Vector2 ePos, int skillID, int attackNum = 1);	//	基本初期化
	void BaseFinalize();																								//	基本解放
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
