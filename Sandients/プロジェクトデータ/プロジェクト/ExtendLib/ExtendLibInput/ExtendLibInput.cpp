/*
	ExtendLibInput.cpp
	DxLibを利用して、入力の状態を管理するクラス。
	DxLibでは、ボタンが押されているか押されていないかは分かるが、
	押された瞬間か、放された瞬間か、というチェックができないため、
	その部分をカバーするための処理をサポートするため、実際の処理を記述する。
*/
#include <DxLib.h>
#include "ExtendLibInput.h"

const int MAX_PLAYER_NUM			   = 4;		//	最大プレイヤー数
const int ExtendLibInput::KEY_CODE_MAX = 256;
const int DEADZONE = 100;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// コンストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
ExtendLibInput::ExtendLibInput()
{
	//	変数の初期化を行う
	Initialize();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// デストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
ExtendLibInput::~ExtendLibInput()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 初期化処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void ExtendLibInput::Initialize()
{
	newConectedPadNum = GetJoypadNum();
	playerInputPad.clear();
	padStatas.clear();

	//	プレイヤー番号初期化
	for (int i = 0; i < MAX_PLAYER_NUM; i++)
	{
		playerInputPad.emplace_back();
	}

	//	ジョイパッドのボタン情報用変数の初期化
	for (int i = 0; i < newConectedPadNum; i++)
	{
		padStatas.emplace_back();
		padStatas[i].PadNum = i + 1;
		for (size_t j = 0; j < static_cast<int>(MAX_BUTTON_NUM); j++)
		{
			padStatas[i].newPadBtnInput.emplace_back();
		}
		for (size_t j = 0; j < static_cast<int>(PadPOV::POVNum); j++)
		{
			padStatas[i].newPadPOVInput.emplace_back();
		}
		for (size_t j = 0; j < static_cast<int>(PadTip::TipNum); j++)
		{
			padStatas[i].newPadTipInput.emplace_back();
		}
	}

	//	パッド初期化処理

	//	キーボードのボタン情報用変数の初期化
	for (int i = 0; i < KEY_CODE_MAX; i++)
	{
		nowKeyInput[i] = 0;
		oldKeyInput[i] = 0;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 更新処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void ExtendLibInput::Update()
{
	DINPUT_JOYSTATE pad;
	//	パッド接続数代入
	oldConectedPadNum = newConectedPadNum;
	newConectedPadNum = GetJoypadNum();
	//	パッドの数が違ったらリセット
	if (oldConectedPadNum != newConectedPadNum) Initialize();

	//	パッドの情報を更新
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		GetJoypadDirectInputState(padStatas[i].PadNum, &pad);

		padStatas[i].oldPadButtonInput = padStatas[i].newPadButtonInput;
		padStatas[i].newPadButtonInput = GetJoypadInputState(padStatas[i].PadNum);

		padStatas[i].oldPadBtnInput = padStatas[i].newPadBtnInput;
		//padStatas[i].newPadBtnInput = pad.Buttons;

		padStatas[i].oldPadPOVInput = padStatas[i].newPadPOVInput;
		padStatas[i].newPadPOVInput[static_cast<int>(PadPOV::Arrow)] = GetJoypadPOVState(padStatas[i].PadNum, static_cast<int>(PadPOV::Arrow));
		//padStatas[i].newPadPOVInput[static_cast<int>(PadPOV::Arrow)] = pad.POV[static_cast<int>(PadPOV::Arrow)];
		padStatas[i].newPadPOVInput[static_cast<int>(PadPOV::none)] = pad.POV[static_cast<int>(PadPOV::none)];
		padStatas[i].newPadPOVInput[static_cast<int>(PadPOV::nasi)] = pad.POV[static_cast<int>(PadPOV::nasi)];
		padStatas[i].newPadPOVInput[static_cast<int>(PadPOV::nee)] = pad.POV[static_cast<int>(PadPOV::nee)];

		padStatas[i].oldPadTipInput = padStatas[i].newPadTipInput;
		GetJoypadAnalogInput(
			&padStatas[i].newPadTipInput[static_cast<int>(PadTip::X)], 
			&padStatas[i].newPadTipInput[static_cast<int>(PadTip::Y)], 
			padStatas[i].PadNum
		);
		//padStatas[i].newPadTipInput[static_cast<int>(PadTip::X)] = pad.X;
		//padStatas[i].newPadTipInput[static_cast<int>(PadTip::Y)] = pad.Y;
		padStatas[i].newPadTipInput[static_cast<int>(PadTip::Z)] = pad.Z;
		padStatas[i].newPadTipInput[static_cast<int>(PadTip::Rx)] = pad.Rx;
		padStatas[i].newPadTipInput[static_cast<int>(PadTip::Ry)] = pad.Ry;
		padStatas[i].newPadTipInput[static_cast<int>(PadTip::Rz)] = pad.Ry;
	}

	//	キーボードのボタン情報をループで更新する
	for (int i = 0; i < KEY_CODE_MAX; i++)
	{
		//	ループでoldKeyInput[i]の中にnowKeyInput[i]を入れ、1フレーム前の情報を確保する
		oldKeyInput[i] = nowKeyInput[i];
		nowKeyInput[i] = CheckHitKey(i);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 解放処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void ExtendLibInput::Finalize()
{
	//	何か必要な終了処理があれば、行う
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// パッドIDから番号を取得
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::GetPadNum(int padID)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		if (padStatas[i].PadNum == padID)
			return i;
	}
	return -1;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのボタンが押されているか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsButtonDown(int padID, int buttonID)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたボタンが押されているかチェックする
	if ((padStatas[ID].newPadButtonInput & buttonID) != 0)
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのボタンが放されているか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsButtonUp(int padID, int buttonID)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたボタンが放されているかチェックする
	if ((padStatas[ID].newPadButtonInput & buttonID) == 0)
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのボタンが押された瞬間か
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsButtonPressed(int padID, int buttonID)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたボタンが押された瞬間かチェックする
	if ((padStatas[ID].newPadButtonInput & buttonID) != 0 &&
		(padStatas[ID].oldPadButtonInput & buttonID) == 0)
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのボタンが放された瞬間か
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsButtonReleased(int padID, int buttonID)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたボタンが放された瞬間かチェックする
	if ((padStatas[ID].newPadButtonInput & buttonID) == 0 &&
		(padStatas[ID].oldPadButtonInput & buttonID) != 0)
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ボタンが押されているかどうか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsButtonDown(int buttonID)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	ボタンが押されている状態かチェックする
		if ((padStatas[i].newPadButtonInput & buttonID) != 0)
			return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ジョイパッドのボタンが放されているか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsButtonUp(int buttonID)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	ボタンが放されている状態かチェックする
		if ((padStatas[i].newPadButtonInput & buttonID) == 0)
			return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ジョイパッドのボタンが押された瞬間か
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsButtonPressed(int buttonID)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	ボタンが押された瞬間かチェックする
		if ((padStatas[i].newPadButtonInput & buttonID) != 0 &&
			(padStatas[i].oldPadButtonInput & buttonID) == 0)
			return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ジョイパッドのボタンが放された瞬間か
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsButtonReleased(int buttonID)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	ボタンが放された瞬間かチェックする
		if ((padStatas[i].newPadButtonInput & buttonID) == 0 &&
			(padStatas[i].oldPadButtonInput & buttonID) != 0)
			return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのPOVボタンが押されているかチェック
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVDown(int padID, int POVID, int val)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたPOVIDになっている状態かチェックする
	if (padStatas[ID].newPadPOVInput[POVID] == val)
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのPOVボタンが放されているかチェック
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVUp(int padID, int POVID, int val)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたPOVになっていない状態かチェックする
	if (padStatas[ID].newPadPOVInput[POVID] != val)
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのPOVボタンが押された瞬間かチェック
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVPressed(int padID, int POVID, int val)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたPOVIDが、前フレームで押されておらず、今フレームで押されていたら、1を返す
	if (padStatas[ID].newPadPOVInput[POVID] == val &&
		padStatas[ID].oldPadPOVInput[POVID] != val)
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのPOVボタンが放された瞬間かチェック
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVReleased(int padID, int POVID, int val)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたPOVIDが、前フレームで押されており、今フレームで押されていないなら、1を返す
	if (padStatas[ID].newPadPOVInput[POVID] != val &&
		padStatas[ID].oldPadPOVInput[POVID] == val)
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 特定のジョイパッドのPOVの値取得
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVVal(int padID, int POVID)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたスティックの値を返す
	return padStatas[ID].newPadPOVInput[POVID];
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ジョイパッドのPOVボタンが押されているか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVDown(int POVID, int val)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	POVが押されたかチェックする
		if (padStatas[i].newPadPOVInput[POVID] == val)
			return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ジョイパッドのPOVボタンが放されているか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVUp(int POVID, int val)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	POVが放されたかチェックする
		if (padStatas[i].newPadPOVInput[POVID] != val)
			return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ジョイパッドのPOVボタンが押された瞬間か
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVPressed(int POVID, int val)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	POVが押された瞬間かチェックする
		if (padStatas[i].newPadPOVInput[POVID] == val &&
			padStatas[i].oldPadPOVInput[POVID] != val)
			return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ジョイパッドのPOVボタンが放された瞬間か
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsPOVReleased(int POVID, int val)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	POVが放された瞬間かチェックする
		if (padStatas[i].newPadPOVInput[POVID] != val &&
			padStatas[i].oldPadPOVInput[POVID] == val)
			return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 倒されいてるか判断
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsTipDown(int padID, int tipID, bool plass)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたスティックが倒されているかチェック
	if ((padStatas[ID].newPadTipInput[tipID] > DEADZONE && plass) || (padStatas[ID].newPadTipInput[tipID] < -DEADZONE && !plass))
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 倒されていないか判断
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsTipUp(int padID, int tipID, bool plass)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたスティックが倒されていないチェック
	if ((padStatas[ID].newPadTipInput[tipID] <= DEADZONE && plass) || (padStatas[ID].newPadTipInput[tipID] >= -DEADZONE && !plass))
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 倒された瞬間か判断
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsTipPressed(int padID, int tipID, bool plass)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたスティックが倒された瞬間チェック
	if (((padStatas[ID].newPadTipInput[tipID] > DEADZONE && plass) || (padStatas[ID].newPadTipInput[tipID] < -DEADZONE && !plass)) &&
		((padStatas[ID].oldPadTipInput[tipID] <= DEADZONE && plass) || (padStatas[ID].oldPadTipInput[tipID] >= -DEADZONE && !plass)))
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 放された瞬間か判断
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsTipRelesed(int padID, int tipID, bool plass)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたスティックが放された瞬間かチェック
	if (((padStatas[ID].newPadTipInput[tipID] <= DEADZONE && plass) || (padStatas[ID].newPadTipInput[tipID] >= -DEADZONE && !plass)) &&
		((padStatas[ID].oldPadTipInput[tipID] > DEADZONE && plass) || (padStatas[ID].oldPadTipInput[tipID] < -DEADZONE && !plass)))
		return 1;

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// どのくらい倒されいてるか取得
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::IsTipVal(int padID, int tipID)
{
	//	パッド番号を取得し存在しなければリターン
	int ID = GetPadNum(padID);
	if (ID < 0) return 0;

	//	指定されたスティックの値を返す
	return padStatas[ID].newPadTipInput[tipID];
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ジョイパッドの指定のボタンが押されているパッドIDを取得
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int ExtendLibInput::GetIsButtonPressedPadID(int buttonID)
{
	for (size_t i = 0; i < padStatas.size(); i++)
	{
		//	ボタンが押された瞬間かチェックする
		if ((padStatas[i].newPadButtonInput & buttonID) != 0 &&
			(padStatas[i].oldPadButtonInput & buttonID) == 0)
			return padStatas[i].PadNum;
	}

	return -1;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// パッドが接続されたかどうか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
bool ExtendLibInput::GetNewConectedPad()
{
	if (oldConectedPadNum < newConectedPadNum) return true;
	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// パッドが切断されたかどうか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
bool ExtendLibInput::GetDisconectedPad()
{
	if (oldConectedPadNum > newConectedPadNum) return true;
	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// そのプレイヤー用のパッドがつながっているかどうか
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
bool ExtendLibInput::GetPlayerPadConected(int playerID)
{
	if (playerInputPad.size() > playerID) return true;
	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// プレイヤーパッド番号設定
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void ExtendLibInput::SetPlayerInputNum(int playerID,int PADID)
{
	playerInputPad[playerID] = PADID;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// プレイヤーのパッド番号取得
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
std::vector<int> ExtendLibInput::GetPlayerInputNum()
{
	return playerInputPad;
}

//	キーボードのボタンが押されているかチェック
int ExtendLibInput::IsKeyDown(int keyCode)
{
	//	指定されたキーコードが押されている状態かチェックする
	if (nowKeyInput[keyCode] == 1)
	{
		return 1;
	}

	return 0;
}

//	キーボードのボタンが放されているかチェック
int ExtendLibInput::IsKeyUp(int keyCode)
{
	//	指定されたキーコードが放されている状態かチェックする
	if (nowKeyInput[keyCode] == 0)
	{
		return 1;
	}

	return 0;
}

//	キーボードのボタンが押された瞬間かチェック
int ExtendLibInput::IsKeyPressed(int keyCode)
{
	//	指定されたキーコードが、前フレームで押されておらず、今フレームで押されていたら、1を返す
	if (oldKeyInput[keyCode] == 0 &&
		nowKeyInput[keyCode] == 1)
	{
		return 1;
	}

	return 0;
}

//	キーボードのボタンが放された瞬間かチェック
int ExtendLibInput::IsKeyReleased(int keyCode)
{
	//	指定されたキーコードが、前フレームで押されており、今フレームで押されていなかったら、1を返す
	if (oldKeyInput[keyCode] == 1 &&
		nowKeyInput[keyCode] == 0)
	{
		return 1;
	}

	return 0;
}