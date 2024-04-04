#pragma once
#include "BaseStatus.h"

class Ingredients
{
protected:

	BaseStatus Base;
	int id;

public:
	Ingredients(BaseStatus Base, int id);
	~Ingredients();

	int GetId();
	int GetHP();
	int GetATK();
	int GetDEF();
	int GetWEI();
	int GetCD();
	int GetTexture();

};


//パン
class Square :public Ingredients
{
public:
	Square(BaseStatus Base, int id);
	~Square();



};

class Mountain :public Ingredients
{
public:
	Mountain(BaseStatus Base, int id);
	~Mountain();


};

class France :public Ingredients
{
public:
	France(BaseStatus Base, int id);
	~France();

};

class Koppe :public Ingredients
{
public:
	Koppe(BaseStatus Base, int id);
	~Koppe();


};

class Waffle :public Ingredients
{
public:
	Waffle(BaseStatus Base, int id);
	~Waffle();

};

class Tortilla :public Ingredients
{
public:
	Tortilla(BaseStatus Base, int id);
	~Tortilla();


};

class Vans :public Ingredients
{
public:
	Vans(BaseStatus Base, int id);
	~Vans();

};

class Muffin :public Ingredients
{
public:
	Muffin(BaseStatus Base, int id);
	~Muffin();


};

class Bagel :public Ingredients
{
public:
	Bagel(BaseStatus Base, int id);
	~Bagel();


};

//野菜
class Lettuce :public Ingredients
{
public:
	Lettuce(BaseStatus Base, int id);
	~Lettuce();



};

class Tomato :public Ingredients
{
public:
	Tomato(BaseStatus Base, int id);
	~Tomato();


};

class Takuan :public Ingredients
{
public:
	Takuan(BaseStatus Base, int id);
	~Takuan();

};

class Onion :public Ingredients
{
public:
	Onion(BaseStatus Base, int id);
	~Onion();



};

class Pepper :public Ingredients
{
public:
	Pepper(BaseStatus Base, int id);
	~Pepper();


};

class Pickles :public Ingredients
{
public:
	Pickles(BaseStatus Base, int id);
	~Pickles();


};

class Cucumber :public Ingredients
{
public:
	Cucumber(BaseStatus Base, int id);
	~Cucumber();



};

class Carrot :public Ingredients
{
public:
	Carrot(BaseStatus Base, int id);
	~Carrot();



};

class Squash :public Ingredients
{
public:
	Squash(BaseStatus Base, int id);
	~Squash();



};
//タンパク質
class Ham :public Ingredients
{
public:
	Ham(BaseStatus Base, int id);
	~Ham();


};

class Chicken :public Ingredients
{
public:
	Chicken(BaseStatus Base, int id);
	~Chicken();


};

class Hamburger :public Ingredients
{
public:
	Hamburger(BaseStatus Base, int id);
	~Hamburger();


};

class Scrambled :public Ingredients
{
public:
	Scrambled(BaseStatus Base, int id);
	~Scrambled();

};

class Boiled :public Ingredients
{
public:
	Boiled(BaseStatus Base, int id);
	~Boiled();

};

class Sausage :public Ingredients
{
public:
	Sausage(BaseStatus Base, int id);
	~Sausage();


};

class Cheese :public Ingredients
{
public:
	Cheese(BaseStatus Base, int id);
	~Cheese();


};

class Bacon :public Ingredients
{
public:
	Bacon(BaseStatus Base, int id);
	~Bacon();


};

class Tuna :public Ingredients
{
public:
	Tuna(BaseStatus Base, int id);
	~Tuna();


};

class Prawn :public Ingredients
{
public:
	Prawn(BaseStatus Base, int id);
	~Prawn();


};

class Fish :public Ingredients
{
public:
	Fish(BaseStatus Base, int id);
	~Fish();


};

class Pork :public Ingredients
{
public:
	Pork(BaseStatus Base, int id);
	~Pork();


};

class Salmon :public Ingredients
{
public:
	Salmon(BaseStatus Base, int id);
	~Salmon();


};

class Roast :public Ingredients
{
public:
	Roast(BaseStatus Base, int id);
	~Roast();


};

//フルーツ
class Avocado :public Ingredients
{
public:
	Avocado(BaseStatus Base, int id);
	~Avocado();

};

class Strawberry :public Ingredients
{
public:
	Strawberry(BaseStatus Base, int id);
	~Strawberry();


};

class Kiwi :public Ingredients
{
public:
	Kiwi(BaseStatus Base, int id);
	~Kiwi();


};

class Grape :public Ingredients
{
public:
	Grape(BaseStatus Base, int id);
	~Grape();


};

class Banana :public Ingredients
{
public:
	Banana(BaseStatus Base, int id);
	~Banana();


};

class Orange :public Ingredients
{
public:
	Orange(BaseStatus Base, int id);
	~Orange();


};

class Blueberry :public Ingredients
{
public:
	Blueberry(BaseStatus Base, int id);
	~Blueberry();


};

class Pineapple :public Ingredients
{
public:
	Pineapple(BaseStatus Base, int id);
	~Pineapple();

};

class Peach :public Ingredients
{
public:
	Peach(BaseStatus Base, int id);
	~Peach();


};

//その他
class Yakisoba :public Ingredients
{
public:
	Yakisoba(BaseStatus Base, int id);
	~Yakisoba();

};

class Whip :public Ingredients
{
public:
	Whip(BaseStatus Base, int id);
	~Whip();


};

class PotatoSalad :public Ingredients
{
public:
	PotatoSalad(BaseStatus Base, int id);
	~PotatoSalad();

};
class KeemaCurry :public Ingredients
{
public:
	KeemaCurry(BaseStatus Base, int id);
	~KeemaCurry();

};

class Gratin :public Ingredients
{
public:
	Gratin(BaseStatus Base, int id);
	~Gratin();

};

class Kimpira :public Ingredients
{
public:
	Kimpira(BaseStatus Base, int id);
	~Kimpira();

};

class Bean :public Ingredients
{
public:
	Bean(BaseStatus Base, int id);
	~Bean();

};

class Chocolate :public Ingredients
{
public:
	Chocolate(BaseStatus Base, int id);
	~Chocolate();

};

//ドレッシング
class Mustard :public Ingredients
{
public:
	Mustard(BaseStatus Base, int id);
	~Mustard();


};

class Mayo :public Ingredients
{
public:
	Mayo(BaseStatus Base, int id);
	~Mayo();


};

class Teriyaki :public Ingredients
{
public:
	Teriyaki(BaseStatus Base, int id);
	~Teriyaki();

};

class Ketchup :public Ingredients
{
public:
	Ketchup(BaseStatus Base, int id);
	~Ketchup();

};

class Demi :public Ingredients
{
public:

	Demi(BaseStatus Base, int id);
	~Demi();

};
