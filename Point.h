#pragma once
#define BOARDWIDTH 5
#define BOARDHEIGTH 6
struct Point
{
	int row{};
	int col{};
	char character = ' ';
	int isValid = 1;
};

void createBoard(Point**&);	//Initialize matrix and randow characters

void deleteBoard(Point**&); //Deallocate matrix 

void shuffleBoard(Point**&);//Shuffle matrix (random)

