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
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
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
		else {
			t->user_id.push_back(u->users[u->users.size() - 1]->user_id[1]);
			t->user_id.push_back(u->users[u->users.size() - 1]->user_id[2] + 1);
			t->user_id.push_back('0');
		}
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
	system("cls");
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
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i)[0] < '1' || new_trim(i)[0] > '4')) {
			cout << "���벻�Ϸ�������������" << endl;
			cout << "������������: ";
			cin.clear();
			getline(cin, i);
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
	getline(cin, name);
	cout << "����������: ";
	getline(cin, key);
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

string User::make_expr() {
	vector<double> inc, o_dec, o_inc;
	map<int, string> so_dec, so_inc;
	map<int, string>::iterator it;
	for (auto& ele : r->reorders) {
		if (ele->user_id == inform->user_id) inc.push_back(ele->money);
	}
	for (auto& ele : o->orders) {
		if (ele->buyer_id == inform->user_id) {
			if (so_dec.find(ele->number) == so_dec.end()) {
				so_dec.insert(pair<int, string>(ele->number, "+" + double_to_string(ele->money)));
			}
			else {
				so_dec[ele->number].append("+" + double_to_string(ele->money));
			}
			for (int i = 0; i < ele->number; i++) {
				o_dec.push_back(ele->money);
			}
		}
	}
	for (auto& ele : o->orders) {
		if (ele->seller_id == inform->user_id) {
			if (so_inc.find(ele->number) == so_inc.end()) {
				so_inc.insert(pair<int, string>(ele->number, "+" + double_to_string(ele->money)));
			}
			else {
				so_inc[ele->number].append("+" + double_to_string(ele->money));
			}
			for (int i = 0; i < ele->number; i++) {
				o_inc.push_back(ele->money);
			}
		}
	}
	if (inc.empty() && o_dec.empty() && o_inc.empty()) {
		return "0";
	}
	string tes, stes;
	for (auto ele : inc) {
		tes.append("+" + double_to_string(ele));
		stes.append("+" + double_to_string(ele));
	}
	for (auto ele : o_dec) {
		tes.append("-" + double_to_string(ele));
	}
	for (auto ele : o_inc) {
		tes.append("+" + double_to_string(ele));
	}
	string StandardExpression = tes.substr(1);
	cout << StandardExpression << endl;
	for (auto ele : so_dec) {
		if (ele.first == 1) {
			stes.append("-" + ele.second.substr(1));
		}
		else {
			if (side_count(ele.second)) {
				stes.append("-" + to_string(ele.first) + "*(" + ele.second.substr(1) + ")");
			}
			else {
				stes.append("-" + to_string(ele.first) + "*" + ele.second.substr(1));
			}
		}

	}
	for (auto ele : so_inc) {
		if (ele.first == 1) {
			stes.append("+" + ele.second.substr(1));
		}
		else {
			if (side_count(ele.second)) {
				stes.append("+" + to_string(ele.first) + "*(" + ele.second.substr(1) + ")");
			}
			else {
				stes.append("+" + to_string(ele.first) + "*" + ele.second.substr(1));
			}
		}

	}
	string SimplyExpression = stes.substr(1);
	cout << SimplyExpression << endl;
	return SimplyExpression;
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
		cin.clear(); i.clear();
		getline(cin, i);
		while (!cin || new_trim(i)[0] < '1' || new_trim(i)[0] > '4') {
			cout << "���벻�Ϸ�������������" << endl;
			cout << "������������: ";
			cin.clear();
			getline(cin, i);
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
	cin.clear(); i.clear();
	getline(cin, i);
	while (!cin || (new_trim(i)[0] < '1' || new_trim(i)[0] > '3')) {
		cout << "���벻�Ϸ�������������" << endl;
		cout << "��ѡ���޸ĵ����ԣ�1���û��� 2����ϵ��ʽ 3����ַ��: ";
		cin.clear();
		getline(cin, i);
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
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		for (auto& ele : u->users) {
			if (ele->user_name == temp) {
				system("cls");
				cout << endl << "******���û����Ѵ��ڣ�������ѡ�����******" << endl << endl;
				return;
			}
		}
		inform->user_name = temp;
		vector<string> valus;
		valus.push_back("�û��� = " + temp);
		sq->Update(user_file_name, "�û�ID = " + inform->user_id, valus);
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
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		inform->con = temp;
		vector<string> valus;
		valus.push_back("��ϵ��ʽ = " + temp);
		sq->Update(user_file_name, "�û�ID = " + inform->user_id, valus);
		u->write_user();
		cout << endl << "******�޸ĳɹ�******" << endl;
		break;
	}
	case 3: {
		string temp;
		cout << "���������ĵ�ַ��������40���ַ���ֻ��������ɣ�: ";
		cin >> temp;
		wstring ctemp = s_to_ws(temp);
		while (!cin || ctemp.size() > 40 || !cevalid(ctemp)) {
			cout << endl << endl << " !!��ַ���Ϸ����밴Ҫ������!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "���������ĵ�ַ��������40���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
			cin >> temp;
			ctemp = s_to_ws(temp);
		}
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		inform->address = temp;
		vector<string> valus;
		valus.push_back("��ַ = " + temp);
		sq->Update(user_file_name, "�û�ID = " + inform->user_id, valus);
		u->write_user();
		cout << endl << "******�޸ĳɹ�******" << endl;
		break;
	}
	default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
	}
}

void User::look_information() {
	string balance = calculator_menu(make_expr());

	cout << endl << endl << "*********************************************************************************" << endl;

	for (auto& ele : u->users) {
		if (ele->user_id == inform->user_id) {
			//cout << "�û�����" << ele->user_name << endl << "��ϵ��ʽ��" << ele->con << endl << "��ַ��" << ele->address << endl << "Ǯ����" << fixed << setprecision(1) << ele->balance << endl;
			cout << "�û�����" << ele->user_name << endl << "��ϵ��ʽ��" << ele->con << endl << "��ַ��" << ele->address << endl << "Ǯ����" << balance << endl;
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
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
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
		i.clear();
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "��������ȷ������" << endl;
			cin.clear();
			getline(cin, i);
		}
		switch (int(trim(i)[0] - '0')) {
		case 1:release(); break;
		case 2:look_good(); break;
		case 3:change_information(); break;
		case 4:del_good(); break;
		case 5:look_order(); break;
		case 6:system("cls"); return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}

void Seller::release() {
	Good* t = new Good;
	cout << "��������Ʒ���ƣ�������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	string temp, desc;
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
	cin.clear();
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, desc);
	ctemp = s_to_ws(desc);
	while (!cin || ctemp.size() > 20) {
		if (ctemp.size() > 20) {
			cout << endl << endl << " !!�������ȳ����ַ����ƣ��밴Ҫ������!! " << endl;
		}
		else {
			cout << endl << endl << " !!��Ʒ�������Ϸ����밴Ҫ������!! " << endl;
		}
		cin.clear();
		cout << "��������Ʒ������������100���ַ���: ";
		getline(cin, desc);
		ctemp = s_to_ws(desc);
	}
	t->description = desc;
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
		else {
			t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[1]);
			t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[2] + 1);
			t->good_id.push_back('0');
		}
	}
	else {
		t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[1]);
		t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[2]);
		t->good_id.push_back(g->goods[g->goods.size() - 1]->good_id[3] + 1);
	}
	cout << endl << endl << "��ȷ�Ϸ�����Ʒ����" << endl << "*********************************************************************************" << endl;
	cout << "��Ʒ���ƣ�" << t->name << endl << "��Ʒ�۸�" << t->price << endl << "��Ʒ������" << t->number << endl << "��Ʒ������" << t->description << endl;
	cout << "*********************************************************************************" << endl << endl << endl << "��ȷ��Ҫ������Ʒ�𣿣�y/n)";
	string chos;
	getline(cin, chos);
	while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
		cout << "�밴Ҫ������" << endl;
		cout << "��ȷ��Ҫ������Ʒ�� (y/n): ";
		cin.clear();
		getline(cin, chos);
	}
	if (trim(chos) == "n") {
		system("cls");
		cout << endl << "����ȡ����������ѡ�����Ĳ���" << endl << endl;
		return;
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
	string temp, desc;
	temp.clear();
	cin.clear();
	getline(cin, temp);
	double new_price;
	string new_description;
	while (!cin) {
		cout << endl << endl << " !!��ƷID���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cout << endl << endl << "�����뱻�޸ĵ���ƷID: ";
		getline(cin, temp);
	}
	for (auto& ele : g->goods) {
		if (ele->good_id == temp) {
			if (ele->seller_id != inform->user_id) {
				system("cls");
				cout << ele->seller_id << endl;
				cout << endl << "!!����Ʒ��������������Ȩ�Դ���Ʒ���в�������" << endl;
				return;
			}
			cout << "�����뱻�޸ĵ���Ʒ���ԣ�1���۸� 2��������: ";
			temp.clear();
			cin.clear();
			getline(cin, temp);
			while ((new_trim(temp) != "1" && new_trim(temp) != "2")) {
				cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
				cin.clear();
				cout << endl << endl << "�����뱻�޸ĵ���Ʒ���ԣ�1���۸� 2��������: ";
				getline(cin, temp);
			}
			switch (int(new_trim(temp)[0] - '0')) {
			case 1: {
				cout << "��������Ʒ�۸�ϵͳ��Ϊ������һλС��������ȥ����С��!!��: ";
				temp.clear();
				cin.clear();
				getline(cin, temp);
				while (!cin || dnvalid(temp)) {
					cout << endl << endl << " !!��Ʒ�۸񲻺Ϸ����밴Ҫ������!! " << endl;
					cin.clear();
					cout << "�������µ���Ʒ�۸�ϵͳ���Զ�Ϊ������һλС����: ";
					getline(cin, temp);
				}
				new_price = exdouble(temp);
				cout << "��ȷ����Ʒ�޸ĵ���Ʒ��Ϣ����" << endl;
				cout << "********************************************************************" << endl;
				cout << "��ƷID��" << ele->good_id << endl << "��Ʒ���ƣ�" << ele->name << endl << "��Ʒ�۸�" << fixed << setprecision(1) << new_price << endl << "��Ʒ������" << ele->description << endl;
				cout << "********************************************************************" << endl;
				cout << "�Ƿ�ȷ���޸ģ�(y/n)��";
				temp.clear();
				cin.clear();
				getline(cin, temp);
				while ((new_trim(temp) != "y" && new_trim(temp) != "n")) {
					cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
					temp.clear();
					cin.clear();
					cout << endl << endl << "�Ƿ�ȷ���޸ģ�(y/n)��";
					getline(cin, temp);
				}
				if (new_trim(temp) == "y") {
					vector<string> valsu;
					valsu.push_back("�۸� = " + to_string(ele->price));
					sq->Update(good_file, "��ƷID = " + ele->good_id, valsu);
					ele->price = new_price;
					g->write_good();
					system("cls");
					cout << endl << "**************�޸ĳɹ�*************" << endl << endl;
				}
				else {
					system("cls");
					cout << endl << "*****************�޸�ȡ����������ѡ�����****************" << endl << endl;
					return;
				}
				break;
			}
			case 2: {
				wstring ctemp;
				cout << "��������Ʒ�µ�������������100���ַ���: ";
				cin.clear();
				getline(cin, desc);
				ctemp = s_to_ws(desc);
				while (!cin || ctemp.size() > 100) {
					if (ctemp.size() > 100) {
						cout << endl << endl << " !!�������ȳ����ַ����ƣ��밴Ҫ������!! " << endl;
					}
					else {
						cout << endl << endl << " !!��Ʒ�������Ϸ����밴Ҫ������!! " << endl;
					}
					cin.clear();
					cout << "��������Ʒ�µ�������������100���ַ���: ";
					getline(cin, desc);
					ctemp = s_to_ws(desc);
				}
				new_description = desc;
				cout << "��ȷ����Ʒ�޸ĵ���Ʒ��Ϣ����" << endl;
				cout << "********************************************************************" << endl;
				cout << "��ƷID��" << ele->good_id << endl << "��Ʒ���ƣ�" << ele->name << endl << "��Ʒ�۸�" << ele->price << endl << "��Ʒ������" << new_description << endl;
				cout << "********************************************************************" << endl;
				cout << "�Ƿ�ȷ���޸ģ�(y/n)��";
				temp.clear();
				cin.clear();
				getline(cin, temp);
				while ((new_trim(temp) != "y" && new_trim(temp) != "n")) {
					cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
					temp.clear();
					cin.clear();
					cout << endl << endl << "�Ƿ�ȷ���޸ģ�(y/n)��";
					getline(cin, temp);
				}
				if (new_trim(temp) == "y") {
					vector<string> valsu;
					ele->description = new_description;
					valsu.push_back("��Ʒ���� = " + ele->description);
					sq->Update(good_file_name, "��ƷID = " + ele->good_id, valsu);
					g->write_good();
					system("cls");
					cout << endl << "**************�޸ĳɹ�*************" << endl << endl;
				}
				else {
					system("cls");
					cout << endl << "*****************�޸�ȡ����������ѡ�����****************" << endl << endl;
					return;
				}
				break;
			}
			default:cout << "������ִ���" << endl; break;
			}
			return;
		}

	}
	cout << endl << "**************û���ҵ�����Ʒ��ţ�����������*********************" << endl << endl;
}

