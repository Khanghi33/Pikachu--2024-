#include "Console.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
using namespace std;

// Set up all
void Setupconsole()
{
    ShowCur(false);
    ShowScrollbar(false);
    CenterConsoleWindow(90, 80);
    DisableResizeWindow();
}
void CenterConsoleWindow(SHORT width, SHORT height)
{
    // Set up size of console
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = width - 1;
    windowSize.Bottom = height - 1;
    SetConsoleWindowInfo(hStdout, TRUE, &windowSize);

    // Get size of console
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Calcute position to set center
    int consolePosX = (screenWidth - width) / 4;
    int consolePosY = (screenHeight - height) / 9;

    // Move Console to the new position
    HWND hwndConsole = GetConsoleWindow();
    MoveWindow(hwndConsole, consolePosX, consolePosY, width * 8, height * 8, TRUE); // Mỗi ký tự có kích thước là 8x8 pixel
}
//Set size of console
void SetWindowSize(SHORT width, SHORT height)
{   // Get handle
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    //Set size from input
    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    //Set size to console
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
//Set buffer size of console
void SetScreenBufferSize(SHORT width, SHORT height)
{   
    //Get handle
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    //Set size from input
    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    //Set size to buffer screen
    SetConsoleScreenBufferSize(hStdout, NewSize);
}
//turn on/off cursor
void ShowCur(bool CursorVisibility)
{
    //Get handle
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    //Set appear or disappear to cursor
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}
//turn on/off scroll bar
void ShowScrollbar(bool Show)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
//Not allow player to resize window
void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}
//Move cursor to the position
void GoTo(SHORT posX, SHORT posY)
{
    //Get handle
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    //Set coordinate from input
    Position.X = posX;
    Position.Y = posY;
    //Set new position to cursor
    SetConsoleCursorPosition(hStdout, Position);
}
//Set color
void SetColor(int backgound_color, int text_color)
{
    //Get handle
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    //Get color code from input and set color to console
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
void printRectangle(int left, int top, int width, int height)
{
    //print top edge of the rec
    GoTo(left, top);
    putchar(218); // char ┌
    for (int i = 0; i < width; i++)
        putchar(196); // -
    putchar(191); // char ┐

    //print the middle of rec (right edge, left edge and middle)
    int i = 0;
    for (; i < height; i++)
    {
        GoTo(left, top + i + 1);
        putchar(179); // char |
        GoTo(left + width + 1, top + i + 1);
        putchar(179);
    }
    //print bottom edge of the rec
    GoTo(left, top + i);
    putchar(192); // char └	
    for (i = 0; i < width; i++)
        putchar(196); // char -
    putchar(217); // char ┘
}
// use vector to store all soundfile
//static vector<const wchar_t*> soundFile{ L"Step.wav",L"Enter.wav",L"Click.wav",L"GameStart.wav",L"Outreach.wav",L"Victory.wav",L"Lose.wav",L"Correct.wav",L"Opening.wav",L"Wrong.wav" };
/**void playSound(int i)
{
    //play sound
    PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
}*/
// get input to action
int getinputfromuser()
{
    int c = _getch();
    while (c) {
        if (c == 72) //Arrow_up
            return 1;
        else if (c == 75)  //Arrow_Left
            return 2;
        else if (c == 77) //Arrow_Right
            return 3;
        else if (c == 80) //Arrow_Down
            return 4;
        else if (c == 87 || c == 119) //W, w
            return 1;
        else if (c == 65 || c == 97)  //A, a
            return 2;
        else if (c == 68 || c == 100) //D, d
            return 3;
        else if (c == 83 || c == 115) //S, s
            return 4;
        else if (c == 'h' || c == 'H') //H,h
            return 5;
        else if (c == 'm' || c == 'M') //M,m
            return 6;
        else if (c == 13)             //Enter
            return 0;
        c = _getch();
    }
}