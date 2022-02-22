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
	wstring ctemp=s_to_ws(temp);
	while (!cin || ctemp.size() > 10 || !cevalid(ctemp)) {
		cout << endl << endl<< " !!�û������Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "�����������û�����������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->user_name=temp;
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
	cout << "���������ĵ�ַ��������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	cin >> temp;
	ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 20 || !cevalid(ctemp)) {
		cout << endl << endl << " !!��ַ���Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "���������ĵ�ַ��������20���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
		cin >> temp;
		ctemp = s_to_ws(temp);
	}
	t->address=temp;
	t->balance = 0;
	t->sit = "����";
	t->user_id.push_back('U');
	if (u.users[u.users.size() - 1]->user_id[3] == '9') {
		if (u.users[u.users.size() - 1]->user_id[2] == '9') {
			if (u.users[u.users.size() - 1]->user_id[1] == '9') {
				cout << "�û������Ѿ������ļ����أ����������˵�" << endl;
				return;
			}
			t->user_id.push_back(u.users[u.users.size() - 1]->user_id[1]+1);
			t->user_id.push_back('0');
			t->user_id.push_back('0');
		}
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[1]);
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[2]+1);
		t->user_id.push_back('0');
	}
	else {
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[1]);
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[2]);
		t->user_id.push_back(u.users[u.users.size() - 1]->user_id[3]+1);
	}
	u.users.push_back(t);
	cout << endl << endl << "******ע��ɹ�********" << endl << endl;
	u.write_user();
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
		while (!cin || (trim(i) < "1" || trim(i) > "4")) {
			cout << "��������ȷ������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (int(trim(i)[0] - '0')) {
		case 1:; break;
		case 2: {Seller er(information, u, o, g); er.seller_menu(); break; }
		case 3:; break;
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
	for (auto& ele : u.users) {
		if (ele->user_name == name) {
			if (ele->key == key) {
				if (ele->sit == "���") {
					system("cls");
					cout << endl << endl << "------�����˻��ѱ�����������������˵�------" << endl << endl << endl;
					return;
				}
				cout << endl << endl << "------��¼�ɹ�����ӭ��------" << endl << endl;
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

Seller::Seller(User_information* information, Usering& us, Ordering& ord, Gooding& go){
	inform = information;
	u = us;
	o = ord;
	g = go;

}

void Seller::seller_menu() {
	system("cls");
	while (true) {
		cout << "Welcome! seller" << endl;
		cout << "===============================================================================================" << endl;
		cout << "  1��������Ʒ 2���鿴������Ʒ 3���޸���Ʒ��Ϣ 4���¼���Ʒ 5���鿴��ʷ���� 6�������û�������  " << endl;
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
		case 1:release(); system("cls"); break;
		case 2:look_good(); system("cls"); break;
		case 3:change_information(); system("cls"); break;
		case 4:del_good(); system("cls"); break;
		case 5:look_order(); system("cls"); break;
		case 6:system("cls"); return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}

void Seller::release() {
	Good* t = new Good;
	cout << "��������Ʒ���ƣ�������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
	string temp;
	cin >> temp;
	wstring ctemp = s_to_ws(temp);
	while (!cin || ctemp.size() > 10 || !cevalid(ctemp)) {
		cout << endl << endl << " !!��Ʒ���Ʋ��Ϸ����밴Ҫ������!! " << endl;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "��������Ʒ���ƣ�������10���ַ������ĺ��ֻ�Ӣ����ĸ��: ";
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
	while (!cin || temp[0]=='0' || !nvalid(temp)) {
		cout << endl << endl << " !!��ϵ��ʽ���Ϸ����밴Ҫ������!! " << endl;
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
	t->good_id.push_back('U');
	if (g.goods[g.goods.size() - 1]->good_id[3] == '9') {
		if (g.goods[g.goods.size() - 1]->good_id[2] == '9') {
			if (g.goods[g.goods.size() - 1]->good_id[1] == '9') {
				cout << "�û������Ѿ������ļ����أ����������˵�" << endl;
				return;
			}
			t->good_id.push_back(g.goods[g.goods.size() - 1]->good_id[1] + 1);
			t->good_id.push_back('0');
			t->good_id.push_back('0');
		}
		t->good_id.push_back(g.goods[g.goods.size() - 1]->good_id[1]);
		t->good_id.push_back(g.goods[g.goods.size() - 1]->good_id[2] + 1);
		t->good_id.push_back('0');
	}
	else {
		t->good_id.push_back(g.goods[g.goods.size() - 1]->good_id[1]);
		t->good_id.push_back(g.goods[g.goods.size() - 1]->good_id[2]);
		t->good_id.push_back(g.goods[g.goods.size() - 1]->good_id[3] + 1);
	}
	g.goods.push_back(t);
	cout << endl << endl << "******ע��ɹ�********" << endl << endl;
	g.write_good();
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
	for (auto& ele : g.goods) {
		if (ele->good_id == temp) {
			if (ele->seller_id != inform->user_id) {
				cout << endl << "!!����Ʒ��������������Ȩ�Դ���Ʒ���в�������" << endl;
				return;
			}
			cout << "�����뱻�޸ĵ���Ʒ���ԣ�1���۸� 2��������: ";
			cin >> temp;
			while (!cin || (trim(temp)!="1" && trim(temp) != "2")) {
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
				cout << "��ƷID��" << ele->good_id << endl << "��Ʒ���ƣ�" << ele->name << endl << "��Ʒ�۸�" << fixed <<setprecision(1) << new_price << endl << "��Ʒ������" <<ele->description<< endl;
				cout << "********************************************************************" << endl;
				cout << "�Ƿ�ȷ���޸ģ�(y/n)��" ;
				cin >> temp;
				while (!cin || (trim(temp) != "y" && trim(temp) != "n")) {
					cout << endl << endl << " !!���벻�Ϸ����밴Ҫ������!! " << endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << endl << endl << "�Ƿ�ȷ���޸ģ�(y/n)��";
					cin >> temp;
				}
				if (trim(temp) == "y") {
					ele->price = new_price;
					g.write_good();
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
					ele->description = new_description;
					g.write_good();
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
	for (auto& ele : g.goods) {
		if (ele->good_id == i) {
			if (ele->seller_id != inform->user_id) {
				cout << endl << "!!����Ʒ��������������Ȩ�Դ���Ʒ���в���!��" << endl;
				return;
			}
			cout << " ID " << "   ����   " << " �۸�  " << " �ϼ�ʱ��  " << " �������  " << " ����ID  " << " ��Ʒ״̬ " << "    ��Ʒ����    " << endl;
			g.print_good(ele);
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
		while (!cin || (trim(chos) != "y" && trim(chos) != "n")) {
			cout << "�밴Ҫ������" << endl;
			cout << "�Ƿ񽫸���Ʒ�¼�(y/n): ";
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> chos;
		}
		if (trim(chos) == "y") {
			de->sit = "���¼�";
			g.write_good();
			cout << "�¼ܳɹ���" << endl << endl;
		}
		else if (trim(chos) == "n") {
			cout << "�¼�ȡ����������ѡ�����Ĳ���" << endl << endl;
		}
	}
}

void Seller::look_order() {
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " ����ID " << "   ��ƷID   " << " ���׵���  " << " ����  " << "  ����ʱ��   " << " ����ID  " << " ���ID " << endl;
	for (auto& t : o.orders) {
		if (t->seller_id == inform->user_id) {
			o.print_order(t);
		}
	}

	cout << "*********************************************************************************" << endl << endl << endl;
}

void Seller::look_good() {
	cout << endl << endl << "*********************************************************************************" << endl;
	cout << " ID " << "   ����   " << " �۸�  " << " �ϼ�ʱ��  " << " �������  " << " ����ID  " << " ��Ʒ״̬ " << "  �� ��   " << endl;
	for (auto& t : g.goods) {
		if (t->seller_id == inform->user_id) {
			g.print_good(t);
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
		int i;
		cin >> i;
		while (!cin) {
			cout << "��������ȷ������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> i;
		}
		switch (i) {
		//case 1:release(); system("cls"); break;
		//case 2:look_good(); system("cls"); break;
		//case 3:change_information(); system("cls"); break;
		//case 4:del_good(); system("cls"); break;
		//case 5:look_order(); system("cls"); break;
		//case 6:system("cls"); return; break;
		default:system("cls"); cout << "�밴Ҫ��������ȷ������" << endl << endl; break;
		}
	}
}