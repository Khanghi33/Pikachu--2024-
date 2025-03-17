#include "Controller.h"
#include <algorithm>
#include <fstream>
#include <cmath>

using namespace std;

//Mange the game
void RunGame()
{
    Accounts player;
    Setupconsole();
    Mainbackground();
    Loginbackground(player);
    int exit = 1;
    do {
        Optionbackground(player);
        SelectOption(exit, player);
    } while (exit != 0);
    system("cls");
}
//Delete 2 boxes
void DelettePair(Point** &board, int del_i_1, int del_j_1, int del_i_2, int del_j_2, int left, int top, int width, int height)
{
    //Print black rectangle to delete
    SetColor(0, 0); printRectangle(left + del_j_1 * (width + 2), top + del_i_1 * (height + 1), width, height);
    SetColor(0, 0); printRectangle(left + del_j_2 * (width + 2), top + del_i_2 * (height + 1), width, height);
    GoTo(left + del_j_1 * (width + 2) + 4, top + del_i_1 * (height + 1) + 2);
    putchar(' ');
    GoTo(left + del_j_2 * (width + 2) + 4, top + del_i_2 * (height + 1) + 2);
    putchar(' ');
    //Set not valid
    board[del_i_1][del_j_1].isValid = 0;
    board[del_i_2][del_j_2].isValid = 0;
}
//Set cursor to the nearest cell when the current cell had deleted
void returnValidCells(Point** board, int& cur_i, int& cur_j)
{
    float distance = 100;
    float mindis = 99;
    int cur_a = -1, cur_b = -1;
    //Calcute and find the minimum distance from current cell to orther valid cells
    for (int i=0 ; i < BOARDHEIGTH ; i++)
        for (int  j=0 ; j < BOARDWIDTH ; j++)
            if (board[i][j].isValid) {
                distance = sqrt(pow(cur_i - i, 2) + pow(cur_j - j, 2));
                if (distance < mindis) {
                    mindis = distance;
                    cur_a = i;
                    cur_b = j;
                }
            }
    //if find set cursor to that cells
    if (cur_a != -1)
        cur_i = cur_a;
    cur_j = cur_b;
}
//Read file background and print
void renderBackground(string imagefile, Point** board, int left, int top, int width, int height)
{
    //Read file
    char image[31][50];
    ifstream fin;
    fin.open(imagefile,ios::in);
    if (!fin)
        cout << "Cannot print image file!!";
    else {
        for (int i = 0; i < 31; i++)
            fin.getline(image[i], 50);
    }
    fin.close();
    int rows = BOARDHEIGTH;
    int cols = BOARDWIDTH;
    //print the part of background which have the position is invalid in struct Point
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            if (!board[i][j].isValid)
                printBackground(image, j * (width + 2), i * (height + 1), width + 2, height + 2);
        }
}
//Print part of background
void printBackground(char image[31][50], int cur_i, int cur_j, int width, int height)
{
    for (int i = cur_j; i < height + cur_j ; i++) {
        GoTo(cur_i+4, i+2);
        for (int j = cur_i; j < width + cur_i ; j++)
            cout << image[i][j];
        cout << "\n";
    }
}
//Advance move arrow up
void advanceArrowup(Point** board, int& i, int& j) {
    float distance = 100;
    float mindis = 99;
    int cur_a = -1, cur_b = -1;
    //Find nearest cell to cursor
    for (int a = 0; a < i; a++)
        for (int b = 0; b < BOARDWIDTH; b++) {
            if (board[a][b].isValid) {
                distance = sqrt(pow(i - a, 2) + pow(j - b, 2));
                if (distance < mindis) {
                    mindis = distance;
                    cur_a = a;
                    cur_b = b;
                }
            }
        }
    //If success find the nearest valid cell,set cursor to that cell
    if (cur_a != -1) {
        i = cur_a;
        j = cur_b;
    }
    //else
        //playSound(OUTREACH);
}
//Advance move arrow down
void advanceArrowdown(Point** board, int& i, int& j) {
    float distance = 100;
    float mindis = 99;
    int cur_a = -1, cur_b = -1;
    //Find the nearest valid cell
    for (int a = BOARDHEIGTH - 1; a > i; a--)
        for (int b = 0; b < BOARDWIDTH; b++) {
            if (board[a][b].isValid) {
                distance = sqrt(pow(i - a, 2) + pow(j - b, 2));
                if (distance < mindis) {
                    mindis = distance;
                    cur_a = a;
                    cur_b = b;
                }
            }
        }
    //If success file, set cursor to that cell
    if (cur_a != -1) {
        i = cur_a;
        j = cur_b;
    }
    //else
        //playSound(OUTREACH);
}
//System move for classic mode
void move_Classic(Point**& board, int& Score, int left, int top, int width, int height)
{
    int score = 0;
    int rows = BOARDHEIGTH;
    int cols = BOARDWIDTH;
    int pairleft = BOARDHEIGTH * BOARDWIDTH;
    int choice = 1;
    int cur_i = 0, cur_j = 0;
    int prev_i, prev_j;
    int choice_i = -1, choice_j = -1;
    int check = 0;
    string imagefile = "Reshiram.txt";
    SetColor(0, 12);
    printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
    while (pairleft != 0) {
        //print score board
        SetColor(0, 15);
        GoTo(65, 5); cout << "Score: " << "    ";
        GoTo(65, 5); cout << "Score: " << score;
        //If the matrix had no pair of boxes to connect,shuffle matrix
        if (!checkValidPairs(board))
        {
            shuffleBoard(board);
            showBoard(board, left, top, width, height);
        }
        choice = getinputfromuser();
        prev_i = cur_i; prev_j = cur_j;
        //Get input to move or select
        switch (choice) {
        case 0: if (check == 0) { choice_i = cur_i; choice_j = cur_j; } break;
        case 1: cur_i = cur_i - 1; break;
        case 2: cur_j = cur_j - 1; break;
        case 3: cur_j = cur_j + 1; break;
        case 4: cur_i = cur_i + 1; break;
        case 5: moveSuggestion(board, left, top, width, height); score -= 5; break;
        case 6: pairleft = 0; break;

        }
        if (choice != 0) {
            if (cur_i < rows && cur_i >= 0 && cur_j < cols && cur_j >= 0 ) {
                // Move up
                if (choice == 1)
                    if (!board[cur_i][cur_j].isValid)
                        while (!board[cur_i][cur_j].isValid) {
                            cur_i = cur_i - 1;
                            if (cur_i < 0) {
                                cur_i = prev_i;
                                cur_j = prev_j;
                                advanceArrowup(board, cur_i, cur_j);
                                break;
                            }
                        }
                // Move down
                if (choice == 4)
                    if (!board[cur_i][cur_j].isValid)
                        while (!board[cur_i][cur_j].isValid) {
                            cur_i = cur_i + 1;
                            if (cur_i >= rows) {
                                cur_i = prev_i;
                                cur_j = prev_j;
                                advanceArrowdown(board, cur_i, cur_j);
                                break;
                            }
                        }
                // Move left
                if (choice == 2) {
                    if (!board[cur_i][cur_j].isValid) {
                        while (!board[cur_i][cur_j].isValid) {
                            cur_j = cur_j - 1;
                            if (cur_j < 0) {
                                cur_j = prev_j - 1;
                                cur_i++;
                            }
                            if (cur_i >= rows) {
                                cur_i = prev_i;
                                cur_j = prev_j;
                                //playSound(OUTREACH);
                                break;
                            }

                        }
                    }
                }
                // Move right
                if (choice == 3) {
                    if (!board[cur_i][cur_j].isValid) {
                        while (!board[cur_i][cur_j].isValid) {
                            cur_j = cur_j + 1;
                            if (cur_j >= cols) {
                                cur_j = prev_j + 1;
                                cur_i++;
                            }
                            if (cur_i >= rows) {
                                cur_i = prev_i;
                                cur_j = prev_j;
                                //playSound(OUTREACH);
                                break;
                            }
                        }
                    }
                }
                if (prev_i == choice_i && prev_j == choice_j)
                {
                    SetColor(12, 15); printRectangle(left + prev_j * (width + 2), top + prev_i * (height + 1), width, height);
                }
                else if ((prev_i != choice_i || prev_j != choice_j) && board[prev_i][prev_j].isValid)
                {
                    SetColor(0, 15); printRectangle(left + prev_j * (width + 2), top + prev_i * (height + 1), width, height);
                }
                SetColor(0, 12); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                //playSound(MOVE);
            }
            //If reach outreach of matrix, set cursor to the previus current box
            else {
                cur_i = prev_i;
                cur_j = prev_j;
                //playSound(OUTREACH);
            }
        }
        //When choose the box
        else {
            //Choose first box
            if (check == 0) {
                //playSound(CLICK);
                SetColor(12, 15); printRectangle(left + choice_j * (width + 2), top + choice_i * (height + 1), width, height);
                check++;
            }
            //choose second box
            else if (check == 1) {
                SetColor(12, 15); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                Sleep(300);
                //Matching 2 boxes
                //Wrong matching
                if (cur_i == choice_i && cur_j == choice_j) {
                    //playSound(WRONG);
                    SetColor(0, 15); printRectangle(left + choice_j * (width + 2), top + choice_i * (height + 1), width, height);
                    SetColor(0, 15); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                    score -= 2;
                }
                //Success matching
                else if (board[choice_i][choice_j].character == board[cur_i][cur_j].character && checkPatterns(board, choice_i, choice_j, cur_i, cur_j)) {
                    // Plus score
                    if (checkI(board, choice_i, choice_j, cur_i, cur_j)) score++;
                    else if (checkL(board, choice_i, choice_j, cur_i, cur_j)) score += 2;
                    else if (checkZ(board, choice_i, choice_j, cur_i, cur_j)) score += 2;
                    else if (checkU(board, choice_i, choice_j, cur_i, cur_j)) score += 3;
                    //playSound(CORRECT);
                    //delete pair
                    drawLine(board, choice_i, choice_j, cur_i, cur_j, left, top, width, height);
                    showBoard(board, 5, 3, 7, 4);
                    DelettePair(board, choice_i, choice_j, cur_i, cur_j, left, top, width, height);
                    pairleft -= 2;
                    SetColor(0, 15);
                    //print background game
                    renderBackground(imagefile, board, 5, 3, 7, 4);
                    showBoard(board, 5, 3, 7, 4);
                    //Move cursor to the nearest valid cell
                    if (pairleft != 0) {
                        returnValidCells(board, cur_i, cur_j);
                        SetColor(0, 12); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                    }
                }
                //Wrong matching
                else {
                    //playSound(WRONG);
                    SetColor(0, 15); printRectangle(left + choice_j * (width + 2), top + choice_i * (height + 1), width, height);
                    SetColor(0, 15); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                    score -= 2;
                }
                choice_i = -1, choice_j = -1;
                check = 0;
            }
        }
    }
    //playSound(VICTORY);
    Score = score;
}
//System move for advance mode
void move_Advance(Point**& board, int& Score, int left, int top, int width, int height)
{
    int score = 0;
    int rows = BOARDHEIGTH;
    int cols = BOARDWIDTH;
    int pairleft = BOARDHEIGTH * BOARDWIDTH;
    int choice = 1;
    int cur_i = 0, cur_j = 0;
    int prev_i, prev_j;
    int choice_i = -1, choice_j = -1;
    int check = 0;
    string imagefile = "Zekrom.txt";
    SetColor(0, 12);
    printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
    while (pairleft != 0) {
        //print board score
        SetColor(0, 15); GoTo(65, 5);
        cout << "Score: " << "     ";
        SetColor(0, 15); GoTo(65, 5);
        cout << "Score: " << score;
        //If the matrix had't had pair of cells to matching -> shuffle matrix
        if (!checkValidPairs(board))
        {
            shuffleBoard(board);
            showBoard(board, left, top, width, height);
        }
        //Get input from user to move or select
        choice = getinputfromuser();
        prev_i = cur_i; prev_j = cur_j;
        switch (choice) {
        case 0: if (check == 0) { choice_i = cur_i; choice_j = cur_j; } break;
        case 1: cur_i = cur_i - 1; break;
        case 2: cur_j = cur_j - 1; break;
        case 3: cur_j = cur_j + 1; break;
        case 4: cur_i = cur_i + 1; break;
        case 5: moveSuggestion(board, left, top, width, height); score = score - 5;  break;
        case 6: pairleft = 0; break;
        }
        if (choice != 0) {
            if (cur_i < rows && cur_i >= 0 && cur_j < cols && cur_j >= 0) {
                // Move up
                if (choice == 1)
                    if (!board[cur_i][cur_j].isValid)
                        while (!board[cur_i][cur_j].isValid) {
                            cur_i = cur_i - 1;
                            if (cur_i < 0) {
                                cur_i = prev_i;
                                cur_j = prev_j;
                                advanceArrowup(board, cur_i, cur_j);
                                break;
                            }
                        }
                // Move down
                if (choice == 4)
                    if (!board[cur_i][cur_j].isValid)
                        while (!board[cur_i][cur_j].isValid) {
                            cur_i = cur_i + 1;
                            if (cur_i >= rows) {
                                cur_i = prev_i;
                                cur_j = prev_j;
                                advanceArrowdown(board, cur_i, cur_j);
                                break;
                            }
                        }
                // Move left
                if (choice == 2) {
                    if (!board[cur_i][cur_j].isValid) {
                        while (!board[cur_i][cur_j].isValid) {
                            cur_j = cur_j - 1;
                            if (cur_j < 0) {
                                cur_j = prev_j - 1;
                                cur_i++;
                            }
                            if (cur_i >= rows) {
                                cur_i = prev_i;
                                cur_j = prev_j;
                                //playSound(OUTREACH);
                                break;
                            }

                        }
                    }
                }
                // Move right
                if (choice == 3) {
                    if (!board[cur_i][cur_j].isValid) {
                        while (!board[cur_i][cur_j].isValid) {
                            cur_j = cur_j + 1;
                            if (cur_j >= cols) {
                                cur_j = prev_j + 1;
                                cur_i++;
                            }
                            if (cur_i >= rows) {
                                cur_i = prev_i;
                                cur_j = prev_j;
                                //playSound(OUTREACH);
                                break;
                            }
                        }
                    }
                }
                if (prev_i == choice_i && prev_j == choice_j)
                {
                    SetColor(12, 15); printRectangle(left + prev_j * (width + 2), top + prev_i * (height + 1), width, height);
                }
                else if (board[prev_i][prev_j].isValid)
                {
                    SetColor(0, 15); printRectangle(left + prev_j * (width + 2), top + prev_i * (height + 1), width, height);
                }
                SetColor(0, 12); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                //playSound(MOVE);
            }
            //If reach outreach of matrix
            else {
                cur_i = prev_i;
                cur_j = prev_j;
                //playSound(OUTREACH);
            }
        }
        //When select box
        else {
            //Select first box
            if (check == 0) {
                //playSound(CLICK);
                SetColor(12, 15); printRectangle(left + choice_j * (width + 2), top + choice_i * (height + 1), width, height);
                check++;
            //Select second box
            }
            else if (check == 1) {
                SetColor(12, 15); 
                printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                Sleep(300);
                //Worng matching
                if (cur_i == choice_i && cur_j == choice_j) {
                    //playSound(WRONG);
                    SetColor(0, 15); printRectangle(left + choice_j * (width + 2), top + choice_i * (height + 1), width, height);
                    SetColor(0, 15); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                    score = score - 2;
                }
                //Success matching
                else if (board[choice_i][choice_j].character == board[cur_i][cur_j].character && checkPatterns(board, choice_i, choice_j, cur_i, cur_j)) {
                    if (checkI(board, choice_i, choice_j, cur_i, cur_j)) score++;
                    else if (checkL(board, choice_i, choice_j, cur_i, cur_j)) score += 2;
                    else if (checkZ(board, choice_i, choice_j, cur_i, cur_j)) score += 2;
                    else if (checkU(board, choice_i, choice_j, cur_i, cur_j)) score += 3;
                    //playSound(CORRECT);
                    drawLine(board, choice_i, choice_j, cur_i, cur_j, left, top, width, height);
                    DelettePair(board, choice_i, choice_j, cur_i, cur_j, left, top, width, height);
                    pairleft = pairleft - 2;
                    // Move Points to upside
                    if (choice_j != cur_j)
                    {
                        int count = 0;
                        int character[BOARDHEIGTH];
                        for (int i = 0; i < BOARDHEIGTH; i++)
                        {
                            if (board[i][choice_j].isValid == 1)
                            {
                                character[count] = board[i][choice_j].character;
                                count++;
                            }
                        }
                        for (int i = 0; i < count; i++)
                        {
                            board[i][choice_j].character = character[i];
                            board[i][choice_j].isValid = 1;
                        }
                        for (int i = count; i < BOARDHEIGTH; i++)
                        {
                            board[i][choice_j].isValid = 0;
                        }
                        SetColor(0, 0); printRectangle(left + choice_j * (width + 2), top + count * (height + 1), width, height);
                        GoTo(left + choice_j * (width + 2) + 4, top + count * (height + 1) + 2);
                        putchar(' ');
                        count = 0;
                        for (int i = 0; i < BOARDHEIGTH; i++)
                        {
                            if (board[i][cur_j].isValid == 1)
                            {
                                character[count] = board[i][cur_j].character;
                                count++;
                            }
                        }
                        for (int i = 0; i < count; i++)
                        {
                            board[i][cur_j].character = character[i];
                            board[i][cur_j].isValid = 1;
                        }
                        for (int i = count; i < BOARDHEIGTH; i++)
                        {
                            board[i][cur_j].isValid = 0;
                        }
                        SetColor(0, 0); printRectangle(left + cur_j * (width + 2), top + count * (height + 1), width, height);
                        GoTo(left + cur_j * (width + 2) + 4, top + count * (height + 1) + 2);
                        putchar(' ');
                        showBoard(board, left, top, width, height);
                    }
                    else
                    {
                        int count = 0;
                        int character[BOARDHEIGTH];
                        for (int i = 0; i < BOARDHEIGTH; i++)
                        {
                            if (board[i][choice_j].isValid == 1)
                            {
                                character[count] = board[i][choice_j].character;
                                count++;
                            }
                        }
                        for (int i = 0; i < count; i++)
                        {
                            board[i][choice_j].character = character[i];
                            board[i][choice_j].isValid = 1;
                        }
                        for (int i = count; i < BOARDHEIGTH; i++)
                        {
                            board[i][choice_j].isValid = 0;
                            SetColor(0, 0);
                            printRectangle(left + choice_j * (width + 2), top + i * (height + 1), width, height);
                            GoTo(left + choice_j * (width + 2) + 4, top + i * (height + 1) + 2);
                            putchar(' ');
                        }
                        showBoard(board, left, top, width, height);
                    }
                    //print background
                    SetColor(0, 15);
                    renderBackground(imagefile, board, 5, 3, 7, 4);
                    showBoard(board, 5, 3, 7, 4);
                    //set invalid 2 boxes
                    if (pairleft != 0) {
                        returnValidCells(board, cur_i, cur_j);
                        SetColor(0, 12); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                    }
                }
                //Wrong matching
                else {
                    //playSound(WRONG);
                    SetColor(0, 15); printRectangle(left + choice_j * (width + 2), top + choice_i * (height + 1), width, height);
                    SetColor(0, 15); printRectangle(left + cur_j * (width + 2), top + cur_i * (height + 1), width, height);
                    score = score - 2;
                }
                choice_i = -1, choice_j = -1;
                check = 0;
            }
        }
    }
    Score = 1.5 * score;
    //playSound(VICTORY);
}
//Suggest matching
void moveSuggestion(Point** board, int left, int top, int width, int height)
{
    // using 4 loops to check board[i][j] and board[p][q]
    for (int i = 0; i < BOARDHEIGTH; i++)
    {
        for (int j = 0; j < BOARDWIDTH; j++)
        {
            for (int p = 0; p < BOARDHEIGTH; p++)
            {
                for (int q = 0; q < BOARDWIDTH; q++)
                {
                    if (board[i][j].character == board[p][q].character && board[i][j].isValid && board[p][q].isValid && (i != p || j != q))
                    {
                        if (checkPatterns(board, i, j, p, q))
                        {
                            // If pattern was found colorize that two boxes
                            SetColor(12, 15); printRectangle(left + j * (width + 2), top + i * (height + 1), width, height);
                            SetColor(12, 15); printRectangle(left + q * (width + 2), top + p * (height + 1), width, height);
                            Sleep(300);
                            return;
                        }
                    }
                }
            }
        }
    }
}
//Draw horizontal line
void drawHorizontalLine(int row1, int col1, int row2, int col2, int left, int top, int width, int height)
{
    SetColor(12, 15);
    if (row1 == row2)
    {
        int y1 = left + col1 * (width + 2) + 4; // calculate center coord of point1 
        int y2 = left + col2 * (width + 2) + 4; // calculate center cooor of point2
        int yMin = min(y1, y2);
        int yMax = max(y1, y2);
        
        // Loop from point 1 to point 2
        for (int y = yMin; y <= yMax; y++) 
        {
            GoTo(y, top + row1 * (height + 1) + 2);
            putchar(' ');
        }
    }
}
void deleteHorizontalLine(int row1, int col1, int row2, int col2, int left, int top, int width, int height)
{
    SetColor(0, 15);
    if (row1 == row2)
    {
        int y1 = left + col1 * (width + 2) + 4; // calculate center coord of point1 
        int y2 = left + col2 * (width + 2) + 4; // calculate center coord of point2
        int yMin = min(y1, y2);
        int yMax = max(y1, y2);
        // Loop from point 1 to point 2
        for (int y = yMin; y <= yMax; y++) 
        {
            GoTo(y, top + row1 * (height + 1) + 2);
            putchar(' ');
        }
    }
}
void drawVerticalLine(int row1, int col1, int row2, int col2, int left, int top, int width, int height)
{
    SetColor(12, 15);
    if (col1 == col2)
    {
        int x1 = top + row1 * (height + 1) + 2; // calculate center coord of point1 
        int x2 = top + row2 * (height + 1) + 2; // calculate center coord of point2
        int xMin = min(x1, x2);
        int xMax = max(x1, x2);
        // Loop from point 1 to point 2
        for (int x = xMin; x <= xMax; x++)
        {
            GoTo(left + col1 * (width + 2) + 4, x);
            putchar(' ');
        }
    }
}

