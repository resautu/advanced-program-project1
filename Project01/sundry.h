#pragma once
#ifndef SUNDRY_H
#define SUNDRY_H
#include<iostream>
#include <string>
#include<regex>
using namespace std;
wstring s_to_ws(string& s);      //�����ַ���ת��Ϊ���ַ���

bool cevalid(wstring& s);         //�ж��Ƿ�ֻ�к��ֺ���ĸ

bool nevalid(string& s);          //�ж��Ƿ�ֻ����ĸ������

bool nvalid(string& s);           //�ж��Ƿ�ֻ������

bool dnvalid(string& s);          //�ж��Ƿ��Ǹ�������ʽ

double exdouble(string& s);         //���ַ���ת��Ϊ��������

int exint(string& s);             //���ַ���ת��Ϊint����

string trim(string s);            //ȥ���û�����Ŀո�,�����ж��û�����ĺϷ���(�˵�������ʱʹ��)

string new_trim(string s);		//ȥ���û�����Ŀո�,�����ж��û�����ĺϷ���(�˵�ʱ����ʹ��)

void _replace(string& s, char c1, char c2);    //��Ӣ�Ķ������ļ��е�ת��

string double_to_string(double d);     //��double����ת��Ϊ����һλС�����ַ���;   

string dint_to_string(double d);       //��С��ȫ��0��double������������

bool side_count(string& s);                //�ж��ַ�����С�����Ƿ񳬹�1�������򷵻�true�����򷵻�false

//string cal_trim(string s);             //ר���ڼ��������ַ����ո���

#endif
