//wbglobal.h
#pragma once

#include <iostream>
using namespace std;
#include <conio.h>

enum keydata
{
    NO_DEFINED, F1, F2, F3, F4, F5, F6, F7, ESC
};

class wbglbal
{
public:
    static void clrscr();                        //화면을 지우는 메서드
    static void pause();                         //화면을 잠시 멈추는 메서드
    static int getnum(const char* title);        //수를 입력받는 메서드
    static const char* getstr(const char* title); //문자열을 입력받는 메서드
    static keydata getkey();                    //기능 키를 입력받는 메서드

private:
    wbglbal()
    {
    }

    ~wbglbal()
    {
    }
};