#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Datebase.h"
using namespace std;

void Gooding::write_good() {
	fstream f;
	f.open(good_file, ios::out);
	if (!f) { cout << "��Ʒ�ļ�������ִ���������������" << endl; exit(0); }
	f << "��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬"<<endl;
	for (auto& ele : goods) {
		f << ele->good_id << ',' << ele->name << ',' << ele->price << ',' << ele->number << ',';
		string s = ele->description;
		replace(s.begin(), s.end(), ',', '`');
		f <<ele->description << ',' << ele->seller_id << ',' << ele->sell_time << ',' << ele->sit << endl;
	}
	f.close();
}

void Usering::write_user() {
	fstream f;
	f.open(user_file, ios::out);
	if (!f) { cout << "�û��ļ�������ִ���������������" << endl; exit(0); }
	f << "�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬"<<endl;
	for (auto& ele : users) {
		f << ele->user_id << ',' << ele->user_name << ',' << ele->key << ',' << ele->con << ',' << ele->address << ',' << ele->balance << ',' \
			<< ele->sit << endl;
	}
	f.close();
}

void Ordering::write_order() {
	fstream f;
	f.open(order_file, ios::out);
	if (!f) { cout << "�����ļ�������ִ���������������" << endl; exit(0); }
	f << "����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID"<<endl;
	for (auto& ele : orders) {
		f << ele->order_id << ',' << ele->good_id << ',' << ele->money << ',' << ele->number << ',' << ele->deal_time << ',' << ele->seller_id << ',' \
			<< ele->buyer_id << endl;
	}
	f.close();
}

void Gooding::check_good() {
	
	for (auto& ele : goods) {
		if (ele->number == 0 && ele->sit != "���¼�") {
			ele->sit = "���¼�";

		}
	}
	write_good();
	
}

void Usering::balance_change(string id, double money) {
	for (auto& ele : users) {
		if (ele->user_id == id) {
			ele->balance = money;
			write_user();
			break;
		}
	}
}

void read_txt() {

}
