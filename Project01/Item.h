#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;
struct Good {
	//char good_id[5] = { 'M' };
	string good_id;
	//char name[11];
	string name;
	double price;
	int number;
	string description;
	string seller_id;
	string sell_time;
	string sit;
};
struct Order {
	string order_id;
	string good_id;
	double money;
	int number;
	string deal_time;
	string seller_id;
	string buyer_id;
};
struct User_information {
	string user_id;        //the lenth is less than 5
	string user_name;
	string key;
	string con;
	string address;
	double balance;
	string sit;
};
struct Reorder {
	string user_id;
	double money;
	string deal_time;
};
#endif
