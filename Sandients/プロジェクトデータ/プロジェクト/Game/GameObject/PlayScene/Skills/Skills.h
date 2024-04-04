#pragma once
#include <vector>

const struct SkillTable
{
	float ct = 5.0f;					//	スキルのクールタイム
	int stock = 1;						//	スキルの最大ストック数
	float beforePunishTime = 0.2f;		//	スキルの前隙
	float afterPunishTime = 0.4f;		//	スキルの後隙
};

const std::vector<SkillTable> SKILL = {
	{  5.0f, 1, 0.25f, 0.1f},	//	Lettuce,
	{  6.0f, 2, 0.1f , 0.1f},	//	Tomato,
	{ 10.0f, 1, 0.3f , 0.3f},	//	Onion,
	
	{ 10.0f, 1, 0.3f , 0.3f},	//	Bacon
	{ 20.0f, 1, 0.1f , 0.1f},	//	Chicken
	{ 10.0f, 1, 0.2f , 0.3f},	//	Salmon
	{ 15.0f, 1, 0.3f , 0.1f},	//	Tuna

	{ 15.0f, 1, 0.0f , 0.2f},	//	Banana
	{ 15.0f, 1, 0.0f , 0.2f},	//	Whip
};

enum class SkillName
{
	Lettuce,
	Tomato,
	Onion,

	Bacon,
	Chicken,
	Salmon,
	Tuna,

	Banana,
	Whip,

	SkillNum
};

#define SKILL_VEGE_LETTUCE_POWER			   2.0f	//	威力
#define SKILL_VEGE_LETTUCE_SIZE				  50.0f	//	大きさ
#define SKILL_VEGE_LETTUCE_REMAINTIME		   3.0f	//	残存時間
#define SKILL_VEGE_LETTUCE_KNOCKBUCK		1000.0f	//	ノックバックの強さ
#define SKILL_VEGE_LETTUCE_KNOCKDEG			  45.0f	//	ノックバックの角度
#define SKILL_VEGE_LETTUCE_MAX_RENGE		1000.0f	//	最大射程
#define SKILL_VEGE_LETTUCE_HEIGHT			200.0f	//	出現位置
#define SKILL_VEGE_LETTUCE_SPD				400.0f	//	落下スピード

#define SKILL_VEGE_TOMATO_POWER				0.8f	//	威力
#define SKILL_VEGE_TOMATO_SIZE			   50.0f	//	大きさ
#define SKILL_VEGE_TOMATO_REMAINTIME	    3.0f	//	残存時間
#define SKILL_VEGE_TOMATO_KNOCKBUCK		 1000.0f	//	ノックバックの強さ
#define SKILL_VEGE_TOMATO_KNOCKDEG		   45.0f	//	ノックバックの角度
#define SKILL_VEGE_TOMATO_SPD		      900.0f	//	スピード

#define SKILL_VEGE_ONION_REMAINTIME		    5.0f	//	効果時間
#define SKILL_VEGE_ONION_ATK_RATE		    1.3f	//	攻撃倍率
#define SKILL_VEGE_ONION_DEF_RATE		    1.3f	//	防御倍率
#define SKILL_VEGE_ONION_KNOCK_RATE		    0.8f	//	ノックバック倍率

#define SKILL_MEAT_BACON_POWER				2.1f	    //	威力
#define SKILL_MEAT_BACON_SIZE			   50.0f	    //	大きさ
#define SKILL_MEAT_BACON_REMAINTIME	        3.0f	    //	残存時間
#define SKILL_MEAT_BACON_KNOCKBUCK		 1000.0f	    //	ノックバックの強さ
#define SKILL_MEAT_BACON_KNOCKDEG		   45.0f	    //	ノックバックの角度
#define SKILL_MEAT_BACON_SPD_X			 1000.0f	    //	スピード
#define SKILL_MEAT_BACON_SPD_Y		 	  300.0f	    //	スピード

#define SKILL_MEAT_CHICKEN_HEAL				0.04f	    //	ヒール%
#define SKILL_MEAT_CHICKEN_SPEED			300.0f	    //	移動速度
#define SKILL_MEAT_CHICKEN_MOVE_RAND		0.33f	    //	移動反転率
#define SKILL_MEAT_CHICKEN_SCALE			50.0f	    //	大きさ
#define SKILL_MEAT_CHICKEN_CREATE_TIME	    5.0f	    //	生成速度
#define SKILL_MEAT_CHICKEN_EGG_SCALE		20.0f	    //	大きさ(ヒール)
#define SKILL_MEAT_CHICKEN_EGG_NUM		    3.0f	    //	個数
#define SKILL_MEAT_CHICKEN_EGG_DROP_SPD		400.0f	    //	落下速度

#define SKILL_MEAT_SALMON_POWER				0.2f	    //	威力
#define SKILL_MEAT_SALMON_NUM				  10	    //	球数
#define SKILL_MEAT_SALMON_SHOT_COOLTIME		8.0f	    //	連射速度
#define SKILL_MEAT_SALMON_SCALE			   30.0f		//	大きさ
#define SKILL_MEAT_SALMON_SPD			  1400.0f	    //	SPD
#define SKILL_MEAT_SALMON_REMAINTIME	    10.0f	    //	残存時間
#define SKILL_MEAT_SALMON_KNOCKBUCK		     0.0f       //	ノックバックの強さ
#define SKILL_MEAT_SALMON_KNOCKDEG		   30.0f	    //	ノックバックの角度

#define SKILL_MEAT_TUNAN_REMAINTIME		    10.0f	    //	効果時間
#define SKILL_MEAT_TUNAN_SPD_RATE		    2.0f	    //	速度倍率

#define SKILL_FRUIT_BANANA_SIZE				  50.0f	    //	大きさ
#define SKILL_FRUIT_BANANA_REMAINTIME		   3.0f	    //	残存時間
#define SKILL_FRUIT_BANANA_DEF_VELX			 600.0f	    //	縦スピード
#define SKILL_FRUIT_BANANA_DEF_VELY			 350.0f	    //	横スピード
#define SKILL_FRUIT_BANANA_DROP_SPD			1200.0f	    //	落下
#define SKILL_FRUIT_BANANA_CANTMOVE_TIME	   1.0f	    //	スタン時間

#define SKILL_FRUIT_WHIP_SIZE				  10.0f	    //	大きさ
#define SKILL_FRUIT_WHIP_REMAINTIME		      10.0f	    //	残存時間
#define SKILL_FRUIT_WHIP_DROP_SPD			1200.0f	    //	落下
#define SKILL_FRUIT_WHIP_SLOW_RATE	           0.5f	    //	鈍足
#define SKILL_FRUIT_WHIP_SLOW_TIME	           5.0f	    //	鈍足時間