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
void make_expr();                //���ö���������ʽ

string calculator_menu(string s);      //�������˵�

bool expr_valid(string& s);                //�жϱ��ʽ�Ƿ�Ϸ�

double calculatoring(string s);           //������ʽ

string cal_trim(string s);                //������ר��ȥ�ո���

double bracket_match(string& s);            //����ƥ�亯��

bool space_match(string& s);               //�жϿո��Ƿ�ƥ��

string trans(string& s);                   //����׺���ʽת��Ϊ�沨�����ʽ

int prior(char ch);                        //�жϱ��ʽ�����ȼ�

vector<double> cal_exdouble(string& s);               //�����ʽ�е��ַ�����ʽ�ĸ�����ת��Ϊ������ű�ע

string cal_exstring(string& s);            //�����ʽ�еĸ�����������ķ��ű�ʾ

double operator_trans(char ch, double op1, double op2);           //���㺯��

string calculator(string& s, vector<double> digit);       //ʵ�ʼ��㺯��

bool hide_op(string& s);                  //�ж��Ƿ�������ص������

bool side_co(string& s);                  //�ж�С����ǰ�Ƿ�������
#endif
