//----------------------------------------------------------------------------------------------------
//	LogoScene
//		���S��`�悳����V�[��
// 
//----------------------------------------------------------------------------------------------------
#pragma once
#include "../GameScene/Scenes.h"
#include "../GameScene/BaseScene.h"
#include <vector>

class LogoScene : public BaseScene
{
private:
	float fadeCount;					//	�t�F�[�h�p�J�E���^
	float timeCount;					//	���ԃJ�E���g


	std::vector<int> logoGraph;			//	���S�摜�p�n���h��
	std::vector<int> logoSound;			//	���S�����p�n���h��
	int logoDrawNum;					//	���S�\���񐔃J�E���^

public:
	LogoScene();
	~LogoScene();

	void Initialize()	override;   //	������
	void Update()       override;   //	�X�V
	void Render()       override;   //	�`��
	void Finalize()     override;	//	�I��

	void LogoUpdate();				//	���S�̍X�V����
	void LogoDraw(int graph);		//	���S�̕`�揈��
};
