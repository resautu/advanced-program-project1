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
extern string good_file;
extern string user_file;
extern string order_file;
extern string reorder_file;
extern string sql_file;
extern string good_file_name;
extern string user_file_name;
extern string order_file_name;

class Gooding {
	friend class Admin;
	friend class Seller;
	friend class Buyer;
public:
	Gooding() {
		fstream f;
		f.open(good_file, ios::in);
		string temp, pr, nu;
		if (!f.is_open()) {
			f.open(good_file, ios::out);
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
		cout << left << setw(8) << us->user_id << setw(18) << us->user_name << setw(15) << us->key \
			<< setw(15) << us->con << setw(20) << us->address << setw(10) << fixed << setprecision(1) << us->balance << setw(6) << us->sit << endl;
	}
	void write_user();
	void balance_change(string id, double money);
private:
	vector< User_information* > users;
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
		cout << setw(8) << paper->order_id << setw(8) << paper->good_id << setw(11) << fixed << setprecision(1) << paper->money \
			<< setw(8) << paper->number << setw(14) << paper->deal_time << setw(8) << paper->seller_id << setw(9) << paper->buyer_id << endl;
	}
	void write_order();
private:
	vector<Order*> orders;
};

class Reordering {
	friend class User;
public:
	Reordering() {
		fstream f;
		f.open(reorder_file, ios::in);
		if (!f.is_open()) {
			f.open(order_file, ios::out);
			if (!f.is_open()) cout << "*********��ֵ��¼�ļ����س�������Ҫ������������**********" << endl;
			f.close();
			return;
		}
		string temp, pr;
		f >> temp;
		while (true) {
			pr.clear();
			string judge;
			f >> judge;
			if (!f) {
				break;
			}
			Reorder* t = new Reorder;
			int i;
			for (i = 0; i < judge.length(); i++) {
				if (judge[i] == ',')break;
				t->user_id.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') {
					t->money = exdouble(pr);
					break;
				}
				pr.push_back(judge[i]);
			}
			for (i += 1; i < judge.length(); i++) {
				if (judge[i] == ',') break;
				t->deal_time.push_back(judge[i]);
			}
			reorders.push_back(t);
		}
		f.close();
	}
	void write_reorder();
private:
	vector<Reorder*> reorders;
};

class Sqling {
public:
	Sqling() {
		fstream f;
		f.open(sql_file, ios::in);
		char temp[200];
		string s;
		if (!f.is_open()) {
			f.open(sql_file, ios::out);
			if (!f.is_open()) cout << "*********sqlָ���ļ����س���,����Ҫ������������**********" << endl;
			f.close();
			return;
		}
		f.getline(temp, 200);
		while (true) {
			if (strlen(temp) == 0) break;
			s = temp;
			sqls.push_back(s);
			f.getline(temp, 200);
		}
	}
	void Select(string file_name, bool complex = false, string col_name = "0", string _name = "0") {
		string s = "SELECT * FROM ";
		s.append(file_name);
		if (complex) {
			s.append(" WHERE " + col_name + " CONTAINS " + _name);
		}
		write_sql(s);
	}
	void Insert(string file_name, string val1 = "-1", string val2 = "-1", string val3 = "-1", string val4 = "-1", string val5 = "-1", string val6 = "-1", string val7 = "-1", string val8 = "-1") {
		string s = "INSERT INTO ";
		s.append(file_name + " VALUES (");
		if (val1 != "-1") s.append(val1);
		if (val2 != "-1") s.append("," + val2);
		if (val3 != "-1") s.append("," + val3);
		if (val4 != "-1") s.append("," + val4);
		if (val5 != "-1") s.append("," + val5);
		if (val6 != "-1") s.append("," + val6);
		if (val7 != "-1") s.append("," + val7);
		if (val8 != "-1") s.append("," + val8);
		s.append(")");
		write_sql(s);
	}
	void Update(string file_name, string lim, string val1 = "-1", string val2 = "-1", string val3 = "-1", string val4 = "-1", string val5 = "-1") {
		string s;
		s.append("UPDATE " + file_name + " SET " + val1);
		if (val2 != "-1") s.append(", " + val2);
		if (val3 != "-1") s.append(", " + val3);
		if (val4 != "-1") s.append(", " + val4);
		if (val5 != "-1") s.append(", " + val5);
		s.append(" WHERE " + lim);
		write_sql(s);
	}
private:
	void write_sql(string s);
	vector<string> sqls;
};

#endif
