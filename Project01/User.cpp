#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "User.h"
#include "sundry.h"
#include"Item.h"
#include<regex>
using namespace std;

void User::user_register() {
	User_information* t = new User_information;
	cout << "请输入您的用户名（不超过10个字符，中文汉字或英文字母）: ";
	string temp;
	cin >> temp;
	wstring ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 10 || !cevalid(ctemp)) {
		cout << endl << endl << " !!用户名不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入您的用户名（不超过10个字符，中文汉字或英文字母）: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	for (auto& ele : u->users) {
		if (ele->user_name == temp) {
			system("cls");
			cout << endl << "******该用户名已存在，请重新选择操作******" << endl << endl;
			return;
		}
	}
	t->user_name = temp;
	cout << "请输入您的密码（不超过20个字符，只由小写字母和数字组成）: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nevalid(temp)) {
		cout << endl << endl << " !!密码不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入您的密码（不超过20个字符，只由小写字母和数字组成）: ";
		cin >> temp;
	}
	t->key = temp;
	cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
	cin >> temp;
	while (!cin || temp.size() > 20 || !nvalid(temp)) {
		cout << endl << endl << " !!联系方式不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
		cin >> temp;
	}
	t->con = temp;
	cout << "请输入您的地址（不超过40个字符，中文汉字或英文字母）: ";
	cin >> temp;
	ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 40 || !cevalid(ctemp)) {
		cout << endl << endl << " !!地址不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入您的地址（不超过40个字符，中文汉字或英文字母）: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	t->address = temp;
	t->balance = 0;
	t->sit = "正常";
	t->user_id.push_back('U');
	if (u->users.size() == 0) {
		string st = "001";
		t->user_id.append(st);
	}
	else {
		string bh = u->users[u->users.size() - 1]->user_id.substr(1);
		if (bh == "999") {
			cout << "用户数量已经超过文件承载，将返回主菜单" << endl;
			return;
		}
		t->user_id.append(str_add(bh));
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
	cout << endl << endl << "******注册成功********" << endl << endl;
	u->write_user();
}

void User::user_menu(User_information* information) {
	system("cls");
	while (true) {
		cout << "Welcome! user" << endl;
		cout << "=================================================================================" << endl;
		cout << "  1、我是买家 2、我是卖家 3、个人信息管理 4、留言菜单 5、注销登录  " << endl;
		cout << "=================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i)[0] < '1' || new_trim(i)[0] > '5')) {
			cout << "输入不合法，请重新输入" << endl;
			cout << "请输入操作序号: ";
			cin.clear();
			getline(cin, i);
		}
		switch (int(trim(i)[0] - '0')) {
		case 1: {
			User* er = new User(u, o, g, r, sq);
			((Buyer*)er)->inform = information;
			((Buyer*)er)->buyer_menu();
			delete er;
			break;
		}
		case 2: {
			User* er = new User(u, o, g, r, sq);
			((Seller*)er)->inform = information;
			((Seller*)er)->seller_menu();
			delete er;
			break;
		}
		case 3:gover_inform(); break;
		case 4:message_menu(); break;
		case 5:system("cls"); return; break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}

void User::user_login() {
	system("cls");
	string name, key;
	cout << "请输入用户名: ";
	getline(cin, name);
	cout << "请输入密码: ";
	getline(cin, key);
	for (auto& ele : u->users) {
		if (ele->user_name == name) {
			if (ele->key == key) {
				if (ele->sit == "封禁") {
					system("cls");
					cout << endl << endl << "------您的账户已被封禁，即将返回主菜单------" << endl << endl << endl;
					return;
				}
				cout << endl << endl << "------登录成功，欢迎您------" << endl << endl;
				inform = ele;
				prm = new PrMessageStore(inform->user_id);
				user_menu(ele);
				return;
			}
			else {
				system("cls");
				cout << endl << endl << "------用户名或密码错误，即将返回主菜单------" << endl << endl << endl;
				return;
			}
		}
	}
	system("cls");
	cout << endl << endl << "------用户名或密码错误，即将返回主菜单------" << endl << endl << endl;
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
			stes.append("-(" + ele.second.substr(1) + ")");
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
		cout << "  1、查看信息 2、修改信息 3、充值 4、返回用户主界面  " << endl;
		cout << "=================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		cin.clear(); i.clear();
		getline(cin, i);
		while (!cin || new_trim(i)[0] < '1' || new_trim(i)[0] > '4') {
			cout << "输入不合法，请重新输入" << endl;
			cout << "请输入操作序号: ";
			cin.clear();
			getline(cin, i);
		}
		switch (int(trim(i)[0] - '0')) {
		case 1: look_information(); break;
		case 2: change_information(); break;
		case 3:recharge(); break;
		case 4:system("cls"); return; break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}

void User::change_information() {
	cout << "请选择修改的属性（1、用户名 2、联系方式 3、地址 4、密码）: ";
	string i;
	cin.clear(); i.clear();
	getline(cin, i);
	while (!cin || (new_trim(i)[0] < '1' || new_trim(i)[0] > '4')) {
		cout << "输入不合法，请重新输入" << endl;
		cout << "请选择修改的属性（1、用户名 2、联系方式 3、地址 4、密码）: ";
		cin.clear();
		getline(cin, i);
	}
	switch (int(trim(i)[0] - '0')) {
	case 1: {
		cout << "请输入您的用户名（不超过10个字符，中文汉字或英文字母）: ";
		string temp; temp.clear();
		cin >> temp;
		wstring ctemp = s_to_ws(temp);
		while (!cin || ctemp.size() > 10 || !cevalid(ctemp)) {
			cout << endl << endl << " !!用户名不合法，请按要求输入!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "请输入您的用户名（不超过10个字符，中文汉字或英文字母）: ";
			cin >> temp;
			ctemp = s_to_ws(temp);
		}
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		for (auto& ele : u->users) {
			if (ele->user_name == temp) {
				system("cls");
				cout << endl << "******该用户名已存在，请重新选择操作******" << endl << endl;
				return;
			}
		}
		inform->user_name = temp;
		vector<string> valus;
		valus.push_back("用户名 = " + temp);
		sq->Update(user_file_name, "用户ID = " + inform->user_id, valus);
		u->write_user();
		cout << endl << "******修改成功******" << endl;
		break;
	}
	case 2: {
		string temp; temp.clear();
		cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
		cin >> temp;
		while (!cin || temp.size() > 20 || !nvalid(temp)) {
			cout << endl << endl << " !!联系方式不合法，请按要求输入!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
			cin >> temp;
		}
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		inform->con = temp;
		vector<string> valus;
		valus.push_back("联系方式 = " + temp);
		sq->Update(user_file_name, "用户ID = " + inform->user_id, valus);
		u->write_user();
		cout << endl << "******修改成功******" << endl;
		break;
	}
	case 3: {
		string temp; temp.clear();
		cout << "请输入您的地址（不超过40个字符，只由数字组成）: ";
		cin >> temp;
		wstring ctemp = s_to_ws(temp);
		while (!cin || ctemp.size() > 40 || !cevalid(ctemp)) {
			cout << endl << endl << " !!地址不合法，请按要求输入!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "请输入您的地址（不超过40个字符，中文汉字或英文字母）: ";
			cin >> temp;
			ctemp = s_to_ws(temp);
		}
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		inform->address = temp;
		vector<string> valus;
		valus.push_back("地址 = " + temp);
		sq->Update(user_file_name, "用户ID = " + inform->user_id, valus);
		u->write_user();
		cout << endl << "******修改成功******" << endl;
		break;
	}
	case 4: {
		string temp; temp.clear();
		cout << "请输入您的密码（不超过20个字符，只由小写字母和数字组成）: ";
		cin >> temp;
		while (!cin || temp.size() > 20 || !nevalid(temp)) {
			cout << endl << endl << " !!密码不合法，请按要求输入!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "请输入您的密码（不超过20个字符，只由小写字母和数字组成）: ";
			cin >> temp;
		}
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		inform->key = temp;
		vector<string> valus;
		valus.push_back("密码 = " + temp);
		sq->Update(user_file_name, "用户ID = " + inform->user_id, valus);
		u->write_user();
		cout << endl << "******修改成功******" << endl;
		break;
	}
	default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
	}
}

void User::look_information() {
	string balance = calculator_menu(make_expr());

	cout << endl << endl << "*********************************************************************************" << endl;

	for (auto& ele : u->users) {
		if (ele->user_id == inform->user_id) {
			//cout << "用户名：" << ele->user_name << endl << "联系方式：" << ele->con << endl << "地址：" << ele->address << endl << "钱包余额：" << fixed << setprecision(1) << ele->balance << endl;
			cout << "用户名：" << ele->user_name << endl << "联系方式：" << ele->con << endl << "地址：" << ele->address << endl << "钱包余额：" << balance << endl;
			cout << "*********************************************************************************" << endl << endl << endl;
		}
	}
}

void User::recharge() {
	string temp;
	cout << "请输入充值金额（系统将为您保留一位小数，即舍去后续小数）: ";
	cin >> temp;
	while (!cin || dnvalid(temp)) {
		cout << endl << endl << " !!商品价格不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入充值金额（系统将自动为您保留一位小数）: ";
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
	cout << endl << endl << "**************充值成功**************" << endl << endl << endl;
}

void User::message_menu() {
	system("cls");
	while (true) {
		cout << "Welcome to messagebox" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1、发送留言 2、查看发件箱 3、查看收件箱 4、查看留言详情 5、删除留言 6、返回用户主界面  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		i.clear();
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "请输入正确的选项" << endl;
			cin.clear();
			getline(cin, i);
		}
		switch (int(trim(i)[0] - '0')) {
		case 1: prm->Send(); break;
		case 2: prm->Looksend(); break;
		case 3: prm->Lookrecieve(); break;
		case 4: prm->Lookmessage(); break;
		case 5: del_message_menu(); break;
		case 6:system("cls"); return; break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}

void User::del_message_menu() {
	system("cls");
	while (true) {
		cout << "please look out the message you want to delete" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1、清空已读留言 2、清空收件箱 3、清空发件箱 4、删除指定留言 5、返回用户主界面  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		i.clear();
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "5")) {
			cout << "请输入正确的选项" << endl;
			cin.clear();
			getline(cin, i);
		}
		switch (int(trim(i)[0] - '0')) {
		case 1: prm->DelReadedMessage(); break;
		case 2: prm->DelAllMessage(); break;
		case 3: prm->DelAllSend(); break;
		case 4: prm->DelSingleMessage(); break;
		case 5:system("cls"); return; break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}

void Seller::seller_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! seller" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1、发布商品 2、查看发布商品 3、修改商品信息 4、下架商品 5、查看历史订单 6、返回用户主界面  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		i.clear();
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "请输入正确的数字" << endl;
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
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}

void Seller::release() {
	Good* t = new Good;
	cout << "请输入商品名称（不超过20个字符，中文汉字或英文字母）: ";
	string temp, desc;
	cin >> temp;
	wstring ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 20 || !cevalid(ctemp)) {
		cout << endl << endl << " !!商品名称不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入商品名称（不超过20个字符，中文汉字或英文字母）: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->name = temp;
	cout << "请输入商品价格（系统将为您保留一位小数，即舍去后续小数）: ";
	cin >> temp;
	while (!cin || dnvalid(temp)) {
		cout << endl << endl << " !!商品价格不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入商品价格（系统将自动为您保留一位小数）: ";
		cin >> temp;
	}
	t->price = exdouble(temp);
	cout << "请输入商品数量（数量为正整数且首位不能为0）: ";
	cin >> temp;
	while (!cin || temp[0] == '0' || !nvalid(temp)) {
		cout << endl << endl << " !!商品数量不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入商品数量（数量为正整数且首位不能为0）: ";
		cin >> temp;
	}
	t->number = exint(temp);
	cout << "请输入商品描述（不超过100个字符）: ";
	cin.clear();
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, desc);
	ctemp = s_to_ws(desc);
	while (!cin || ctemp.size() > 20) {
		if (ctemp.size() > 20) {
			cout << endl << endl << " !!描述长度超过字符限制，请按要求输入!! " << endl;
		}
		else {
			cout << endl << endl << " !!商品描述不合法，请按要求输入!! " << endl;
		}
		cin.clear();
		cout << "请输入商品描述（不超过100个字符）: ";
		getline(cin, desc);
		ctemp = s_to_ws(desc);
	}
	t->description = desc;
	t->seller_id = inform->user_id;
	t->sit = "销售中";
	t->good_id.push_back('M');
	if (g->goods.size() == 0) {
		string st = "001";
		t->good_id.append(st);
	}
	else {
		string bh = g->goods[g->goods.size() - 1]->good_id.substr(1);
		if (bh == "999") {
			cout << "商品数量已经超过文件承载，将返回主菜单" << endl;
			return;
		}
		t->good_id.append(str_add(bh));
	}
	cout << endl << endl << "请确认发布商品无误" << endl << "*********************************************************************************" << endl;
	cout << "商品名称：" << t->name << endl << "商品价格：" << t->price << endl << "商品数量：" << t->number << endl << "商品描述：" << t->description << endl;
	cout << "*********************************************************************************" << endl << endl << endl << "请确认要发布商品吗？（y/n)";
	string chos;
	getline(cin, chos);
	while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
		cout << "请按要求输入" << endl;
		cout << "请确认要发布商品吗？ (y/n): ";
		cin.clear();
		getline(cin, chos);
	}
	if (trim(chos) == "n") {
		system("cls");
		cout << endl << "发布取消，请重新选择您的操作" << endl << endl;
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
	cout << endl << endl << "******发布成功********" << endl << endl;
	g->write_good();
}

void Seller::change_information() {
	cout << endl << endl << "请输入被修改的商品ID: ";
	string temp, desc;
	temp.clear();
	cin.clear();
	getline(cin, temp);
	double new_price;
	string new_description;
	while (!cin) {
		cout << endl << endl << " !!商品ID不合法，请按要求输入!! " << endl;
		cin.clear();
		cout << endl << endl << "请输入被修改的商品ID: ";
		getline(cin, temp);
	}
	for (auto& ele : g->goods) {
		if (ele->good_id == temp) {
			if (ele->seller_id != inform->user_id) {
				system("cls");
				cout << ele->seller_id << endl;
				cout << endl << "!!此商品不属于您，您无权对此商品进行操作！！" << endl;
				return;
			}
			cout << "请输入被修改的商品属性（1、价格 2、描述）: ";
			temp.clear();
			cin.clear();
			getline(cin, temp);
			while ((new_trim(temp) != "1" && new_trim(temp) != "2")) {
				cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
				cin.clear();
				cout << endl << endl << "请输入被修改的商品属性（1、价格 2、描述）: ";
				getline(cin, temp);
			}
			switch (int(new_trim(temp)[0] - '0')) {
			case 1: {
				cout << "请输入商品价格（系统将为您保留一位小数，即舍去后续小数!!）: ";
				temp.clear();
				cin.clear();
				getline(cin, temp);
				while (!cin || dnvalid(temp)) {
					cout << endl << endl << " !!商品价格不合法，请按要求输入!! " << endl;
					cin.clear();
					cout << "请输入新的商品价格（系统将自动为您保留一位小数）: ";
					getline(cin, temp);
				}
				new_price = exdouble(temp);
				cout << "请确定商品修改的商品信息无误！" << endl;
				cout << "********************************************************************" << endl;
				cout << "商品ID：" << ele->good_id << endl << "商品名称：" << ele->name << endl << "商品价格：" << fixed << setprecision(1) << new_price << endl << "商品描述：" << ele->description << endl;
				cout << "********************************************************************" << endl;
				cout << "是否确认修改？(y/n)：";
				temp.clear();
				cin.clear();
				getline(cin, temp);
				while ((new_trim(temp) != "y" && new_trim(temp) != "n")) {
					cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
					temp.clear();
					cin.clear();
					cout << endl << endl << "是否确认修改？(y/n)：";
					getline(cin, temp);
				}
				if (new_trim(temp) == "y") {
					vector<string> valsu;
					valsu.push_back("价格 = " + to_string(ele->price));
					sq->Update(good_file, "商品ID = " + ele->good_id, valsu);
					ele->price = new_price;
					g->write_good();
					system("cls");
					cout << endl << "**************修改成功*************" << endl << endl;
				}
				else {
					system("cls");
					cout << endl << "*****************修改取消，请重新选择操作****************" << endl << endl;
					return;
				}
				break;
			}
			case 2: {
				wstring ctemp;
				cout << "请输入商品新的描述（不超过100个字符）: ";
				cin.clear();
				getline(cin, desc);
				ctemp = s_to_ws(desc);
				while (!cin || ctemp.size() > 100) {
					if (ctemp.size() > 100) {
						cout << endl << endl << " !!描述长度超过字符限制，请按要求输入!! " << endl;
					}
					else {
						cout << endl << endl << " !!商品描述不合法，请按要求输入!! " << endl;
					}
					cin.clear();
					cout << "请输入商品新的描述（不超过100个字符）: ";
					getline(cin, desc);
					ctemp = s_to_ws(desc);
				}
				new_description = desc;
				cout << "请确定商品修改的商品信息无误！" << endl;
				cout << "********************************************************************" << endl;
				cout << "商品ID：" << ele->good_id << endl << "商品名称：" << ele->name << endl << "商品价格：" << ele->price << endl << "商品描述：" << new_description << endl;
				cout << "********************************************************************" << endl;
				cout << "是否确认修改？(y/n)：";
				temp.clear();
				cin.clear();
				getline(cin, temp);
				while ((new_trim(temp) != "y" && new_trim(temp) != "n")) {
					cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
					temp.clear();
					cin.clear();
					cout << endl << endl << "是否确认修改？(y/n)：";
					getline(cin, temp);
				}
				if (new_trim(temp) == "y") {
					vector<string> valsu;
					ele->description = new_description;
					valsu.push_back("商品描述 = " + ele->description);
					sq->Update(good_file_name, "商品ID = " + ele->good_id, valsu);
					g->write_good();
					system("cls");
					cout << endl << "**************修改成功*************" << endl << endl;
				}
				else {
					system("cls");
					cout << endl << "*****************修改取消，请重新选择操作****************" << endl << endl;
					return;
				}
				break;
			}
			default:cout << "程序出现错误" << endl; break;
			}
			return;
		}

	}
	cout << endl << "**************没有找到该商品编号，或输入有误*********************" << endl << endl;
}

void Seller::del_good() {
	cout << endl << "请输入您想要下架的商品ID： ";
	string i, chos;
	i.clear(); cin.clear();
	getline(cin, i);
	cout << endl << endl << "*********************************************************************************" << endl;
	int nfind = 0;
	Good* de = new Good;
	for (auto& ele : g->goods) {
		if (ele->good_id == i) {
			if (ele->seller_id != inform->user_id) {
				cout << endl << "!!此商品不属于您，您无权对此商品进行操作!！" << endl;
				return;
			}
			cout << "商品ID " << "       名称   " << "       价格  " << "     上架时间  " << " 库存数量  " << "卖家ID  " << "商品状态 " << endl;
			g->print_good(ele);
			if (ele->sit == "已下架") {
				nfind = 1;
				cout << "该商品已下架，请重新选择操作" << endl;
				break;
			}
			else { nfind = 2; de = ele; break; }
		}
	}
	if (nfind == 0) {
		cout << "没有搜索到您想要下架的商品，请重新选择操作" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
	if (nfind == 2) {
		cout << "是否将该商品下架(y/n): ";
		cin.clear(); chos.clear();
		getline(cin, chos);
		while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
			cout << "请按要求输入" << endl;
			cout << "是否将该商品下架(y/n): ";
			cin.clear();
			getline(cin, chos);
		}
		if (trim(chos) == "y") {
			vector<string> valsu;
			valsu.push_back("商品状态 = 已下架");
			sq->Update(good_file_name, "商品ID = " + de->good_id, valsu);
			de->sit = "已下架";
			g->write_good();
			cout << "下架成功！" << endl << endl;
		}
		else if (trim(chos) == "n") {
			cout << "下架取消，请重新选择您的操作" << endl << endl;
		}
	}
}

void Seller::look_order() {
	sq->Select(order_file_name);
	bool nfind = true;
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "订单ID " << " 商品ID   " << " 交易单价  " << " 数量  " << "  交易时间   " << " 卖家ID  " << " 买家ID " << endl;
	for (auto& t : o->orders) {
		if (t->seller_id == inform->user_id) {
			o->print_order(t);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "******您暂时没有订单******" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Seller::look_good() {
	sq->Select(good_file_name);
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "商品ID " << "       名称   " << "       价格  " << "     上架时间  " << " 库存数量  " << "卖家ID  " << "商品状态 " << endl;
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
		cout << "Welcome! buyer" << endl;
		cout << "================================================================================================================" << endl;
		cout << "  1、查看商品列表 2、购买商品 3、搜索商品 4、查看历史订单 5、查看商品详细信息 6、查看购物车 7、返回用户主界面  " << endl;
		cout << "================================================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		i.clear();
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "7")) {
			cout << "请输入正确的选项" << endl;
			cin.clear();
			getline(cin, i);
		}
		switch (int(trim(i)[0] - '0')) {
		case 1:look_good(); break;
		case 2:buy(); break;
		case 3:search_good(); break;
		case 4:look_order(); break;
		case 5:look_good_information(); break;
		case 6:TtroBuyMenu(); break;
		case 7:system("cls"); return; break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}

void Buyer::look_good() {
	sq->Select(good_file_name);
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "商品ID " << "       名称   " << "       价格  " << "     上架时间  " << " 库存数量  " << "卖家ID  " << "商品状态 " << endl;
	for (auto& t : g->goods) {
		if (t->sit == "销售中") {
			g->print_good(t);
		}
	}

	cout << "*********************************************************************************" << endl << endl << endl;
}

bool Buyer::buy(string _good_id, int num) {
	string temp, num_temp;
	int buy_number;
	if (_good_id == "-1") {
		cout << "请输入商品ID：";
		cin.clear(); temp.clear();
		getline(cin, temp);
		while (!cin) {
			cout << "请输入正确的商品ID:" << endl;
			cin.clear();
			getline(cin, temp);
		}
	}
	else { temp = _good_id; }
	for (auto& ele : g->goods) {
		if (ele->good_id == temp && ele->sit == "销售中") {
			if (num == -1) {
				cout << endl << endl << "*********************************************************************************" << endl;
				cout << "商品ID " << "       名称   " << "       价格  " << "     上架时间  " << " 库存数量  " << "卖家ID  " << "商品状态 " << endl;
				g->print_good(ele);
				cout << "*********************************************************************************" << endl << endl << endl;
				cout << "请输入购买数量: ";
				temp.clear(); cin.clear();
				getline(cin, temp);
				num_temp = trim(temp);
				while (!cin || num_temp[0] == '0' || !nvalid(num_temp)) {
					cout << endl << endl << " !!商品数量不合法，请按要求输入!! " << endl;
					cin.clear();
					cout << "请输入商品数量（数量为正整数且首位不能为0）: ";
					getline(cin, temp);
					num_temp = trim(temp);
				}
				buy_number = exint(num_temp);
			}
			else { buy_number = num; }
			if (ele->number < buy_number) {
				cout << endl << "！！欲购买商品数量超过商品库存，购买失败！！" << endl;
				return false;
			}
			else if (inform->balance < buy_number * ele->price) {
				cout << endl << "！！账户余额不足，购买失败！！" << endl;
				cout << "是否要进入充值界面（y/n）：";
				temp.clear(); cin.clear();
				getline(cin, temp);
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
					cin.clear();
					cout << "是否要进入充值界面（y/n）： ";
					getline(cin, temp);
				}
				if (trim(temp) == "n") {
					system("cls");
					return false;
				}
				else {
					system("cls");
					recharge();
					return false;
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

				else {
					string bh = o->orders[o->orders.size() - 1]->order_id.substr(1);
					if (bh == "999") {
						cout << endl << "**********订单数量已达上限***********" << endl << endl;
						return false;
					}
					paper->order_id.append(str_add(bh));
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
				valsu.push_back("数量 = " + to_string(ele->number));
				if (ele->sit == "已下架") valsu.push_back("商品状态 = 已下架");
				sq->Update(good_file_name, "商品ID = " + paper->good_id, valsu);
				o->orders.push_back(paper);
				cout << endl << endl << "******购买成功********" << endl;
				o->write_order();
				cout << "**************************" << endl << "!!交易提醒!!" << endl << "交易时间：" << paper->deal_time << endl << "交易单价：" << paper->money << endl \
					<< "交易数量：" << paper->number << endl << "交易状态：交易成功" << endl << "您的余额：" << inform->balance << endl << "**************************" << endl << endl;
				return true;
			}
		}
	}
	system("cls");
	cout << endl << "***********没有找到您想要的商品或该商品已下架**********" << endl << endl;
	return false;

}

void Buyer::search_good() {
	string s;
	cout << "请输入您想要查找的商品： ";
	s.clear(); cin.clear();
	getline(cin, s);
	while (!cin) {
		cout << "请输入正确的商品名称" << endl;
		cin.clear();
		getline(cin, s);
	}
	sq->Select(good_file_name, true, "名称", s);
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "商品ID " << "       名称   " << "       价格  " << "     上架时间  " << " 库存数量  " << "卖家ID  " << "商品状态 " << endl;
	bool nfind = true;
	for (auto& ele : g->goods) {
		if (fuzzy_mathing(trim(s),ele->name) && ele->sit != "已下架") {
			g->print_good(ele);
			nfind = false;
		}
	}
	if (nfind) {
		cout << endl << endl << "没有找到关键词相关商品,请重新选择操作" << endl << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Buyer::look_order() {
	sq->Select(order_file_name);
	bool nfind = true;
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << "订单ID " << " 商品ID   " << " 交易单价  " << " 数量  " << "  交易时间   " << " 卖家ID  " << " 买家ID " << endl;
	for (auto& t : o->orders) {
		if (t->buyer_id == inform->user_id) {
			o->print_order(t);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "******您暂时没有订单******" << endl;
	}

	cout << "*********************************************************************************" << endl << endl << endl;
}

void Buyer::look_good_information() {
	string s;
	cout << "请输入您想要查找的商品ID： ";
	cin.clear();
	s.clear();
	getline(cin, s);
	while (!cin) {
		cout << "请输入正确的商品ID" << endl;
		cin.clear();
		getline(cin, s);
	}
	sq->Select(good_file_name, true, "商品ID", s);
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g->goods) {
		if (ele->good_id == s && ele->sit != "已下架") {
			cout << "商品ID：" << ele->good_id << endl << "商品名称：" << ele->name << endl << "商品价格：" << fixed << setprecision(1) << ele->price << endl \
				<< "上架时间：" << ele->sell_time << endl << "商品描述：" << ele->description << endl << "商品卖家：" << ele->seller_id << endl;
			cout << "*********************************************************************************" << endl << endl << endl;
			return;
		}
	}

	cout << "没有找到关键词相关商品或商品已下架,请重新选择操作" << endl;

	cout << "*********************************************************************************" << endl << endl << endl;
}

void Buyer::TtroBuyOne() {
	cout << endl << "请输入您想要结算的物品在购物车中的编号ID： ";
	string i;
	i.clear(); cin.clear();
	getline(cin, i);
	bool nfind = 1;
	for (auto it = mysgs.begin(); it < mysgs.end(); it++) {
		if ((*it)->sg_id == i) {
			if ((*it)->number == 0) {
				cout << endl << "******该物品库存不足*******" << endl;
				cout << "请问是否将其从购物车中删除？（y/n）：";
				string chos;
				cin.clear(); chos.clear();
				getline(cin, chos);
				while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
					cout << "请按要求输入" << endl;
					cout << "请问是否将其从购物车中删除？(y/n): ";
					cin.clear();
					getline(cin, chos);
				}
				if (trim(chos) == "y") {
					mysgs.erase(it);
					st->TtroDel((*it)->sg_id);
					return;
				}
				else if (trim(chos) == "n") {
					cout << "删除取消，请重新选择您的操作" << endl << endl;
					return;
				}
			}
			bool judge = buy((*it)->good_id, (*it)->number);
			if (!judge) return;
			st->TtroDel((*it)->sg_id);
			nfind = 0;
			return;
		}
	}
	if (nfind) {
		system("cls");
		cout << endl << "*********没有在您的购物车中找到您输入编号对应的购物车物品********" << endl << endl;
	}
}

void Buyer::TtroBuyOne(string sg_id) {
	for (auto it = mysgs.begin(); it < mysgs.end(); it++) {
		buy((*it)->good_id, (*it)->number);
		st->TtroDel((*it)->sg_id);
	}
}

void Buyer::TtroBuyAll() {
	double sum = 0;
	for (auto& ele : mysgs) {
		sum += ele->number * ele->price;
	}
	if (sum > inform->balance) {
		string temp;
		cout << endl << "！！账户余额不足，购买失败！！" << endl;
		cout << "是否要进入充值界面（y/n）：";
		temp.clear(); cin.clear();
		getline(cin, temp);
		while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
			cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
			cin.clear();
			cout << "是否要进入充值界面（y/n）： ";
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
	for (auto& ele : mysgs) {
		TtroBuyOne(ele->sg_id);
	}
}

void Buyer::TtroLook() {
	cout << endl << endl << "*******************************************************************************" << endl;
	cout << "购物车物品ID       商品名称  商品ID  商品价格  商品数量  卖家ID" << endl;
	for (auto& ele : mysgs) {
		st->Ttroprint(ele);
	}
	cout << "*******************************************************************************" << endl << endl;
}

void Buyer::TtroAdd() {
	regex m("^([0][0-9]*)$");
	ShopGood* temp = new ShopGood;
	string id, num;
	cout << endl << "请输入您想要添加的商品ID： ";
	id.clear(); cin.clear();
	getline(cin, id);
	cout << endl << "请输入您想要添加的商品数量： ";
	num.clear(); cin.clear();
	getline(cin, num);
	num = trim(num);
	while (!cin || regex_match(num, m)) {
		system("cls");
		cout << endl << "请按要求输入(商品数量必须为正整数)" << endl << endl;
		id.clear(); num.clear(); cin.clear();
		return;
	}
	Good* temporary = new Good;
	bool nfind = 1; int max_num = -1;
	for (auto& ele : mysgs) {
		if (ele->good_id == id) {
			max_num = exint(num) + ele->number;
			break;
		}
	}
	for (auto& ele : g->goods) {
		if (ele->good_id == id && ele->sit!="已下架") {
			nfind = 0;
			if (ele->number < exint(num) || ele->number < max_num) {
				system("cls");
				cout << endl << "*******添加失败！！欲添加商品数量或与购物车中已添加的数量之和超过该商品的当前库存*******" << endl << endl;
				return;
			}
			temporary = ele;
			break;
		}
	}
	if (nfind) {
		system("cls");
		cout << endl << "*********没有找到您想添加的商品********" << endl << endl;
		return;
	}
	temp->buyer_id = inform->user_id; temp->good_id = temporary->good_id; temp->good_name = temporary->name; temp->number = exint(num);
	temp->price = temporary->price; temp->seller_id = temporary->seller_id;
	st->TtroInsert(temp);
}

void Buyer::TtroBuyMenu() {
	system("cls");
	st = new Shopttro(inform->user_id);
	mysgs = st->getsgs();
	while (true) {
		cout << "Welcome to shoppingtrolley" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1、查看购物车 2、添加商品 3、删除商品 4、结算单件商品 5、清空购物车（全部结算） 6、返回买家主界面  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		i.clear();
		cin.clear();
		getline(cin, i);
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "请输入正确的选项" << endl;
			cin.clear();
			getline(cin, i);
		}
		switch (int(trim(i)[0] - '0')) {
		case 1: TtroLook(); break;
		case 2: TtroAdd(); break;
		case 3: st->TtroDel(); break;
		case 4: TtroBuyOne(); break;
		case 5: TtroBuyAll(); break;
		case 6:system("cls"); return; break;
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
		mysgs = st->getsgs();
	}
}