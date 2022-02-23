#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

Gooding() {
	fstream f;
	f.open(good_file, ios::in);
	if (!f.is_open()) {
		f.open(good_file, ios::trunc);
		if (!f.is_open()) cout << "*********商品文件加载出错,如需要请重启程序尝试**********" << endl;
		f.close();
		return;
	}
	while (true) {
		string judge;
		f >> judge;
		if (!f) {
			break;
		}
		Good* t = new Good;
		t->good_id = judge;

		f >> t->name >> t->price >> t->number >> t->description >> t->seller_id >> t->sell_time >> t->sit;
		goods.push_back(t);
	}
	f.close();
}