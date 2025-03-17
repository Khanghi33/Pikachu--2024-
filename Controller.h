#pragma once
#include "Menu.h"
#include "Point.h"
#include "CheckPattern.h"
void RunGame();   //Control the game

void DelettePair(Point**& board, int del_i_1, int del_j_1, int del_i_2, int del_j_2, int left, int top, int width, int height); //Delete 2 boxes which success connect

void showBoard(Point** board, int left, int top, int width, int height);	//Print the matrix

void returnValidCells(Point** board, int& cur_i, int& cur_j);				//set cur box to the nearest box after delete

void advanceArrowup(Point** board, int& i, int& j);							//Advance move for arrow up

void advanceArrowdown(Point** board, int& i, int& j);						//Advance move for arrow down

void move_Classic(Point**& board, int& score, int left, int top, int width, int height);	//System movement for classic mode

void renderBackground(std::string imagefile, Point** board, int left, int top, int width, int height);	//Read background game from file and print

void printBackground(char image[31][50], int cur_i, int cur_j, int width, int height);					//Print each part of background if it isn't valid

void moveSuggestion(Point** board, int, int, int, int);													//Suggest to do Matching

void drawHorizontalLine(int, int, int, int, int, int, int, int);										//Draw horizontal line of Draw line system

void deleteHorizontalLine(int, int, int, int, int, int, int, int);										//Delete horizontal line of Draw line system

void drawVerticalLine(int, int, int, int, int, int, int, int);											//Draw vertical line of Draw line system

void deleteVerticalLine(int, int, int, int, int, int, int, int);										//Delete vertical line of Draw line system

void drawLine(Point**, int, int, int, int, int, int, int, int);											//Draw line system 

void move_Advance(Point**& board, int& score, int left, int top, int width, int height);				//System movement for advance mode