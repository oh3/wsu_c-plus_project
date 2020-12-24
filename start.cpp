//start.cpp

#include <iostream>
using namespace std;
#include "accmanager.h"

class CompareByIntP
{
	int number;
public:
	CompareByIntP(int _number) : number(_number) {}
	
	bool operator()(int* value)
	{
		return (*value == number);
	}
};

class Data
{
	int number;
	char name[20];
	char juso[200];
public:
	Data(int n, const char* _name, const char* _juso) : number(n)
	{
		strcpy_s(name, sizeof(name), _name);
		strcpy_s(juso, sizeof(juso), _juso);
	}

	int GetNumber() const		{ return number;	}
	const char* GetName() const { return name;		}
	const char* GetJuso() const { return juso; }

	void print() const
	{
		cout << name << "," << number << "," << juso << endl;
	}
};


class CompareByNumber	//비교의 대상 number
{
	int number;
public:
	//비교할 값을 생성자를 통해 전달받아 맴버변수에 저장
	CompareByNumber(int _number) : number(_number) {}

	//find_if에서 반복적으로 호출되는 부분
	//vector<Data*> 로 만들어져 있기 때문에 이때 전달되는 타입은
	//Data*
	bool operator()(Data* value)
	{
		return (value->GetNumber() == number);
	}
};

class CompareByName	//비교의 대상 name
{
	char name[20];
public:
	//비교할 값을 생성자를 통해 전달받아 맴버변수에 저장
	CompareByName(const char* _name)
	{
		strcpy_s(name, sizeof(name), _name);
	}

	//find_if에서 반복적으로 호출되는 부분
	//vector<Data*> 로 만들어져 있기 때문에 이때 전달되는 타입은
	//Data*
	bool operator()(Data* value)
	{
		return ( strcmp(value->GetName(), name) == 0);
	}
};

int main()
{

	accManager* sm = new accManager();
	sm->Run();
	delete sm;	

	return 0;
}