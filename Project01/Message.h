#pragma once
#ifndef MESSAGE
#define MESSAGE
#include <vector>
#include <string>
using namespace std;
extern string message_file;
struct Message {
	string mes_id;
	string send_time;
	string sender;
	string reciever;
	string sender_sit;        //sent successfully or delete successfully or has been read
	string reciever_sit;      //hasn't been read or delete successfully
	string content;
};

class MessageStore {
public:
	MessageStore();
	void write_mes();
protected:
	vector<Message*> mes;
};

class PrMessageStore :public MessageStore {
public:
	PrMessageStore(string user_id);
	void Send();
	void Lookrecieve();
	void Looksend();
	void Lookmessage();
	void SimplePrintRe(Message* m);
	void SimplePrintSe(Message* m);
	void DelSingleMessage();
	void DelAllSend();
	void DelReadedMessage();
	void DelAllMessage();
private:
	string user_id;
	vector<Message*> sen, rec;
};
#endif
