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
		cout << "    " << "1������Ա��¼ 2���û�ע�� 3���û���¼ 4��ʹ�ü����� 5���˳�����" << "    " << endl;
		cout << "======================================================================" << endl;
		cout << "����д�������룺";

		int i;
		cin >> i;
		while (!cin) {
			cout << "��������ȷ������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (i) {
		case 0: {Admin a(u, o, g); a.look_order(); break; }
		case 1: {Admin a(u, o, g); a.admin_login(); break; }
		case 2: {User er(u, o, g); er.user_register(); break; }
		case 3: {User er(u, o, g); er.user_login(); break; }
		case 4:break;                                 //�������ӿ�
		case 5:exit(0); break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ����??" << endl << endl; break;
		}
	}
}