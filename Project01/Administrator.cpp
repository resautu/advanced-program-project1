#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"Administrator.h"
#include <fstream>
#include <iomanip>
using namespace std;
void Admin :: admin_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! admin" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1、查看所有商品 2、搜索商品 3、下架商品 4、查看所有订单 5、查看所有用户 6、封禁用户 7、注销  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "请输入操作序号: ";
		int i;
		cin >> i;
		while (!cin) {
			cout << "请输入正确的数字" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (i) {
		case 1:look_good(); break;
		case 2:search_good(); break;
		case 3:del_good(); break;
		case 4:look_order(); break;
		case 5:look_user(); break;
		case 6:del_user(); break;
		case 7:return; break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}
void Admin :: print_good(Good* t) {
	cout << left << t->good_id << "  " << t->name << "  " << fixed << setprecision(1) << t->price << "  " << setw(10) << t->sell_time << "     " << t->number << "        " << t->seller_id << "   " << t->sit << "  " << t->description << endl;
}
void Admin::look_good() {
	cout <<endl<<endl<< "*********************************************************************************" << endl;
	cout << " ID " << "   名称   " << " 价格  " << " 上架时间  " << " 库存数量  " << " 卖家ID  " << " 商品状态 " << "  描 述   " << endl;
	for(auto &t : g.goods) {
		print_good(t);
	}
	
	cout << "*********************************************************************************" << endl << endl << endl;

}

void Admin::search_good() {
	string s;
	cout << "请输入您想要查找的商品： ";

}

void Admin::del_good() {

}

void Admin::look_order() {

}

void Admin::look_user() {

}
void Admin::del_user() {

}
