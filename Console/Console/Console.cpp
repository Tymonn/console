#include "stdafx.h"
#include "Console.h"

Console::Console(ConsoleType type) {
    switch (type) {
        case ConsoleTyle_Input: {
            console_handle_ = ::GetStdHandle(STD_INPUT_HANDLE);
            break;
        }
        case ConsoleTyle_Output: {
            console_handle_ = ::GetStdHandle(STD_OUTPUT_HANDLE);
            break;
        }
        case ConsoleTyle_Error: {
            console_handle_ = ::GetStdHandle(STD_ERROR_HANDLE);
            break;
        }
        default: {

        }
    }
}

Console::~Console() {

}

void Console::show_cursor(bool show) {
    CONSOLE_CURSOR_INFO cursor_info;
    if (GetConsoleCursorInfo(console_handle_, &cursor_info))
    {
        cursor_info.bVisible = show ? TRUE : FALSE;
        SetConsoleCursorInfo(console_handle_, &cursor_info);
    }
}

void Console::set_console_color(ConsoleColor forge_color, ConsoleColor back_color) {
    WORD wforge_color = get_forge_color(forge_color);
    //SetConsoleTextAttribute(console_handle_, color);
    WORD wback_color = get_back_color(back_color);
    SetConsoleTextAttribute(console_handle_, wforge_color | wback_color);
}

void Console::clear_console(ConsoleColor forge_color, ConsoleColor back_color) {
    set_console_color(forge_color, back_color);

    //This structure will hold all of the console info,including the size of our console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(console_handle_, &csbi)) {
        //write space character into the console buffer
        COORD coord = { 0,0 };
        DWORD count = 0;
        FillConsoleOutputCharacter(console_handle_, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        FillConsoleOutputAttribute(console_handle_, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        // locate the cursor at the origin positon
        SetConsoleCursorPosition(console_handle_, coord);
    }
}

void Console::clear_line(short line) {
    COORD coord = {0, line};
    DWORD count = 0;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(console_handle_, &csbi)) {
        FillConsoleOutputCharacter(console_handle_, ' ', csbi.dwSize.X, coord, &count);
    }
}

void Console::set_cursor_xy(short x, short y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(console_handle_, coord);
}

WORD Console::get_forge_color(ConsoleColor color) {
    //default white color
    WORD wcolor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    switch (color) {
    case ConsoleColor_Red: {
        wcolor = FOREGROUND_RED;
        break;
    }
    case ConsoleColor_Green: {
        wcolor = FOREGROUND_GREEN;
        break;
    }
    case ConsoleColor_Blue: {
        wcolor = FOREGROUND_BLUE;
        break;
    }
    case ConsoleColor_Black: {
        wcolor = (~FOREGROUND_RED) & (~FOREGROUND_GREEN) & (~FOREGROUND_BLUE);
        break;
    }
    default: { //defult use white color
    }
    }
    
    return wcolor;
}

WORD Console::get_back_color(ConsoleColor color) {
    //default white color
    WORD wcolor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    switch (color) {
    case ConsoleColor_Red: {
        wcolor = BACKGROUND_RED;
        break;
    }
    case ConsoleColor_Green: {
        wcolor = BACKGROUND_GREEN;
        break;
    }
    case ConsoleColor_Blue: {
        wcolor = BACKGROUND_BLUE;
        break;
    }
    case ConsoleColor_Black: {
        wcolor = (~BACKGROUND_RED) & (~BACKGROUND_GREEN) & (~BACKGROUND_BLUE);
        break;
    }
    default: { //defult use white color
    }
    }

    return wcolor;
}