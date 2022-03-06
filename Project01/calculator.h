#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<iostream>
#include<string>
#include<exception>
#include"sundry.h"
#include<regex>
#include<stack>
#include<vector>
extern string divede_zero;
void make_expr();                //利用订单构造表达式

string calculator_menu(string s);      //计算器菜单

bool expr_valid(string& s);                //判断表达式是否合法

double calculatoring(string s);           //计算表达式

string cal_trim(string s);                //计算器专用去空格函数

double bracket_match(string& s);            //括号匹配函数

bool space_match(string& s);               //判断空格是否匹配

string trans(string& s);                   //将中缀表达式转化为逆波兰表达式

int prior(char ch);                        //判断表达式的优先级

vector<double> cal_exdouble(string& s);               //将表达式中的字符串形式的浮点数转化为特殊符号标注

string cal_exstring(string& s);            //将表达式中的浮点数用特殊的符号表示

double operator_trans(char ch, double op1, double op2);           //运算函数

string calculator(string& s, vector<double> digit);       //实际计算函数

bool hide_op(string& s);                  //判断是否存在隐藏的运算符

bool side_co(string& s);                  //判断小数点前是否有数字
#endif
