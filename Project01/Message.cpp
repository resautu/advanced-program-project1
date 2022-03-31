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
		if (ele->sender == user_id && ele->sender_sit.find("已删除") == string::npos) {
			sen.push_back(ele);
		}
		else if (ele->reciever == user_id && ele->reciever_sit.find("已删除") == string::npos) {
			rec.push_back(ele);
		}
	}
	this->user_id = user_id;
}

void PrMessageStore::Send() {
	cout << "请输入接收人的用户ID:";
	string id; id.clear(); cin.clear();
	getline(cin, id);
	if (id == user_id) {
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
	_replace(content, ',', '`');
	Message* message = new Message;
	if (mes.empty()) { message->mes_id = "L001"; }
	else {
		string number = mes[mes.size() - 1]->mes_id.substr(1);
		message->mes_id = ("L" + str_add(number));
	}
	message->content = content; message->sender = user_id; message->reciever = id; message->reciever_sit = "未读"; message->sender_sit = "已发送";
	time_t t;
	t = time(NULL);
	message->send_time = ctime(&t);
	message->send_time.pop_back();
	sen.push_back(message); mes.push_back(message);
	write_mes();
	system("cls");
	cout << endl << "*******发送成功*******" << endl << endl;
}

void PrMessageStore::SimplePrintRe(Message* m) {
	cout << left << setw(10) << m->mes_id << setw(30) << m->send_time << setw(12) << m->sender << setw(8) << m->reciever_sit << endl;
}

void PrMessageStore::SimplePrintSe(Message* m) {
	cout << left << setw(10) << m->mes_id << setw(30) << m->send_time << setw(12) << m->sender << setw(8) << m->sender_sit << endl;
}

void PrMessageStore::Lookrecieve() {
	cout << "*********************************************************************" << endl;
	cout << "留言编号" << "           留言时间           留言者ID     留言状态" << endl;
	for (auto& ele : rec) {
		SimplePrintRe(ele);
	}
	cout << "*********************************************************************" << endl;
}

void PrMessageStore::Looksend() {
	cout << "*********************************************************************" << endl;
	cout << "留言编号" << "           留言时间           接收者ID     留言状态" << endl;
	for (auto& ele : sen) {
		SimplePrintSe(ele);
	}
	cout << "*********************************************************************" << endl;
}

void PrMessageStore::Lookmessage() {
	cout << "请输入您想查看的留言编号：";
	string id; cin.clear();
	getline(cin, id);
	for (auto& ele : rec) {
		if (ele->mes_id == id) {
			ele->reciever_sit = "已读";
			if (ele->sender_sit == "已发送") { ele->sender_sit = "已读"; }
			write_mes();
			cout << "************************************" << endl;
			cout << "留言编号：" << ele->mes_id << endl;
			cout << "留言时间：" << ele->send_time << endl;
			cout << "发送者：" << ele->sender << endl;
			cout << "邮件状态：" << ele->reciever_sit << endl;
			cout << "邮件内容：" << ele->content << endl;
			cout << "************************************" << endl << endl << endl;
			return;
		}
	}
	for (auto& ele : sen) {
		if (ele->mes_id == id) {
			cout << "************************************" << endl;
			cout << "留言编号：" << ele->mes_id << endl;
			cout << "留言时间：" << ele->send_time << endl;
			cout << "接收者：" << ele->sender << endl;
			if (ele->reciever_sit.find("已读") != string::npos) { cout << "邮件状态：已读" << endl; }
			else if (ele->reciever_sit.find("未读") != string::npos) { cout << "邮件状态：未读" << endl; }
			cout << "邮件内容：" << ele->content << endl;
			cout << "************************************" << endl << endl << endl;
			return;
		}
	}
	system("cls");
	cout << endl << "*******在您的发送和接收的邮件中未找到该编号的邮件*******" << endl << endl;
}

void PrMessageStore::DelSingleMessage() {
	cout << "请输入您想删除的留言编号：";
	string id; cin.clear();
	getline(cin, id);
	auto it1 = rec.begin(), it2 = sen.begin();
	for (auto& ele : rec) {
		if (ele->mes_id == id) {
			if (ele->reciever_sit == "已读") { ele->reciever_sit = "已读已删除"; }
			else if (ele->reciever_sit == "未读") { ele->reciever_sit = "未读已删除"; }
			write_mes();
			rec.erase(it1);
			system("cls");
			cout << endl << "*****删除成功！！！*****" << endl << endl;
			return;
		}
		it1++;
	}
	for (auto& ele : sen) {
		if (ele->mes_id == id) {
			if (ele->reciever_sit.find("已读")) { ele->sender_sit = "已删除"; }
			else if (ele->reciever_sit.find("未读") != string::npos) {
				ele->sender_sit = "已删除";
				ele->reciever_sit = "未读已删除";
			}
			write_mes();
			rec.erase(it2);
			system("cls");
			cout << endl << "*****删除成功！！！*****" << endl << endl;
			return;
		}
		it2++;
	}
	system("cls");
	cout << endl << "*******在您的发送和接收的邮件中未找到该编号的邮件*******" << endl << endl;
}

void PrMessageStore::DelAllSend() {
	for (auto& ele : sen) {
		if (ele->reciever_sit.find("已读") != string::npos) { ele->sender_sit = "已删除"; }
		else if (ele->reciever_sit.find("未读") != string::npos) {
			ele->sender_sit = "已删除";
			ele->reciever_sit = "未读已删除";
		}
	}
	write_mes();
	sen.clear();
	system("cls");
	cout << endl << "*****所有发送记录已经被删除*****" << endl << endl;
}

void PrMessageStore::DelReadedMessage() {
	int count = 0;
	for (auto& ele : rec) {
		if (ele->reciever_sit == "已读") { ele->reciever_sit = "已读已删除"; }
		count++;
	}
	write_mes();
	for (int i = 0; i < count; i++) {
		auto it = rec.begin();
		for (; it < rec.end(); it++) {
			if ((*it)->reciever_sit == "已读已删除") { rec.erase(it); break; }
		}
	}
	system("cls");
	cout << endl << "*****所有已读留言已经被删除*****" << endl << endl;
}

void PrMessageStore::DelAllMessage() {
	for (auto& ele : rec) {
		if (ele->reciever_sit == "未读") { ele->reciever_sit = "未读已删除"; }
		else if (ele->reciever_sit == "已读") { ele->reciever_sit = "已读已删除"; }
	}
	write_mes();
	rec.clear();
	system("cls");
	cout << endl << "*****所有收到的留言已经被删除*****" << endl << endl;
}