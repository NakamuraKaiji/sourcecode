#pragma once
#include <DxLib.h>

const struct DualShock4Input
{
	static const int  ARROW_POV   = 0;
	static const int  ARROW_UP    = 0;					//	Å™	
	static const int  ARROW_DOWN  = 18000;				//	Å´
	static const int  ARROW_LEFT  = 27000;				//	Å©
	static const int  ARROW_RIGHT = 9000;				//	Å®
					 
	static const int  UP        = PAD_INPUT_UP;	        //	Å™
	static const int  DOWN      = PAD_INPUT_DOWN;	    //	Å´
	static const int  LEFT      = PAD_INPUT_LEFT;	    //	Å©
	static const int  RIGHT     = PAD_INPUT_RIGHT;	    //	Å®
					 
	static const int  SQUARE    = PAD_INPUT_1;	        //	Å†
	static const int  CROSS     = PAD_INPUT_2;	        //	Å~
	static const int  CIRCLE    = PAD_INPUT_3;	        //	Åõ
	static const int  TRIANGLE  = PAD_INPUT_4;	        //	Å¢
					 
	static const int  LEFT1     = PAD_INPUT_5;	        //	L1
	static const int  RIGHT1    = PAD_INPUT_6;	        //	R1
	static const int  LEFT2     = PAD_INPUT_7;	        //	L2
	static const int  RIGHT2    = PAD_INPUT_8;	        //	R2
					 
	static const int  SHARE     = PAD_INPUT_9;	        //	SHARE
	static const int  OPTIONS   = PAD_INPUT_10;	        //	OPTIONS
	static const int  LEFT3     = PAD_INPUT_11;	        //	L3
	static const int  RIGHT3    = PAD_INPUT_12;	        //	R3
					 
	static const int  PS        = PAD_INPUT_13;	        //	PS
	static const int  PAD       = PAD_INPUT_14;	        //	PAD
					 
	static const int  LS_X      = 0;
	static const bool LS_RIGHT  = true;
	static const bool LS_LEFT   = false;
	static const int  LS_Y      = 1;
	static const bool LS_UP     = false;
	static const bool LS_DOWN   = true;
	static const int  RS_X      = 2;
	static const bool RS_RIGHT  = true;
	static const bool RS_LEFT   = false;
	static const int  RS_Y      = 5;
	static const bool RS_UP     = false;
	static const bool RS_DOWN   = true;
};
