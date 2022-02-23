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
	void gover_inform();
	void look_information();
	void change_information();
protected:
	Usering u;
	Ordering o;
	Gooding g;
	User_information* inform;
};

class Buyer :public User {
public:
	//Buyer(User_information* information, Usering& us, Ordering& ord, Gooding& go) {
		//inform = information;
		//u = us;
		//o = ord;
		//g = go;

	//}
	void buyer_menu();
	void buy();
	void look_good();
	void look_good_information();
	void search_good();
	void look_order();

};
class Seller :public User {
public:
	//Seller(User_information* information, Usering& us, Ordering& ord, Gooding& go) {
		//inform = information;
		//u = us;
		//o = ord;
		//g = go;

	//}
	void seller_menu();
	void release();
	void look_good();
	void change_information();
	void del_good();
	void look_order();

};
#endif
