#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;
struct Good {
	char good_id[5] = { 'M' };
	char name[11];
	double price;
	int number;
	char description[101];
	char seller_id = { 'U' };
	string sell_time;
	string sit;
};
struct Order {
	char order_id[5] = { 'T' };
	char good_id[5] = { 'M' };
	double money;
	int number;
	string deal_time;
	char seller_id = { 'U' };
	char buyer_id = { 'U' };
};
#endif
