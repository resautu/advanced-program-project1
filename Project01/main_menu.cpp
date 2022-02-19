#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"MainMenu.h"
#include"Administrator.h"
#include"User.h"
using namespace std;
void admin_menu() {
	
}
void user_menu() {

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
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (i) {
		case 1:admin_menu(); break;
		case 2:user_register(); break;
		case 3:user_menu(); break;
		case 4:break;
		case 5:exit(0); break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl<<endl; break;
		}
	}
}
