#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"
using namespace std;
void calculator_menu(string s) {
	string temp;
	if (s == "-1") {
		cout << "��������Ҫ����ı��ʽ��";
		cin >> temp;
		while (!cin) {
			cout << "��������ȷ������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> temp;
		}

	}
	else { temp = s; }
	while (!expr_valid(temp)) {
		calculator_menu("-1");
	}
}

bool expr_valid(string s) {

}