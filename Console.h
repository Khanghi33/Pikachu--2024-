#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>

#define MOVE 0
#define ENTER 1
#define CLICK 2
#define GAMESTART 3
#define OUTREACH 4
#define VICTORY 5
#define LOSE 6
#define CORRECT 7
#define OPENING 8
#define WRONG 9


void Setupconsole();                       //Set up console before starting game

void SetWindowSize(SHORT, SHORT);          //Set size of console

void SetScreenBufferSize(SHORT, SHORT);    //Set buffer size of console

void CenterConsoleWindow(SHORT, SHORT);	   //Set Center of console

void ShowScrollbar(bool);                  //Turn on/off Scroll bar

void ShowCur(bool);						   //Turn on/off Cursor

void GoTo(SHORT, SHORT);				   //Move cursor to position

void SetColor(int, int);                   //Change color

void DisableResizeWindow();                //Disable resize console

void printRectangle(int, int, int, int);   //print rectangle by (pos x/pos y/width/height)

int getinputfromuser();					   //Get input from user to move cursor or select

//void playSound(int i);					   // Play sound