//----------------------------------------------------------------------------------------------------
//	Player・・・サンドウィッチ達
// 
//----------------------------------------------------------------------------------------------------
#pragma once
#include <vector>
#include "../../GameDatas/Vector.h"
#include "../../../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "../../GameDatas/TextureManager.h"
#include "../../GameDatas/Sound.h"
#include "AttackManager.h"
#include "../../GameObject/PlayScene/Skills/Skills.h"
#include "../../GameObject/PlayerScore.h"


//	ステータス用構造体
struct PlayerStatas
{
	float hp               = 0.0f;				    //	体力
	float atk              = 0.0f;				    //	攻撃力
	float def              = 0.0f;				    //	防御力
	float weight           = 0.0f;			        //	重量
	int   atkID			   = 0;						//	攻撃ID
	std::vector<int>	skillID = {0};				//	各スキルID
	float sp			   = 100.0f;				//	必殺技ゲージ
	float maxHp			   = hp;					//	最大HP
	float maxSp			   = sp;					//	最大SP
	float defAtk		   = atk;					//	基本ATK
};

struct PlayerCondition
{
	float atkRate = 1.0f;		//	攻撃力倍率
	float defRate = 1.0f;		//	防御力倍率
	float spdRate = 1.0f;		//	移動速度倍率
	float knockRate = 1.0f;		//	ノックアップ倍率
};

class Player
{
private:
	Score score;
	Vector2 defPos;

	GameSystemObjects* system;	        //	移動等のシステム系
	TextureManger* tdata;
	Sound* sdata;

	AttackManager* attackManager;		//	攻撃時扱う
	Vector2 screenSize;		            //	画面サイズ
	float ground;						//	地面位置
	int pID;							//	プレイヤーID
	int padNum;					        //	パッドの番号

	PlayerStatas statas;	            //	プレイヤーのステータス
	PlayerCondition conditoin;			//	プレイヤーの状態
	Vector2		 pos;	                //	プレイヤーの座標
	Vector2		 scale;		            //	プレイヤーの大きさ
	Vector2		 vel;                   //	プレイヤーの移動量

	//	アニメーション用
	float        jumpVal;				//	ジャンプの値
	float		 maxJumpVal;			//	そのジャンプの最大値
	float        dropTime;				//	落下時間
	float        standbyTime;			//	待機時間
	float        inviTime;				//	無敵時間
	float        maxAttackTime;

	bool		 fly;			        //	空中かどうか
	bool		 guard;					//	ガードしているかどうか
	bool		 right;					//	右を向いているかどうか
	bool         special;				//	スペシャル状態かどうか
	bool		 charge;
	bool		 attack;				//	攻撃かどうか

	float		 deltaTime;

	float        skillPunishTime;		//	スキル前隙
	float		 attackPunishTime;		//	攻撃前隙
	float        attackComboRemainTime;	//	攻撃コンボ時間
	float		 cantMoveTime;		    //	動けないかどうか
	float		 invincibleTime;		//	無敵時間

	int			 nowAtkNum;				//	現在の攻撃
	int			 nowSkillNum;			//	現在の選択スキル
	std::vector<float> skillCoolTime;	//	スキルのクールタイム
	std::vector<int>   skillStock;		//	スキルのストック

public:
	Player();
	~Player();

	void Initialize(GameSystemObjects* system, TextureManger* tdata, Sound* sdata, AttackManager* attackManager, int pID, Vector2 screen, float ground, PlayerStatas statas, Vector2 defpos);	//	初期化
	void Update(float deltaTime);																					//	更新
	void Render();																									//	描画
	void Finalize();																								//	終了

	void PlayerControll();													//	プレイヤーの更新
	void UseAttack();														//	攻撃使用
	void UseSkill();														//	スキル使用
	void Hited(float atk, float power, float knock, float deg);				//	攻撃を受けた時の処理

	void Reset();															//	プレイヤーリセット

	void SetRight(bool right);												//	右が正面かセットする
	void SetPadNum(int padNum);												//	対応PADを決める
	void SetCondition(PlayerCondition condition);							//	状態異常をセットする
	void ResetCondition();													//	状態異常リセット
	void SetCantMoveTime(float time);										//	行動不能時間をセット
	void SetCoolTime(int id, float ct);										//	クールタイムセット
	void SetStatas(PlayerStatas p);											//	ステータスセット
	void SetPosition(Vector2 pos);											//	位置設定

	PlayerStatas GetStatas();												//	ステータス受渡
	PlayerCondition GetCondition();											//	状態受渡
	Vector2		 GetPosition();												//	座標位置受渡
	Vector2		 GetScale();												//	大きさ受け渡し
	bool		 GetIsRight();												//	右が正面かどうか渡す
	int			 GetPadNum();												//	パッド番号を返す
	int			 GetPID();													//	プレイヤーID受渡

	Score        GetScore();												//	スコアを受け渡す

	int			 GetNowSkillNum();											//	スキルの番号を受渡
	std::vector<float> GetSkillCoolTime();									//	スキルのクールタイム受渡
	std::vector<int>   GetSkillStock();										//	スキルのストックを受け渡す
};

