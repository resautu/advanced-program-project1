#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include"MainMenu.h"
#include"Administrator.h"
#include"User.h"
#include <string>
#include"calculator.h"
#include"Shoppingtrolley.h"
using namespace std;

void main_menu() {
	system("md datebase");
	system("cls");
	Usering* u = new Usering;
	Ordering* o = new Ordering;
	Gooding* g = new Gooding;
	Reordering* r = new Reordering;
	Sqling* s = new Sqling;
	while (true) {
		cout << "Welcome to Winter Olympics souvenir trading platform" << endl << endl;
		cout << "======================================================================" << endl;
		cout << "    " << "1������Ա��¼ 2���û�ע�� 3���û���¼ 4��ʹ�ü����� 5���˳�����" << "    " << endl;
		cout << "======================================================================" << endl;
		cout << "����д�������룺";

		string temp;
		cin.clear();
		getline(cin, temp);
		while (!cin || new_trim(temp)[0] < '1' || new_trim(temp)[0]>'5') {
			cout << "��������ȷ������" << endl;
			cin.clear();
			getline(cin, temp);
		}
		switch (int(trim(temp)[0] - '0')) {
			//case 0: {Admin a(u, o, g, s); a.look_order(); break; }
		case 1: {Admin a(u, o, g, s); a.admin_login(); break; }
		case 2: {User er(u, o, g, r, s); er.user_register(); break; }
		case 3: {User er(u, o, g, r, s); er.user_login(); break; }
		case 4: calculator_menu("-1"); break;                                 //�������ӿ�
		case 5:exit(0); break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}