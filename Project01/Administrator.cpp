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
	cin >> s;
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g.goods) {
		if (ele->name.find(s) != string::npos) {
			print_good(ele);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "没有找到关键词相关商品,请重新选择操作" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Admin::del_good() {
	cout << endl << "请输入您想要下架的商品ID： ";
	string i,chos;
	cin >> i;
	cout << endl << endl << "*********************************************************************************" << endl;
	int nfind = 0;
	Good* de=new Good;
	for (auto& ele : g.goods) {
		if (ele->good_id == i) {
			print_good(ele);
			if (ele->sit == "已下架") {
				nfind = 1;
				cout << "该商品已下架，请重新选择操作" << endl;
				break;
			}
			else { nfind = 2; de = ele; break; }
		}
	}
	if (nfind==0) {
		cout << "没有搜索到您想要下架的商品，请重新选择操作" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
	if (nfind == 2) {
		cout << "是否将该商品下架(y/n): ";
		cin >> chos;
		while (!cin || (chos!="y" && chos !="n")) {
			cout << "请按要求输入" << endl;
			cout << "是否将该商品下架(y/n): ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> chos;
		}
		if (chos == "y") {
			de->sit = "已下架";
			cout << "下架成功！" << endl << endl;
		}
		else if (chos == "n") {
			cout << "下架取消，请重新选择您的操作" << endl << endl;
		}
	}
}

void Admin::look_order() {
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " 订单ID " << "   商品ID   " << " 交易单价  " << " 数量  " << "  交易时间   " << " 卖家ID  " << " 买家ID " << endl;
	for (auto& t : o.orders) {
		o.print_order(t);
	}

	cout << "*********************************************************************************" << endl << endl << endl;

}

void Admin::look_user() {
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " 用户ID " << "   用户名   " << "       密码      " << "  联系方式  " << "          地址   " << "   钱包余额  " << " 用户状态 " << endl;
	for (auto& t : u.users) {
		u.print_user(t);
	}

	cout << "*********************************************************************************" << endl << endl << endl;
}
void Admin::del_user() {

}
