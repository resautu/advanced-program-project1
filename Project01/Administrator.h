#pragma once
#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
using namespace std;
#include<string>
#include<vector>
#include"Item.h"
//#include"User.h"
#include"Datebase.h"
class Admin {
public:
	Admin(Usering* us, Ordering* ord, Gooding* go, Sqling* s) {
		u = us;
		o = ord;
		g = go;
		sq = s;
	}
	void admin_login();
	void admin_menu();
	void look_good();
	void search_good();
	void del_good();
	void look_order();
	void look_user();
	void del_user();
private:
	Usering* u;
	Ordering* o;
	Gooding* g;
	Sqling* sq;
};

#endif
