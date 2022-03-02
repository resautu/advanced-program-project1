#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Datebase.h"
using namespace std;
string good_file = "D:/proj1/commodity.txt";
string user_file = "D:/proj1/user.txt";
string order_file = "D:/proj1/order.txt";
string reorder_file = "D:/proj1/reorder.txt";
string sql_file = "D:/proj1/commands.txt";
string good_file_name = "commodity";
string user_file_name = "user";
string order_file_name = "order";

void Gooding::write_good() {
	fstream f;
	f.open(good_file, ios::out);
	if (!f) { cout << "��Ʒ�ļ�������ִ���������������" << endl; exit(0); }
	f << "��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬" << endl;
	for (auto& ele : goods) {
		f << ele->good_id << ',' << ele->name << ',' << ele->price << ',' << ele->number << ',';
		string s = ele->description;
		_replace(s, '`', '\'');
		_replace(s, ',', '`');
		f << s << ',' << ele->seller_id << ',' << ele->sell_time << ',' << ele->sit << endl;
	}
	f.close();
}

void Usering::write_user() {
	fstream f;
	f.open(user_file, ios::out);
	if (!f) { cout << "�û��ļ�������ִ���������������" << endl; exit(0); }
	f << "�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬" << endl;
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
	f << "����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID" << endl;
	for (auto& ele : orders) {
		f << ele->order_id << ',' << ele->good_id << ',' << fixed << setprecision(1) << ele->money << ',' << ele->number << ',' << ele->deal_time << ',' << ele->seller_id << ',' \
			<< ele->buyer_id << endl;
	}
	f.close();
}

void Reordering::write_reorder() {
	fstream f;
	f.open(reorder_file, ios::out);
	if (!f) { cout << "���׼�¼�ļ�������ִ���������������" << endl; exit(0); }
	f << "����Id,��ֵ���,��ֵʱ��" << endl;
	for (auto& ele : reorders) {
		f << ele->user_id << ',' << fixed << setprecision(1) << ele->money << ',' << ele->deal_time << endl;
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

void Sqling::write_sql(string s) {
	time_t t;
	t = time(NULL);
	tm* m = localtime(&t);
	string pt;
	pt.append(to_string(m->tm_year + 1900));
	pt.push_back('-');
	if (m->tm_mon + 1 < 10) pt.push_back('0');
	pt.append(to_string(m->tm_mon + 1));
	pt.push_back('-');
	pt.append(to_string(m->tm_mday));
	pt.push_back(' ');
	pt.append(to_string(m->tm_hour));
	pt.push_back(':');
	pt.append(to_string(m->tm_min));
	pt.push_back(':');
	pt.append(to_string(m->tm_sec));
	pt.append(": ");
	pt.append(s);
	sqls.push_back(pt);
	fstream f;
	f.open(sql_file, ios::out);
	if (!f) { cout << "sql�����ļ�������ִ���������������" << endl; exit(0); }
	for (auto& str : sqls) {
		f << str << endl;
	}
	f.close();
}

