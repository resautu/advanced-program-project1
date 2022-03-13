#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"Administrator.h"
#include <fstream>
#include <iomanip>
using namespace std;

void Admin::admin_login() {
	system("cls");
	string name, key;
	cout << "���������Ա����: ";
	getline(cin, name);
	cout << "����������: ";
	getline(cin, key);
	if (name != "admin" || key != "123456") {
		system("cls");
		cout << endl << endl << "------�û�����������󣬼����������˵�------" << endl << endl << endl;
		return;
	}
	cout << endl << endl << "------��¼�ɹ�����ӭ��------" << endl << endl;
	admin_menu();
}

void Admin::admin_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! admin" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1���鿴������Ʒ 2��������Ʒ 3���¼���Ʒ 4���鿴���ж��� 5���鿴�����û� 6������û� 7��ע��  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "������������: ";
		string temp;
		temp.clear();
		cin.clear();
		getline(cin, temp);
		while (!cin || new_trim(temp)[0] < '1' || new_trim(temp)[0]>'7') {
			cout << "��������ȷ������" << endl;
			cin.clear();
			getline(cin, temp);
		}
		switch (int(trim(temp)[0] - '0')) {
		case 1:look_good(); break;
		case 2:search_good(); break;
		case 3:del_good(); break;
		case 4:look_order(); break;
		case 5:look_user(); break;
		case 6:del_user(); break;
		case 7:system("cls"); return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}

void Admin::look_good() {
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "��ƷID " << "       ����   " << "       �۸�  " << "     �ϼ�ʱ��  " << " �������  " << "����ID  " << "��Ʒ״̬ " << endl;
	for (auto& t : g->goods) {
		g->print_good(t);
	}
	sq->Select(good_file_name);
	cout << "*********************************************************************************" << endl << endl << endl;

}

void Admin::search_good() {
	string s;
	cout << "����������Ҫ���ҵ���Ʒ�� ";
	cin >> s;
	while (!cin) {
		cout << "��������ȷ����ƷID" << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> s;
	}
	sq->Select(good_file_name, true, "����", s);
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g->goods) {
		if (ele->name.find(s) != string::npos) {
			cout << "��ƷID " << "       ����   " << "       �۸�  " << "     �ϼ�ʱ��  " << " �������  " << "����ID  " << "��Ʒ״̬ " << endl;
			g->print_good(ele);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "û���ҵ��ؼ��������Ʒ,������ѡ�����" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Admin::del_good() {                               //this function should write the document
	cout << endl << "����������Ҫ�¼ܵ���ƷID�� ";
	string i, chos;
	i.clear();
	cin.clear();
	getline(cin, i);
	cout << endl << endl << "*********************************************************************************" << endl;
	int nfind = 0;
	Good* de = new Good;
	for (auto& ele : g->goods) {
		if (ele->good_id == trim(i)) {
			cout << "��ƷID " << "       ����   " << "       �۸�  " << "     �ϼ�ʱ��  " << " �������  " << "����ID  " << "��Ʒ״̬ " << endl;
			g->print_good(ele);
			if (ele->sit == "���¼�") {
				nfind = 1;
				cout << "����Ʒ���¼ܣ�������ѡ�����" << endl;
				break;
			}
			else { nfind = 2; de = ele; break; }
		}
	}
	if (nfind == 0) {
		cout << "û������������Ҫ�¼ܵ���Ʒ��������ѡ�����" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
	if (nfind == 2) {
		cout << "�Ƿ񽫸���Ʒ�¼�(y/n): ";
		chos.clear();
		cin.clear();
		getline(cin, chos);
		while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
			cout << "�밴Ҫ������" << endl;
			cout << "�Ƿ񽫸���Ʒ�¼�(y/n): ";
			cin.clear();
			getline(cin, chos);
		}
		if (chos == "y") {
			de->sit = "���¼�";
			g->write_good();
			cout << "�¼ܳɹ���" << endl << endl;
			vector<string> valsu;
			valsu.push_back("��Ʒ״̬ = ���¼�");
			sq->Update(good_file_name, "��ƷID = " + de->good_id, valsu);
			system("cls");
			cout << endl << "***************�¼ܳɹ���������**********" << endl << endl;
		}
		else if (chos == "n") {
			system("cls");
			cout << endl << "***************�¼�ȡ����������ѡ�����Ĳ���**********" << endl << endl;
		}
	}
}

void Admin::look_order() {
	sq->Select(order_file_name);
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "����ID " << " ��ƷID   " << " ���׵���  " << " ����  " << "  ����ʱ��   " << " ����ID  " << " ���ID " << endl;
	for (auto& t : o->orders) {
		o->print_order(t);
	}

	cout << "*********************************************************************************" << endl << endl << endl;

}

void Admin::look_user() {
	sq->Select(user_file_name);
	cout << endl << endl << "***************************************************************************************************" << endl;
	cout << "�û�ID " << "    �û���   " << "       ����      " << "    ��ϵ��ʽ  " << "          ��ַ   " << "       Ǯ�����  " << "�û�״̬ " << endl;
	for (auto& t : u->users) {
		u->print_user(t);
	}

	cout << "***************************************************************************************************" << endl << endl << endl;
}

void Admin::del_user() {
	cout << endl << "����������Ҫ������û�ID�� ";
	string i, chos;
	i.clear(); cin.clear();
	getline(cin, i);
	cout << endl << endl << "*****************************************************************************************" << endl;
	int nfind = 0;
	User_information* de = new User_information;
	for (auto& ele : u->users) {
		if (ele->user_id == trim(i)) {
			u->print_user(ele);
			if (ele->sit == "���") {
				nfind = 1;
				cout << "���û��ѷ����������ѡ�����" << endl;
				break;
			}
			else { nfind = 2; de = ele; break; }
		}
	}
	if (nfind == 0) {
		cout << "û������������Ҫ������û���������ѡ�����" << endl;
	}
	cout << "*****************************************************************************************" << endl << endl << endl;
	if (nfind == 2) {
		cout << "�Ƿ񽫸��û����(y/n): ";
		chos.clear(); cin.clear();
		getline(cin, chos);
		while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
			cout << "�밴Ҫ������" << endl;
			cout << "�Ƿ񽫸��û����(y/n): ";
			cin.clear();
			getline(cin, chos);
		}
		if (chos == "y") {

			de->sit = "���";
			for (auto& e : g->goods) {
				if (e->seller_id == de->user_id) {
					vector<string> valsu;
					valsu.push_back("��Ʒ״̬ = ���¼�");
					sq->Update(good_file_name, "����ID = " + e->seller_id, valsu);
					e->sit = "���¼�";
					g->write_good();
				}
			}
			vector<string> valsu;
			valsu.push_back("�û�״̬ = ���");
			sq->Update(user_file_name, "�û�ID = " + de->user_id, valsu);
			u->write_user();
			system("cls");
			cout << endl << "***********����ɹ���**************" << endl << endl;
		}
		else if (chos == "n") {
			system("cls");
			cout << endl << "*************���ȡ����������ѡ�����Ĳ���************" << endl << endl;
		}
	}
}
