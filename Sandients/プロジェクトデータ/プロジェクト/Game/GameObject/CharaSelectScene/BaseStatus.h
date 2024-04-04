#pragma once
#include <string>
#include <vector>

using namespace std;

class BaseStatus
{
public:
	int HP;						//ヒットポイント
	int ATK;					//アタック
	int DEF;					//ディフェンス
	int WEI;					//ウェイト
	std::vector<int> SKILLID;
	int CD;						//クールダウン
	int TextureHandle;			//テクスチャ
};