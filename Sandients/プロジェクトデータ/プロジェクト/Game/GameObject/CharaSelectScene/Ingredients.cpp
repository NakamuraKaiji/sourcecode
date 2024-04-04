#include "Ingredients.h"

Ingredients::Ingredients(BaseStatus Base, int id)
{
	this->Base = Base;
	this->id = id;
}

Ingredients::~Ingredients()
{
}

int Ingredients::GetId()
{
	return id;
}
int Ingredients::GetHP()
{
	return Base.HP;
}
int Ingredients::GetATK()
{
	return Base.ATK;
}
int Ingredients::GetDEF()
{
	return Base.DEF;
}
int Ingredients::GetWEI()
{
	return Base.WEI;
}

int Ingredients::GetCD()
{
	return Base.CD;
}

int Ingredients::GetTexture()
{
	return Base.TextureHandle;
}


//--------------------------/
//			パン            /
//--------------------------/
Square::Square(BaseStatus Base, int id) :Ingredients(Base, id)
{

}
Mountain::Mountain(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
France::France(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Koppe::Koppe(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Waffle::Waffle(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Tortilla::Tortilla(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Vans::Vans(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Muffin::Muffin(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Bagel::Bagel(BaseStatus Base, int id) : Ingredients(Base, id)
{

}

//--------------------------/
//			野菜            /
//--------------------------/
Lettuce::Lettuce(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Tomato::Tomato(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Takuan::Takuan(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Onion::Onion(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Pepper::Pepper(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Pickles::Pickles(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Cucumber::Cucumber(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Carrot::Carrot(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Squash::Squash(BaseStatus Base, int id) : Ingredients(Base, id)
{

}

//--------------------------/
//		タンパク質          /
//--------------------------/
Ham::Ham(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Chicken::Chicken(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Hamburger::Hamburger(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Scrambled::Scrambled(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Boiled::Boiled(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Sausage::Sausage(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Cheese::Cheese(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Bacon::Bacon(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Tuna::Tuna(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Prawn::Prawn(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Fish::Fish(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Pork::Pork(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Salmon::Salmon(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Roast::Roast(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
//--------------------------/
//		  フルーツ          /
//--------------------------/
Avocado::Avocado(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Strawberry::Strawberry(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Kiwi::Kiwi(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Grape::Grape(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Banana::Banana(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Orange::Orange(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Blueberry::Blueberry(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Pineapple::Pineapple(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Peach::Peach(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
//--------------------------/
//		  　その他          /
//--------------------------/
Yakisoba::Yakisoba(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Whip::Whip(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
PotatoSalad::PotatoSalad(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
KeemaCurry::KeemaCurry(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Gratin::Gratin(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Kimpira::Kimpira(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Bean::Bean(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Chocolate::Chocolate(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
//--------------------------/
//		 ドレッシング       /
//--------------------------/
Mustard::Mustard(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Mayo::Mayo(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Teriyaki::Teriyaki(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Ketchup::Ketchup(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
Demi::Demi(BaseStatus Base, int id) : Ingredients(Base, id)
{

}
