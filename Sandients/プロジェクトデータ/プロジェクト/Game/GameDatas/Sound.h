#pragma once 

class Sound
{
private:
	int s_attack;
	int m_attack;
	int l_attack;
	int hitedSkill;
	int guard;
	int jump;
	int round1;
	int round2;
	int round3;
	int fight;
	int you_win;
	int you_lose;
	int select;
	int decision;
	int ready;
	int blow;
	int useskill;
	int resultSonud;

	int eggDrop;
	int eggHeal;

	int titleBgm;
	int selectBgm;
	int playBgm;

public:
	Sound();
	~Sound();

	void S_Attack();
	void M_Attack();
	void L_Attack();
	void HitedSkill();
	void Guard();
	void Jump();
	void Round1();
	void Round2();
	void Round3();
	void Fight();
	void You_Win();
	void You_Lose();
	void Select();
	void Decision();
	void Ready();
	void Blow();
	void useSkill();
	void resultSE();

	void EggDrop();
	void EggHeal();

	void TitleBGM();
	void SelectBGM();
	void PlayBGM();

	void StopTitleBGM();
	void StopSelectBGM();
	void StopPlayBGM();
};