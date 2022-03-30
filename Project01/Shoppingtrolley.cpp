#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Shoppingtrolley.h"
#include "sundry.h"
#include<iomanip>
#include"Datebase.h"
using namespace std;
string shopttro_file = "datebase/shopttro.txt";
Shopttroing::Shopttroing() {
	fstream f;
	f.open(shopttro_file, ios::in);
	string temp, pr, nu;
	if (!f.is_open()) {
		f.open(shopttro_file, ios::out);
		if (!f.is_open()) cout << "*********���ﳵ�ļ����س���,����Ҫ������������**********" << endl;
		f.close();
		return;
	}
	string outline;
	getline(f, outline);
	string shopin;
	while (1) {
		shopin.clear();
		getline(f, shopin, ',');
		if (shopin.length() == 0 || !f) break;
		ShopGood* temp = new ShopGood;
		temp->sg_id = shopin; shopin.clear();
		getline(f, temp->good_name, ',');
		getline(f, temp->good_id, ',');
		getline(f, temp->buyer_id, ',');
		getline(f, temp->seller_id, ',');
		getline(f, shopin, ','); temp->number = exint(shopin); shopin.clear();
		getline(f, shopin); temp->price = exdouble(shopin); shopin.clear();
		sgings.push_back(temp);
	}
	f.close();
	Gooding* g = new Gooding;
	for (auto& ele : sgings) {
		for (auto& goodings : g->get_good()) {
			if (ele->good_id == goodings->good_id && ele->number > goodings->number) {
				ele->number = goodings->number;
				break;
			}
		}
	}
	write_st();
}
void Shopttroing::DelGood(string sg_id) {
	auto it = sgings.begin();
	for (auto& ele : sgings) {
		if (ele->sg_id == sg_id) {
			sgings.erase(it);
			break;
		}
		it++;
	}
	write_st();
}
void Shopttroing::ClearGood(string buyer_id) {
	int count = 0;
	for (auto& ele : sgings) {
		if (ele->buyer_id == buyer_id) count++;
	}
	for (int i = 0; i < count; i++) {
		for (auto it = sgings.begin(); it < sgings.end(); it++) {
			if ((*it)->buyer_id == buyer_id) {
				sgings.erase(it);
				break;
			}
		}
	}
	write_st();
}
void Shopttroing::InsertGood(ShopGood* sg) {
	sgings.push_back(sg);
	write_st();
}
void Shopttroing::write_st() {
	fstream f;
	f.open(shopttro_file, ios::out);
	if (!f) { cout << "���ﳵ�ļ�������ִ���������������" << endl; exit(0); }
	f << "���ﳵ��ƷID,��Ʒ����,��ƷID,���ID,����ID,����,�۸�" << endl;
	for (auto& ele : sgings) {
		f << ele->sg_id << ',' << ele->good_name << ',' << ele->good_id << ',' << ele->buyer_id << ',' << ele->seller_id << ',' << ele->number << ',' \
			<< fixed << setprecision(1) << ele->price << endl;
	}
	f.close();
}
void  Shopttroing::DelSeller(string seller_id) {
	int count = 0, count1 = 0;
	for (auto& ele : sgings) {
		if (ele->seller_id == seller_id) count++;
		if (ele->buyer_id == seller_id && ele->seller_id != seller_id) count1++;
	}
	for (int i = 0; i < count; i++) {
		for (auto it = sgings.begin(); it < sgings.end(); it++) {
			if ((*it)->seller_id == seller_id) {
				sgings.erase(it);
				break;
			}
		}
	}
	for (int i = 0; i < count1; i++) {
		for (auto it = sgings.begin(); it < sgings.end(); it++) {
			if ((*it)->buyer_id == seller_id) {
				sgings.erase(it);
				break;
			}
		}
	}
	write_st();
}



Shopttro::Shopttro(string buyer_id) {
	for (auto& ele : sgings) {
		if (ele->buyer_id == buyer_id) {
			sgs.push_back(ele);
		}
	}
}
vector<ShopGood*> Shopttro::getsgs() const {
	return sgs;
}
void Shopttro::TtroInsert(ShopGood* sg) {
	if (sgings.empty()) { sg->sg_id = "C001"; }
	else {
		sg->sg_id = "C" + str_add((*(sgings.end() - 1))->sg_id.substr(1));
	}
	for (auto& ele : sgs) {
		if (ele->good_id == sg->good_id) {
			ele->number += sg->number;
			//ChangeGood(ele->sg_id, ele->number);
			write_st();
			system("cls");
			cout << endl << "*********��ӳɹ�***********" << endl << endl;
			return;
		}
	}
	sgs.push_back(sg);
	InsertGood(sg);
	system("cls");
	cout << endl << "*********��ӳɹ�***********" << endl << endl;

}
void Shopttro::TtroDel() {
	cout << endl << "����������Ҫ�¼ܵĹ��ﳵ����Ʒ�ı��ID�� ";
	string i;
	i.clear(); cin.clear();
	getline(cin, i);
	bool nfind = 1;
	for (auto it = sgs.begin(); it < sgs.end(); it++) {
		if ((*it)->sg_id == i) {
			sgs.erase(it);
			DelGood(i);
			nfind = 0;
			break;
		}
	}
	if (nfind) {
		system("cls");
		cout << endl << "*********û�������Ĺ��ﳵ���ҵ��������Ŷ�Ӧ�Ĺ��ﳵ��Ʒ********" << endl << endl;
	}
	else {
		cout << endl << "*********����ɹ�********" << endl << endl;
	}
}
void Shopttro::TtroDel(string sg_id) {
	for (auto it = sgs.begin(); it < sgs.end(); it++) {
		if ((*it)->sg_id == sg_id) {
			sgs.erase(it);
			DelGood(sg_id);
			break;
		}
	}

}
void Shopttro::Ttroprint(ShopGood* sg) {
	cout << left << setw(15) << sg->sg_id << setw(15) << sg->good_name << setw(10) << sg->good_id << setw(11) << fixed << setprecision(1) << sg->price \
		<< setw(8) << sg->number << sg->seller_id << endl;
}
