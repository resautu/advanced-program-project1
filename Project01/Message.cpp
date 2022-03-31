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
		if (!f.is_open()) cout << "*********�����ļ����س���,����Ҫ������������**********" << endl;
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
	f << "����ID,����ʱ��,������ID,������ID,����״̬,����״̬,��������" << endl;
	for (auto& ele : mes) {
		f << ele->mes_id << "," << ele->send_time << "," << ele->sender << "," << ele->reciever << "," << ele->sender_sit << "," << ele->reciever_sit << "," << ele->content << endl;
	}
	f.close();
}

PrMessageStore::PrMessageStore(string user_id) {
	for (auto& ele : mes) {
		if (ele->sender == user_id && ele->sender_sit.find("��ɾ��") == string::npos) {
			sen.push_back(ele);
		}
		else if (ele->reciever == user_id && ele->reciever_sit.find("��ɾ��") == string::npos) {
			rec.push_back(ele);
		}
	}
	this->user_id = user_id;
}

void PrMessageStore::Send() {
	cout << "����������˵��û�ID:";
	string id; id.clear(); cin.clear();
	getline(cin, id);
	if (id == user_id) {
		system("cls");
		cout << endl << "******�����ܸ����Լ�����******" << endl << endl;
		return;
	}
	Usering* u = new Usering;
	if (!u->find_user(id)) {
		system("cls");
		cout << endl << "******���޴��û�******" << endl << endl;
		return;
	}
	string content; content.clear(); cin.clear();
	cout << "��������������:";   getline(cin, content);
	_replace(content, ',', '`');
	Message* message = new Message;
	if (mes.empty()) { message->mes_id = "L001"; }
	else {
		string number = mes[mes.size() - 1]->mes_id.substr(1);
		message->mes_id = ("L" + str_add(number));
	}
	message->content = content; message->sender = user_id; message->reciever = id; message->reciever_sit = "δ��"; message->sender_sit = "�ѷ���";
	time_t t;
	t = time(NULL);
	message->send_time = ctime(&t);
	message->send_time.pop_back();
	sen.push_back(message); mes.push_back(message);
	write_mes();
	system("cls");
	cout << endl << "*******���ͳɹ�*******" << endl << endl;
}

void PrMessageStore::SimplePrintRe(Message* m) {
	cout << left << setw(10) << m->mes_id << setw(30) << m->send_time << setw(12) << m->sender << setw(8) << m->reciever_sit << endl;
}

void PrMessageStore::SimplePrintSe(Message* m) {
	cout << left << setw(10) << m->mes_id << setw(30) << m->send_time << setw(12) << m->sender << setw(8) << m->sender_sit << endl;
}

void PrMessageStore::Lookrecieve() {
	cout << "*********************************************************************" << endl;
	cout << "���Ա��" << "           ����ʱ��           ������ID     ����״̬" << endl;
	for (auto& ele : rec) {
		SimplePrintRe(ele);
	}
	cout << "*********************************************************************" << endl;
}

void PrMessageStore::Looksend() {
	cout << "*********************************************************************" << endl;
	cout << "���Ա��" << "           ����ʱ��           ������ID     ����״̬" << endl;
	for (auto& ele : sen) {
		SimplePrintSe(ele);
	}
	cout << "*********************************************************************" << endl;
}

