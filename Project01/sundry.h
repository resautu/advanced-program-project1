#pragma once
#ifndef SUNDRY_H
#define SUNDRY_H
#include<iostream>
#include <string>
#include<regex>
using namespace std;
wstring s_to_ws(string& s);      //将短字符串转化为宽字符串

bool cevalid(wstring& s);         //判断是否只有汉字和字母

bool nevalid(string& s);          //判断是否只有字母和数字

bool nvalid(string& s);           //判断是否只有数字

bool dnvalid(string& s);          //判断是否是浮点数形式

double exdouble(string& s);         //将字符串转变为浮点类型

int exint(string& s);             //将字符串转变为int类型

string trim(string s);            //去掉用户输入的空格,并简单判断用户输入的合法性(菜单外输入时使用)

string new_trim(string s);		//去掉用户输入的空格,并简单判断用户输入的合法性(菜单时输入使用)

void _replace(string& s, char c1, char c2);    //将英文逗号在文件中的转换

string double_to_string(double d);     //将double类型转换为保留一位小数的字符串;   

string dint_to_string(double d);       //将小数全是0的double保留整数部分

bool side_count(string& s);                //判断字符串中小数点是否超过1，超过则返回true，否则返回false

//string cal_trim(string s);             //专用于计算器的字符串空格处理

#endif
