#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"Administrator.h"
#include <fstream>
#include <iomanip>
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
void Admin :: print_good(Good* t) {
	cout << left << t->good_id << "  " << t->name << "  " << fixed << setprecision(1) << t->price << "  " << setw(10) << t->sell_time << "     " << t->number << "        " << t->seller_id << "   " << t->sit << "  " << t->description << endl;
}
void Admin::look_good() {
	cout <<endl<<endl<< "*********************************************************************************" << endl;
	cout << " ID " << "   ����   " << " �۸�  " << " �ϼ�ʱ��  " << " �������  " << " ����ID  " << " ��Ʒ״̬ " << "  �� ��   " << endl;
	for(auto &t : g.goods) {
		print_good(t);
	}
	
	cout << "*********************************************************************************" << endl << endl << endl;

}

void Admin::search_good() {
	string s;
	cout << "����������Ҫ���ҵ���Ʒ�� ";

}

void Admin::del_good() {

}

void Admin::look_order() {

}

void Admin::look_user() {

}
void Admin::del_user() {

}
