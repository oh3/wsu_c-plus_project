//accmanager.cpp

#include "accmanager.h"

accManager::accManager()
{
}

accManager::~accManager()
{
    //vector에 저장된 갯수 반환하는 함수 
    //base.size();
    //순회알고리즘1(전통적인 방식)
    for (int i = 0; i < (int)base.size(); i++)
    {
        delete base[i];
    }
}

void accManager::Run()
{
    int key = 0;
    while ((key = SelectMenu()) != ESC)
    {
        switch (key)
        {
            case F1: AddAccount();          break;
            case F2: RemoveAccount();       break;
            case F3: SearchAccountByNum();  break;
            case F4: SearchAccountByName(); break;
            case F5: UpdateInputAccount();  break;
            //case F6: UpdateOutputAccount(); break;
            default: cout << "잘못된 메뉴를 선택하였습니다." << endl;
        }
        wbglbal::pause();
    }
}

keydata accManager::SelectMenu()
{
    wbglbal::clrscr();
    ListAll();
    cout << "-----------------------------------------" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "\tWS 택배 관리 시스템 " << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "[F1] 운송장 추가" << endl;
    cout << "[F2] 운송장 삭제" << endl;
    cout << "[F3] 운송장번호로 검색(KEY)" << endl;
    cout << "[F4] 고객명으로 검색(다수)" << endl;
    cout << "[F5] 배송시뮬레이터" << endl;
    cout << "[ESC] 종료" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "메뉴키를 입력해주세요" << endl;

    return wbglbal::getkey();
}

//==========================================================
void accManager::ListAll()
{
    //순회알고리즘1(STL의 iterator를 사용한 방식) : 구간
    vector<Account*>::iterator begin = base.begin();    //시작점
    vector<Account*>::iterator end = base.end();        //끝점의 다음위치

    for (int i=0; begin != end; begin++, i++ )
    {
        cout << "[" << i << "]";
        Account* acc = *begin;  //<===============================
        if (acc)                //실제 학생이 보관되었는지 확인
        {
            cout << acc;        //출력연산자재정의
        }
        cout << endl;
    }
}

void accManager::AddAccount()
{
    //[정상흐름]
    //저장정보를 입력받는다.
    //저장객체를 생성한다.(저장정보를 이용해서)
    //저장한다. (저장객체를)

    //[예외흐름 적용]

    int accnumber;
    char name[20];
    char juso[50];

    accnumber = wbglbal::getnum("신규 운송장 번호를 입력하세요.");
    strcpy_s(name, sizeof(name), wbglbal::getstr("이름을 입력하세요"));

    //주소등록
    strcpy_s(juso, sizeof(juso), wbglbal::getstr("주소를 입력해주세요"));
    //=================================================================

    Account* acc = new Account(accnumber, name,juso);

    base.push_back(acc);    //acc 저장해 줘~~!!!!

    cout << "저장되었습니다." << endl;    
}

//직접 만든 검색 함수를 활용하여 삭제 연산 수행
void accManager::RemoveAccount()
{
    try
    {
        int accnumber;
        accnumber = wbglbal::getnum("삭제할 운송장 번호를 입력하세요");

        int idx = NumberToIdx(accnumber);   //직접 만든 검색함수 호출

        vector<Account*>::iterator cur = base.begin();
        cur = cur + idx;
        base.erase(cur);            //STL에서 지원되는 삭제함수 

        cout << "삭제되었습니다" << endl; 
    }
    catch (const char* msg)
    {
        cout << "[삭제에러] " << msg << endl; 
    }   
}

//직접 검색
void accManager::SearchAccountByNum()
{
    try
    {
        int accnumber = 0;
        accnumber = wbglbal::getnum("검색할 운송장 번호를 입력하세요");

        int idx = NumberToIdx(accnumber);   //직접 만든 검색함수 호출

        Account* acc = base[idx];
        cout << acc << endl;
    }
    catch (const char* msg)
    {
        cout << "[검색에러] " << msg << endl;
    }
}

//find_if함수 활용
void accManager::SearchAccountByNum1()
{
    try
    {
        int accnumber = 0;
        accnumber = wbglbal::getnum("검색할 운송장 번호를 입력하세요");

        CompareByAccNumber cban(accnumber);
        vector<Account*>::iterator itr = find_if(base.begin(), base.end(), cban);

        Account* acc = *itr;
        cout << acc << endl;
    }
    catch (const char* msg)
    {
        cout << "[검색에러] " << msg << endl;
    }
}

void accManager::SearchAccountByName()
{
    char name[20];
    strcpy_s(name, sizeof(name), wbglbal::getstr("검색할 고객 이름을 입력하세요"));

    for (int i = 0; i < (int)base.size(); i++)
    {
        Account* acc = base[i];
        if (strcmp(acc->GetName(), name) == 0)
        {
                cout << base[i] << endl;                
        }
    }    
}

//find_if함수 활용
void accManager::SearchAccountByName1()
{
    char name[20];
    strcpy_s(name, sizeof(name), wbglbal::getstr("검색할 고객 이름을 입력하세요"));

    CompareByAccName cban(name);
    vector<Account*>::iterator itr = find_if(base.begin(), base.end(), cban);
    if (itr == base.end())
    {
        cout << "없다" << endl; 
        return;
    }
    Account* acc = *itr;
    cout << acc << endl;
}

void accManager::UpdateInputAccount()
{
    try
    {
        int accnumber = 0;
        accnumber = wbglbal::getnum("입금할 계좌 번호를 입력하세요");

        //검색기능 요청 
        int idx = NumberToIdx(accnumber);   //<==  throw

        //입금 입력 처리
        Account* acc = base[idx];
        int money = wbglbal::getnum("입금액");
        acc->InputMoney(money);                 //<== throw
        cout << "입금되었습니다" << endl;
    }
    catch (const char* msg)
    {
        cout << msg << endl; 
    }
}

void accManager::UpdateOutputAccount()
{
    try
    {
        int accnumber = 0;
        accnumber = wbglbal::getnum("출금할 계좌 번호를 입력하세요");

        //검색기능 요청 
        int idx = NumberToIdx(accnumber);   //<==  throw

        //출금 입력 처리
        Account* acc = base[idx];
        int money = wbglbal::getnum("출금액");
        acc->OutputMoney(money);                 //<== throw
        cout << "출금되었습니다" << endl;
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
}

int  accManager::NumberToIdx(int accnumber)
{
    //순회
    for (int i = 0; i < (int)base.size(); i++)
    {
        Account* acc = base[i];
        if (acc->GetNumber() == accnumber)
        {
            return i;
        }
    }
    throw "해당 계좌번호는 존재하지 않습니다.";
}