#pragma once
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "Account.h"
#include "Controller.h"


void Mainbackground();									//First background
void Animation();										//Animation effect
void Loginbackground(Accounts&);						//Menu Login and signup background
void Optionbackground(Accounts);						//Menu mode background
void Classicgamebackground(Accounts&);					//Classic game mode
void Advancegamebackground(Accounts&);					//Advance game mode
void Rankbackground();									//Leaderboard
void Rulebackground();									//Rule background
void MenuOption();										//option menu
void Exitbackground(int&);								//Menu exit
int MovementOption();									//Action to move
void choiceExit(int&);									//Menu option Yes/No
void SelectOption(int&, Accounts&);						//Select mode on menu mode
int BackorContinue();									//Menu option back/continue
void SignupScreen(std::string, Accounts*);				//Sign up system
int LoginScreen(std::string, Accounts*, Accounts&);		//Login system