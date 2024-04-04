//----------------------------------------------------------------------------------------------------
//	FontHandle
//		Dxlibで扱うフォント周りのクラス 
// 
//----------------------------------------------------------------------------------------------------
#include <DxLib.h>
#include "FontHandle.h"

const Font DEF_FONT   = { 30,7,DX_FONTTYPE_ANTIALIASING_4X4 };							//	基礎フォント
const Font DEF_BIG_FONT = { 40,7,DX_FONTTYPE_ANTIALIASING_EDGE_4X4 };					//	大きい基礎フォント
const Font DEF_SUPERBIG_FONT = { 60,7,DX_FONTTYPE_ANTIALIASING_4X4 };					//	超大きい基礎フォント
const Font DEF_SUPERBIGEDGE_FONT = { 70,7,DX_FONTTYPE_ANTIALIASING_EDGE_4X4 };			//	超大きい基礎フォント
const Font DEF_SUPERULTRABIGEDGE_FONT = { 120,7,DX_FONTTYPE_ANTIALIASING_EDGE_4X4 };	//	超特大きい基礎フォント
const Font EDGE_FONT = { 30,7,DX_FONTTYPE_ANTIALIASING_EDGE_4X4 };						//	超大きい基礎フォント

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// コンストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
FontHandle::FontHandle()
{
	//fontData.push_back(FontResources{ "Resources/Fonts/HGRPP1.TTC", "KyouryunoGuratan" });
	fontData.push_back(FontResources{ "Resources/Fonts/HGRPP1.TTC", "HG創英角ポップ体" });

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// デストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
FontHandle::~FontHandle()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 初期化処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void FontHandle::Initialize()
{
	//	フォントの数ループ
	for (size_t i = 0; i < fontData.size(); i++)
	{
		//	PCにフォントをインストールする
		if (AddFontResourceEx(fontData[i].path, FR_PRIVATE, NULL) > 0) {
		}
		else {
			// フォント読込エラー処理
			MessageBox(NULL, "フォント読込失敗", "", MB_OK);
			//printfDx("font読み込みエラー\n");
		}
	}

	//	フォント設定
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_FONT.size, DEF_FONT.thick, DEF_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_BIG_FONT.size, DEF_BIG_FONT.thick, DEF_BIG_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_SUPERBIG_FONT.size, DEF_SUPERBIG_FONT.thick, DEF_SUPERBIG_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_SUPERBIGEDGE_FONT.size, DEF_SUPERBIGEDGE_FONT.thick, DEF_SUPERBIGEDGE_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, DEF_SUPERULTRABIGEDGE_FONT.size, DEF_SUPERULTRABIGEDGE_FONT.thick, DEF_SUPERULTRABIGEDGE_FONT.type));
	fontHandle.push_back(CreateFontToHandle(fontData[0].name, EDGE_FONT.size, EDGE_FONT.thick, EDGE_FONT.type));
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 解放処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void FontHandle::Finalize()
{
	//	全フォントハンドルを消去
	InitFontToHandle();
	fontHandle.clear();

	//	フォントの数ループ
	for (size_t i = 0; i < fontData.size(); i++)
	{
		//	PCにインストールしたフォントを削除する
		if (RemoveFontResourceEx(fontData[i].path, FR_PRIVATE, NULL)) {
		}
		else {
			MessageBox(NULL, "remove failure", "", MB_OK);
			//printfDx("font消去エラー\n");
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// フォントハンドルを渡す
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int FontHandle::GetFontHandle(FontID font)
{
	return fontHandle[static_cast<int>(font)];
}