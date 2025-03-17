#include "CheckPattern.h"
#include <algorithm>
using namespace std;

bool checkLine(Point** board, int row1, int col1, int row2, int col2) {
    // check horizontal
    if (row1 == row2) {
        int yMin, yMax, count = 0;
        yMin = min(col1, col2);
        yMax = max(col1, col2);
        for (int y = yMin; y <= yMax; y++) {
            if (board[row1][y].isValid) {
                count++;
                if (count == 2) return false;
            }
        }
        if ((count == 1) && ((!board[row1][col1].isValid && board[row2][col2].isValid) || (board[row1][col1].isValid && !board[row2][col2].isValid))) {
            return true;
        }
        else if (count == 0) {
            return true;
        }
        return false;
    }
    // check Vertical
    if (col1 == col2) {
        int xMin, xMax, count = 0;
        xMin = min(row1, row2);
        xMax = max(row1, row2);
        for (int x = xMin; x <= xMax; x++) {
            if (board[x][col1].isValid) {
                count++;
                if (count == 2) return false;
            }
        }
        if ((count == 1) && ((!board[row1][col1].isValid && board[row2][col2].isValid) || (board[row1][col1].isValid && !board[row2][col2].isValid))) {//sai
            return true;
        }
        else if (count == 0) {
            return true;
        }
        return false;
    }
    return false;
}


bool checkI(Point** board, int row1, int col1, int row2, int col2) {
    // check Horizontal
    if (row1 == row2) {
        int yMin, yMax, count = 0;
        yMin = min(col1, col2);
        yMax = max(col1, col2);
        for (int y = yMin + 1; y < yMax; y++) {
            if (board[row1][y].isValid) {
                return false;
            }
        }
        return true;
    }
    // check vertical
    if (col1 == col2) {
        int xMin, xMax;
        xMin = min(row1, row2);
        xMax = max(row1, row2);
        for (int x = xMin + 1; x < xMax; x++) {
            if (board[x][col1].isValid) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkL(Point** board, int row1, int col1, int row2, int col2) {
    if (row1 == row2 || col1 == col2) {
        return false;
    }
    bool c1, c2;
    if (!board[row1][col2].isValid) {
        c1 = checkLine(board, row1, col1, row1, col2);
        c2 = checkLine(board, row2, col2, row1, col2);
        if (c1 && c2) {
            return true;
        }
    }
    if (!board[row2][col1].isValid) {
        c1 = checkLine(board, row1, col1, row2, col1);
        c2 = checkLine(board, row2, col2, row2, col1);
        if (c1 && c2) {
            return true;
        }
    }
    return false;
}

bool checkZ(Point** board, int row1, int col1, int row2, int col2) {
    if (row1 == row2 || col1 == col2) {
        return false;
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
    for (int i = x + 1; i < y; i++) {
        c3 = checkLine(board, row1, i, row2, i);
        if (c3) {
            c1 = checkLine(board, row1, col1, row1, i);
            c2 = checkLine(board, row2, col2, row2, i);
            if (c1 && c2)
                return true;
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
                return true;
        }
    }
    return false;
}

bool checkU(Point** board, int row1, int col1, int row2, int col2) {
    if (((row1 == row2) && (row1 == 0 || row1 == BOARDHEIGTH - 1) || ((col1 == col2) && (col1 == 0 || col2 == BOARDWIDTH - 1)))) {
        return true;
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
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDWIDTH - 1)) {
                c1 = checkLine(board, row1, col1, row1, i);
                c2 = checkLine(board, row2, col2, row2, i);
                if ((c1 && c2) || (c1 && col2 == i) || (col1 == i && c2)) {
                    return true;
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
                if (c1 && c2) {
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDHEIGTH - 1)) {
                c1 = checkLine(board, row1, col1, i, col1);
                c2 = checkLine(board, row2, col2, i, col2);
                if ((c1 && c2) || (c1 && row2 == i) || (row1 == i && c2)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool checkPatterns(Point** board, int row1, int col1, int row2, int col2) {
    if (board[row1][col1].character == board[row2][col2].character && (row1 != row2 || col1 != col2))
    {
        if (checkI(board, row1, col1, row2, col2)) {
            return true;
        }
        else if (checkL(board, row1, col1, row2, col2)) {
            return true;
        }
        else if (checkZ(board, row1, col1, row2, col2)) {
            return true;
        }
        else if (checkU(board, row1, col1, row2, col2)) {
            return true;
        }
    }
    
    return false;
}

bool checkValidPairs(Point** board) {
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
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}