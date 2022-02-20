#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "User.h"
using namespace std;
void User::user_register() {
	User_information* t = new User_information;
	cout << "�����������û�����������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	string temp;
	cin >> temp;
	while (!cin || temp.size() > 10 || !cevalid(temp)) {
		cout << endl << endl<< " !!�û������Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> temp;
	}
	temp = t->user_name;
	cout << "�������������루������20���ַ���ֻ��Сд��ĸ��������ɣ�: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nevalid(temp)) {
		cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> temp;
	}
	t->key = temp;
	cout << "������������ϵ��ʽ��������20���ַ���ֻ��������ɣ�: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nvalid(temp)) {
		cout << endl << endl << " !!��ϵ��ʽ���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> temp;
	}
	t->con = temp;
	cout << "���������ĵ�ַ��������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !cevalid(temp)) {
		cout << endl << endl << " !!��ַ���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> temp;
	}
	temp = t->address;
	t->balance = 0;
	t->sit = "����";
	t->user_id.push_back('U');
	if (u.users[u.users.size() - 1]->user_id[3] == '9') {
		if (u.users[u.users.size() - 1]->user_id[2] == '9') {
			if (u.users[u.users.size() - 1]->user_id[1] == '9') {
				cout << "�û������Ѿ������ļ����أ����������˵�" << endl;
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
	cout << endl << endl << "******ע��ɹ�********" << endl << endl;
	u.write_user();
}

bool cevalid(string& s) {                //�ж��Ƿ�Ϊ���ֺ�Ӣ����ĸ;
	for (int i = 0; i < s.size();i++) {
		if (s[i] >= 0xB0) {
			if (i == s.size() - 1) { return false; }
			else {
				if (s[i + 1] >= 0xA0) { i++; continue; }
				else { return false; }
			}
		}
		else if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))) {
			return false;
		}
	}
	return true;
}
bool nevalid(string& s) {                 //�ж��Ƿ�ΪСд��ĸ������;
	for (auto& ele : s) {
		if (!((ele >= 'a' && ele <= 'z') || (ele >= '0' && ele <= '9'))) {
			return false;
		}
	}
	return true;
}

bool nvalid(string& s) {                 //�ж��Ƿ�ȫΪ����;
	for (auto& ele : s) {
		if (!(ele >= '0' && ele <= '9')) return false;
	}
	return true;
}