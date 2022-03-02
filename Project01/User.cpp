#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "User.h"
#include "sundry.h"
#include"Item.h"

using namespace std;

void User::user_register() {
	User_information* t = new User_information;
	cout << "�����������û�����������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	string temp;
	cin >> temp;
	wstring ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 10 || !cevalid(ctemp)) {
		cout << endl << endl << " !!�û������Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "�����������û�����������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	for (auto& ele : u->users) {
		if (ele->user_name == temp) {
			system("cls");
			cout << endl << "******���û����Ѵ��ڣ�������ѡ�����******" << endl << endl;
			return;
		}
	}
	t->user_name = temp;
	cout << "�������������루������20���ַ���ֻ��Сд��ĸ��������ɣ�: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nevalid(temp)) {
		cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "�������������루������20���ַ���ֻ��Сд��ĸ��������ɣ�: ";
		cin >> temp;
	}
	t->key = temp;
	cout << "������������ϵ��ʽ��������20���ַ���ֻ��������ɣ�: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nvalid(temp)) {
		cout << endl << endl << " !!��ϵ��ʽ���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "������������ϵ��ʽ��������20���ַ���ֻ��������ɣ�: ";
		cin >> temp;
	}
	t->con = temp;
	cout << "���������ĵ�ַ��������40���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	cin >> temp;
	ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 40 || !cevalid(ctemp)) {
		cout << endl << endl << " !!��ַ���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "���������ĵ�ַ��������40���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->address = temp;
	t->balance = 0;
	t->sit = "����";
	t->user_id.push_back('U');
	if (u->users.size() == 0) {
		string st = "001";
		t->user_id.append(st);
	}
	else if (u->users[u->users.size() - 1]->user_id[3] == '9') {
		if (u->users[u->users.size() - 1]->user_id[2] == '9') {
			if (u->users[u->users.size() - 1]->user_id[1] == '9') {
				cout << "�û������Ѿ������ļ����أ����������˵�" << endl;
				return;
			}
			t->user_id.push_back(u->users[u->users.size() - 1]->user_id[1] + 1);
			t->user_id.push_back('0');
			t->user_id.push_back('0');
		}
		t->user_id.push_back(u->users[u->users.size() - 1]->user_id[1]);
		t->user_id.push_back(u->users[u->users.size() - 1]->user_id[2] + 1);
		t->user_id.push_back('0');
	}
	else {
		t->user_id.push_back(u->users[u->users.size() - 1]->user_id[1]);
		t->user_id.push_back(u->users[u->users.size() - 1]->user_id[2]);
		t->user_id.push_back(u->users[u->users.size() - 1]->user_id[3] + 1);
	}
	vector<string> vals;
	vals.push_back(t->user_id);
	vals.push_back(t->user_name);
	vals.push_back(t->key);
	vals.push_back(t->con);
	vals.push_back(t->address);
	vals.push_back("0");
	vals.push_back(t->sit);
	sq->Insert(user_file_name, vals);
	u->users.push_back(t);
	cout << endl << endl << "******ע��ɹ�********" << endl << endl;
	u->write_user();
}

void User::user_menu(User_information* information) {
	system("cls");
	while (true) {
		cout << "Welcome! user" << endl;
		cout << "=================================================================================" << endl;
		cout << "  1��������� 2���������� 3��������Ϣ���� 4��ע����¼  " << endl;
		cout << "=================================================================================" << endl;
		cout << "������������: ";
		string i;
		cin >> i;
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "4")) {
			cout << "���벻�Ϸ�������������" << endl;
			cout << "������������: ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (int(trim(i)[0] - '0')) {
		case 1: {
			User* er = new User(u, o, g, r, sq);
			((Buyer*)er)->inform = information;
			((Buyer*)er)->buyer_menu();
			break;
		}
		case 2: {
			User* er = new User(u, o, g, r, sq);
			((Seller*)er)->inform = information;
			((Seller*)er)->seller_menu();
			break;
		}
		case 3:gover_inform(); break;
		case 4:system("cls"); return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}

