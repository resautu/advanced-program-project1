#pragma once
#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "Item.h"
#include "Datebase.h"
#include "MainMenu.h"
#include <regex>
#include<time.h>
using namespace std;
class User {
public:
	User();
	User(Usering* us, Ordering* ord, Gooding* go, Reordering* re, Sqling* s) {
		u = us;
		o = ord;
		g = go;
		r = re;
		sq = s;
	}
	void user_menu(User_information* information);
	void user_login();
	void user_information();
	void recharge();
	void user_register();
	void gover_inform();
	void look_information();
	void change_information();
protected:
	Usering* u;
	Ordering* o;
	Gooding* g;
	Reordering* r;
	User_information* inform;
	Sqling* sq;
};

class Buyer :public User {
public:
	void buyer_menu();
	void buy();
	void look_good();
	void look_good_information();
	void search_good();
	void look_order();

};
class Seller :public User {
public:
	void seller_menu();
	void release();
	void look_good();
	void change_information();
	void del_good();
	void look_order();

};
#endif
