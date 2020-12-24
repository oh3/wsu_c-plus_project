//account.h
#pragma once

#include "wbglobal.h"
#include <time.h>
//https://blog.naver.com/rbcjf1214/221518615553
class Account
{
	const int accnumber;	//상수 멤버 변수
	char name[20];
	char juso[200];
	int  balance;			//잔액
	tm tmc;					//개설일

public:
	Account(int _num, const char* _name, const char* _juso) 
		: accnumber(_num)
	{
		strcpy_s(name, sizeof(name), _name);

		//주소
		strcpy_s(juso, sizeof(name), _juso);
		balance = 0;
		//계좌생성될 때 현재 일시를 저장
		time_t t = time(0); //#include <time.h>
		localtime_s(&tmc, &t);
	}

	Account(int _num, const char* _name, const char* _juso, int _balance, int y,int m,int d)
		: accnumber(_num)
	{
		strcpy_s(name, sizeof(name), _name);
		strcpy_s(juso, sizeof(juso), _juso);
		balance = _balance;

		//계좌생성될 때 전달된 일시를 사용 
		tmc.tm_year = y - 1900;
		tmc.tm_mon = m - 1;
		tmc.tm_mday = d;
	}

	//Get 메서드 
public:
	int GetNumber() const		{ return accnumber; }
	const char* GetName() const { return name;		}
	const char* GetJuso() const { return juso; }
	int GetBalance() const		{ return balance;	}
	tm  GetTm() const			{ return tmc;		}
	//Set 메서드 
	void SetName(const char* value)
	{
		strcpy_s(name, sizeof(name), value);
	}

public:
	//입금 & 출금
	void InputMoney(int money)
	{
		if (money <= 0)
			throw "잘못된 입금액입니다.";
		balance += money;
	}

	void OutputMoney(int money) 
	{
		if (money <= 0)
			throw "잘못된 입금액입니다.";
		if (money > balance)
			throw "잔액이 부족합니다.";

		balance -= money;
	}

	friend ostream& operator<<(ostream& os, Account* acc)
	{
		os << "운송장번호:" << acc->accnumber << " 이름:" << acc->name <<" 주소:" << acc->juso;

		char str[80];
		strftime(str, sizeof(str), "%y-%m-%d %H:%M:%S", &acc->tmc);
		os << " 등록 일시:" << str;
		return os;
	}
};


class CompareByAccNumber	//비교의 대상 number
{
	int accnum;
public:
	//비교할 값을 생성자를 통해 전달받아 맴버변수에 저장
	CompareByAccNumber(int _number) : accnum(_number) {}

	//find_if에서 반복적으로 호출되는 부분
	//vector<Account*> 로 만들어져 있기 때문에 이때 전달되는 타입은
	bool operator()(Account* value)
	{
		return (value->GetNumber() == accnum);
	}
};

class CompareByAccName	//비교의 대상 name
{
	char name[20];
public:
	//비교할 값을 생성자를 통해 전달받아 맴버변수에 저장
	CompareByAccName(const char* _name)
	{
		strcpy_s(name, sizeof(name), _name);
	}

	//find_if에서 반복적으로 호출되는 부분
	//vector<Account*> 로 만들어져 있기 때문에 이때 전달되는 타입은
	//함수객체.....
	bool operator()(Account* value)
	{
		return ( strcmp(value->GetName(), name) == 0);
	}
};
