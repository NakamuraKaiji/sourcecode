//----------------------------------------------------------------------------------------------------
//	TextureManger
//		テクスチャを一括読み込みする関数
//----------------------------------------------------------------------------------------------------
#pragma once
#include <string>
#include <vector>
#include "../GameScene/Scenes.h"

enum class TitleSceneTexture
{
	Vege1,
	Vege2,
	Vege3,
	Vege4,
	Vege5,
	Vege6,
	Vege7,
	Vege8,
	Vege9,
	Vege10,

	Back,
	Yellow,
	Logo,
	Matto,

	TextureNum
};
enum class ModeSelectSceneTexture
{


	TextureNum
};
enum class CharaSelectSceneTexture
{
	//	アイコン
	IconLettuce,
	IconTomato,
	IconOnion,

	IconBacon,
	IconChicken,
	IconSalmon,
	IconTuna,

	IconBanana,
	IconWhip,

	Back,

	TextureNum
};
enum class GameSceneTexture
{
	//	アイコン
	IconLettuce,
	IconTomato,
	IconOnion,

	IconBacon,
	IconChicken,
	IconSalmon,
	IconTuna,

	IconBanana,
	IconWhip,

	//	スキル
	Lettuce,
	Tomato,
	Onion,

	Bacon,
	Chicken,
	Egg,
	Salmon,
	Tuna,

	Banana,
	Whip,

	Back,
	Player,

	PlayerGuard,
	PlayerBarrier,

	PlayerJump1,
	PlayerJump2,
	PlayerJump3,
	PlayerJump4,

	PlayerDrop1,
	PlayerDrop2,
	PlayerDrop3,

	PlayerStandby1,
	PlayerStandby2,
	PlayerStandby3,
	PlayerStandby4,
	PlayerStandby5,
	PlayerStandby6,
	PlayerStandby7,
	PlayerStandby8,
	PlayerStandby9,
	PlayerStandby10,

	PlayerAttack1,
	PlayerAttack2,
	PlayerAttack3,
	PlayerAttack4,

	TextureNum
};
enum class ResultSceneTexture
{
	Back,
	Player,

	TextureNum
};

class TextureManger
{
private:
	std::vector<int> textureHandle;			//	テクスチャハンドル

public:
	TextureManger();
	~TextureManger();

	void LoadSceneGraph(SceneID sceneID);		//	画像読み込み
	void DeleteSceneGraph();						//	画像消去

	std::vector<int> GetTextureHandle();		//	テクスチャを渡す
	int GetTextureHandle(int num);				//	テクスチャを渡す
};