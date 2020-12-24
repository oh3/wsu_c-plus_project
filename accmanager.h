//accmanager.h
#pragma once
//page115
#include <vector>
using namespace std;
#include "account.h"		//data≈¨∑°Ω∫

class accManager
{
	vector<Account*> base;// Account* base;

public:
	accManager();
	~accManager();

public:
	void Run();

private:
	keydata SelectMenu();
	void ListAll();

	void AddAccount();				//insert
	void RemoveAccount();			//delete
	void SearchAccountByNum();		//select
	void SearchAccountByNum1();		//select

	void SearchAccountByName();		//select
	void SearchAccountByName1();		//select

	void UpdateInputAccount();		//update
	void UpdateOutputAccount();		//update

	int NumberToIdx(int accnumber);	//select
};