void User::user_login() {
	system("cls");
	string name, key;
	cout << "�������û���: ";
	cin >> name;
	cout << "����������: ";
	cin >> key;
	for (auto& ele : u->users) {
		if (ele->user_name == name) {
			if (ele->key == key) {
				if (ele->sit == "���") {
					system("cls");
					cout << endl << endl << "------�����˻��ѱ�����������������˵�------" << endl << endl << endl;
					return;
				}
				cout << endl << endl << "------��¼�ɹ�����ӭ��------" << endl << endl;
				inform = ele;
				user_menu(ele);
				return;
			}
			else {
				system("cls");
				cout << endl << endl << "------�û�����������󣬼����������˵�------" << endl << endl << endl;
				return;
			}
		}
	}
	system("cls");
	cout << endl << endl << "------�û�����������󣬼����������˵�------" << endl << endl << endl;
	return;
}

void User::gover_inform() {
	system("cls");
	while (true) {
		cout << "Welcome! user" << endl;
		cout << "=================================================================================" << endl;
		cout << "  1���鿴��Ϣ 2���޸���Ϣ 3����ֵ 4�������û�������  " << endl;
		cout << "=================================================================================" << endl;
		cout << "������������: ";
		string i;
		cin >> i;
		while (!cin || (trim(i) < "1" || trim(i) > "4")) {
			cout << "���벻�Ϸ�������������" << endl;
			cout << "������������: ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (int(trim(i)[0] - '0')) {
		case 1: look_information(); break;
		case 2: change_information(); break;
		case 3:recharge(); break;
		case 4:system("cls"); return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}

void User::change_information() {
	cout << "��ѡ���޸ĵ����ԣ�1���û��� 2����ϵ��ʽ 3����ַ��: ";
	string i;
	cin >> i;
	while (!cin || (trim(i) < "1" || trim(i) > "3")) {
		cout << "���벻�Ϸ�������������" << endl;
		cout << "��ѡ���޸ĵ����ԣ�1���û��� 2����ϵ��ʽ 3����ַ��: ";
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> i;
	}
	switch (int(trim(i)[0] - '0')) {
	case 1: {
		cout << "�����������û�����������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
		string temp;
		cin >> temp;
		wstring ctemp = s_to_ws(temp);
		while (!cin || ctemp.size() > 10 || !cevalid(ctemp)) {
			cout << endl << endl << " !!�û������Ϸ����밴Ҫ������!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "�����������û�����������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
			cin >> temp;
			ctemp = s_to_ws(temp);
		}
		for (auto& ele : u->users) {
			if (ele->user_name == temp) {
				system("cls");
				cout << endl << "******���û����Ѵ��ڣ�������ѡ�����******" << endl << endl;
				return;
			}
		}
		inform->user_name = temp;
		u->write_user();
		cout << endl << "******�޸ĳɹ�******" << endl;
		break;
	}
	case 2: {
		string temp;
		cout << "������������ϵ��ʽ��������20���ַ���ֻ��������ɣ�: ";
		cin >> temp;
		while (!cin || temp.size() > 20 || !nvalid(temp)) {
			cout << endl << endl << " !!��ϵ��ʽ���Ϸ����밴Ҫ������!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "������������ϵ��ʽ��������20���ַ���ֻ��������ɣ�: ";
			cin >> temp;
		}
		inform->con = temp;
		u->write_user();
		cout << endl << "******�޸ĳɹ�******" << endl;
		break;
	}
	case 3: {
		string temp;
		cout << "������������ϵ��ʽ��������20���ַ���ֻ��������ɣ�: ";
		cin >> temp;
		wstring ctemp = s_to_ws(temp);
		while (!cin || ctemp.size() > 20 || !cevalid(ctemp)) {
			cout << endl << endl << " !!��ַ���Ϸ����밴Ҫ������!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "���������ĵ�ַ��������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
			cin >> temp;
			ctemp = s_to_ws(temp);
		}
		inform->address = temp;
		u->write_user();
		cout << endl << "******�޸ĳɹ�******" << endl;
		break;
	}
	default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
	}
}

void User::look_information() {
	cout << endl << endl << "*********************************************************************************" << endl;

	for (auto& ele : u->users) {
		if (ele->user_id == inform->user_id) {
			cout << "�û�����" << ele->user_name << endl << "��ϵ��ʽ��" << ele->con << endl << "��ַ��" << ele->address << endl << "Ǯ����" << fixed << setprecision(1) << ele->balance << endl;
			cout << "*********************************************************************************" << endl << endl << endl;
		}
	}
}

void User::recharge() {
	string temp;
	cout << "�������ֵ��ϵͳ��Ϊ������һλС��������ȥ����С����: ";
	cin >> temp;
	while (!cin || dnvalid(temp)) {
		cout << endl << endl << " !!��Ʒ�۸񲻺Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "�������ֵ��ϵͳ���Զ�Ϊ������һλС����: ";
		cin >> temp;
	}
	Reorder* re = new Reorder;
	re->user_id = inform->user_id;
	re->money = exdouble(temp);
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
	re->deal_time = pt;
	r->reorders.push_back(re);
	r->write_reorder();
	inform->balance += exdouble(temp);
	u->write_user();
	cout << endl << endl << "**************��ֵ�ɹ�**************" << endl << endl << endl;
}

void Seller::seller_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! seller" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1��������Ʒ 2���鿴������Ʒ 3���޸���Ʒ��Ϣ 4���¼���Ʒ 5���鿴��ʷ���� 6�������û�������  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "������������: ";
		string i;
		cin >> i;
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "��������ȷ������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (int(trim(i)[0] - '0')) {
		case 1:release(); break;
		case 2:look_good(); break;
		case 3:change_information(); system("cls"); break;
		case 4:del_good(); system("cls"); break;
		case 5:look_order(); break;
		case 6:system("cls"); return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}

void Seller::release() {
	Good* t = new Good;
	cout << "��������Ʒ���ƣ�������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	string temp;
	cin >> temp;
	wstring ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 20 || !cevalid(ctemp)) {
		cout << endl << endl << " !!��Ʒ���Ʋ��Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "��������Ʒ���ƣ�������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->name = temp;
	cout << "��������Ʒ�۸�ϵͳ��Ϊ������һλС��������ȥ����С����: ";
	cin >> temp;
	while (!cin || dnvalid(temp)) {
		cout << endl << endl << " !!��Ʒ�۸񲻺Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "��������Ʒ�۸�ϵͳ���Զ�Ϊ������һλС����: ";
		cin >> temp;
	}
	t->price = exdouble(temp);
	cout << "��������Ʒ����������Ϊ����������λ����Ϊ0��: ";
	cin >> temp;
	while (!cin || temp[0] == '0' || !nvalid(temp)) {
		cout << endl << endl << " !!��Ʒ�������Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "��������Ʒ����������Ϊ����������λ����Ϊ0��: ";
		cin >> temp;
	}
	t->number = exint(temp);
	cout << "��������Ʒ������������100���ַ���: ";
	cin >> temp;
	ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 20) {
		if (ctemp.size() > 20) {
			cout << endl << endl << " !!�������ȳ����ַ����ƣ��밴Ҫ������!! " << endl;
		}
		else {
			cout << endl << endl << " !!��Ʒ�������Ϸ����밴Ҫ������!! " << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "��������Ʒ������������100���ַ���: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->description = temp;
	t->seller_id = inform->user_id;
	t->sit = "������";
	t->good_id.push_back('M');
	if (g->goods.size() == 0) {
		string st = "001";
		t->good_id.append(st);
	}
	else if (g->goods[g->goods.size() - 1]->good_id[3] == '9') {
		if (g->goods[g->goods.size() - 1]->good_id[2] == '9') {
			if (g->goods[g->goods.size() - 1]->good_id[1] == '9') {
				cout << "��Ʒ�����Ѿ������ļ����أ����������˵�" << endl;
				return;
			}
			t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[1] + 1);
			t->good_id.push_back('0');
			t->good_id.push_back('0');
		}
		t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[1]);
		t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[2] + 1);
		t->good_id.push_back('0');
	}
	else {
		t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[1]);
		t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[2]);
		t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[3] + 1);
	}
	time_t cl;
	cl = time(NULL);
	tm* m = localtime(&cl);
	string pt;
	pt.append(to_string(m->tm_year + 1900));
	pt.push_back('-');
	if (m->tm_mon + 1 < 10) pt.push_back('0');
	pt.append(to_string(m->tm_mon + 1));
	pt.push_back('-');
	pt.append(to_string(m->tm_mday));
	t->sell_time = pt;
	vector<string> vals;
	vals.push_back(t->name);
	vals.push_back(double_to_string(t->price));
	vals.push_back(to_string(t->number));
	vals.push_back(t->description);
	sq->Insert(good_file_name, vals);
	g->goods.push_back(t);
	system("cls");
	cout << endl << endl << "******�����ɹ�********" << endl << endl;
	g->write_good();
}

