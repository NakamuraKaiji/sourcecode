#pragma once
#include <vector>

const struct AttackTable
{
	float power = 1.0f;		            //	攻撃の威力（倍率）
	int maxConbo = 3;			        //	攻撃の最大コンボ数
	float maxConboRate = 1.8f;			//	攻撃の最大コンボの倍率
	float beforePunishTime = 0.2f;		//	攻撃の前隙
	float afterPunishTime = 0.4f;		//	攻撃の後隙
	float maxConboPunishRate = 4.0f;	//	攻撃の最大コンボの後隙倍率
	float hitSize = 1.0f;		        //	攻撃の判定の大きさ
	float hitRemainTime = 3.0f;		    //	攻撃の判定の残存時間	
	float knockBack = 1000.0f;	        //	攻撃のノックバックの強さ
	float knockDeg = 45.0f;		        //	攻撃のノックバックの角度
};

const std::vector<AttackTable> ATTACK = {
	{ 0.41f, 3, 2.2f, 0.05f, 0.2f, 2.0f, 22.0f,  0.2f,  500.0f, 70.0f},
};