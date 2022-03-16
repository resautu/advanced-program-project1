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

void Sqling::selectAnalyze(string cmd, Gooding* g, Usering* u, Ordering* o) {
	if (!g && !u && !o) return;
	string fileName, column, value;
	int count = 0;
	bool judge = false;
	if (cmd.find('W' == string::npos)) judge = true;
	else judge = false;
	for (auto ch : cmd) {
		if (ch == '*' && judge) {
			for (auto e : cmd) {
				if (count == 3) {
					if (e == 'c') {
						for (auto ele : g->goods) {
							g->print_good(ele);
						}
					}
					else if (e == 'u') {
						for (auto ele : u->users) {
							u->print_user(ele);
						}
					}
					else {
						for (auto ele : o->orders) {
							o->print_order(ele);
						}
					}
					break;
				}
				if (e == ' ') {
					count++;
				}
			}
			break;
		}
	}
	if (!judge) {
		count = 0;
		for (auto ch : cmd) {
			if (count == 3 && ch != ' ') {
				fileName.push_back(ch);
			}
			if (count == 5 && ch != ' ') {
				column.push_back(ch);
			}
			if (count == 7 && ch != ' ') {
				value.push_back(ch);
			}
			if (ch == ' ') {
				count++;
			}

		}
	}
	if (fileName == "commodity" && !judge) {
		if (column == "����") {
			for (auto ele : g->goods) {
				if (ele->name.find(value) != string::npos) {
					g->print_good(ele); break;
				}
			}
		}
	}
	return;
}

void Sqling::insertAnalyze(string cmd, Gooding* g, Usering* u, Ordering* o) {
	if (!g && !u && !o) return;
	string fileName;
	vector<string> values;
	string value;
	int count = 0, i = 0;
	bool judge = false;
	for (auto ch : cmd) {
		if (ch == ' ') count++;
		if (count == 2 && ch != ' ') {
			fileName.push_back(ch);
		}
		if (ch == '(') {
			judge = true;
			value.clear();
		}
		else if (judge && ch == ',') {
			values.push_back(value);
			value.clear();
		}
		else if (judge && ch != ')') {
			value.push_back(ch);
		}
		else if (judge && ch == ')') {
			values.push_back(value);
			value.clear();
		}
	}
	if (fileName == "order") {
		Order* paper = new Order;
		paper->order_id = values[0];
		paper->good_id = values[1];
		paper->money = exdouble(values[2]);
		paper->number = exint(values[3]);
		paper->buyer_id = values[4];
		paper->seller_id = values[5];
		o->orders.push_back(paper);
		o->write_order();
	}
	else if (fileName == "commodity") {
		Good* t = new Good;
		t->name = values[0];
		t->price = exdouble(values[1]);
		t->number = exint(values[2]);
		t->description = values[3];
		g->goods.push_back(t);
		g->write_good();
	}
}

void Sqling::updateAnalyze(string cmd, Gooding* g, Usering* u, Ordering* o) {
	if (!g && !u && !o) return;
	vector<string> column, values;
	string fileName;
	string col, val;
	string col_lim, val_lim;
	bool lim1 = false, lim2 = false;
	int count = 0;
	for (int i = 0; i < cmd.length(); i++) {
		if (count == 1 && cmd[i] != ' ') {
			fileName.push_back(cmd[i]);
		}
		if (cmd[i] == ' ') count++;
		if (cmd[i] == 'E' && cmd[i + 1] == 'T') {
			i += 2;
			lim1 = true;
			continue;
		}
		if (lim1 && cmd[i] == ' ') {
			lim1 = false;
			lim2 = true;
			column.push_back(col);
			col.clear();
			i += 2;
			continue;
		}
		if (cmd[i] == ',') {
			lim1 = true;
			lim2 = false;
			values.push_back(val);
			val.clear();
			i += 1;
			continue;
		}
		if (lim2 && cmd[i] == ' ' && cmd[i + 1] == 'W') {
			int j = i + 7;
			for (; j < cmd.length(); j++) {
				if (cmd[j] == ' ') break;
				col_lim.push_back(cmd[j]);
			}
			for (j = j + 3; j < cmd.length(); j++) {
				val_lim.push_back(cmd[j]);
			}
			break;
		}
		if (lim1) {
			col.push_back(cmd[i]);
		}
		else if (lim2) {
			val.push_back(cmd[i]);
		}

	}
	if (fileName == "commodity") {
		if (col_lim == "��ƷID") {
			if (column.size() == 1 && column[0] == "��Ʒ״̬") {
				for (auto ele : g->goods) {
					if (ele->good_id == val_lim) {
						ele->sit = values[0];
					}
				}
			}
			else if (column.size() == 1 && column[0] == "�۸�") {
				for (auto ele : g->goods) {
					if (ele->good_id == val_lim) {
						ele->price = exdouble(values[0]);
					}
				}
			}
			else if (column.size() == 1 && column[0] == "����") {
				for (auto ele : g->goods) {
					if (ele->good_id == val_lim) {
						ele->description = values[0];
					}
				}
			}
			else if (column.size() == 1 && column[0] == "����") {
				for (auto ele : g->goods) {
					if (ele->good_id == val_lim) {
						ele->number = exint(values[0]);
					}
				}
			}
			else if (column.size() == 2) {
				for (auto ele : g->goods) {
					if (ele->good_id == val_lim) {
						ele->number = exint(values[0]);
						ele->sit = values[1];
					}
				}
			}
		}
		else if (col_lim == "����ID") {
			for (auto ele : g->goods) {
				if (ele->seller_id == val_lim) {
					ele->sit == values[0];
				}
			}
		}
	}
	else if (fileName == "user") {
		for (auto ele : u->users) {
			if (ele->user_id == val_lim) {
				ele->sit = values[0];
			}
		}
	}
}

