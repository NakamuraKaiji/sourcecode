#pragma once
#include "../Attack.h"

class SkillFruitBanana : public Attack
{
private:

public:
	SkillFruitBanana();
	~SkillFruitBanana();

	void Initialize()				override;	//	初期化
	void Update(float deltaTIme)	override;	//	更新
	void Render()					override;	//	描画
	void Finalize()					override;	//	終了
	void HitPlayerCheck()			override;	//	当たりプレイヤー判定
	void HitAttackCheck()			override;	//	当たり攻撃判定
	void Hited()					override;	//	衝突時
};
