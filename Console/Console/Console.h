#pragma once
#include "windows.h"

enum ConsoleType {
    ConsoleType_Input,
    ConsoleType_Output,
    ConsoleType_Error
};

enum ConsoleColor {
    ConsoleColor_Red,
    ConsoleColor_Green,
    ConsoleColor_Blue,
    ConsoleColor_Black,
    ConsoleColor_White
};

class Console
{
public:
    Console(ConsoleType type);
    ~Console();

    void show_cursor(bool show);
    void set_console_color(ConsoleColor forge_color, ConsoleColor back_color);
    void clear_console(ConsoleColor forge_color, ConsoleColor back_color);
    void clear_line(short line);
    void set_cursor_xy(short x, short y);
private:
    WORD get_forge_color(ConsoleColor color);
    WORD get_back_color(ConsoleColor color);
    HANDLE console_handle_ = NULL;
};

