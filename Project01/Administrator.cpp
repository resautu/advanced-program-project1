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
	cin >> s;
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g.goods) {
		if (ele->name.find(s) != string::npos) {
			print_good(ele);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "û���ҵ��ؼ��������Ʒ,������ѡ�����" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Admin::del_good() {
	cout << endl << "����������Ҫ�¼ܵ���ƷID�� ";
	string i,chos;
	cin >> i;
	cout << endl << endl << "*********************************************************************************" << endl;
	int nfind = 0;
	Good* de=new Good;
	for (auto& ele : g.goods) {
		if (ele->good_id == i) {
			print_good(ele);
			if (ele->sit == "���¼�") {
				nfind = 1;
				cout << "����Ʒ���¼ܣ�������ѡ�����" << endl;
				break;
			}
			else { nfind = 2; de = ele; break; }
		}
	}
	if (nfind==0) {
		cout << "û������������Ҫ�¼ܵ���Ʒ��������ѡ�����" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
	if (nfind == 2) {
		cout << "�Ƿ񽫸���Ʒ�¼�(y/n): ";
		cin >> chos;
		while (!cin || (chos!="y" && chos !="n")) {
			cout << "�밴Ҫ������" << endl;
			cout << "�Ƿ񽫸���Ʒ�¼�(y/n): ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> chos;
		}
		if (chos == "y") {
			de->sit = "���¼�";
			cout << "�¼ܳɹ���" << endl << endl;
		}
		else if (chos == "n") {
			cout << "�¼�ȡ����������ѡ�����Ĳ���" << endl << endl;
		}
	}
}

void Admin::look_order() {
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " ����ID " << "   ��ƷID   " << " ���׵���  " << " ����  " << "  ����ʱ��   " << " ����ID  " << " ���ID " << endl;
	for (auto& t : o.orders) {
		o.print_order(t);
	}

	cout << "*********************************************************************************" << endl << endl << endl;

}

void Admin::look_user() {
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " �û�ID " << "   �û���   " << "       ����      " << "  ��ϵ��ʽ  " << "          ��ַ   " << "   Ǯ�����  " << " �û�״̬ " << endl;
	for (auto& t : u.users) {
		u.print_user(t);
	}

	cout << "*********************************************************************************" << endl << endl << endl;
}
void Admin::del_user() {

}
