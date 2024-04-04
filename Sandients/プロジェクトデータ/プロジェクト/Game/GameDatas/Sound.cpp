#include <DxLib.h>
#include "Sound.h"

Sound::Sound():
s_attack(0),
m_attack(0),
l_attack(0),
hitedSkill(0),
guard(0),
jump(0),
round1(0),
round2(0),
round3(0),
fight(0),
you_win(0),
you_lose(0),
select(0),
decision(0),
resultSonud(0),
eggDrop(0),
eggHeal(0),
titleBgm(0),
selectBgm(0),
playBgm(0)
{
	s_attack = LoadSoundMem("Resources/Sounds/attack1.mp3");
	m_attack = LoadSoundMem("Resources/Sounds/attack2.mp3");
	l_attack = LoadSoundMem("Resources/Sounds/attack3.mp3");
	hitedSkill = LoadSoundMem("Resources/Sounds/isHitSkill.mp3");

	guard = LoadSoundMem("Resources/Sounds/guard.mp3");
	jump = LoadSoundMem("Resources/Sounds/jump.mp3");

	round1 = LoadSoundMem("Resources/Sounds/round1.mp3");
	round2 = LoadSoundMem("Resources/Sounds/round2.mp3");
	round3 = LoadSoundMem("Resources/Sounds/round3.mp3");
	fight = LoadSoundMem("Resources/Sounds/fight.mp3");
	you_win = LoadSoundMem("Resources/Sounds/you_win.mp3");
	you_lose = LoadSoundMem("Resources/Sounds/you_lose.mp3");
	select = LoadSoundMem("Resources/Sounds/select.mp3");
	decision = LoadSoundMem("Resources/Sounds/decision.mp3");
	ready = LoadSoundMem("Resources/Sounds/ready.mp3");
	useskill = LoadSoundMem("Resources/Sounds/useSkill.mp3");
	blow = LoadSoundMem("Resources/Sounds/blow.mp3");
	resultSonud = LoadSoundMem("Resources/Sounds/ResultSE.mp3");

	eggDrop = LoadSoundMem("Resources/Sounds/Skills/eggDrop.mp3");
	eggHeal = LoadSoundMem("Resources/Sounds/Skills/eggHeal.mp3");

	titleBgm = LoadSoundMem("Resources/Sounds/BGM/TitleBGM.mp3");
	ChangeVolumeSoundMem(150, titleBgm);
	selectBgm = LoadSoundMem("Resources/Sounds/BGM/SelectBGM.mp3");
	playBgm = LoadSoundMem("Resources/Sounds/BGM/PlayBGM.mp3");
	ChangeVolumeSoundMem(100, playBgm);
}

Sound::~Sound()
{
	StopSoundMem(s_attack);
	DeleteSoundMem(s_attack);
	s_attack = -1;

	StopSoundMem(m_attack);
	DeleteSoundMem(m_attack);
	m_attack = -1;

	StopSoundMem(l_attack);
	DeleteSoundMem(l_attack);
	l_attack = -1;

	StopSoundMem(hitedSkill);
	DeleteSoundMem(hitedSkill);
	l_attack = -1;

	StopSoundMem(guard);
	DeleteSoundMem(guard);
	guard = -1;

	StopSoundMem(jump);
	DeleteSoundMem(jump);
	jump = -1;

	StopSoundMem(round1);
	DeleteSoundMem(round1);
	round1 = -1;

	StopSoundMem(round2);
	DeleteSoundMem(round2);
	round2 = -1;

	StopSoundMem(round3);
	DeleteSoundMem(round3);
	round3 = -1;

	StopSoundMem(fight);
	DeleteSoundMem(fight);
	fight = -1;

	StopSoundMem(you_win);
	DeleteSoundMem(you_win);
	you_win = -1;

	StopSoundMem(you_lose);
	DeleteSoundMem(you_lose);
	you_lose = -1;

	StopSoundMem(select);
	DeleteSoundMem(select);
	select = -1;

	StopSoundMem(decision);
	DeleteSoundMem(decision);
	decision = -1;

	StopSoundMem(ready);
	DeleteSoundMem(ready);
	decision = -1;

	StopSoundMem(blow);
	DeleteSoundMem(blow);
	decision = -1;

	StopSoundMem(useskill);
	DeleteSoundMem(useskill);
	decision = -1;

	StopSoundMem(resultSonud);
	DeleteSoundMem(resultSonud);
	decision = -1;

	StopSoundMem(eggDrop);
	DeleteSoundMem(eggDrop);
	decision = -1;

	StopSoundMem(eggHeal);
	DeleteSoundMem(eggHeal);
	decision = -1;

	StopSoundMem(titleBgm);
	DeleteSoundMem(titleBgm);
	decision = -1;

	StopSoundMem(selectBgm);
	DeleteSoundMem(selectBgm);
	decision = -1;

	StopSoundMem(playBgm);
	DeleteSoundMem(playBgm);
	decision = -1;
}

