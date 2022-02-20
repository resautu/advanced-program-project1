#pragma once
#ifndef DATEBASE_H
#define DATEBASE_H
//#include "Administrator.h"
#include"User.h"
#include <vector>
//#include "Item.h"
#include <fstream>
#include<iostream>
#include <iomanip>
//extern string good_file = "D:/proj1/commodity.txt";
//extern string user_file = "D:/proj1/Users.txt";
//extern string order_file = "D:/proj1/Orders.txt";
class Gooding {
	friend class Admin;
	friend class User;
	string good_file = "D:/proj1/commodity.txt";
public:
	Gooding() {
		fstream f;
		f.open(good_file, ios::in);
		if (!f.is_open()) {
			f.open(good_file, ios::trunc);
			if (!f.is_open()) cout << "*********商品文件加载出错,如需要请重启程序尝试**********" << endl;
			f.close();
			return;
		}
		while (true) {
			string judge;
			f >> judge;
			if (!f) {
				break;
			}
			Good* t = new Good;
			t->good_id = judge;

			f >> t->name >> t->price >> t->number >> t->description >> t->seller_id >> t->sell_time >> t->sit;
			goods.push_back(t);
		}
		f.close();
	}
private:
	vector<Good*> goods;
};
class Usering {
	friend class Admin;
public:
	Usering() {
		fstream f;
		f.open(user_file, ios::in);
		if (!f.is_open()) {
			f.open(user_file, ios::out);
			if (!f.is_open()) cout << "*********用户文件加载出错，如需要请重启程序尝试**********" << endl;
			f.close();
			return;
		}
		while (true) {
			string judge;
			f >> judge;
			if (!f) {
				break;
			}
			User_information* t = new User_information;
			t->user_id = judge;

			f >> t->user_name >> t->key >> t->con >> t->address >> t->balance >> t->sit;
			users.push_back(t);
		}
		f.close();
	}
	void print_user(User_information* us) {
		cout << setw(6) << us->user_id << setw(10) << us->user_name << setw(15) << us->key \
			<< setw(15) << us->con << setw(20) << us->address << setw(10) << fixed << setprecision(1)<< us->balance << setw(10) << us->sit << endl;
	}
private:
	vector< User_information*> users;
	string user_file = "D:/proj1/user.txt";
};
class Ordering {
public:
	friend class Admin;
	friend class User;
	Ordering() {
		fstream f;
		f.open(order_file, ios::in);
		if (!f.is_open()) {
			f.open(order_file, ios::out);
			if (!f.is_open()) cout << "*********订单文件加载出错，如需要请重启程序尝试**********" << endl;
			f.close();
			return;
		}
		while (true) {
			string judge;
			f >> judge;
			if (!f) {
				break;
			}
			Order* t = new Order;
			t->order_id = judge;

			f >> t->good_id >> t->money >> t->number >> t->deal_time >> t->seller_id>> t->buyer_id;
			orders.push_back(t);
		}
		f.close();
	}
	void print_order(Order* paper) {
		cout <<setw(6)<< paper->order_id << setw(10)<<paper->good_id << setw(11) << fixed << setprecision(1) << paper->money \
			<< setw(8) << paper->number << setw(14) << paper->deal_time << setw(8) << paper->seller_id << setw(9) << paper->buyer_id << endl;
	}
private:
	vector<Order*> orders;
	string order_file = "D:/proj1/order.txt";
};
#endif
