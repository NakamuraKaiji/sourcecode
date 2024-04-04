//----------------------------------------------------------------------------------------------------
//	FontHandle
//		Dxlibで扱うフォント周りのクラス 
// 
//----------------------------------------------------------------------------------------------------
#pragma once
#include <vector>

enum class FontID	    //	フォントID
{
	MainFont = 0,				    //	メインフォント
	BigMainFont = 1,		        //	大きいバージョン
	SuperBigMainFont = 2,	        //	超大きいバージョン
	SuperBigEdgeMainFont = 3,
	SuperUltraBigEdgeMainFont = 4,
	EdgeMainFont = 5,

	FontNum			                //	フォントハンドルの数
};

struct Font				            //	フォントハンドル
{
	int size;			            //	フォントの大きさ
	int thick;			            //	フォントの厚さ
	int type;			            //	フォントの形式
};

struct FontResources	            //	フォントのデータ
{
	const char* path;	            //	フォントのパス
	const char* name;	            //	フォントの名前
};

class FontHandle
{
private:
	std::vector<FontResources> fontData;		//	フォントのデータ
	std::vector<int>      fontHandle;	//	フォントハンドル

public:
	FontHandle();
	~FontHandle();

	void Initialize();	            //	初期化処理
	void Finalize();	            //	解放処理
	int GetFontHandle(FontID fontID);	//	フォントハンドルを渡す
};
