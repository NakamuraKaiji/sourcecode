#pragma once

#include "../../../ExtendLib/GameSystemObject/GameSystemObjects.h"
#include "Ingredients.h"
class BreadSelect
{
private:
	int BreadTextures[9];

	bool B_flg[2];						//パン決定フラグ

	GameSystemObjects* system;

	Ingredients* Bread[9];			//パンのクラスのまとめ 
	BaseStatus SBread[9];			//パンのステータス保存用
	int bread_Id[2];					//パンのID保存

	float Chara_Cooltime[2];
public:
	BreadSelect();
	~BreadSelect();

	void Initialize(GameSystemObjects* system);									//初期化
	void Update(float deltatime);		                                        //更新
	void Render();		                                                        //描画
	void Finalize();															//終了

	int GetFlg(int id);															//選択フラグを戻す
};