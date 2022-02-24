#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"Administrator.h"
#include <fstream>
#include <iomanip>
using namespace std;

void Admin::admin_login() {
	system("cls");
	string name, key;
	cout << "请输入管理员姓名: ";
	cin >> name;
	cout << "请输入密码: ";
	cin >> key;
	if (name != "admin" || key != "123456") {
		system("cls");
		cout << endl << endl << "------用户名或密码错误，即将返回主菜单------" << endl << endl << endl;
		return;
	}
	cout << endl << endl << "------登录成功，欢迎您------" << endl << endl;
	admin_menu();
}

void Admin::admin_menu() {
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

void Admin::look_good() {
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "商品ID " << "       名称   " << "       价格  " << "     上架时间  " << " 库存数量  " << "卖家ID  " << "商品状态 " << endl;
	for (auto& t : g.goods) {
		g.print_good(t);
	}

	cout << "*********************************************************************************" << endl << endl << endl;

}

void Admin::search_good() {
	string s;
	cout << "请输入您想要查找的商品： ";
	cin >> s;
	while (!cin) {
		cout << "请输入正确的商品ID" << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> s;
	}
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g.goods) {
		if (ele->name.find(s) != string::npos) {
			g.print_good(ele);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "没有找到关键词相关商品,请重新选择操作" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Admin::del_good() {                               //this function should write the document
	cout << endl << "请输入您想要下架的商品ID： ";
	string i, chos;
	cin >> i;
	cout << endl << endl << "*********************************************************************************" << endl;
	int nfind = 0;
	Good* de = new Good;
	for (auto& ele : g.goods) {
		if (ele->good_id == i) {
			cout << " ID " << "   名称   " << " 价格  " << " 上架时间  " << " 库存数量  " << " 卖家ID  " << " 商品状态 " << "  描 述   " << endl;
			g.print_good(ele);
			if (ele->sit == "已下架") {
				nfind = 1;
				cout << "该商品已下架，请重新选择操作" << endl;
				break;
			}
			else { nfind = 2; de = ele; break; }
		}
	}
	if (nfind == 0) {
		cout << "没有搜索到您想要下架的商品，请重新选择操作" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
	if (nfind == 2) {
		cout << "是否将该商品下架(y/n): ";
		cin >> chos;
		while (!cin || (chos != "y" && chos != "n")) {
			cout << "请按要求输入" << endl;
			cout << "是否将该商品下架(y/n): ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> chos;
		}
		if (chos == "y") {
			de->sit = "已下架";
			g.write_good();
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
	cout << endl << "请输入您想要封禁的用户ID： ";
	string i, chos;
	cin >> i;
	cout << endl << endl << "*********************************************************************************" << endl;
	int nfind = 0;
	User_information* de = new User_information;
	for (auto& ele : u.users) {
		if (ele->user_id == i) {
			u.print_user(ele);
			if (ele->sit == "封禁") {
				nfind = 1;
				cout << "该用户已封禁，请重新选择操作" << endl;
				break;
			}
			else { nfind = 2; de = ele; break; }
		}
	}
	if (nfind == 0) {
		cout << "没有搜索到您想要封禁的用户，请重新选择操作" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
	if (nfind == 2) {
		cout << "是否将该用户封禁(y/n): ";
		cin >> chos;
		while (!cin || (chos != "y" && chos != "n")) {
			cout << "请按要求输入" << endl;
			cout << "是否将该用户封禁(y/n): ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> chos;
		}
		if (chos == "y") {
			de->sit = "封禁";
			for (auto& e : g.goods) {
				if (e->seller_id == de->user_id) {
					e->sit = "已下架";
					g.write_good();
					u.write_user();
				}
			}
			cout << "封禁成功！" << endl << endl;
		}
		else if (chos == "n") {
			cout << "封禁取消，请重新选择您的操作" << endl << endl;
		}
	}
}
