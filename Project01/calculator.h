#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<iostream>
#include<string>
#include<exception>
#include"sundry.h"
void make_expr();                //利用订单构造表达式

void calculator_menu(string s = "-1");      //计算器菜单

bool expr_valid(string s);                //判断表达式是否合法

double calculatoring(string s);           //计算表达式
#endif
