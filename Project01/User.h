#pragma once
#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "Item.h"
#include "MainMenu.h"

using namespace std;
struct User_information {
	string user_id;        //the lenth is less than 5
	string user_name;
	string key;
	string con;
	string address;
	double balance;
	string sit;
};
class User {
	string user_id ;        //the lenth is less than 5
	char user_name[11];
	char key[21];
	string con;
	string address;
	double balance;
	string sit;
public:
	void user_menu();
	void user_login();
	void user_information();
	void recharge();
	void user_register(){}
};
class Buyer :public User {
public:
	void buyer_menu();
	void buy();
	void look_good();
	void look_menu();
	void search_good();
	

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
