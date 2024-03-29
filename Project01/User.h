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
#include"calculator.h"
#include<map>
#include"Shoppingtrolley.h"
#include"Message.h"
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
		if (inform) {
			st = new Shopttro(inform->user_id);
			prm = new PrMessageStore(inform->user_id);
			mysgs = st->getsgs();
		}
	}
	void user_menu(User_information* information);
	void user_login();
	void user_information();
	void recharge();
	void user_register();
	void gover_inform();
	void look_information();
	void change_information();
	void message_menu();
	void del_message_menu();
	string make_expr();
protected:
	Usering* u;
	Ordering* o;
	Gooding* g;
	Reordering* r;
	User_information* inform;
	Sqling* sq;
	Shopttro* st;
	vector<ShopGood*> mysgs;
	PrMessageStore* prm;
};

class Buyer :public User {
public:
	void buyer_menu();
	bool buy(string _good_id = "-1", int num = -1);
	void look_good();
	void look_good_information();
	void search_good();
	void look_order();
	void TtroBuyMenu();
	void TtroBuyOne();
	void TtroBuyOne(string sg_id);
	void TtroBuyAll();
	void TtroLook();
	void TtroAdd();
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
