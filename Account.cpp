#include "Account.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include "Account.h"
#include "Console.h"
#include "Menu.h"
using namespace std;
// Get data account from user
void inputData(Accounts& input)
{
    GoTo(24, 22); cout << "Username: "; getline(cin, input.username);
    GoTo(24, 24); cout << "Password: "; getline(cin, input.password);
    input.score = 0;
}
// Check if the account exist
bool checkexist(Accounts* data, int n, Accounts check)
{
    for (int i = 0; i < n; i++)
        if (data[i].username == check.username || data[i].password == check.password)
            return true;
    return false;
}
// Check if the account had already signed up
bool checksignup(Accounts* data, int n, Accounts& check)
{
    for (int i = 0; i < n; i++) {
        if (data[i].username == check.username && data[i].password == check.password) {
            check.score = data[i].score;
            return true;
        }
    }
    return false;
}
// Sign up
bool signupAccount(string accountfile, Accounts* data, int& n)
{
    Accounts signup;
    inputData(signup);
    // if the account is existed -> sign up fail 
    if (checkexist(data, n, signup)) {
        GoTo(26, 26); SetColor(0, 12);
        cout << "Username or Password had existed!!\n";
        SetColor(0, 15);
        return 0;
    }
    // if the account isn't existed open file to save -> sign up success
    ofstream fsignup;
    fsignup.open(accountfile, ios::app);
    if (!fsignup)
        cout << "Cannot open file!!";
    else {
        //save data to file
        fsignup << signup.username << "," << signup.password << "," << signup.score << "\n";
        n++;
    }
    fsignup.close();
    GoTo(34, 26); SetColor(0, 10);
    cout << "Sign up success!!\n";
    _getch();
    SetColor(0, 15);
    return 1;
}
// Get account data from Account.txt
void getinfoaccount(string accountfile, Accounts*& data, int& n)
{
    delete[] data;
    data = new Accounts[100];
    ifstream fin;
    fin.open(accountfile, ios::in);
    if (!fin)
        cout << "Cannot open file!!";
    else {
        int i = 0;
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, data[i].username, ',');
            getline(ss, data[i].password, ',');
            ss >> data[i].score;
            i++;
        }
        n = i;
    }
    fin.close();
}
// Login
bool loginAccount(Accounts* data, int n, Accounts& player)
{
    Accounts login;
    inputData(login);
    // Check if data isn't existed -> login fail
    if (!checksignup(data, n, login)) {
        GoTo(26, 26); SetColor(0, 12);
        cout << "Username or Password had error!!\n";
        SetColor(0, 15);
        return 0;
    }
    // if data is existed -> login success
    GoTo(34, 26); SetColor(0, 10);
    cout << "Login success!!\n";
    player = login;
    SetColor(0, 15);
    _getch();
    return 1;
}
//Print ranking
void printRank(Accounts* data, int n)
{
    SetColor(0, 15);
    GoTo(16, 8); cout << "User";
    GoTo(36, 8); cout << "Score";
    //Print score of players
    for (int i = 0; i < 10; i++)
    {
        GoTo(13, 10 + 2 * i); cout << i + 1 << "." << data[i].username;
        GoTo(36, 10 + 2 * i); cout << data[i].score << endl;
    }
    GoTo(53, 8); cout << "User";
    GoTo(73, 8); cout << "Score";
    for (int i = 0; i < 10; i++)
    {
        GoTo(53, 10 + 2 * i); cout << i + 1 + 10 << "." << data[i + 10].username;
        GoTo(73, 10 + 2 * i); cout << data[i + 10].score << endl;
    }
}
//Sorting best players' score
void SortbestScore(Accounts*& data, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (data[i].score < data[j].score) {
                Accounts tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
}
//Save highest score to file
void Updatedatafile(string accountfile, Accounts player, Accounts* data, int n)
{
    // open file
    ofstream fout;
    fout.open(accountfile, ios::trunc);
    if (!fout)
        cout << "cannot open file!!\n";
    else {
        for (int i = 0; i < n; i++) {
            if (data[i].username == player.username && data[i].password == player.password)
                fout << data[i].username << "," << data[i].password << "," << player.score << "\n";
            else
                fout << data[i].username << "," << data[i].password << "," << data[i].score << "\n";
        }
    }
    fout.close();
}