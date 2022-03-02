#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "User.h"
#include "sundry.h"
#include"Item.h"

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
	t->address = temp;
	t->balance = 0;
	t->sit = "正常";
	t->user_id.push_back('U');
	if (u->users.size() == 0) {
		string st = "001";
		t->user_id.append(st);
	}
	else if (u->users[u->users.size() - 1]->user_id[3] == '9') {
		if (u->users[u->users.size() - 1]->user_id[2] == '9') {
			if (u->users[u->users.size() - 1]->user_id[1] == '9') {
				cout << "用户数量已经超过文件承载，将返回主菜单" << endl;
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
	cout << endl << endl << "******注册成功********" << endl << endl;
	u->write_user();
}

void User::user_menu(User_information* information) {
	system("cls");
	while (true) {
		cout << "Welcome! user" << endl;
		cout << "=================================================================================" << endl;
		cout << "  1、我是买家 2、我是卖家 3、个人信息管理 4、注销登录  " << endl;
		cout << "=================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		cin >> i;
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "4")) {
			cout << "输入不合法，请重新输入" << endl;
			cout << "请输入操作序号: ";
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
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}

void User::user_login() {
	system("cls");
	string name, key;
	cout << "请输入用户名: ";
	cin >> name;
	cout << "请输入密码: ";
	cin >> key;
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

void User::gover_inform() {
	system("cls");
	while (true) {
		cout << "Welcome! user" << endl;
		cout << "=================================================================================" << endl;
		cout << "  1、查看信息 2、修改信息 3、充值 4、返回用户主界面  " << endl;
		cout << "=================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		cin >> i;
		while (!cin || (trim(i) < "1" || trim(i) > "4")) {
			cout << "输入不合法，请重新输入" << endl;
			cout << "请输入操作序号: ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
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
	cout << "请选择修改的属性（1、用户名 2、联系方式 3、地址）: ";
	string i;
	cin >> i;
	while (!cin || (trim(i) < "1" || trim(i) > "3")) {
		cout << "输入不合法，请重新输入" << endl;
		cout << "请选择修改的属性（1、用户名 2、联系方式 3、地址）: ";
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> i;
	}
	switch (int(trim(i)[0] - '0')) {
	case 1: {
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
		inform->user_name = temp;
		u->write_user();
		cout << endl << "******修改成功******" << endl;
		break;
	}
	case 2: {
		string temp;
		cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
		cin >> temp;
		while (!cin || temp.size() > 20 || !nvalid(temp)) {
			cout << endl << endl << " !!联系方式不合法，请按要求输入!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
			cin >> temp;
		}
		inform->con = temp;
		u->write_user();
		cout << endl << "******修改成功******" << endl;
		break;
	}
	case 3: {
		string temp;
		cout << "请输入您的联系方式（不超过20个字符，只由数字组成）: ";
		cin >> temp;
		wstring ctemp = s_to_ws(temp);
		while (!cin || ctemp.size() > 20 || !cevalid(ctemp)) {
			cout << endl << endl << " !!地址不合法，请按要求输入!! " << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "请输入您的地址（不超过20个字符，中文汉字或英文字母）: ";
			cin >> temp;
			ctemp = s_to_ws(temp);
		}
		inform->address = temp;
		u->write_user();
		cout << endl << "******修改成功******" << endl;
		break;
	}
	default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
	}
}

void User::look_information() {
	cout << endl << endl << "*********************************************************************************" << endl;

	for (auto& ele : u->users) {
		if (ele->user_id == inform->user_id) {
			cout << "用户名：" << ele->user_name << endl << "联系方式：" << ele->con << endl << "地址：" << ele->address << endl << "钱包余额：" << fixed << setprecision(1) << ele->balance << endl;
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

void Seller::seller_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! seller" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1、发布商品 2、查看发布商品 3、修改商品信息 4、下架商品 5、查看历史订单 6、返回用户主界面  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		cin >> i;
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "请输入正确的数字" << endl;
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
		default:system("cls"); cout << "请按要求输入正确的数字" << endl << endl; break;
		}
	}
}

void Seller::release() {
	Good* t = new Good;
	cout << "请输入商品名称（不超过20个字符，中文汉字或英文字母）: ";
	string temp;
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
	cin >> temp;
	ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 20) {
		if (ctemp.size() > 20) {
			cout << endl << endl << " !!描述长度超过字符限制，请按要求输入!! " << endl;
		}
		else {
			cout << endl << endl << " !!商品描述不合法，请按要求输入!! " << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "请输入商品描述（不超过100个字符）: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->description = temp;
	t->seller_id = inform->user_id;
	t->sit = "销售中";
	t->good_id.push_back('M');
	if (g->goods.size() == 0) {
		string st = "001";
		t->good_id.append(st);
	}
	else if (g->goods[g->goods.size() - 1]->good_id[3] == '9') {
		if (g->goods[g->goods.size() - 1]->good_id[2] == '9') {
			if (g->goods[g->goods.size() - 1]->good_id[1] == '9') {
				cout << "商品数量已经超过文件承载，将返回主菜单" << endl;
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
	cout << endl << endl << "******发布成功********" << endl << endl;
	g->write_good();
}

void Seller::change_information() {
	cout << endl << endl << "请输入被修改的商品ID: ";
	string temp;
	cin >> temp;
	double new_price;
	string new_description;
	while (!cin) {
		cout << endl << endl << " !!商品ID不合法，请按要求输入!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << endl << endl << "请输入被修改的商品ID: ";
		cin >> temp;
	}
	for (auto& ele : g->goods) {
		if (ele->good_id == temp) {
			if (ele->seller_id != inform->user_id) {
				cout << endl << "!!此商品不属于您，您无权对此商品进行操作！！" << endl;
				return;
			}
			cout << "请输入被修改的商品属性（1、价格 2、描述）: ";
			cin >> temp;
			while (!cin || (trim(temp) != "1" && trim(temp) != "2")) {
				cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << endl << endl << "请输入被修改的商品属性（1、价格 2、描述）: ";
				cin >> temp;
			}
			switch (int(trim(temp)[0] - '0')) {
			case 1: {
				cout << "请输入商品价格（系统将为您保留一位小数，即舍去后续小数）: ";
				cin >> temp;
				while (!cin || dnvalid(temp)) {
					cout << endl << endl << " !!商品价格不合法，请按要求输入!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << "请输入新的商品价格（系统将自动为您保留一位小数）: ";
					cin >> temp;
				}
				new_price = exdouble(temp);
				cout << "请确定商品修改的商品信息无误！" << endl;
				cout << "********************************************************************" << endl;
				cout << "商品ID：" << ele->good_id << endl << "商品名称：" << ele->name << endl << "商品价格：" << fixed << setprecision(1) << new_price << endl << "商品描述：" << ele->description << endl;
				cout << "********************************************************************" << endl;
				cout << "是否确认修改？(y/n)：";
				cin >> temp;
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << endl << endl << "是否确认修改？(y/n)：";
					cin >> temp;
				}
				if (trim(temp) == "y") {
					vector<string> valsu;
					valsu.push_back("价格 = " + to_string(ele->price));
					sq->Update(good_file, "商品ID = " + ele->good_id, valsu);
					ele->price = new_price;
					g->write_good();
				}
				else { return; }
				break;
			}
			case 2: {
				wstring ctemp;
				cout << "请输入商品新的描述（不超过100个字符）: ";
				cin >> temp;
				ctemp = s_to_ws(temp);
				while (!cin || ctemp.size() > 20) {
					if (ctemp.size() > 20) {
						cout << endl << endl << " !!描述长度超过字符限制，请按要求输入!! " << endl;
					}
					else {
						cout << endl << endl << " !!商品描述不合法，请按要求输入!! " << endl;
					}
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << "请输入商品新的描述（不超过100个字符）: ";
					cin >> temp;
					ctemp = s_to_ws(temp);
				}
				new_description = temp;
				cout << "请确定商品修改的商品信息无误！" << endl;
				cout << "********************************************************************" << endl;
				cout << "商品ID：" << ele->good_id << endl << "商品名称：" << ele->name << endl << "商品价格：" << ele->price << endl << "商品描述：" << new_description << endl;
				cout << "********************************************************************" << endl;
				cout << "是否确认修改？(y/n)：";
				cin >> temp;
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << endl << endl << "是否确认修改？(y/n)：";
					cin >> temp;
				}
				if (trim(temp) == "y") {
					vector<string> valsu;
					valsu.push_back("商品描述 = " + ele->description);
					sq->Update(good_file_name, "商品ID = " + ele->good_id, valsu);
					ele->description = new_description;
					g->write_good();
				}
				else { return; }
				break;
			}
			default:cout << "程序出现错误" << endl; break;
			}
		}
	}
}

void Seller::del_good() {
	cout << endl << "请输入您想要下架的商品ID： ";
	string i, chos;
	cin >> i;
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
		cin >> chos;
		while (!cin || (new_trim(chos) != "y" && new_trim(chos) != "n")) {
			cout << "请按要求输入" << endl;
			cout << "是否将该商品下架(y/n): ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> chos;
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
	cout << " 订单ID " << "   商品ID   " << " 交易单价  " << " 数量  " << "  交易时间   " << " 卖家ID  " << " 买家ID " << endl;
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
		cout << "Welcome! seller" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1、查看商品列表 2、购买商品 3、搜索商品 4、查看历史订单 5、查看商品详细信息 6、返回用户主界面  " << endl;
		cout << "===============================================================================================" << endl;
		cout << "请输入操作序号: ";
		string i;
		cin >> i;
		while (!cin || (new_trim(i) < "1" || new_trim(i) > "6")) {
			cout << "请输入正确的选项" << endl;
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

void Buyer::buy() {
	string temp;
	int buy_number;
	cout << "请输入商品ID：";
	cin >> temp;
	while (!cin) {
		cout << "请输入正确的商品ID:" << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> temp;
	}

	for (auto& ele : g->goods) {
		if (ele->good_id == temp && ele->sit == "销售中") {
			cout << endl << endl << "*********************************************************************************" << endl;
			cout << "商品ID " << "       名称   " << "       价格  " << "     上架时间  " << " 库存数量  " << "卖家ID  " << "商品状态 " << endl;
			g->print_good(ele);
			cout << "*********************************************************************************" << endl << endl << endl;
			cout << "请输入购买数量: ";
			cin >> temp;
			while (!cin || temp[0] == '0' || !nvalid(temp)) {
				cout << endl << endl << " !!商品数量不合法，请按要求输入!! " << endl;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "请输入商品数量（数量为正整数且首位不能为0）: ";
				cin >> temp;
			}
			buy_number = exint(temp);
			if (ele->number < buy_number) {
				cout << endl << "！！欲购买商品数量超过商品库存，购买失败！！" << endl;
				return;
			}
			else if (inform->balance < buy_number * ele->price) {
				cout << endl << "！！账户余额不足，购买失败！！" << endl;
				cout << "是否要进入充值界面（y/n）：";
				cin >> temp;
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!输入不合法，请按要求输入!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << "请输入商品数量（数量为正整数且首位不能为0）: ";
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
							cout << "订单数量已经超过文件承载，将返回主菜单" << endl;
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
				valsu.push_back("数量 = " + to_string(ele->number));
				if (ele->sit == "已下架") valsu.push_back("商品状态 = 已下架");
				sq->Update(good_file_name, "商品ID = " + paper->good_id, valsu);
				o->orders.push_back(paper);
				cout << endl << endl << "******购买成功********" << endl << endl;
				o->write_order();

			}
		}
	}

}

void Buyer::search_good() {
	string s;
	cout << "请输入您想要查找的商品： ";
	cin >> s;
	while (!cin) {
		cout << "请输入正确的商品ID" << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> s;
	}
	sq->Select(good_file_name, true, "名称", s);
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g->goods) {
		if (ele->name.find(s) != string::npos && ele->sit != "已下架") {
			cout << "商品ID " << "       名称   " << "       价格  " << "     上架时间  " << " 库存数量  " << "卖家ID  " << "商品状态 " << endl;
			g->print_good(ele);
			nfind = false;
		}
	}
	if (nfind) {
		cout << "没有找到关键词相关商品,请重新选择操作" << endl;
	}
	cout << "*********************************************************************************" << endl << endl << endl;
}

void Buyer::look_order() {
	sq->Select(order_file_name);
	bool nfind = true;
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " 订单ID " << "   商品ID   " << " 交易单价  " << " 数量  " << "  交易时间   " << " 卖家ID  " << " 买家ID " << endl;
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
	cin >> s;
	while (!cin) {
		cout << "请输入正确的商品ID" << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cin >> s;
	}
	sq->Select(good_file_name, true, "商品ID", s);
	cout << endl << endl << "*********************************************************************************" << endl;
	bool nfind = true;
	for (auto& ele : g->goods) {
		if (ele->name.find(s) != string::npos && ele->sit != "已下架") {
			cout << "商品ID：" << ele->good_id << endl << "商品名称：" << ele->name << endl << "商品价格" << fixed << setprecision(1) << ele->price << endl \
				<< "上架时间：" << ele->sell_time << endl << "商品描述：" << ele->description << endl << "商品卖家：" << ele->seller_id << endl;
			cout << "*********************************************************************************" << endl << endl << endl;
		}
	}

	cout << "没有找到关键词相关商品或商品已下架,请重新选择操作" << endl;

	cout << "*********************************************************************************" << endl << endl << endl;
}