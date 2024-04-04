#pragma once
#include <vector>
struct Score
{
	float hitedDamage = 0.0f;
	std::vector<int> useSkillNum;
};

struct Statas
{
	int HP;						//�q�b�g�|�C���g
	int ATK;					//�A�^�b�N
	int DEF;					//�f�B�t�F���X
	int WEI;					//�E�F�C�g
	std::vector<int>	skillID = { 0 };				//	�e�X�L��ID
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

	void SetScore(int pID, Score score);	//	�X�R�A�ݒ�
	Score GetScore(int pID);				//	�X�R�A��n

	void SetStatas(int pID, Statas statas);
	Statas GetStatas(int pID);
};
