#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"Message.h"
#include <fstream>
#include <time.h>
#include "Datebase.h"
#include "sundry.h"
using namespace std;
string message_file = "datebase/message.txt";
MessageStore::MessageStore() {
	fstream f;
	f.open(message_file, ios::in);
	string temp, pr, nu;
	if (!f.is_open()) {
		f.open(message_file, ios::out);
		if (!f.is_open()) cout << "*********留言文件加载出错,如需要请重启程序尝试**********" << endl;
		f.close();
		return;
	}
	string outline;
	getline(f, outline);
	string messaging;
	while (1) {
		messaging.clear();
		getline(f, messaging, ',');
		if (messaging.length() == 0 || !f) break;
		Message* temp = new Message;
		temp->mes_id = messaging; messaging.clear();
		getline(f, temp->send_time, ',');
		getline(f, temp->sender, ',');
		getline(f, temp->reciever, ',');
		getline(f, temp->sender_sit, ',');
		getline(f, temp->reciever_sit, ',');
		getline(f, temp->content);
		mes.push_back(temp);
	}
	f.close();
}

void MessageStore::write_mes() {
	fstream f;
	f.open(message_file, ios::out);
	f << "留言ID,留言时间,留言人ID,接收者ID,留言状态,接收状态,留言内容" << endl;
	for (auto& ele : mes) {
		f << ele->mes_id << "," << ele->send_time << "," << ele->sender << "," << ele->reciever << "," << ele->sender_sit << "," << ele->reciever_sit << "," << ele->content << endl;
	}
	f.close();
}

PrMessageStore::PrMessageStore(string user_id) {
	for (auto& ele : mes) {
		if (ele->sender == user_id) {
			sen.push_back(ele);
		}
		else if (ele->reciever == user_id) {
			rec.push_back(ele);
		}
	}
}

void PrMessageStore::Send(string sender_id) {
	cout << "请输入接收人的用户ID:";
	string id; id.clear(); cin.clear();
	getline(cin, id);
	if (id == sender_id) {
		system("cls");
		cout << endl << "******您不能给您自己留言******" << endl << endl;
		return;
	}
	Usering* u = new Usering;
	if (!u->find_user(id)) {
		system("cls");
		cout << endl << "******查无此用户******" << endl << endl;
		return;
	}
	string content; content.clear(); cin.clear();
	cout << "请输入您的留言:";   getline(cin, content);
	Message* message = new Message;
	if (mes.empty()) { message->mes_id = "L001"; }
	else {
		string number = mes[mes.size() - 1]->mes_id.substr(1);
		message->mes_id = ("L" + str_add(number));
	}
	message->content = content; message->sender = sender_id; message->reciever = id; message->reciever_sit = "未读"; message->sender_sit = "已发送";
	time_t t;
	t = time(NULL);
	message->send_time = ctime(&t);
	rec.push_back(message); mes.push_back(message);
	write_mes();
	system("cls");
	cout << endl << "*******发送成功*******" << endl << endl;
}