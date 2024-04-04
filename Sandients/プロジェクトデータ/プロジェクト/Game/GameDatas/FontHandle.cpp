//----------------------------------------------------------------------------------------------------
//	FontHandle
//		Dxlib�ň����t�H���g����̃N���X 
// 
//----------------------------------------------------------------------------------------------------
#include <DxLib.h>
#include "FontHandle.h"

const Font DEF_FONT   = { 30,7,DX_FONTTYPE_ANTIALIASING_4X4 };							//	��b�t�H���g
const Font DEF_BIG_FONT = { 40,7,DX_FONTTYPE_ANTIALIASING_EDGE_4X4 };					//	�傫����b�t�H���g
const Font DEF_SUPERBIG_FONT = { 60,7,DX_FONTTYPE_ANTIALIASING_4X4 };					//	���傫����b�t�H���g
const Font DEF_SUPERBIGEDGE_FONT = { 70,7,DX_FONTTYPE_ANTIALIASING_EDGE_4X4 };			//	���傫����b�t�H���g
const Font DEF_SUPERULTRABIGEDGE_FONT = { 120,7,DX_FONTTYPE_ANTIALIASING_EDGE_4X4 };	//	�����傫����b�t�H���g
const Font EDGE_FONT = { 30,7,DX_FONTTYPE_ANTIALIASING_EDGE_4X4 };						//	���傫����b�t�H���g

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �R���X�g���N�^
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
FontHandle::FontHandle()
{
	//fontData.push_back(FontResources{ "Resources/Fonts/HGRPP1.TTC", "KyouryunoGuratan" });
	fontData.push_back(FontResources{ "Resources/Fonts/HGRPP1.TTC", "HG�n�p�p�|�b�v��" });

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �f�X�g���N�^
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
FontHandle::~FontHandle()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// ����������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void FontHandle::Initialize()
{
	//	�t�H���g�̐����[�v
	for (size_t i = 0; i < fontData.size(); i++)
	{
		//	PC�Ƀt�H���g���C���X�g�[������
		if (AddFontResourceEx(fontData[i].path, FR_PRIVATE, NULL) > 0) {
		}
		else {
			// �t�H���g�Ǎ��G���[����
			MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
			//printfDx("font�ǂݍ��݃G���[\n");
		}
	}

	//	�t�H���g�ݒ�
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_FONT.size, DEF_FONT.thick, DEF_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_BIG_FONT.size, DEF_BIG_FONT.thick, DEF_BIG_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_SUPERBIG_FONT.size, DEF_SUPERBIG_FONT.thick, DEF_SUPERBIG_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_SUPERBIGEDGE_FONT.size, DEF_SUPERBIGEDGE_FONT.thick, DEF_SUPERBIGEDGE_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_SUPERULTRABIGEDGE_FONT.size, DEF_SUPERULTRABIGEDGE_FONT.thick, DEF_SUPERULTRABIGEDGE_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, EDGE_FONT.size, EDGE_FONT.thick, EDGE_FONT.type));
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �������
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void FontHandle::Finalize()
{
	//	�S�t�H���g�n���h��������
	InitFontToHandle();
	fontHandle.clear();

	//	�t�H���g�̐����[�v
	for (size_t i = 0; i < fontData.size(); i++)
	{
		//	PC�ɃC���X�g�[�������t�H���g���폜����
		if (RemoveFontResourceEx(fontData[i].path, FR_PRIVATE, NULL)) {
		}
		else {
			MessageBox(NULL, "remove failure", "", MB_OK);
			//printfDx("font�����G���[\n");
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// �t�H���g�n���h����n��
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int FontHandle::GetFontHandle(FontID font)
{
	return fontHandle[static_cast<int>(font)];
}