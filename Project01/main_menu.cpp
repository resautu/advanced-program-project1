#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include"MainMenu.h"
#include"Administrator.h"
#include"User.h"
#include <string>
//#include"Datebase.h"
using namespace std;
void admin_login(Usering& us, Ordering& ord, Gooding& go) {
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
	Admin admin(us, ord, go);
	admin.admin_menu();
}

void main_menu() {
	Usering u;
	Ordering o;
	Gooding g;
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
		case 0: {Admin a(u, o, g); a.look_user(); break; }
		case 1:admin_login(u,o,g); break;
		case 2: {User er(u, o, g); er.user_register(); break; }
		case 3:{User er(u, o, g); er.user_login(); break;}
		case 4:break;                                 //计算器接口
		case 5:exit(0); break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl<<endl; break;
		}
	}
}
