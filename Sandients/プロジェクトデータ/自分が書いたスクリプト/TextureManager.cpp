#include <DxLib.h>
#include "TextureManager.h"

using namespace std;

const vector<string> TITLE_TEXTURE_PATH
{
	"Resources/Textures/Vege1_pumpkin.png",
	"Resources/Textures/Vege2_cabbage.png",
	"Resources/Textures/Vege3_cucumber.png",
	"Resources/Textures/Vege4_radish.png",
	"Resources/Textures/Vege5_tomato.png",
	"Resources/Textures/Vege6_greenbellpepper.png",
	"Resources/Textures/Vege7_pickles.png",
	"Resources/Textures/Vege8_lettuce.png",
	"Resources/Textures/Vege9_onion.png",
	"Resources/Textures/Vege10_carrot.png",
	"Resources/Textures/titleback.png",
	"Resources/Textures/yellow.png",
	"Resources/Textures/logo.png",
	"Resources/Textures/matte.png"




};
const vector<string> MODE_SELECT_TEXTURE_PATH
{
};
const vector<string> CHARA_SELECT_TEXTURE_PATH
{
		"Resources/Textures/CharaSelectScene/Vege/lettuce.png",
		"Resources/Textures/CharaSelectScene/Vege/tomato.png",
		"Resources/Textures/CharaSelectScene/Vege/onion.png",
		"Resources/Textures/CharaSelectScene/Meat/bacon.png",
		"Resources/Textures/CharaSelectScene/Meat/chicken.png",
		"Resources/Textures/CharaSelectScene/Meat/salmon.png",
		"Resources/Textures/CharaSelectScene/Meat/tuna.png",
		"Resources/Textures/CharaSelectScene/Fruit/banana.png",
		"Resources/Textures/CharaSelectScene/Fruit/whip.png",

		"Resources/Textures/CharaSelectScene/background.png"
};
const vector<string> GAME_TEXTURE_PATH
{
		"Resources/Textures/PlayScene/Icons/Vege/lettuce.png",
		"Resources/Textures/PlayScene/Icons/Vege/tomato.png",
		"Resources/Textures/PlayScene/Icons/Vege/onion.png",
		"Resources/Textures/PlayScene/Icons/Meat/pig.png",
		"Resources/Textures/PlayScene/Icons/Meat/chicken.png",
		"Resources/Textures/PlayScene/Icons/Meat/salmon.png",
		"Resources/Textures/PlayScene/Icons/Meat/tuna.png",
		"Resources/Textures/PlayScene/Icons/Fruit/banana.png",
		"Resources/Textures/PlayScene/Icons/Fruit/whip.png",

		"Resources/Textures/PlayScene/Skills/lettuce.png",
		"Resources/Textures/PlayScene/Skills/tomato.png",
		"Resources/Textures/PlayScene/Skills/onion.png",
		"Resources/Textures/PlayScene/Skills/pig.png",
		"Resources/Textures/PlayScene/Skills/chicken.png",
		"Resources/Textures/PlayScene/Skills/chickenegg.png",
		"Resources/Textures/PlayScene/Skills/salmon.png",
		"Resources/Textures/PlayScene/Skills/tuna.png",
		"Resources/Textures/PlayScene/Skills/banana.png",
		"Resources/Textures/PlayScene/Skills/whip.png",

		"Resources/Textures/PlayScene/background.png",
		"Resources/Textures/PlayScene/player.png",

		"Resources/Textures/PlayScene/Player/defense.png",
		"Resources/Textures/PlayScene/Player/barrier.png",

		"Resources/Textures/PlayScene/Player/Jump/jump_1.png",
		"Resources/Textures/PlayScene/Player/Jump/jump_2.png",
		"Resources/Textures/PlayScene/Player/Jump/jump_3.png",
		"Resources/Textures/PlayScene/Player/Jump/jump_4.png",

		"Resources/Textures/PlayScene/Player/Drop/down_1.png",
		"Resources/Textures/PlayScene/Player/Drop/down_2.png",
		"Resources/Textures/PlayScene/Player/Drop/down_3.png",

		"Resources/Textures/PlayScene/Player/Standby/standby_1.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_2.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_3.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_4.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_5.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_6.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_7.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_8.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_9.png",
		"Resources/Textures/PlayScene/Player/Standby/standby_10.png",

		"Resources/Textures/PlayScene/Player/Attack/attack_1.png",
		"Resources/Textures/PlayScene/Player/Attack/attack_2.png",
		"Resources/Textures/PlayScene/Player/Attack/attack_3.png",
		"Resources/Textures/PlayScene/Player/Attack/attack_4.png"
};
const vector<string> RESULT_TEXTURE_PATH
{
	"Resources/Textures/PlayScene/background.png",
	"Resources/Textures/PlayScene/player.png"
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// コンストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
TextureManger::TextureManger()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// デストラクタ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
TextureManger::~TextureManger()
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 画像読み込み
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void TextureManger::LoadSceneGraph(SceneID sceneID)
{
	switch (sceneID)
	{
	case SceneID::Logo:
		break;
	case SceneID::Title:
		for (int i = 0; i < static_cast<int>(TitleSceneTexture::TextureNum); i++)
		{
			textureHandle.push_back(LoadGraph(TITLE_TEXTURE_PATH[i].c_str()));
		}
		break;
	case SceneID::ModeSelect:
		for (int i = 0; i < static_cast<int>(ModeSelectSceneTexture::TextureNum); i++)
		{
			textureHandle.push_back(LoadGraph(TITLE_TEXTURE_PATH[i].c_str()));
		}
		break;
	case SceneID::CharaSelect:
		for (int i = 0; i < static_cast<int>(CharaSelectSceneTexture::TextureNum); i++)
		{
			textureHandle.push_back(LoadGraph(CHARA_SELECT_TEXTURE_PATH[i].c_str()));
		}
		break;
	case SceneID::Play:
		for (int i = 0; i < static_cast<int>(GameSceneTexture::TextureNum); i++)
		{
			textureHandle.push_back(LoadGraph(GAME_TEXTURE_PATH[i].c_str()));
		}
		break;
	case SceneID::Result:
		for (int i = 0; i < static_cast<int>(ResultSceneTexture::TextureNum); i++)
		{
			textureHandle.push_back(LoadGraph(RESULT_TEXTURE_PATH[i].c_str()));
		}
		break;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// 画像解放処理
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
void TextureManger::DeleteSceneGraph()
{
	for (size_t i = 0; i < textureHandle.size(); i++)
	{
		DeleteGraph(textureHandle[i]);
	}
	textureHandle.clear();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// テクスチャデータを渡す
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
std::vector<int> TextureManger::GetTextureHandle()
{
	return textureHandle;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// テクスチャデータを渡す
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
int TextureManger::GetTextureHandle(int num)
{
	return textureHandle[static_cast<int>(num)];
}
