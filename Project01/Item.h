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
	char description[101];
	string seller_id;
	string sell_time;
	string sit;
};
struct Order {
	string order_id  ;
	char good_id[5] ;
	double money;
	int number;
	string deal_time;
	string seller_id ;
	string buyer_id ;
};
#endif
