#pragma once
#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
using namespace std;
#include<string>
#include<vector>
#include"Item.h"
#include"User.h"
class Admin {
public:
	void admin_menu();
	void look_good();
	void search_good();
	void del_good();
	void look_order();
	void look_user();
	void del_user();
private:
	vector<Good*> goods;
	vector<Order*> orders;
	vector<User*> users;
};

#endif
