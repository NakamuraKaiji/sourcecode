#pragma once
#include <vector>

const struct AttackTable
{
	float power = 1.0f;		            //	�U���̈З́i�{���j
	int maxConbo = 3;			        //	�U���̍ő�R���{��
	float maxConboRate = 1.8f;			//	�U���̍ő�R���{�̔{��
	float beforePunishTime = 0.2f;		//	�U���̑O��
	float afterPunishTime = 0.4f;		//	�U���̌㌄
	float maxConboPunishRate = 4.0f;	//	�U���̍ő�R���{�̌㌄�{��
	float hitSize = 1.0f;		        //	�U���̔���̑傫��
	float hitRemainTime = 3.0f;		    //	�U���̔���̎c������	
	float knockBack = 1000.0f;	        //	�U���̃m�b�N�o�b�N�̋���
	float knockDeg = 45.0f;		        //	�U���̃m�b�N�o�b�N�̊p�x
};

const std::vector<AttackTable> ATTACK = {
	{ 0.41f, 3, 2.2f, 0.05f, 0.2f, 2.0f, 22.0f,  0.2f,  500.0f, 70.0f},
};