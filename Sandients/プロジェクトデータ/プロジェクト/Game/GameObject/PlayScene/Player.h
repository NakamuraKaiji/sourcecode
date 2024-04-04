//----------------------------------------------------------------------------------------------------
//	Player�E�E�E�T���h�E�B�b�`�B
// 
//----------------------------------------------------------------------------------------------------
#pragma once
#include <vector>
#include "../../GameDatas/Vector.h"
#include "../../../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "../../GameDatas/TextureManager.h"
#include "../../GameDatas/Sound.h"
#include "AttackManager.h"
#include "../../GameObject/PlayScene/Skills/Skills.h"
#include "../../GameObject/PlayerScore.h"


//	�X�e�[�^�X�p�\����
struct PlayerStatas
{
	float hp               = 0.0f;				    //	�̗�
	float atk              = 0.0f;				    //	�U����
	float def              = 0.0f;				    //	�h���
	float weight           = 0.0f;			        //	�d��
	int   atkID			   = 0;						//	�U��ID
	std::vector<int>	skillID = {0};				//	�e�X�L��ID
	float sp			   = 100.0f;				//	�K�E�Z�Q�[�W
	float maxHp			   = hp;					//	�ő�HP
	float maxSp			   = sp;					//	�ő�SP
	float defAtk		   = atk;					//	��{ATK
};

struct PlayerCondition
{
	float atkRate = 1.0f;		//	�U���͔{��
	float defRate = 1.0f;		//	�h��͔{��
	float spdRate = 1.0f;		//	�ړ����x�{��
	float knockRate = 1.0f;		//	�m�b�N�A�b�v�{��
};

class Player
{
private:
	Score score;
	Vector2 defPos;

	GameSystemObjects* system;	        //	�ړ����̃V�X�e���n
	TextureManger* tdata;
	Sound* sdata;

	AttackManager* attackManager;		//	�U��������
	Vector2 screenSize;		            //	��ʃT�C�Y
	float ground;						//	�n�ʈʒu
	int pID;							//	�v���C���[ID
	int padNum;					        //	�p�b�h�̔ԍ�

	PlayerStatas statas;	            //	�v���C���[�̃X�e�[�^�X
	PlayerCondition conditoin;			//	�v���C���[�̏��
	Vector2		 pos;	                //	�v���C���[�̍��W
	Vector2		 scale;		            //	�v���C���[�̑傫��
	Vector2		 vel;                   //	�v���C���[�̈ړ���

	//	�A�j���[�V�����p
	float        jumpVal;				//	�W�����v�̒l
	float		 maxJumpVal;			//	���̃W�����v�̍ő�l
	float        dropTime;				//	��������
	float        standbyTime;			//	�ҋ@����
	float        inviTime;				//	���G����
	float        maxAttackTime;

	bool		 fly;			        //	�󒆂��ǂ���
	bool		 guard;					//	�K�[�h���Ă��邩�ǂ���
	bool		 right;					//	�E�������Ă��邩�ǂ���
	bool         special;				//	�X�y�V������Ԃ��ǂ���
	bool		 charge;
	bool		 attack;				//	�U�����ǂ���

	float		 deltaTime;

	float        skillPunishTime;		//	�X�L���O��
	float		 attackPunishTime;		//	�U���O��
	float        attackComboRemainTime;	//	�U���R���{����
	float		 cantMoveTime;		    //	�����Ȃ����ǂ���
	float		 invincibleTime;		//	���G����

	int			 nowAtkNum;				//	���݂̍U��
	int			 nowSkillNum;			//	���݂̑I���X�L��
	std::vector<float> skillCoolTime;	//	�X�L���̃N�[���^�C��
	std::vector<int>   skillStock;		//	�X�L���̃X�g�b�N

public:
	Player();
	~Player();

	void Initialize(GameSystemObjects* system, TextureManger* tdata, Sound* sdata, AttackManager* attackManager, int pID, Vector2 screen, float ground, PlayerStatas statas, Vector2 defpos);	//	������
	void Update(float deltaTime);																					//	�X�V
	void Render();																									//	�`��
	void Finalize();																								//	�I��

	void PlayerControll();													//	�v���C���[�̍X�V
	void UseAttack();														//	�U���g�p
	void UseSkill();														//	�X�L���g�p
	void Hited(float atk, float power, float knock, float deg);				//	�U�����󂯂����̏���

	void Reset();															//	�v���C���[���Z�b�g

	void SetRight(bool right);												//	�E�����ʂ��Z�b�g����
	void SetPadNum(int padNum);												//	�Ή�PAD�����߂�
	void SetCondition(PlayerCondition condition);							//	��Ԉُ���Z�b�g����
	void ResetCondition();													//	��Ԉُ탊�Z�b�g
	void SetCantMoveTime(float time);										//	�s���s�\���Ԃ��Z�b�g
	void SetCoolTime(int id, float ct);										//	�N�[���^�C���Z�b�g
	void SetStatas(PlayerStatas p);											//	�X�e�[�^�X�Z�b�g
	void SetPosition(Vector2 pos);											//	�ʒu�ݒ�

	PlayerStatas GetStatas();												//	�X�e�[�^�X��n
	PlayerCondition GetCondition();											//	��Ԏ�n
	Vector2		 GetPosition();												//	���W�ʒu��n
	Vector2		 GetScale();												//	�傫���󂯓n��
	bool		 GetIsRight();												//	�E�����ʂ��ǂ����n��
	int			 GetPadNum();												//	�p�b�h�ԍ���Ԃ�
	int			 GetPID();													//	�v���C���[ID��n

	Score        GetScore();												//	�X�R�A���󂯓n��

	int			 GetNowSkillNum();											//	�X�L���̔ԍ�����n
	std::vector<float> GetSkillCoolTime();									//	�X�L���̃N�[���^�C����n
	std::vector<int>   GetSkillStock();										//	�X�L���̃X�g�b�N���󂯓n��
};

