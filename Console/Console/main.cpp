// Console.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "Console.h"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
    Console c(ConsoleType_Output);
    c.show_cursor(false);    
    c.clear_console(ConsoleColor_Green, ConsoleColor_White);
    //c.set_console_color(ConsoleColor_Green, ConsoleColor_White);  
    int x = 5;
    int y = 10;
    c.set_cursor_xy(x, y);
    for (int i = 0; i < 10; i++) {
        ::Sleep(1000);
        std::stringstream stream;
        stream << "Hello�� ��λ�����Ե� " << 10 - i << " ��.";
        c.clear_line(y);
        c.set_cursor_xy(x, y);
        std::cout << stream.str();
    }

    return 0;
}