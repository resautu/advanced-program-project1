#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Datebase.h"
using namespace std;

void Gooding::write_good() {
	fstream f;
	f.open(good_file, ios::out);
	if (!f) { cout << "商品文件输出出现错误，请重启程序尝试" << endl; exit(0); }
	f << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态"<<endl;
	for (auto& ele : goods) {
		f << ele->good_id << ',' << ele->name << ',' << ele->price << ',' << ele->number << ',';
		string s = ele->description;
		replace(s.begin(), s.end(), ',', '`');
		f <<ele->description << ',' << ele->seller_id << ',' << ele->sell_time << ',' << ele->sit << endl;
	}
	f.close();
}

void Usering::write_user() {
	fstream f;
	f.open(user_file, ios::out);
	if (!f) { cout << "用户文件输出出现错误，请重启程序尝试" << endl; exit(0); }
	f << "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态"<<endl;
	for (auto& ele : users) {
		f << ele->user_id << ',' << ele->user_name << ',' << ele->key << ',' << ele->con << ',' << ele->address << ',' << ele->balance << ',' \
			<< ele->sit << endl;
	}
	f.close();
}

void Ordering::write_order() {
	fstream f;
	f.open(order_file, ios::out);
	if (!f) { cout << "订单文件输出出现错误，请重启程序尝试" << endl; exit(0); }
	f << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID"<<endl;
	for (auto& ele : orders) {
		f << ele->order_id << ',' << ele->good_id << ',' << ele->money << ',' << ele->number << ',' << ele->deal_time << ',' << ele->seller_id << ',' \
			<< ele->buyer_id << endl;
	}
	f.close();
}

void Gooding::check_good() {
	
	for (auto& ele : goods) {
		if (ele->number == 0 && ele->sit != "已下架") {
			ele->sit = "已下架";

		}
	}
	write_good();
	
}

void Usering::balance_change(string id, double money) {
	for (auto& ele : users) {
		if (ele->user_id == id) {
			ele->balance = money;
			write_user();
			break;
		}
	}
}

void read_txt() {

}
