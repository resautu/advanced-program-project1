#pragma once
#ifndef DATEBASE_H
#define DATEBASE_H
//#include "Administrator.h"
//#include"User.h"
#include <vector>
#include "Item.h"
#include <fstream>
#include<iostream>
//#pragma execution_character_set("utf-8")
#include <iomanip>
#include<algorithm>
#include"sundry.h"
//extern string good_file = "D:/proj1/commodity.txt";
//extern string user_file = "D:/proj1/Users.txt";
//extern string order_file = "D:/proj1/Orders.txt";

class Gooding {
	friend class Admin;
	friend class Seller;
	friend class Buyer;
	string good_file = "D:/proj1/commodity.txt";
public:
	Gooding() {
		fstream f;
		f.open(good_file, ios::in);
		string temp, pr, nu;
		if (!f.is_open()) {
			f.open(good_file, ios::trunc);
			if (!f.is_open()) cout << "*********��Ʒ�ļ����س���,����Ҫ������������**********" << endl;
			f.close();
			return;
		}
		f >> temp;
		while (true) {
			pr.clear();
			nu.clear();
			string judge;
			f >> judge;
			if (!f) {
				break;
			}
			Good* t = new Good;
			int i;
			for (i = 0; i < judge.length(); i++) {
				if (judge[i] == ',')break;
				t->good_id.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',')break;
				t->name.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') {
					t->price = exdouble(pr);
					break;
				}
				pr.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') {
					t->number = exint(nu);
					break;
				}
				nu.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') { _replace(t->description, '`', ','); break; }
				t->description.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->seller_id.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->sell_time.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->sit.push_back(judge[i]);
			}
			goods.push_back(t);
		}
		f.close();
	}
	void print_good(Good* t) {

		cout << left << setw(12) << t->good_id << setw(15) << t->name << setw(12) << fixed << setprecision(1) << t->price << setw(15) << t->sell_time << setw(8) << t->number << setw(8) << t->seller_id << setw(8) << t->sit << endl;
	}
	void write_good();
	void check_good();
private:
	vector<Good*> goods;
};

class Usering {
	friend class Admin;
	friend class User;
	//	friend void user_login(Usering& us, Ordering& ord, Gooding& go);
public:
	Usering() {
		fstream f;
		f.open(user_file, ios::in);
		if (!f.is_open()) {
			f.open(user_file, ios::out);
			if (!f.is_open()) cout << "*********�û��ļ����س�������Ҫ������������**********" << endl;
			f.close();
			return;
		}
		string judge, ba;
		f >> judge;
		while (true) {
			ba.clear();
			f >> judge;
			if (!f) {
				break;
			}
			User_information* t = new User_information;
			int i;
			for (i = 0; i < judge.length(); i++) {
				if (judge[i] == ',')break;
				t->user_id.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',')break;
				t->user_name.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->key.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->con.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->address.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') {
					t->balance = exdouble(ba);
					break;
				}
				ba.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->sit.push_back(judge[i]);
			}
			users.push_back(t);
		}
		f.close();
	}
	void print_user(User_information* us) {
		cout << setw(6) << us->user_id << setw(10) << us->user_name << setw(15) << us->key \
			<< setw(15) << us->con << setw(20) << us->address << setw(10) << fixed << setprecision(1) << us->balance << setw(10) << us->sit << endl;
	}
	void write_user();
	void balance_change(string id, double money);
private:
	vector< User_information* > users;
	string user_file = "D:/proj1/user.txt";
};

class Ordering {
public:
	friend class Admin;
	friend class Seller;
	friend class Buyer;
	Ordering() {
		fstream f;
		f.open(order_file, ios::in);
		if (!f.is_open()) {
			f.open(order_file, ios::out);
			if (!f.is_open()) cout << "*********�����ļ����س�������Ҫ������������**********" << endl;
			f.close();
			return;
		}
		string temp, pr, nu;
		f >> temp;
		while (true) {
			pr.clear();
			nu.clear();
			string judge;
			f >> judge;
			if (!f) {
				break;
			}
			Order* t = new Order;
			int i;
			for (i = 0; i < judge.length(); i++) {
				if (judge[i] == ',')break;
				t->order_id.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',')break;
				t->good_id.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') {
					t->money = exdouble(pr);
					break;
				}
				pr.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') {
					t->number = exint(nu);
					break;
				}
				nu.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->deal_time.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->seller_id.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->buyer_id.push_back(judge[i]);
			}
			orders.push_back(t);
		}
		f.close();
	}
	void print_order(Order* paper) {
		cout << setw(6) << paper->order_id << setw(10) << paper->good_id << setw(11) << fixed << setprecision(1) << paper->money \
			<< setw(8) << paper->number << setw(14) << paper->deal_time << setw(8) << paper->seller_id << setw(9) << paper->buyer_id << endl;
	}
	void write_order();
private:
	vector<Order*> orders;
	string order_file = "D:/proj1/order.txt";
};

void read_txt();
void user_login(Usering& us, Ordering& ord, Gooding& go);
#endif
