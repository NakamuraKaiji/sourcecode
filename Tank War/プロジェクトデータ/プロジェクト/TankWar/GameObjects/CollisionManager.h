//*********************************************************************
//			�T�v	�F�Փ˔���N���X
// 
//			�����	�F11��2��
// 
//			�����	�FKaiji Nakamura
//*********************************************************************
#pragma once
#include "GameObject.h"

class CollisionManager
{
private:
	// �o�^���X�g
	std::vector<GameObject*> m_objects;

public:
	// �R���X�g���N�^
	CollisionManager() = default;

	// �X�V
	void Update();

	// �o�^�֐�
	void AddObject(GameObject* object);
};