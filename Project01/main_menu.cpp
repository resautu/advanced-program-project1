#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include"MainMenu.h"
#include"Administrator.h"
#include"User.h"
#include <string>
//#include"Datebase.h"
using namespace std;

void main_menu() {
	Usering* u = new Usering;
	Ordering* o = new Ordering;
	Gooding* g = new Gooding;
	while (true) {
		cout << "Welcome to Winter Olympics souvenir trading platform" << endl << endl;
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
		case 0: {Admin a(u, o, g); a.look_order(); break; }
		case 1: {Admin a(u, o, g); a.admin_login(); break; }
		case 2: {User er(u, o, g); er.user_register(); break; }
		case 3: {User er(u, o, g); er.user_login(); break; }
		case 4:break;                                 //计算器接口
		case 5:exit(0); break;
		default:system("cls"); cout << "请按要求输入正确的数??" << endl << endl; break;
		}
	}
}