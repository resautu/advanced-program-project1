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

string trim(string s);            //去掉用户输入的空格
#endif
