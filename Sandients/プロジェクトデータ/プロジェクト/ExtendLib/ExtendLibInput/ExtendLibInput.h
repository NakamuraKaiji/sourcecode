/*
	ExtendLibInput.h
	DxLibを利用して、入力の状態を管理するクラス。
	DxLibでは、ボタンが押されているか押されていないかは分かるが、
	押された瞬間か、放された瞬間か、というチェックができないため、
	その部分をカバーするための処理をサポートする。
*/
#pragma once
#include <vector>

//	ボタン数
const int MAX_BUTTON_NUM = 32;

//	スティック
enum class PadTip
{
	X,
	Y,
	Z,
	Rx,
	Ry,
	Rz,

	TipNum
};

//	POV
enum class PadPOV
{
	Arrow,
	none,
	nasi,
	nee,

	POVNum
};

//	パッド用構造体
struct PadStatas
{
	int PadNum = 0;							//	パッド番号
	int newPadButtonInput = 0;				//	ジョイパッドの現在の入力
	int oldPadButtonInput = 0;				//	ジョイパッドの1フレーム前の入力
	std::vector<char> newPadBtnInput = {};	//	ジョイパッドの現在の入力
	std::vector<char> oldPadBtnInput = {};	//	ジョイパッドの1フレーム前の入力
	std::vector<int> newPadPOVInput = {};	//	ジョイパッドの現在の矢印入力
	std::vector<int> oldPadPOVInput = {};	//	ジョイパッドの1フレーム前の矢印入力
	std::vector<int> newPadTipInput = {};	//	ジョイパッドの現在のスティック傾き
	std::vector<int> oldPadTipInput = {};	//	ジョイパッドの1フレーム前のスティック傾き
};

enum class PlayerID
{
	player1 = 0,
	player2 = 1
};

class ExtendLibInput
{
private:
	static const int KEY_CODE_MAX;		//	キーの最大数
	std::vector<int> playerInputPad;	//	各プレイヤーのパッド番号

	int newConectedPadNum;				//	パッド接続数
	int oldConectedPadNum;				//	1フレーム前のパッド接続数

	std::vector<PadStatas> padStatas;	//	各パッド情報

	int nowKeyInput[256];				//	キーコードの現在の入力
	int oldKeyInput[256];				//	キーコードの1フレーム前の入力

public:
	ExtendLibInput();					//	コンストラクタ
	~ExtendLibInput();					//	デストラクタ

	void Initialize();					//	初期化処理
	void Update();						//	更新処理
	void Finalize();					//	終了処理

	int GetPadNum(int padID);						        //	パッドIDから番号を取得
	
	int IsButtonDown(int padID, int tipID);			        //	特定のジョイパッドのボタンが押されているか
	int IsButtonUp(int padID, int tipID);			        //	特定のジョイパッドのボタンが放されているか
	int IsButtonPressed(int padID, int tipID);		        //	特定のジョイパッドのボタンが押された瞬間か
	int IsButtonReleased(int padID, int tipID);		        //	特定のジョイパッドのボタンが放された瞬間か

	int IsButtonDown(int tipID);					        //	ジョイパッドのボタンが押されているか
	int IsButtonUp(int tipID);						        //	ジョイパッドのボタンが放されているか
	int IsButtonPressed(int tipID);					        //	ジョイパッドのボタンが押された瞬間か
	int IsButtonReleased(int tipID);				        //	ジョイパッドのボタンが放された瞬間か

	int IsPOVDown(int padID, int POVID, int val);		    //	特定のジョイパッドのPOVボタンが押されているか
	int IsPOVUp(int padID, int POVID, int val);			    //	特定のジョイパッドのPOVボタンが放されているか
	int IsPOVPressed(int padID, int POVID, int val);	    //	特定のジョイパッドのPOVボタンが押された瞬間か
	int IsPOVReleased(int padID, int POVID, int val);	    //	特定のジョイパッドのPOVボタンが放された瞬間か
	int IsPOVVal(int padID, int POVID);						//	特定のジョイパッドの値をチェック

	int IsPOVDown(int POVID, int val);						//	ジョイパッドのPOVボタンが押されているか
	int IsPOVUp(int POVID, int val);			            //	ジョイパッドのPOVボタンが放されているか
	int IsPOVPressed(int POVID, int val);	                //	ジョイパッドのPOVボタンが押された瞬間か
	int IsPOVReleased(int POVID, int val);	                //	ジョイパッドのPOVボタンが放された瞬間か

	int IsTipDown(int padID, int analogID, bool plass);		//	特定のスティックが倒されているかチェック
	int IsTipUp(int padID, int analogID, bool plass);		//	特定のスティックが普通の状態かチェック
	int IsTipPressed(int padID, int analogID, bool plass);  //	特定のスティックが倒された瞬間かチェック
	int IsTipRelesed(int padID, int analogID, bool plass);  //	特定のスティックが戻った瞬間かチェック
	int IsTipVal(int padID, int analogID);				    //	特定のスティックの値チェック

	int GetIsButtonPressedPadID(int tipID);			        //	ジョイパッドの指定のボタンが押されているパッドIDを取得

	bool GetNewConectedPad();						        //	パッドが接続されたかどうか
	bool GetDisconectedPad();						        //	パッドが切断されたかどうか

	bool GetPlayerPadConected(int playerID);		        //	そのプレイヤー用のパッドがつながっているかどうか

	void SetPlayerInputNum(int playerID, int PADID);        //	パッド番号設定
	std::vector<int> GetPlayerInputNum();			        //	パッド番号取得

	int IsKeyDown(int keyCode);						        //	キーボードのボタンが押されているかチェック
	int IsKeyUp(int keyCode);						        //	キーボードのボタンが放されているかチェック
	int IsKeyPressed(int keyCode);					        //	キーボードのボタンが押された瞬間かチェック
	int IsKeyReleased(int keyCode);					        //	キーボードのボタンが放された瞬間かチェック
};

