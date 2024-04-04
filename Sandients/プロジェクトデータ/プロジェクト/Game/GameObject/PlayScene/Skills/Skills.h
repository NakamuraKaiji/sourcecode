#pragma once
#include <vector>

const struct SkillTable
{
	float ct = 5.0f;					//	�X�L���̃N�[���^�C��
	int stock = 1;						//	�X�L���̍ő�X�g�b�N��
	float beforePunishTime = 0.2f;		//	�X�L���̑O��
	float afterPunishTime = 0.4f;		//	�X�L���̌㌄
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

#define SKILL_VEGE_LETTUCE_POWER			   2.0f	//	�З�
#define SKILL_VEGE_LETTUCE_SIZE				  50.0f	//	�傫��
#define SKILL_VEGE_LETTUCE_REMAINTIME		   3.0f	//	�c������
#define SKILL_VEGE_LETTUCE_KNOCKBUCK		1000.0f	//	�m�b�N�o�b�N�̋���
#define SKILL_VEGE_LETTUCE_KNOCKDEG			  45.0f	//	�m�b�N�o�b�N�̊p�x
#define SKILL_VEGE_LETTUCE_MAX_RENGE		1000.0f	//	�ő�˒�
#define SKILL_VEGE_LETTUCE_HEIGHT			200.0f	//	�o���ʒu
#define SKILL_VEGE_LETTUCE_SPD				400.0f	//	�����X�s�[�h

#define SKILL_VEGE_TOMATO_POWER				0.8f	//	�З�
#define SKILL_VEGE_TOMATO_SIZE			   50.0f	//	�傫��
#define SKILL_VEGE_TOMATO_REMAINTIME	    3.0f	//	�c������
#define SKILL_VEGE_TOMATO_KNOCKBUCK		 1000.0f	//	�m�b�N�o�b�N�̋���
#define SKILL_VEGE_TOMATO_KNOCKDEG		   45.0f	//	�m�b�N�o�b�N�̊p�x
#define SKILL_VEGE_TOMATO_SPD		      900.0f	//	�X�s�[�h

#define SKILL_VEGE_ONION_REMAINTIME		    5.0f	//	���ʎ���
#define SKILL_VEGE_ONION_ATK_RATE		    1.3f	//	�U���{��
#define SKILL_VEGE_ONION_DEF_RATE		    1.3f	//	�h��{��
#define SKILL_VEGE_ONION_KNOCK_RATE		    0.8f	//	�m�b�N�o�b�N�{��

#define SKILL_MEAT_BACON_POWER				2.1f	    //	�З�
#define SKILL_MEAT_BACON_SIZE			   50.0f	    //	�傫��
#define SKILL_MEAT_BACON_REMAINTIME	        3.0f	    //	�c������
#define SKILL_MEAT_BACON_KNOCKBUCK		 1000.0f	    //	�m�b�N�o�b�N�̋���
#define SKILL_MEAT_BACON_KNOCKDEG		   45.0f	    //	�m�b�N�o�b�N�̊p�x
#define SKILL_MEAT_BACON_SPD_X			 1000.0f	    //	�X�s�[�h
#define SKILL_MEAT_BACON_SPD_Y		 	  300.0f	    //	�X�s�[�h

#define SKILL_MEAT_CHICKEN_HEAL				0.04f	    //	�q�[��%
#define SKILL_MEAT_CHICKEN_SPEED			300.0f	    //	�ړ����x
#define SKILL_MEAT_CHICKEN_MOVE_RAND		0.33f	    //	�ړ����]��
#define SKILL_MEAT_CHICKEN_SCALE			50.0f	    //	�傫��
#define SKILL_MEAT_CHICKEN_CREATE_TIME	    5.0f	    //	�������x
#define SKILL_MEAT_CHICKEN_EGG_SCALE		20.0f	    //	�傫��(�q�[��)
#define SKILL_MEAT_CHICKEN_EGG_NUM		    3.0f	    //	��
#define SKILL_MEAT_CHICKEN_EGG_DROP_SPD		400.0f	    //	�������x

#define SKILL_MEAT_SALMON_POWER				0.2f	    //	�З�
#define SKILL_MEAT_SALMON_NUM				  10	    //	����
#define SKILL_MEAT_SALMON_SHOT_COOLTIME		8.0f	    //	�A�ˑ��x
#define SKILL_MEAT_SALMON_SCALE			   30.0f		//	�傫��
#define SKILL_MEAT_SALMON_SPD			  1400.0f	    //	SPD
#define SKILL_MEAT_SALMON_REMAINTIME	    10.0f	    //	�c������
#define SKILL_MEAT_SALMON_KNOCKBUCK		     0.0f       //	�m�b�N�o�b�N�̋���
#define SKILL_MEAT_SALMON_KNOCKDEG		   30.0f	    //	�m�b�N�o�b�N�̊p�x

#define SKILL_MEAT_TUNAN_REMAINTIME		    10.0f	    //	���ʎ���
#define SKILL_MEAT_TUNAN_SPD_RATE		    2.0f	    //	���x�{��

#define SKILL_FRUIT_BANANA_SIZE				  50.0f	    //	�傫��
#define SKILL_FRUIT_BANANA_REMAINTIME		   3.0f	    //	�c������
#define SKILL_FRUIT_BANANA_DEF_VELX			 600.0f	    //	�c�X�s�[�h
#define SKILL_FRUIT_BANANA_DEF_VELY			 350.0f	    //	���X�s�[�h
#define SKILL_FRUIT_BANANA_DROP_SPD			1200.0f	    //	����
#define SKILL_FRUIT_BANANA_CANTMOVE_TIME	   1.0f	    //	�X�^������

#define SKILL_FRUIT_WHIP_SIZE				  10.0f	    //	�傫��
#define SKILL_FRUIT_WHIP_REMAINTIME		      10.0f	    //	�c������
#define SKILL_FRUIT_WHIP_DROP_SPD			1200.0f	    //	����
#define SKILL_FRUIT_WHIP_SLOW_RATE	           0.5f	    //	�ݑ�
#define SKILL_FRUIT_WHIP_SLOW_TIME	           5.0f	    //	�ݑ�����