#pragma once
#include "Point.h"

bool checkLine(Point**, int, int, int, int);		//Check horizontal line and vertical line

bool checkI(Point**, int, int, int, int);			//Check I-Matching

bool checkL(Point**, int, int, int, int);			//Check L-Matching

bool checkZ(Point**, int, int, int, int);			//Check Z-Matching

bool checkU(Point**, int, int, int, int);			//Check U-Matching

bool checkPatterns(Point**, int, int, int, int);	//Check and identify 4 types of Matching 

bool checkValidPairs(Point**);						//Check if the matrix still have 2 pair of boxes to matching or not

