//----------------------------------------------------------------------------------------------------
//	FontHandle
//		Dxlib�ň����t�H���g����̃N���X 
// 
//----------------------------------------------------------------------------------------------------
#pragma once
#include <vector>

enum class FontID	    //	�t�H���gID
{
	MainFont = 0,				    //	���C���t�H���g
	BigMainFont = 1,		        //	�傫���o�[�W����
	SuperBigMainFont = 2,	        //	���傫���o�[�W����
	SuperBigEdgeMainFont = 3,
	SuperUltraBigEdgeMainFont = 4,
	EdgeMainFont = 5,

	FontNum			                //	�t�H���g�n���h���̐�
};

struct Font				            //	�t�H���g�n���h��
{
	int size;			            //	�t�H���g�̑傫��
	int thick;			            //	�t�H���g�̌���
	int type;			            //	�t�H���g�̌`��
};

struct FontResources	            //	�t�H���g�̃f�[�^
{
	const char* path;	            //	�t�H���g�̃p�X
	const char* name;	            //	�t�H���g�̖��O
};

class FontHandle
{
private:
	std::vector<FontResources> fontData;		//	�t�H���g�̃f�[�^
	std::vector<int>      fontHandle;	//	�t�H���g�n���h��

public:
	FontHandle();
	~FontHandle();

	void Initialize();	            //	����������
	void Finalize();	            //	�������
	int GetFontHandle(FontID fontID);	//	�t�H���g�n���h����n��
};
