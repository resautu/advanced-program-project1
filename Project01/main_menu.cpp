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
		case 1:admin_menu(); break;
		case 2:user_register(); break;
		case 3:user_menu(); break;
		case 4:break;
		case 5:exit(0); break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl<<endl; break;
		}
	}
}