void Sound::S_Attack()
{
	PlaySoundMem(s_attack, DX_PLAYTYPE_BACK);
}

void Sound::M_Attack()
{
	PlaySoundMem(m_attack, DX_PLAYTYPE_BACK);
}

void Sound::L_Attack()
{
	PlaySoundMem(l_attack, DX_PLAYTYPE_BACK);
}

void Sound::HitedSkill()
{
	PlaySoundMem(hitedSkill, DX_PLAYTYPE_BACK);
}

void Sound::Guard()
{
	PlaySoundMem(guard, DX_PLAYTYPE_BACK);
}

void Sound::Jump()
{
	PlaySoundMem(jump, DX_PLAYTYPE_BACK);
}

void Sound::Round1()
{
	PlaySoundMem(round1, DX_PLAYTYPE_BACK);
}

void Sound::Round2()
{
	PlaySoundMem(round2, DX_PLAYTYPE_BACK);
}

void Sound::Round3()
{
	PlaySoundMem(round3, DX_PLAYTYPE_BACK);
}

void Sound::Fight()
{
	PlaySoundMem(fight, DX_PLAYTYPE_BACK);
}

void Sound::You_Win()
{
	PlaySoundMem(you_win, DX_PLAYTYPE_BACK);
}

void Sound::You_Lose()
{
	PlaySoundMem(you_lose, DX_PLAYTYPE_BACK);
}

void Sound::Select()
{
	PlaySoundMem(select, DX_PLAYTYPE_BACK);
}

void Sound::Decision()
{
	PlaySoundMem(decision, DX_PLAYTYPE_BACK);
}

void Sound::Ready()
{
	PlaySoundMem(ready, DX_PLAYTYPE_BACK);
}

void Sound::Blow()
{
	PlaySoundMem(blow, DX_PLAYTYPE_BACK);
}

void Sound::useSkill()
{
	PlaySoundMem(useskill, DX_PLAYTYPE_BACK);
}

void Sound::resultSE()
{
	PlaySoundMem(resultSonud, DX_PLAYTYPE_BACK);
}

void Sound::EggDrop()
{
	PlaySoundMem(eggDrop, DX_PLAYTYPE_BACK);
}

void Sound::EggHeal()
{
	PlaySoundMem(eggHeal, DX_PLAYTYPE_BACK);
}

void Sound::TitleBGM()
{
	PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
}

void Sound::SelectBGM()
{
	PlaySoundMem(selectBgm, DX_PLAYTYPE_LOOP);
}

void Sound::PlayBGM()
{
	PlaySoundMem(playBgm, DX_PLAYTYPE_LOOP);
}

void Sound::StopTitleBGM()
{
	StopSoundMem(titleBgm);
}

void Sound::StopSelectBGM()
{
	StopSoundMem(selectBgm);
}

void Sound::StopPlayBGM()
{
	StopSoundMem(playBgm);
}
