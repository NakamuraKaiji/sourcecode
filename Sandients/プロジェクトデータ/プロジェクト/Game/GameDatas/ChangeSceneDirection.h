//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ChangeSceneDirection
//				シーン切り替え時のフェードイン、アウト処理を行うクラス
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
#pragma once
#include "../GameScene/BaseScene.h"

class ChangeSceneDirection :public BaseScene
{
private:

	bool in;					//	フェードイン処理かどうか
	bool nowDirection;			//	描画中かどうか
	bool readyChangeScene;		//	シーン遷移できるかどうか

	float timeCount;			//	時間カウント

public:
	ChangeSceneDirection();
	~ChangeSceneDirection();

	void Initialize()	override;			//	初期化
	void Update()		override;			//	更新
	void Render()		override;			//	描画
	void Finalize()		override;			//	解放

	void StartSceneDirection(bool in);		//	演出開始時に呼び出す初期化処理
	bool GetNowSceneDirection();			//	切り替え演出中かどうかを渡す
	bool GetReadyChangeScene();				//	シーン切り替え可能かどうかを渡す
};
