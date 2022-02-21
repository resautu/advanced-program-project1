#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "User.h"
#include "sundry.h"
using namespace std;

bool cevalid(wstring& s) {                //判断是否为汉字和英文字母;
	for (auto &ele : s) {
		if (!((ele >= 'a' && ele <= 'z') || (ele >= 'A' && ele <= 'Z') || (int(ele) >= 0x4E00 && int(ele) <= 0x9FA0))) return false;
	}
	return true;
}
bool nevalid(string& s) {                 //判断是否为小写字母和数字;
	for (auto& ele : s) {
		if (!((ele >= 'a' && ele <= 'z') || (ele >= '0' && ele <= '9'))) {
			return false;
		}
	}
	return true;
}

bool nvalid(string& s) {                 //判断是否全为数字;
	for (auto& ele : s) {
		if (!(ele >= '0' && ele <= '9')) return false;
	}
	return true;
}

void User::user_register() {
	User_information* t = new User_information;
	cout << "请输入您的用户名（不超过10个字符，中文汉字或英文字母,其中中文占两个字符）: ";
	string temp;
	cin >> temp;
	wstring ctemp=s_to_ws(temp);
	while (!cin || ctemp.size() > 10 || !cevalid(ctemp)) {
		cout << endl << endl<< " !!用户名不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入您的用户名（不超过10个字符，中文汉字或英文字母）: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->user_name=temp;
	cout << "请输入您的密码（不超过20个字符，只由小写字母和数字组成）: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nevalid(temp)) {
		cout << endl << endl << " !!密码不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入您的密码（不超过20个字符，只由小写字母和数字组成）: ";
		cin >> temp;
	}
	t->key = temp;
	cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nvalid(temp)) {
		cout << endl << endl << " !!联系方式不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
		cin >> temp;
	}
	t->con = temp;
	cout << "请输入您的地址（不超过20个字符，中文汉字或英文字母）: ";
	cin >> temp;
	ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 20 || !cevalid(ctemp)) {
		cout << endl << endl << " !!地址不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入您的地址（不超过20个字符，中文汉字或英文字母）: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->address=temp;
	t->balance = 0;
	t->sit = "正常";
	t->user_id.push_back('U');
	if (u.users[u.users.size() - 1]->user_id[3] == '9') {
		if (u.users[u.users.size() - 1]->user_id[2] == '9') {
			if (u.users[u.users.size() - 1]->user_id[1] == '9') {
				cout << "用户数量已经超过文件承载，将返回主菜单" << endl;
				return;
			}
			t->user_id.push_back(u.users[u.users.size() - 1]->user_id[1]+1);
			t->user_id.push_back('0');
			t->user_id.push_back('0');
		}
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[1]);
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[2]+1);
		t->user_id.push_back('0');
	}
	else {
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[1]);
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[2]);
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[3]+1);
	}
	u.users.push_back(t);
	cout << endl << endl << "******注册成功********" << endl << endl;
	u.write_user();
}

void User::user_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! admin" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1、我是买家 2、我是卖家 3、个人信息管理 4、注销登录  " << endl;
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
		//case 1:look_good(); break;
		//case 2:search_good(); break;
		//case 3:del_good(); break;
		case 4:return; break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}