void Seller::del_good() {
	cout << endl << "����������Ҫ�¼ܵ���ƷID�� ";
	string i, chos;
	i.clear(); cin.clear();
	getline(cin, i);
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
		cin.clear(); chos.clear();
		getline(cin, chos);
		while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
			cout << "�밴Ҫ������" << endl;
			cout << "�Ƿ񽫸���Ʒ�¼�(y/n): ";
			cin.clear();
			getline(cin, chos);
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
	cout << "����ID " << " ��ƷID   " << " ���׵���  " << " ����  " << "  ����ʱ��   " << " ����ID  " << " ���ID " << endl;
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
		i.clear();
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "��������ȷ��ѡ��" << endl;
			cin.clear();
			getline(cin, i);
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
	string temp, num_temp;
	int buy_number;
	cout << "��������ƷID��";
	cin.clear(); temp.clear();
	getline(cin, temp);
	while (!cin) {
		cout << "��������ȷ����ƷID:" << endl;
		cin.clear();
		getline(cin, temp);
	}

	for (auto& ele : g->goods) {
		if (ele->good_id == temp && ele->sit == "������") {
			cout << endl << endl << "*********************************************************************************" << endl;
			cout << "��ƷID " << "       ����   " << "       �۸�  " << "     �ϼ�ʱ��  " << " �������  " << "����ID  " << "��Ʒ״̬ " << endl;
			g->print_good(ele);
			cout << "*********************************************************************************" << endl << endl << endl;
			cout << "�����빺������: ";
			temp.clear(); cin.clear();
			getline(cin, temp);
			num_temp = trim(temp);
			while (!cin || num_temp[0] == '0' || !nvalid(num_temp)) {
				cout << endl << endl << " !!��Ʒ�������Ϸ����밴Ҫ������!! " << endl;
				cin.clear();
				cout << "��������Ʒ����������Ϊ����������λ����Ϊ0��: ";
				getline(cin, temp);
				num_temp = trim(temp);
			}
			buy_number = exint(num_temp);
			if (ele->number < buy_number) {
				cout << endl << "������������Ʒ����������Ʒ��棬����ʧ�ܣ���" << endl;
				return;
			}
			else if (inform->balance < buy_number * ele->price) {
				cout << endl << "�����˻����㣬����ʧ�ܣ���" << endl;
				cout << "�Ƿ�Ҫ�����ֵ���棨y/n����";
				temp.clear(); cin.clear();
				getline(cin, temp);
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
					cin.clear();
					cout << "�Ƿ�Ҫ�����ֵ���棨y/n���� ";
					getline(cin, temp);
				}
				if (trim(temp) == "n") {
					system("cls");
					return;
				}
				else {
					system("cls");
					recharge();
					return;
				}

			}
			else {
				ele->number -= buy_number;
				g->check_good();
				inform->balance -= buy_number * ele->price;
				for (auto& seller : u->users) {
					if (seller->user_id == ele->seller_id) {
						seller->balance += buy_number * ele->price;
						u->write_user();
					}
				}
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
					else {
						paper->order_id.push_back(o->orders[o->orders.size() - 1]->order_id[1]);
						paper->order_id.push_back(o->orders[o->orders.size() - 1]->order_id[2] + 1);
						paper->order_id.push_back('0');
					}
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
				cout << endl << endl << "******����ɹ�********" << endl;
				o->write_order();
				cout << "**************************" << endl << "!!��������!!" << endl << "����ʱ�䣺" << paper->deal_time << endl << "���׵��ۣ�" << paper->money << endl \
					<< "����������" << paper->number << endl << "����״̬�����׳ɹ�" << endl << "������" << inform->balance << endl << "**************************" << endl << endl;
				return;
			}
		}
	}
	system("cls");
	cout << endl << "***********û���ҵ�����Ҫ����Ʒ�����Ʒ���¼�**********" << endl << endl;

}

