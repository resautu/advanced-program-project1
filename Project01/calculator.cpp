#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"
using namespace std;
void calculator_menu(string s) {
	string temp;
	if (s == "-1") {
		cout << "请输入您要计算的表达式：";
		cin >> temp;
		while (!cin) {
			cout << "请输入正确的数字" << endl;
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