void Seller::change_information() {
	cout << endl << endl << "�����뱻�޸ĵ���ƷID: ";
	string temp;
	cin >> temp;
	double new_price;
	string new_description;
	while (!cin) {
		cout << endl << endl << " !!��ƷID���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << endl << endl << "�����뱻�޸ĵ���ƷID: ";
		cin >> temp;
	}
	for (auto& ele : g->goods) {
		if (ele->good_id == temp) {
			if (ele->seller_id != inform->user_id) {
				cout << endl << "!!����Ʒ��������������Ȩ�Դ���Ʒ���в�������" << endl;
				return;
			}
			cout << "�����뱻�޸ĵ���Ʒ���ԣ�1���۸� 2��������: ";
			cin >> temp;
			while (!cin || (trim(temp) != "1" && trim(temp) != "2")) {
				cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << endl << endl << "�����뱻�޸ĵ���Ʒ���ԣ�1���۸� 2��������: ";
				cin >> temp;
			}
			switch (int(trim(temp)[0] - '0')) {
			case 1: {
				cout << "��������Ʒ�۸�ϵͳ��Ϊ������һλС��������ȥ����С����: ";
				cin >> temp;
				while (!cin || dnvalid(temp)) {
					cout << endl << endl << " !!��Ʒ�۸񲻺Ϸ����밴Ҫ������!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << "�������µ���Ʒ�۸�ϵͳ���Զ�Ϊ������һλС����: ";
					cin >> temp;
				}
				new_price = exdouble(temp);
				cout << "��ȷ����Ʒ�޸ĵ���Ʒ��Ϣ����" << endl;
				cout << "********************************************************************" << endl;
				cout << "��ƷID��" << ele->good_id << endl << "��Ʒ���ƣ�" << ele->name << endl << "��Ʒ�۸�" << fixed << setprecision(1) << new_price << endl << "��Ʒ������" << ele->description << endl;
				cout << "********************************************************************" << endl;
				cout << "�Ƿ�ȷ���޸ģ�(y/n)��";
				cin >> temp;
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << endl << endl << "�Ƿ�ȷ���޸ģ�(y/n)��";
					cin >> temp;
				}
				if (trim(temp) == "y") {
					vector<string> valsu;
					valsu.push_back("�۸� = " + to_string(ele->price));
					sq->Update(good_file, "��ƷID = " + ele->good_id, valsu);
					ele->price = new_price;
					g->write_good();
				}
				else { return; }
				break;
			}
			case 2: {
				wstring ctemp;
				cout << "��������Ʒ�µ�������������100���ַ���: ";
				cin >> temp;
				ctemp = s_to_ws(temp);
				while (!cin || ctemp.size() > 20) {
					if (ctemp.size() > 20) {
						cout << endl << endl << " !!�������ȳ����ַ����ƣ��밴Ҫ������!! " << endl;
					}
					else {
						cout << endl << endl << " !!��Ʒ�������Ϸ����밴Ҫ������!! " << endl;
					}
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << "��������Ʒ�µ�������������100���ַ���: ";
					cin >> temp;
					ctemp = s_to_ws(temp);
				}
				new_description = temp;
				cout << "��ȷ����Ʒ�޸ĵ���Ʒ��Ϣ����" << endl;
				cout << "********************************************************************" << endl;
				cout << "��ƷID��" << ele->good_id << endl << "��Ʒ���ƣ�" << ele->name << endl << "��Ʒ�۸�" << ele->price << endl << "��Ʒ������" << new_description << endl;
				cout << "********************************************************************" << endl;
				cout << "�Ƿ�ȷ���޸ģ�(y/n)��";
				cin >> temp;
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << endl << endl << "�Ƿ�ȷ���޸ģ�(y/n)��";
					cin >> temp;
				}
				if (trim(temp) == "y") {
					vector<string> valsu;
					valsu.push_back("��Ʒ���� = " + ele->description);
					sq->Update(good_file_name, "��ƷID = " + ele->good_id, valsu);
					ele->description = new_description;
					g->write_good();
				}
				else { return; }
				break;
			}
			default:cout << "������ִ���" << endl; break;
			}
		}
	}
}