void deleteVerticalLine(int row1, int col1, int row2, int col2, int left, int top, int width, int height)
{
    SetColor(0, 15);
    if (col1 == col2)
    {
        int x1 = top + row1 * (height + 1) + 2; // calculate center coord of point1
        int x2 = top + row2 * (height + 1) + 2; // calculate center coord of point1
        int xMin = min(x1, x2);
        int xMax = max(x1, x2);
        // Loop from point 1 to point 2
        for (int x = xMin; x <= xMax; x++)
        {
            GoTo(left + col1 * (width + 2) + 4, x);
            putchar(' ');
        }
    }
}

void drawLine(Point** board, int row1, int col1, int row2, int col2, int left, int top, int width, int height)
{
    // check patterns, if pattern was found, draw line based on that pattern. 
    // Draw I
    if (checkI(board, row1, col1, row2, col2))
    {
        if (row1 == row2)
        {
            drawHorizontalLine(row1, col1, row2, col2, left, top, width, height);
            Sleep(320);
            deleteHorizontalLine(row1, col1, row2, col2, left, top, width, height);
        }
        else
        {
            drawVerticalLine(row1, col1, row2, col2, left, top, width, height);
            Sleep(320);
            deleteVerticalLine(row1, col1, row2, col2, left, top, width, height);
        }
    }
    // Draw L
    else if (checkL(board, row1, col1, row2, col2))
    {
        bool c1, c2;
        if (!board[row1][col2].isValid) {
            c1 = checkLine(board, row1, col1, row1, col2);
            c2 = checkLine(board, row2, col2, row1, col2);
            if (c1 && c2) {
                drawHorizontalLine(row1, col1, row1, col2, left, top, width, height);
                drawVerticalLine(row2, col2, row1, col2, left, top, width, height);
                Sleep(320);
                deleteHorizontalLine(row1, col1, row1, col2, left, top, width, height);
                deleteVerticalLine(row2, col2, row1, col2, left, top, width, height);
                return;
            }
        }
        if (!board[row2][col1].isValid) {
            c1 = checkLine(board, row1, col1, row2, col1);
            c2 = checkLine(board, row2, col2, row2, col1);
            if (c1 && c2) {
                drawVerticalLine(row1, col1, row2, col1, left, top, width, height);
                drawHorizontalLine(row2, col2, row2, col1, left, top, width, height);
                Sleep(320);
                deleteVerticalLine(row1, col1, row2, col1, left, top, width, height);
                deleteHorizontalLine(row2, col2, row2, col1, left, top, width, height);
                return;
            }
        }
    }
    // Draw Z
    else if (checkZ(board, row1, col1, row2, col2))
    {
        bool c1, c2, c3;
        int x, y;
        if (col2 < col1) {
            x = col2;
            y = col1;
        }
        else {
            x = col1;
            y = col2;
        }
        for (int i = x + 1; i < y; i++) {
            c3 = checkLine(board, row1, i, row2, i);
            if (c3) {
                c1 = checkLine(board, row1, col1, row1, i);
                c2 = checkLine(board, row2, col2, row2, i);
                if (c1 && c2)
                {
                    drawHorizontalLine(row1, col1, row1, i, left, top, width, height);
                    drawVerticalLine(row1, i, row2, i, left, top, width, height);
                    drawHorizontalLine(row2, col2, row2, i, left, top, width, height);
                    Sleep(320);
                    deleteHorizontalLine(row1, col1, row1, i, left, top, width, height);
                    deleteVerticalLine(row1, i, row2, i, left, top, width, height);
                    deleteHorizontalLine(row2, col2, row2, i, left, top, width, height);
                    return;
                }
            }
        }
        if (row2 < row1) {
            x = row2;
            y = row1;
        }
        else {
            x = row1;
            y = row2;
        }
        for (int i = x + 1; i < y; i++) {
            c3 = checkLine(board, i, col1, i, col2);
            if (c3) {
                c1 = checkLine(board, row1, col1, i, col1);
                c2 = checkLine(board, row2, col2, i, col2);
                if (c1 && c2)
                {
                    drawVerticalLine(row1, col1, i, col1, left, top, width, height);
                    drawHorizontalLine(i, col1, i, col2, left, top, width, height);
                    drawVerticalLine(row2, col2, i, col2, left, top, width, height);
                    Sleep(320);
                    deleteVerticalLine(row1, col1, i, col1, left, top, width, height);
                    deleteHorizontalLine(i, col1, i, col2, left, top, width, height);
                    deleteVerticalLine(row2, col2, i, col2, left, top, width, height);
                    return;
                }
            }
        }
    }
    // Draw U
    else if (checkU(board, row1, col1, row2, col2))
    {
        if (((row1 == row2) && row1 == 0 )) {
            drawVerticalLine(row1, col1, -1, col1, left, top, width, height);
            drawHorizontalLine(-1, col1, -1, col2, left, top, width, height);
            drawVerticalLine(row2, col2, -1, col2, left, top, width, height);
            Sleep(320);
            deleteVerticalLine(row1, col1, -1, col1, left, top, width, height);
            deleteHorizontalLine(-1, col1, -1, col2, left, top, width, height);
            deleteVerticalLine(row2, col2, -1, col2, left, top, width, height);
            return;
        }
        if (((row1 == row2) && (row1 == BOARDHEIGTH - 1))) {
            drawVerticalLine(row1, col1, BOARDHEIGTH, col1, left, top, width, height);
            drawHorizontalLine(BOARDHEIGTH, col1, BOARDHEIGTH, col2, left, top, width, height);
            drawVerticalLine(row2, col2, BOARDHEIGTH, col2, left, top, width, height);
            Sleep(320);
            deleteVerticalLine(row1, col1, BOARDHEIGTH, col1, left, top, width, height);
            deleteHorizontalLine(BOARDHEIGTH, col1, BOARDHEIGTH, col2, left, top, width, height);
            deleteVerticalLine(row2, col2, BOARDHEIGTH, col2, left, top, width, height);
            return;
        }
        if (((col1 == col2) && (col1 == 0)))
        {
            drawHorizontalLine(row1, col1, row1, -1, left, top, width, height);
            drawVerticalLine(row1, -1, row2, -1, left, top, width, height);
            drawHorizontalLine(row2, col2, row2, -1, left, top, width, height);
            Sleep(320);
            deleteHorizontalLine(row1, col1, row1, -1, left, top, width, height);
            deleteVerticalLine(row1, -1, row2, -1, left, top, width, height);
            deleteHorizontalLine(row2, col2, row2, -1, left, top, width, height);
            return;
        }
        if (((col1 == col2) && (col2 == BOARDWIDTH - 1)))
        {
            drawHorizontalLine(row1, col1, row1, BOARDWIDTH, left, top, width, height);
            drawVerticalLine(row1, BOARDWIDTH, row2, BOARDWIDTH, left, top, width, height);
            drawHorizontalLine(row2, col2, row2, BOARDWIDTH, left, top, width, height);
            Sleep(320);
            deleteHorizontalLine(row1, col1, row1, BOARDWIDTH, left, top, width, height);
            deleteVerticalLine(row1, BOARDWIDTH, row2, BOARDWIDTH, left, top, width, height);
            deleteHorizontalLine(row2, col2, row2, BOARDWIDTH, left, top, width, height);
            return;
        }
        bool c1, c2, c3;
        int x, y;
        if (col2 < col1) {
            x = col2;
            y = col1;
        }
        else {
            x = col1;
            y = col2;
        }
        for (int i = 0; i < BOARDWIDTH; i++) {
            if (i <= x || i >= y) {
                c3 = checkLine(board, row1, i, row2, i);
                if (c3) {
                    c1 = checkLine(board, row1, col1, row1, i);
                    c2 = checkLine(board, row2, col2, row2, i);
                    if (c1 && c2) {
                        drawHorizontalLine(row1, col1, row1, i, left, top, width, height);
                        drawVerticalLine(row1, i, row2, i, left, top, width, height);
                        drawHorizontalLine(row2, col2, row2, i, left, top, width, height);
                        Sleep(320);
                        deleteHorizontalLine(row1, col1, row1, i, left, top, width, height);
                        deleteVerticalLine(row1, i, row2, i, left, top, width, height);
                        deleteHorizontalLine(row2, col2, row2, i, left, top, width, height);
                        return;
                    }
                }
                else if (i == 0 || i == (BOARDWIDTH - 1)) {
                    c1 = checkLine(board, row1, col1, row1, i);
                    c2 = checkLine(board, row2, col2, row2, i);
                    if ((c1 && c2) || (c1 && col2 == i) || (col1 == i && c2)) {
                        if (i == 0) // Draw column -1
                        {
                            drawHorizontalLine(row1, col1, row1, -1, left, top, width, height);
                            drawVerticalLine(row1, -1, row2, -1, left, top, width, height);
                            drawHorizontalLine(row2, col2, row2, -1, left, top, width, height);
                            Sleep(320);
                            deleteHorizontalLine(row1, col1, row1, -1, left, top, width, height);
                            deleteVerticalLine(row1, -1, row2, -1, left, top, width, height);
                            deleteHorizontalLine(row2, col2, row2, -1, left, top, width, height);
                            return;
                        }
                        if (i == (BOARDWIDTH - 1)) // Draw column BOARDWIDTH
                        {
                            drawHorizontalLine(row1, col1, row1, BOARDWIDTH, left, top, width, height);
                            drawVerticalLine(row1, BOARDWIDTH, row2, BOARDWIDTH, left, top, width, height);
                            drawHorizontalLine(row2, col2, row2, BOARDWIDTH, left, top, width, height);
                            Sleep(320);
                            deleteHorizontalLine(row1, col1, row1, BOARDWIDTH, left, top, width, height);
                            deleteVerticalLine(row1, BOARDWIDTH, row2, BOARDWIDTH, left, top, width, height);
                            deleteHorizontalLine(row2, col2, row2, BOARDWIDTH, left, top, width, height);
                            return;
                        }
                    }
                }
            }
        }

        if (row2 < row1) {
            x = row2;
            y = row1;
        }
        else {
            x = row1;
            y = row2;
        }
        for (int i = 0; i < BOARDHEIGTH; i++) {
            if (i <= x || i >= y) {
                c3 = checkLine(board, i, col1, i, col2);
                if (c3) {
                    c1 = checkLine(board, row1, col1, i, col1);
                    c2 = checkLine(board, row2, col2, i, col2);
                    if (c1 && c2)
                    {
                        drawVerticalLine(row1, col1, i, col1, left, top, width, height);
                        drawHorizontalLine(i, col1, i, col2, left, top, width, height);
                        drawVerticalLine(row2, col2, i, col2, left, top, width, height);
                        Sleep(320);
                        deleteVerticalLine(row1, col1, i, col1, left, top, width, height);
                        deleteHorizontalLine(i, col1, i, col2, left, top, width, height);
                        deleteVerticalLine(row2, col2, i, col2, left, top, width, height);
                        return;
                    }
                }
                else if (i == 0 || i == (BOARDHEIGTH - 1)) {
                    c1 = checkLine(board, row1, col1, i, col1);
                    c2 = checkLine(board, row2, col2, i, col2);
                    if ((c1 && c2) || (c1 && row2 == i) || (row1 == i && c2))
                    {
                        if (i == 0) // Draw row -1
                        {
                            drawVerticalLine(row1, col1, -1, col1, left, top, width, height);
                            drawHorizontalLine(-1, col1, -1, col2, left, top, width, height);
                            drawVerticalLine(row2, col2, -1, col2, left, top, width, height);
                            Sleep(320);
                            deleteVerticalLine(row1, col1, -1, col1, left, top, width, height);
                            deleteHorizontalLine(-1, col1, -1, col2, left, top, width, height);
                            deleteVerticalLine(row2, col2, -1, col2, left, top, width, height);
                            return;
                        }
                        if (i == (BOARDHEIGTH - 1)) // Draw row BOARDHEIGHT
                        {
                            drawVerticalLine(row1, col1, BOARDHEIGTH, col1, left, top, width, height);
                            drawHorizontalLine(BOARDHEIGTH, col1, BOARDHEIGTH, col2, left, top, width, height);
                            drawVerticalLine(row2, col2, BOARDHEIGTH, col2, left, top, width, height);
                            Sleep(320);
                            deleteVerticalLine(row1, col1, BOARDHEIGTH, col1, left, top, width, height);
                            deleteHorizontalLine(BOARDHEIGTH, col1, BOARDHEIGTH, col2, left, top, width, height);
                            deleteVerticalLine(row2, col2, BOARDHEIGTH, col2, left, top, width, height);
                            return;
                        }
                    }
                }
            }
        }
    }
}
//print matrix
void showBoard(Point** board, int left, int top, int width, int height)
{
    srand(time(NULL));
    int rows = BOARDHEIGTH;
    int cols = BOARDWIDTH;
    //Using 2d floop to matrix 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j].isValid == 1)
            {
                //Set color character
                SetColor(0, 15);
                printRectangle(left + j * (width + 2), top + i * (height + 1), width, height);
                int color;
                do {
                    color = rand() % 15 + 1;
                } while (color == 12 || color == 4);
                SetColor(0, color);
                GoTo(left + j * (width + 2) + 4, top + i * (height + 1) + 2);
                putchar(board[i][j].character);
            }
        }
    }
}

