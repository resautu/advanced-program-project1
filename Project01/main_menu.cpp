#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"MainMenu.h"
#include"Administrator.h"
#include"User.h"
#include <string>
#include<windows.h>
#include<limits.h>
using namespace std;
void admin_login() {
	system("cls");
	string name, key;
	cout << "请输入管理员姓名: ";
	cin >> name;
	cout << "请输入密码: ";
	cin >> key;
	if (name != "admin" || key != "123456") {
		cout << endl << endl << "------用户名或密码错误，即将返回主菜单------" << endl;
		Sleep(500);
		return;
	}
	cout << endl << endl << "------登录成功，欢迎您------" << endl << endl;
	Admin admin;
	admin.admin_menu();
}
void user_login() {

}
void main_menu() {
	cout << "Welcome to Winter Olympics souvenir trading platform" << endl << endl;
	while (true) {
		cout << "======================================================================" << endl;
		cout << "    " << "1、管理员登录 2、用户注册 3、用户登录 4、使用计算器 5、退出程序" << "    " << endl;
		cout << "======================================================================" << endl;
		cout << "请填写您的输入：";

		int i;
		cin >> i;
		while (!cin) {
			cout << "请输入正确的数字" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> i;
		}
		switch (i) {
		case 1:admin_login(); break;
		case 2:user_register(); break;
		case 3:user_login(); break;
		case 4:break;
		case 5:exit(0); break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl<<endl; break;
		}
	}
}
