#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<iostream>
#include<string>
#include<exception>
#include"sundry.h"
void make_expr();                //���ö���������ʽ

void calculator_menu(string s = "-1");      //�������˵�

bool expr_valid(string s);                //�жϱ��ʽ�Ƿ�Ϸ�

double calculatoring(string s);           //������ʽ
#endif