void Seller::del_good() {
	cout << endl << "����������Ҫ�¼ܵ���ƷID�� ";
	string i, chos;
	cin >> i;
	cout << endl << endl << "*********************************************************************************" << endl;
	int nfind = 0;
	Good* de = new Good;
	for (auto& ele : g->goods) {
		if (ele->good_id == i) {
			if (ele->seller_id != inform->user_id) {
				cout << endl << "!!����Ʒ��������������Ȩ�Դ���Ʒ���в���!��" << endl;
				return;
			}
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
		cin >> chos;
		while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
			cout << "�밴Ҫ������" << endl;
			cout << "�Ƿ񽫸���Ʒ�¼�(y/n): ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> chos;
		}
		if (trim(chos) == "y") {
			vector<string> valsu;
			valsu.push_back("��Ʒ״̬ = ���¼�");
			sq->Update(good_file_name, "��ƷID = " + de->good_id, valsu);
			de->sit = "���¼�";
			g->write_good();
			cout << "�¼ܳɹ���" << endl << endl;
		}
		else if (trim(chos) == "n") {
			cout << "�¼�ȡ����������ѡ�����Ĳ���" << endl << endl;
		}
	}
}

void Seller::look_order() {
	sq->Select(order_file_name);
	bool nfind = true;
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " ����ID " << "   ��ƷID   " << " ���׵���  " << " ����  " << "  ����ʱ��   " << " ����ID  " << " ���ID " << endl;
	for (auto& t : o->orders) {
		if (t->seller_id == inform->user_id) {
			o->print_order(t);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "******����ʱû�ж���******" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Seller::look_good() {
	sq->Select(good_file_name);
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "��ƷID " << "       ����   " << "       �۸�  " << "     �ϼ�ʱ��  " << " �������  " << "����ID  " << "��Ʒ״̬ " << endl;
	for (auto& t : g->goods) {
		if (t->seller_id == inform->user_id) {
			g->print_good(t);
		}
	}

	cout << "*********************************************************************************" << endl << endl << endl;
}

void Buyer::buyer_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! seller" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1���鿴��Ʒ�б� 2��������Ʒ 3��������Ʒ 4���鿴��ʷ���� 5���鿴��Ʒ��ϸ��Ϣ 6�������û�������  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "������������: ";
		string i;
		cin >> i;
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "��������ȷ��ѡ��" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (int(trim(i)[0] - '0')) {
		case 1:look_good(); break;
		case 2:buy(); break;
		case 3:search_good(); break;
		case 4:look_order(); break;
		case 5:look_good_information(); break;
		case 6:system("cls"); return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}

void Buyer::look_good() {
	sq->Select(good_file_name);
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "��ƷID " << "       ����   " << "       �۸�  " << "     �ϼ�ʱ��  " << " �������  " << "����ID  " << "��Ʒ״̬ " << endl;
	for (auto& t : g->goods) {
		if (t->sit == "������") {
			g->print_good(t);
		}
	}

	cout << "*********************************************************************************" << endl << endl << endl;
}

void Buyer::buy() {
	string temp;
	int buy_number;
	cout << "��������ƷID��";
	cin >> temp;
	while (!cin) {
		cout << "��������ȷ����ƷID:" << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> temp;
	}

	for (auto& ele : g->goods) {
		if (ele->good_id == temp && ele->sit == "������") {
			cout << endl << endl << "*********************************************************************************" << endl;
			cout << "��ƷID " << "       ����   " << "       �۸�  " << "     �ϼ�ʱ��  " << " �������  " << "����ID  " << "��Ʒ״̬ " << endl;
			g->print_good(ele);
			cout << "*********************************************************************************" << endl << endl << endl;
			cout << "�����빺������: ";
			cin >> temp;
			while (!cin || temp[0] == '0' || !nvalid(temp)) {
				cout << endl << endl << " !!��Ʒ�������Ϸ����밴Ҫ������!! " << endl;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "��������Ʒ����������Ϊ����������λ����Ϊ0��: ";
				cin >> temp;
			}
			buy_number = exint(temp);
			if (ele->number < buy_number) {
				cout << endl << "������������Ʒ����������Ʒ��棬����ʧ�ܣ���" << endl;
				return;
			}
			else if (inform->balance < buy_number * ele->price) {
				cout << endl << "�����˻����㣬����ʧ�ܣ���" << endl;
				cout << "�Ƿ�Ҫ�����ֵ���棨y/n����";
				cin >> temp;
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << "��������Ʒ����������Ϊ����������λ����Ϊ0��: ";
					cin >> temp;
				}
				if (temp == "n") {
					return;
				}
				else {

				}

			}
			else {
				ele->number -= buy_number;
				g->check_good();
				inform->balance -= buy_number * ele->price;
				u->balance_change(inform->user_id, inform->balance);
				Order* paper = new Order;
				paper->good_id = ele->good_id;
				paper->money = ele->price;
				paper->number = buy_number;
				paper->buyer_id = inform->user_id;
				paper->seller_id = ele->seller_id;
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
				paper->deal_time = pt;
				paper->order_id.push_back('T');
				if (o->orders.size() == 0) {
					string st = "001";
					paper->order_id.append(st);
				}
				else if (o->orders[o->orders.size() - 1]->order_id[3] == '9') {
					if (o->orders[o->orders.size() - 1]->order_id[2] == '9') {
						if (o->orders[o->orders.size() - 1]->order_id[1] == '9') {
							cout << "���������Ѿ������ļ����أ����������˵�" << endl;
							return;
						}
						paper->order_id.push_back(o->orders[o->orders.size() - 1]->order_id[1] + 1);
						paper->order_id.push_back('0');
						paper->order_id.push_back('0');
					}
					paper->order_id.push_back(o->orders[o->orders.size() - 1]->order_id[1]);
					paper->order_id.push_back(o->orders[o->orders.size() - 1]->order_id[2] + 1);
					paper->order_id.push_back('0');
				}
				else {
					paper->order_id.push_back(o->orders[o->orders.size() - 1]->order_id[1]);
					paper->order_id.push_back(o->orders[o->orders.size() - 1]->order_id[2]);
					paper->order_id.push_back(o->orders[o->orders.size() - 1]->order_id[3] + 1);
				}
				vector<string> vals;
				vals.push_back(paper->order_id);
				vals.push_back(paper->good_id);
				vals.push_back(double_to_string(paper->money));
				vals.push_back(to_string(paper->number));
				vals.push_back(paper->deal_time);
				vals.push_back(paper->seller_id);
				vals.push_back(paper->buyer_id);
				sq->Insert(order_file_name, vals);
				vector<string> valsu;
				valsu.push_back("���� = " + to_string(ele->number));
				if (ele->sit == "���¼�") valsu.push_back("��Ʒ״̬ = ���¼�");
				sq->Update(good_file_name, "��ƷID = " + paper->good_id, valsu);
				o->orders.push_back(paper);
				cout << endl << endl << "******����ɹ�********" << endl << endl;
				o->write_order();

			}
		}
	}

}

void Buyer::search_good() {
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
		if (ele->name.find(s) != string::npos && ele->sit != "���¼�") {
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

void Buyer::look_order() {
	sq->Select(order_file_name);
	bool nfind = true;
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " ����ID " << "   ��ƷID   " << " ���׵���  " << " ����  " << "  ����ʱ��   " << " ����ID  " << " ���ID " << endl;
	for (auto& t : o->orders) {
		if (t->buyer_id == inform->user_id) {
			o->print_order(t);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "******����ʱû�ж���******" << endl;
	}

	cout << "*********************************************************************************" << endl << endl << endl;
}

void Buyer::look_good_information() {
	string s;
	cout << "����������Ҫ���ҵ���ƷID�� ";
	cin >> s;
	while (!cin) {
		cout << "��������ȷ����ƷID" << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> s;
	}
	sq->Select(good_file_name, true, "��ƷID", s);
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g->goods) {
		if (ele->name.find(s) != string::npos && ele->sit != "���¼�") {
			cout << "��ƷID��" << ele->good_id << endl << "��Ʒ���ƣ�" << ele->name << endl << "��Ʒ�۸�" << fixed << setprecision(1) << ele->price << endl \
				<< "�ϼ�ʱ�䣺" << ele->sell_time << endl << "��Ʒ������" << ele->description << endl << "��Ʒ���ң�" << ele->seller_id << endl;
			cout << "*********************************************************************************" << endl << endl << endl;
		}
	}

	cout << "û���ҵ��ؼ��������Ʒ����Ʒ���¼�,������ѡ�����" << endl;

	cout << "*********************************************************************************" << endl << endl << endl;
}