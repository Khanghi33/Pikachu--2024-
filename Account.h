#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Console.h"

struct Accounts
{
    std::string username;
    std::string password;
    int score = 0;
};
void inputData(Accounts&);
bool checkexist(Accounts*, Accounts);                                //Check account existence
bool checksignup(Accounts*, int, Accounts&);                         //Check account id or password exist
bool signupAccount(std::string, Accounts*, int&);                    //Sign up
void getinfoaccount(std::string, Accounts*&, int&);                  //Read user data
bool loginAccount(Accounts*, int, Accounts&);                        //Log in
void printRank(Accounts*, int);                                      //Print leaderboard
void SortbestScore(Accounts*&, int);                                 //Sorting top score players
void Updatedatafile(std::string, Accounts, Accounts*, int);          //Update score of player in file