void Buyer::search_good() {
	string s;
	cout << "����������Ҫ���ҵ���Ʒ�� ";
	s.clear(); cin.clear();
	getline(cin, s);
	while (!cin) {
		cout << "��������ȷ����Ʒ����" << endl;
		cin.clear();
		getline(cin, s);
	}
	sq->Select(good_file_name, true, "����", s);
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "��ƷID " << "       ����   " << "       �۸�  " << "     �ϼ�ʱ��  " << " �������  " << "����ID  " << "��Ʒ״̬ " << endl;
	bool nfind = true;
	for (auto& ele : g->goods) {
		if (ele->name.find(trim(s)) != string::npos && ele->sit != "���¼�") {
			g->print_good(ele);
			nfind = false;
		}
	}
	if (nfind) {
		cout << endl << endl << "û���ҵ��ؼ��������Ʒ,������ѡ�����" << endl << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Buyer::look_order() {
	sq->Select(order_file_name);
	bool nfind = true;
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "����ID " << " ��ƷID   " << " ���׵���  " << " ����  " << "  ����ʱ��   " << " ����ID  " << " ���ID " << endl;
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
	cin.clear();
	s.clear();
	getline(cin, s);
	while (!cin) {
		cout << "��������ȷ����ƷID" << endl;
		cin.clear();
		getline(cin, s);
	}
	sq->Select(good_file_name, true, "��ƷID", s);
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g->goods) {
		if (ele->good_id == s && ele->sit != "���¼�") {
			cout << "��ƷID��" << ele->good_id << endl << "��Ʒ���ƣ�" << ele->name << endl << "��Ʒ�۸�" << fixed << setprecision(1) << ele->price << endl \
				<< "�ϼ�ʱ�䣺" << ele->sell_time << endl << "��Ʒ������" << ele->description << endl << "��Ʒ���ң�" << ele->seller_id << endl;
			cout << "*********************************************************************************" << endl << endl << endl;
			return;
		}
	}

	cout << "û���ҵ��ؼ��������Ʒ����Ʒ���¼�,������ѡ�����" << endl;

	cout << "*********************************************************************************" << endl << endl << endl;
}