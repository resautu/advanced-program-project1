#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"Administrator.h"
#include <fstream>
#include <iomanip>
string good_file = "D:/proj1/commodity.txt";
string user_file = "D:/proj1/Users.txt";
string order_file = "D:/proj1/Orders.txt";
using namespace std;
void Admin :: admin_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! admin" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1���鿴������Ʒ 2��������Ʒ 3���¼���Ʒ 4���鿴���ж��� 5���鿴�����û� 6������û� 7��ע��  " << endl;
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
		case 1:look_good(); break;
		case 2:search_good(); break;
		case 3:del_good(); break;
		case 4:look_order(); break;
		case 5:look_user(); break;
		case 6:del_user(); break;
		case 7:return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}

void Admin::look_good() {
	cout <<endl<<endl<< "*********************************************************************************" << endl;
	fstream f;
	f.open(good_file, ios::in);
	if (!f.is_open()) {
		cout << endl << "--------�ļ���ʧ��--------" << endl; 
		cout << "*******************************************" << endl;
		return;
	}
	cout << " ID " << "   ����   " << " �۸�  " << " �ϼ�ʱ��  " << " �������  " << " ����ID  " << " ��Ʒ״̬ " << "  �� ��   " << endl;
	while (true) {
		string judge;
		f >> judge;
		if (!f) {
			break;
		}
		Good* t = new Good;
		t->good_id = judge;
		
		f >> t->name >> t->price >> t->number >> t->description >> t->seller_id >> t->sell_time >> t->sit;
		cout << t->good_id<<"  "<< t->name << "  " << fixed << setprecision(1) << t->price << "  " << t->sell_time << "     " << t->number << "        " << t->seller_id << "   " << t->sit << "  " << t->description << endl;
		
		goods.push_back(t);
	}
	f.close();
	cout << "*********************************************************************************" << endl << endl << endl;

}

void Admin::search_good() {

}

void Admin::del_good() {

}

void Admin::look_order() {

}

void Admin::look_user() {

}
void Admin::del_user() {

}
