//wbglobal.cpp

#include "wbglobal.h"


//화면을 지우는 메서드
void wbglbal::clrscr()
{
    system("cls");
}

//화면을 잠시 멈추는 메서드
void wbglbal::pause()
{
    cout << "아무키나 누르세요....";
    _getch();
}

//수를 입력받는 메서드
int wbglbal::getnum(const char* title)
{
    //    int num;
    //    cin >> num;
    //    return num;

    int num;
    char buf[255 + 1];

    cout << title << " : ";
    cin.getline(buf, 255); //버퍼에 입력받음, gets()동일하다
    cin.clear();//cin 내부 버퍼를 지움
    sscanf_s(buf, "%d", &num); //포맷에 맞게 버퍼에 내용을 정수로 변환

    return num;
}

// 문자열을 입력받는 메서드
const char* wbglbal::getstr(const char* title)
{
    char* buf = new char[255 + 1];

    cout << title << " : ";
    cin.getline(buf, 255);
    cin.clear();

    return buf;
}

//기능 키(F1..)를 입력받는 메서드
keydata wbglbal::getkey()       //#include <conio.h>
{
    int key = _getch();
    if (key == 27) //ESC를 누를 때의 key 값이 27임
    {
        return ESC;
    }

    if (key == 0) //기능 키를 눌렀을 때는 getch의 반환값이 0임
    {
        //어떤 기능 키를 눌렀는지 확인하려면 getch를 다시 호출해야 함
        //사용자에게 다시 키를 입력받는 것은 아님
        key = _getch();

        switch (key) //입력한 키에 따라 약속된 값 반환
        {
        case 59: return F1;
        case 60: return F2;
        case 61: return F3;
        case 62: return F4;
        case 63: return F5;
        case 64: return F6;
        case 65: return F7;
        }
    }
    return NO_DEFINED; //열거되지 않은 키를 눌렀을 때
}
