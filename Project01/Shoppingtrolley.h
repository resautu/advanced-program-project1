#pragma once
#ifndef SHOPPINGTROLLEY
#define SHOPPINGTROLLEY
#include <string>
#include <vector>
using namespace std;
extern string shopttro_file;
struct ShopGood {
	string sg_id;
	string good_name;
	string good_id;
	string buyer_id;
	string seller_id;
	int number;
	double price;
};

class Shopttroing {
public:
	Shopttroing();
	void DelGood(string sg_id);
	void DelSeller(string seller_id);
	void ClearGood(string buyer_id);
	void InsertGood(ShopGood* sg);
	void ChangeGood(string sg_id, int num);
	void write_st();
protected:
	vector<ShopGood*>sgings;
};

class Shopttro :public Shopttroing {
public:
	Shopttro(string buyer_id);
	vector<ShopGood*> getsgs() const;
	void TtroInsert(ShopGood* sg);
	void TtroDel();
	void TtroDel(string sg_id);
	void Ttroprint(ShopGood* sg);
private:
	vector<ShopGood*> sgs;
};

#endif
