#define _CRT_SECURE_NO_WARNINGS
#include "sundry.h"
wstring s_to_ws(string& s)
{
    setlocale(LC_ALL, "chs");
    const char* temp = s.c_str();
    int l = s.size() + 1;
    wchar_t* dest = new wchar_t[l];
    wmemset(dest, 0, l);
    mbstowcs(dest, temp, l);
    wstring result = dest;
    delete[]dest;
    setlocale(LC_ALL, "C");
    return result;
}

bool cevalid(wstring& s) {                //�ж��Ƿ�Ϊ���ֺ�Ӣ����ĸ;
	for (auto& ele : s) {
		if (!((ele >= 'a' && ele <= 'z') || (ele >= 'A' && ele <= 'Z') || (int(ele) >= 0x4E00 && int(ele) <= 0x9FA0))) return false;
	}
	return true;
}
bool nevalid(string& s) {                 //�ж��Ƿ�ΪСд��ĸ������;
	for (auto& ele : s) {
		if (!((ele >= 'a' && ele <= 'z') || (ele >= '0' && ele <= '9'))) {
			return false;
		}
	}
	return true;
}

bool nvalid(string& s) {                 //�ж��Ƿ�ȫΪ����;
	for (auto& ele : s) {
		if (!(ele >= '0' && ele <= '9')) return false;
	}
	return true;
}

bool dnvalid(string& s) {
	regex d("^(([1-9][0-9]{0,}(\.[0-9]+)?)|[0]\.[0-9]*)$");
	return regex_match(s, d);
}

double exdouble(string& s) {
	double sum=0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.') {
			sum += int(s[i + 1] - '0') / 10;
			return sum;
		}
		sum = sum * 10 + int(s[i + 1] - '0');
	}
	return sum;
}

int exint(string& s) {
	int sum=0;
	for (auto& c : s) {
		sum = sum * 10 + int(c - '0');
	}
	return sum;
}

string trim(string s) {
	if (s.empty())
		return s;
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
