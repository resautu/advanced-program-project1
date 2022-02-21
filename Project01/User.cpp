#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "User.h"
#include "sundry.h"
using namespace std;

bool cevalid(wstring& s) {                //�ж��Ƿ�Ϊ���ֺ�Ӣ����ĸ;
	for (auto &ele : s) {
		if (!((ele >= 'a' && ele <= 'z') || (ele >= 'A' && ele <= 'Z') || (int(ele) >= 0x4E00 && int(ele) <= 0x9FA0))) return false;
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

void User::user_register() {
	User_information* t = new User_information;
	cout << "�����������û�����������10���ַ������ĺ��ֻ�Ӣ����ĸ,��������ռ�����ַ���: ";
	string temp;
	cin >> temp;
	wstring ctemp=s_to_ws(temp);
	while (!cin || ctemp.size() > 10 || !cevalid(ctemp)) {
		cout << endl << endl<< " !!�û������Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "�����������û�����������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->user_name=temp;
	cout << "�������������루������20���ַ���ֻ��Сд��ĸ��������ɣ�: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nevalid(temp)) {
		cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "�������������루������20���ַ���ֻ��Сд��ĸ��������ɣ�: ";
		cin >> temp;
	}
	t->key = temp;
	cout << "������������ϵ��ʽ��������20���ַ���ֻ��������ɣ�: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nvalid(temp)) {
		cout << endl << endl << " !!��ϵ��ʽ���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "������������ϵ��ʽ��������20���ַ���ֻ��������ɣ�: ";
		cin >> temp;
	}
	t->con = temp;
	cout << "���������ĵ�ַ��������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	cin >> temp;
	ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 20 || !cevalid(ctemp)) {
		cout << endl << endl << " !!��ַ���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "���������ĵ�ַ��������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->address=temp;
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

void User::user_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! admin" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1��������� 2���������� 3��������Ϣ���� 4��ע����¼  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "������������: ";
		int i;
		cin >> i;
		while (!cin) {
			cout << "��������ȷ������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (i) {
		//case 1:look_good(); break;
		//case 2:search_good(); break;
		//case 3:del_good(); break;
		case 4:return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}