void PrMessageStore::Lookmessage() {
	cout << "����������鿴�����Ա�ţ�";
	string id; cin.clear();
	getline(cin, id);
	for (auto& ele : rec) {
		if (ele->mes_id == id) {
			ele->reciever_sit = "�Ѷ�";
			if (ele->sender_sit == "�ѷ���") { ele->sender_sit = "�Ѷ�"; }
			write_mes();
			cout << "************************************" << endl;
			cout << "���Ա�ţ�" << ele->mes_id << endl;
			cout << "����ʱ�䣺" << ele->send_time << endl;
			cout << "�����ߣ�" << ele->sender << endl;
			cout << "�ʼ�״̬��" << ele->reciever_sit << endl;
			cout << "�ʼ����ݣ�" << ele->content << endl;
			cout << "************************************" << endl << endl << endl;
			return;
		}
	}
	for (auto& ele : sen) {
		if (ele->mes_id == id) {
			cout << "************************************" << endl;
			cout << "���Ա�ţ�" << ele->mes_id << endl;
			cout << "����ʱ�䣺" << ele->send_time << endl;
			cout << "�����ߣ�" << ele->sender << endl;
			if (ele->reciever_sit.find("�Ѷ�") != string::npos) { cout << "�ʼ�״̬���Ѷ�" << endl; }
			else if (ele->reciever_sit.find("δ��") != string::npos) { cout << "�ʼ�״̬��δ��" << endl; }
			cout << "�ʼ����ݣ�" << ele->content << endl;
			cout << "************************************" << endl << endl << endl;
			return;
		}
	}
	system("cls");
	cout << endl << "*******�����ķ��ͺͽ��յ��ʼ���δ�ҵ��ñ�ŵ��ʼ�*******" << endl << endl;
}

void PrMessageStore::DelSingleMessage() {
	cout << "����������ɾ�������Ա�ţ�";
	string id; cin.clear();
	getline(cin, id);
	auto it1 = rec.begin(), it2 = sen.begin();
	for (auto& ele : rec) {
		if (ele->mes_id == id) {
			if (ele->reciever_sit == "�Ѷ�") { ele->reciever_sit = "�Ѷ���ɾ��"; }
			else if (ele->reciever_sit == "δ��") { ele->reciever_sit = "δ����ɾ��"; }
			write_mes();
			rec.erase(it1);
			system("cls");
			cout << endl << "*****ɾ���ɹ�������*****" << endl << endl;
			return;
		}
		it1++;
	}
	for (auto& ele : sen) {
		if (ele->mes_id == id) {
			if (ele->reciever_sit.find("�Ѷ�")) { ele->sender_sit = "��ɾ��"; }
			else if (ele->reciever_sit.find("δ��") != string::npos) {
				ele->sender_sit = "��ɾ��";
				ele->reciever_sit = "δ����ɾ��";
			}
			write_mes();
			rec.erase(it2);
			system("cls");
			cout << endl << "*****ɾ���ɹ�������*****" << endl << endl;
			return;
		}
		it2++;
	}
	system("cls");
	cout << endl << "*******�����ķ��ͺͽ��յ��ʼ���δ�ҵ��ñ�ŵ��ʼ�*******" << endl << endl;
}

void PrMessageStore::DelAllSend() {
	for (auto& ele : sen) {
		if (ele->reciever_sit.find("�Ѷ�") != string::npos) { ele->sender_sit = "��ɾ��"; }
		else if (ele->reciever_sit.find("δ��") != string::npos) {
			ele->sender_sit = "��ɾ��";
			ele->reciever_sit = "δ����ɾ��";
		}
	}
	write_mes();
	sen.clear();
	system("cls");
	cout << endl << "*****���з��ͼ�¼�Ѿ���ɾ��*****" << endl << endl;
}

void PrMessageStore::DelReadedMessage() {
	int count = 0;
	for (auto& ele : rec) {
		if (ele->reciever_sit == "�Ѷ�") { ele->reciever_sit = "�Ѷ���ɾ��"; }
		count++;
	}
	write_mes();
	for (int i = 0; i < count; i++) {
		auto it = rec.begin();
		for (; it < rec.end(); it++) {
			if ((*it)->reciever_sit == "�Ѷ���ɾ��") { rec.erase(it); break; }
		}
	}
	system("cls");
	cout << endl << "*****�����Ѷ������Ѿ���ɾ��*****" << endl << endl;
}

void PrMessageStore::DelAllMessage() {
	for (auto& ele : rec) {
		if (ele->reciever_sit == "δ��") { ele->reciever_sit = "δ����ɾ��"; }
		else if (ele->reciever_sit == "�Ѷ�") { ele->reciever_sit = "�Ѷ���ɾ��"; }
	}
	write_mes();
	rec.clear();
	system("cls");
	cout << endl << "*****�����յ��������Ѿ���ɾ��*****" << endl << endl;
}