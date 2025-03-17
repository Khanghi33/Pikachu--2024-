#include "Point.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
void createBoard(Point** &board)
{
	// Allocate 2D matrix
	board = new Point * [BOARDHEIGTH];
	for (int i = 0; i < BOARDHEIGTH; i++)
	{
		board[i] = new Point[BOARDWIDTH];
	}
	int length = BOARDHEIGTH * BOARDWIDTH;
	srand(time(0));
	// Random char in 1D Array
	int* characters = new int[length];
	for (int i = 0; i < length - 1; i += 2)
	{
		char ch = 'A' + rand() % 26;
		characters[i] = ch;
		characters[i + 1] = ch;
	}
	for (int i = 0; i < length; i++)
	{
		int idx = rand() % length;
		if (idx != i) {
			char temp = characters[idx];
			characters[idx] = characters[i];
			characters[i] = temp;
		}
	}
	// Convert 1D to 2D
	for (int i = 0; i < length; i++)
	{
		board[i / BOARDWIDTH][i % BOARDWIDTH].character = characters[i];
	}
	delete[] characters;
	// Assign row, col value
	for (int i = 0; i < BOARDHEIGTH; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			board[i][j].row = i;
			board[i][j].col = j;
		}
	}
}

void deleteBoard(Point**& board)
{
	for (int i = 0; i < BOARDHEIGTH; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

void shuffleBoard(Point**& board)
{
	int countPoint = 0;
	for (int i = 0; i < BOARDHEIGTH; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			if (board[i][j].isValid == 1) countPoint++;
		}
	}
	// Random in 1D Array
	int length = countPoint;
	int* characters = new int[length];
	for (int i = 0; i < length - 1; i += 2)
	{
		char ch = 'A' + rand() % 26;
		characters[i] = ch;
		characters[i + 1] = ch;
	}
	for (int i = 0; i < length; i++)
	{
		int idx = rand() % length;
		if (idx != i) {
			char temp = characters[idx];
			characters[idx] = characters[i];
			characters[i] = temp;
		}
	}
	// Convert to board
	int count = 0;
	for (int i = 0; i < BOARDHEIGTH; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			if (board[i][j].isValid == 1)
			{
				board[i][j].character = characters[count];
				count++;
			}
		}
	}
	delete[] characters;
}

