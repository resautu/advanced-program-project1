#pragma once
#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "Item.h"
#include "MainMenu.h"
using namespace std;
class User {
	char user_id[5] = { 'U' };
	char user_name[11];
	char key[21];
	string con;
	string address;
	double balance;
public:
	void user_login();
	void user_information();
	void recharge();
};
class Buyer :public User {
public:
	void buyer_menu();
	void buy();
	void look_good();
	void look_menu();
	void search_good();
	
private:
	vector<Good> goods;
	vector<Order> orders;
};
class Seller :public User {
public:
	void seller_menu();
	void release();
	void look_good();
	void change_information();
	void del_good();
	void look_order();
private:
	vector<Good> goods;
	vector<Order> orders;
};
void user_register(){}
#endif
