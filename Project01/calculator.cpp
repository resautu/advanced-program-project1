#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"
using namespace std;
string cal_trim(string s) {
	if (s.empty()) return s;
	string res;
	for (auto c : s) {
		if (c != ' ') res.push_back(c);
	}
	return res;
}

bool space_match(string& s) {
	for (int i = 1; i < s.length(); i++) {
		if (((s[i - 1] < '9' && s[i - 1]>'0') || s[i - 1] == '.') && s[i] == ' ') {
			for (int j = i; j < s.length(); i++) {
				if ((s[j] < '9' && s[j]>'0') || s[j] == '.') {
					return false;
				}
			}
		}
	}
	return true;
}

double bracket_match(string& s) {
	int lef = 0, righ = 0;
	for (auto ch : s) {
		if (ch == '(') lef++;
		if (ch == ')') righ++;
		if (righ > lef) return false;
	}
	if (lef != righ) return false;
	return true;
}

void calculator_menu(string s) {
	string temp;
	if (s == "-1") {
		cout << "请输入您要计算的表达式：";
		//getline(cin, temp);
		cin >> temp;
		while (!expr_valid(temp)) {
			cout << "请输入正确的数字" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> temp;
		}

	}
	else { temp = s; }
	if (!expr_valid(temp)) {
		calculator_menu("-1");
	}
	string expr = cal_trim(temp);
	vector<double> digit = cal_exdouble(expr);
	string new_expr = cal_exstring(expr);
	string stand_expr = trans(new_expr);
	cout << endl << endl << "计算结果为：";
	cout << calculator(stand_expr, digit) << endl;

}

bool expr_valid(string& s) {
	regex _side("^(([0-9]|[\*]|[\+]|[-]|[/]|[\)]|[\(]|[ ]|[.])*)$");
	if (!regex_match(s, _side)) {
		cout << endl << "****符号不合法****" << endl;
		return false;
	}
	else if (!bracket_match(s)) {
		cout << endl << "****括号不匹配****" << endl;
		return false;
	}
	else if (!space_match(s)) {
		cout << endl << "****数字间及小数点与数字之间不能有空格****" << endl;
		return false;
	}
	s = cal_trim(s);
	return true;
}

int prior(char ch) {
	if (ch == '+' || ch == '-') {
		return 0;
	}
	else {
		return 1;
	}
}

string trans(string& s) {
	stack<char> st;
	string result;
	for (auto ch : s) {
		//		if (ch <= '9' && ch >= '0' || ch == '.' || ch == '|') {
		if (ch == '#') {
			result.push_back(ch);
		}
		else if (ch == '(') {
			st.push(ch);
		}
		else if (ch == ')') {
			while (st.top() != '(') {
				result.push_back(st.top());
				st.pop();                               //可以利用这里检查一下括号的匹配合法性
			}
			st.pop();
		}
		else {
			if (st.empty() || st.top() == '(') {
				st.push(ch);
			}
			else if (prior(ch) > prior(st.top())) {
				st.push(ch);
			}
			else {
				while (!st.empty()) {
					result.push_back(st.top());
					st.pop();
				}
				st.push(ch);
			}
		}
	}
	while (!st.empty()) {
		result.push_back(st.top());
		st.pop();
	}
	return result;

}

string cal_exstring(string& s) {
	string res;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] <= '9' && s[i] >= '0') {
			res.push_back('#');
			while (i < s.length() && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) {
				i++;
			}
		}
		if (i != s.length() - 1 && i != s.length()) {
			res.push_back(s[i]);
		}
	}
	return res;
}

vector<double> cal_exdouble(string& s) {
	vector<double> res;
	string temp;
	for (auto ch : s) {
		if ((ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')') && temp.length() != 0) {
			res.push_back(exdouble(temp));
			temp.clear();
		}
		else {
			temp.push_back(ch);
		}
	}
	res.push_back(exdouble(temp));
	return res;
}

double operator_trans(char ch, double op1, double op2) {
	int i;
	if (ch == '+') i = 1;
	else if (ch == '-') i = 2;
	else if (ch == '*') i = 3;
	else  i = 4;
	switch (i) {
	case 1:return op1 + op2; break;
	case 2:return op1 - op2; break;
	case 3:return op1 * op2; break;
	case 4:return op1 / op2; break;
	default:cerr << "程序出现未知错误，即将退出" << endl; exit(-1); break;
	}
}

double calculator(string& s, vector<double> digit) {
	stack<double> st;
	int count = 0;
	double op1, op2;
	//cout << "debug:  " << s[5] << endl;
	for (auto ch : s) {
		//if (ch == '\0') continue;
		if (ch == '#') {
			st.push(digit[count]);
			count++;
		}
		else {
			op2 = st.top();
			st.pop();
			op1 = st.top();
			st.pop();
			st.push(operator_trans(ch, op1, op2));
		}
	}
	return st.top();
}