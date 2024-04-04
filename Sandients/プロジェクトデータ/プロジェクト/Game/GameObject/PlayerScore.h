#pragma once
#include <vector>
struct Score
{
	float hitedDamage = 0.0f;
	std::vector<int> useSkillNum;
};

struct Statas
{
	int HP;						//ヒットポイント
	int ATK;					//アタック
	int DEF;					//ディフェンス
	int WEI;					//ウェイト
	std::vector<int>	skillID = { 0 };				//	各スキルID
};

class PlayerScore
{
private:
	Score p1Score;
	Score p2Score;

	Statas p1Statas;
	Statas p2Statas;

	int WinPID;

public:
	PlayerScore();
	~PlayerScore();

	void SetWinPID(int PID);
	int GetWinPID();

	void SetScore(int pID, Score score);	//	スコア設定
	Score GetScore(int pID);				//	スコア受渡

	void SetStatas(int pID, Statas statas);
	Statas GetStatas(int pID);
};
