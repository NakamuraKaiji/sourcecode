//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//	PlayScene
//		プレイシーン
// 
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"

#include "../GameDatas/Vector.h"
#include "../GameDatas/Sound.h"
#include "../GameObject/PlayScene/Player.h"
#include "../GameObject/PlayScene/AttackManager.h"

class PlayScene : public BaseScene
{
private:
	Player player1;
	Player player2;
	AttackManager attackManager;
	Sound sound;

	float Timer;		//	時間
	float countTime;	//	カウントダウン用

	int P1WinNum;       //	1P勝利数
	int P2WinNum;       //	2P勝利数

	bool P1Win;			//	1P勝利
	bool P2Win;			//	2P勝利

	int CoolTimeH;		//	スキルのクールタイム

	bool countDown;		//	カウントダウン
	bool roundEnd;		//	ラウンド終了
	bool matchEnd;		//	試合終了
	bool pause;			//	ポーズ
	bool debug;			//	デバッグ

public:
	PlayScene();
	~PlayScene();

	void Initialize()	override;   //	初期化
	void Update()       override;   //	更新
	void Render()       override;   //	描画
	void Finalize()     override;	//	終了

	void Reset();					//	ラウンドリセット

	void HitUpdate();				//	当たり判定の更新
	void JugeRight();				//	どっちか右か判断する

	void UIRender();				//	UI描画

	void PauseUpdate();				//	ポーズ更新
	void PauseRender();				//	ポーズ描画

	void RoundEnd();				//	ラウンド終了処理
};
