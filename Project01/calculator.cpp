#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"
using namespace std;
string divede_zero = "****出现除0错误****";
string single_op = "****请不要使用一元运算（‘-’除外）****";
string cal_trim(string s) {
	if (s.empty()) return s;
	string res;
	for (auto c : s) {
		if (c != ' ') res.push_back(c);
	}
	return res;
}

bool side_co(string& s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.') {
			if (i == 0 || i == s.length() - 1) return false;
			else if (s[i - 1] < '0' || s[i - 1]>'9' || s[i + 1] < '0' || s[i + 1]>'9') return false;
		}
	}
	return true;
}

bool hide_op(string& s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(' && i != 0) {
			if (s[i - 1] <= '9' && s[i - 1] >= '0') {
				return false;
			}
		}
		else if (s[i] == ')' && i != s.length() - 1) {
			if (s[i + 1] <= '9' && s[i + 1] >= '0') {
				return false;
			}
		}
	}
}

bool space_match(string& s) {
	for (int i = 1; i < s.length(); i++) {
		if (((s[i - 1] < '9' && s[i - 1]>'0') || s[i - 1] == '.') && s[i] == ' ') {
			for (int j = i; j < s.length(); j++) {
				if (s[j] == '+' || s[j] == '-' || s[j] == '/' || s[j] == '*' || s[j] == '(' || s[j] == ')') {
					break;
				}
				else if ((s[j] < '9' && s[j]>'0') || s[j] == '.') {
					return false;
				}
			}
		}
	}
	return true;
}

bool op_judge(string& s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
			if (i == s.length() - 1) return false;
			else if (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/') return false;
		}
	}
	return true;
}

bool side_judge(string& s) {
	bool judge = false;
	for (auto ch : s) {
		if (ch == '.') {
			if (judge == true) return false;
			judge = true;
		}
		else if ((ch <= '0' || ch >= '9') && ch != '.' && judge) {
			judge = false;
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

string calculator_menu(string s) {
	string te;
	if (s == "-1") {
		cout << "请输入您要计算的表达式：" << endl;
		getline(cin, te);
		while (!expr_valid(te)) {
			cout << "请输入您要计算的表达式" << endl;
			cin.clear();
			te.clear();
			getline(cin, te);
		}

	}
	else { te = s; }
	if (!expr_valid(te)) {
		calculator_menu("-1");
	}
	string expr = cal_trim(te);
	vector<double> digit = cal_exdouble(expr);
	string new_expr = cal_exstring(expr);
	string stand_expr = trans(new_expr);
	//cout << stand_expr << endl;
	string res = calculator(stand_expr, digit);
	if (res == divede_zero) {
		cout << endl << res << endl << endl;
		calculator_menu("-1");
	}
	else if (res == single_op) {
		cout << endl << res << endl << endl;
		calculator_menu("-1");
	}
	else {
		if (s == "-1") {
			cout << endl << endl << "计算结果为：";
			cout << res << endl;
		}
		return res;
	}
	return "0";
}

bool expr_valid(string& s) {
	regex _side("^(([0-9]|[\*]|[\+]|[-]|[/]|[\)]|[\(]|[ ]|[.])*)$");
	string expr_judge = cal_trim(s);
	if (!regex_match(s, _side)) {
		cout << endl << "****符号不合法****" << endl;
		return false;
	}
	else if (!bracket_match(s)) {
		cout << endl << "****括号不匹配****" << endl;
		return false;
	}
	else if (!side_judge(expr_judge)) {
		cout << endl << "****小数点使用错误****" << endl;
		return false;
	}
	else if (!space_match(s)) {
		cout << endl << "****数字间及小数点与数字之间不能有空格****" << endl;
		return false;
	}
	else if (!hide_op(s)) {
		cout << endl << "****请不要存在隐藏（默认）的运算符****" << endl;
		return false;
	}
	else if (!side_co(s)) {
		cout << endl << "****小数点前后必须与数字相连****" << endl;
		return false;
	}
	else if (!op_judge(expr_judge)) {
		cout << endl << "****操作符存在误用（注：不支持自增自检运算）****" << endl;
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
				while (!st.empty() && st.top() != '(') {
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
		if (i != s.length()) {
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
		else if ((ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')') && temp.length() == 0) {
			continue;
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

string calculator(string& s, vector<double> digit) {
	stack<double> st;
	int count = 0, sub_count;
	double op1, op2;
	int i = 0;
	bool judge;
	for (auto ch : s) {
		if (ch == '#') {
			st.push(digit[count]);
			count++;
		}
		else {
			op2 = st.top();
			st.pop();
			if (ch == '-') {
				if (st.size() == 0) {
					op1 = 0;
				}
				else {
					sub_count = 0;
					for (int j = i; j <= s.length(); j++) {
						if (j == s.length() || s[j] == '#') {
							if (sub_count > st.size()) {
								op1 = 0;
							}
							else {
								op1 = st.top();
								st.pop();
							}
							break;
						}
						sub_count++;
					}
				}
			}
			else {
				if (st.size() == 0) {
					return single_op;
				}
				op1 = st.top();
				st.pop();
			}
			if (ch == '/' && op2 == 0) return divede_zero;
			st.push(operator_trans(ch, op1, op2));
		}
		i++;
	}
	if (st.top() == (int)st.top()) {
		return dint_to_string(st.top());
	}
	return double_to_string(st.top());
}

