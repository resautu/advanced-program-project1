#pragma once
#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "Item.h"
#include "Datebase.h"
#include "MainMenu.h"
using namespace std;
class User {
public:
	User();
	User(Usering& us, Ordering& ord, Gooding& go) {
		u = us;
		o = ord;
		g = go;
	}
	void user_menu(User_information* information);
	void user_login();
	void user_information();
	void recharge();
	void user_register();
protected:
	Usering u;
	Ordering o;
	Gooding g;
	User_information* inform;
};

class Buyer :public User {
public:
	Buyer(User_information* information, Usering& us, Ordering& ord, Gooding& go) {
		inform = information;
		u = us;
		o = ord;
		g = go;

	}
	void buyer_menu();
	void buy();
	void look_good();
	void look_menu();
	void search_good();
	

};
class Seller :public User {
public:
	Seller(User_information* information, Usering& us, Ordering& ord, Gooding& go) {
		inform = information;
		u = us;
		o = ord;
		g = go;

	}
	void seller_menu();
	void release();
	void look_good();
	void change_information();
	void del_good();
	void look_order();

};

bool cevalid(wstring& s);

bool nevalid(string& s);

bool nvalid(string& s);
#endif
