#include "Menu.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include "Console.h"
#include "Account.h"

using namespace std;
unsigned char logo1[] = R"(
                          ____ ___ _  __   _    ____ _   _ _   _
                         |  _ |_ _| |/ /  / \  / ___| | | | | | |
                         | |_) | || ' /  / _ \| |   | |_| | | | |
                         |  __/| || . \ / ___ | |___|  _  | |_| |
                         |_|  |___|_|\_/_/   \_\____|_| |_|\___/
    )";
unsigned char logo2[] = R"(
        __  __    _  _____ ____ _   _ ___ _   _  ____    ____    _    __  __ _____
       |  \/  |  / \|_   _/ ___| | | |_ _| \ | |/ ___|  / ___|  / \  |  \/  | ____|
       | |\/| | / _ \ | || |   | |_| || ||  \| | |  _  | |  _  / _ \ | |\/| |  _|
       | |  | |/ ___ \| || |___|  _  || || |\  | |_| | | |_| |/ ___ \| |  | | |___
       |_|  |_/_/   \_\_| \____|_| |_|___|_| \_|\____|  \____/_/   \_\_|  |_|_____|
    )";
unsigned char khangkhai[] = R"(
                                |/|_  _  _  _ __|/|_  _ .
                                |\| |(_|| |(_|  |\| |(_||
                                            _|
    )";
unsigned char Press[] = R"(
                                   PRESS ENTER TO PLAY
    )";
unsigned char logopikachu[] = R"(
                                           :+#@=
                                        .-#@@@#:
                                        -#%%###=
                                      .-=::::::.
                                     .::::::::.
                                    .-:::::::.
                                   .-:::::--.           pika-pikachu~~~
                                  .:::::--:
                                 .-::-----:.
                                .--::::::::::::.
                               .-:::::::::::::::::.
                               .-:---::::::::::::::-:.
                      ..::.   .::=@#==::::::::::::::::::.
                     :-:::::..----#%%+::::::::::::::-:::::.
                     :::::::-****=:::::::--:::===+-:--::::::.
                     ::::::::-+**+:::=+==-::::*@@@=-:--:::::-.
                     .-:::::::-++:::-*%%%%#+-::---::. :-:::::::.
                      -:::::::::-:::-+++*#*-::=***+:.   =*=-:::-
                      --::::::::-:::-=+++=:::=*****=::::::=%@@@@=
                       .=:::::::::::::-==-::::-+***=-::::::::--=**
                        :=-:::::::::-:::::::::--=--==-::::::::::..
  )";
unsigned char logokage[] = R"(
                                                                ..;;:..  
                                                              :;::::::;+.
                                                             .;:::::::::;+.
                                                             ;;;:::::;;:;x;                         
                                                             +:::::::::x+$+                         
                                                             +$;:::::::xxX++
                                                            :;::::::::::;;;x.            :
                                                            :+x;;;;;;++x+++.            .;+:
                                                             .;;+x++;::+;;;            :;++:        
                                                                .:+;++;;;+;::.         ;;;;;:
                                                            .;:;::;;::;;;:::::;;;:;   .;++;::
                                                          +;:::::;;.....;;::::::+;;: .:::::;:
                                                           :+;++++.......;;++++;;;.   :::.:+:
                                                               .:........:::;.        ..;::.
                                                               ...........:::;:        +;.
                                                             .;;.........+:::;;     :+;;
                                                            ::::;:.:::::::::::;++++++++.
                                                           :::;;;+::::::;::::;;x+++++;.
                                                          ;;;;;;;;+++;::+;;;;;x+;;:.
                                                          .;;+;;;;:       ;;;;;+.
                                                         .::+;::.          :;++;+;.
)";
//animation
void Animation()
{
    int i = 0;
    //playSound(OPENING);
    //using floop to print animation
    while (i != 30)
    {
        //Set color logo
        SetColor(0, rand() % 7 + 9);
        cout << logo1;
        i++;
        Sleep(300 - 5 * i);
    }
    system("cls");
}
//First Screen
void Mainbackground()
{
    Animation();
    SetColor(0, 14);
    cout << logo1;
    SetColor(0, 11);
    cout << khangkhai;
    SetColor(0, 15);
    cout << Press;
    SetColor(0, 6);
    cout << logopikachu;
    int c;
    //Press enter to start
    do {
        c = _getch();
    } while (c != 13);
    system("cls");
    //playSound(GAMESTART);
}
//Classic mode
void Classicgamebackground(Accounts& player)
{
    Point** board;
    Accounts* data = new Accounts[100];
    string accountfile = "Accounts.txt";
    int n = 0;
    int Score;
    do {
        //Print score board and support board
        SetColor(0, 15); printRectangle(60, 3, 27, 6);
        SetColor(0, 15); printRectangle(62, 4, 24, 3);
        SetColor(0, 15); GoTo(63, 4); cout << "Pokedex";
        SetColor(0, 15); printRectangle(60, 10, 27, 7);
        GoTo(70, 11); cout << "_Rule_";
        GoTo(62, 12); cout << "I Catching get 1 point";
        GoTo(62, 13); cout << "L Catching get 2 points";
        GoTo(62, 14); cout << "Z Catching get 2 points";
        GoTo(62, 15); cout << "U Catching get 3 points";
        SetColor(0, 12); GoTo(62, 16); cout << "MissCatching lost 2 points";
        SetColor(0, 15); printRectangle(60, 18, 27, 5);
        GoTo(68, 19); cout << "_PokeSupport_";
        GoTo(62, 20); cout << "Auto shuffle";
        GoTo(62, 21); cout << "Press H to get support";
        SetColor(0, 12); GoTo(62, 22); cout << "Each support lost 5 points"; SetColor(0, 15);
        //Create game matrix
        createBoard(board);
        showBoard(board, 5, 3, 7, 4);
        //System move to play
        move_Classic(board, Score, 5, 3, 7, 4);
        //Save the highest score
        if (Score > player.score)
            player.score = Score;
        //Save highest score to file data
        getinfoaccount(accountfile, data, n);
        Updatedatafile(accountfile, player, data, n);
        deleteBoard(board);
        _getch();

    } while (BackorContinue());
    system("cls");
}
//Advance mode
void Advancegamebackground(Accounts& player)
{
    Point** board;
    Accounts* data = new Accounts[100];
    string accountfile = "Accounts.txt";
    int n = 0;
    int Score;
    do {
        //Print score board and support board
        SetColor(0, 15); printRectangle(60, 3, 27, 6);
        SetColor(0, 15); printRectangle(62, 4, 24, 3);
        SetColor(0, 15); GoTo(63, 4); cout << "Pokedex";
        SetColor(0, 15); printRectangle(60, 10, 27, 7);
        GoTo(70, 11); cout << "_Rule_";
        GoTo(62, 12); cout << "I Catching get 1 point";
        GoTo(62, 13); cout << "L Catching get 2 points";
        GoTo(62, 14); cout << "Z Catching get 2 points";
        GoTo(62, 15); cout << "U Catching get 3 points";
        SetColor(0, 12); GoTo(62, 16); cout << "MissCatching lost 2 points";
        SetColor(0, 15); printRectangle(60, 18, 27, 6);
        GoTo(68, 19); cout << "_PokeSupport_";
        GoTo(62, 20); cout << "Auto shuffle";
        GoTo(62, 21); cout << "Press H to get support";
        SetColor(0, 12); GoTo(62, 22); cout << "Each support lost 5 points"; SetColor(0, 15);
        GoTo(62, 23); cout << "Advance mode x 1.5 points";
        //Create game matrix
        createBoard(board);
        showBoard(board, 5, 3, 7, 4);
        //System move to play
        move_Advance(board, Score, 5, 3, 7, 4);
        //Save the highest score
        if (Score > player.score)
            player.score = Score;
        //Save highest score to file data
        getinfoaccount(accountfile, data, n);
        Updatedatafile(accountfile, player, data, n);
        deleteBoard(board);
        _getch();
    } while (BackorContinue());
    system("cls");

}
//Menu back or continue
int BackorContinue()
{
    //print menu
    SetColor(0, 15);
    printRectangle(28, 27, 10, 2);
    GoTo(32, 28); cout << "BACK";
    printRectangle(48, 27, 10, 2);
    GoTo(50, 28); cout << "CONTINUE";
    int c = 1;
    int i = 28;
    SetColor(0, 12);
    printRectangle(i, 27, 10, 2);
    //Get input from player
    while (c)
    {
        //System movement and select
        c = getinputfromuser();
        int j = i;
        switch (c) {
        case 2:  i = i - 20; break;
        case 3:  i = i + 20; break;
        }
        //Move cursor
        if (i == 28 || i == 48) {
            SetColor(0, 15); printRectangle(j, 27, 10, 2);
            SetColor(0, 12); printRectangle(i, 27, 10, 2);
            //playSound(MOVE);
        }
        //reach outreach
        else {
            i = j;
            //playSound(OUTREACH);
        }
    }
    system("cls");
    //playSound(MOVE);
    //choose option
    if (i == 28)
        return 0;
    return 1;
}
//Sign up screen
void SignupScreen(string accountfile, Accounts* data)
{
    int n = 0;
    int check1, check2;
    do {
        system("cls");
        SetColor(0, 14);
        cout << logo1;
        SetColor(0, 10);
        cout << logo2;
        SetColor(0, 15);
        printRectangle(18, 20, 50, 10);
        //check input information is existed or not
        getinfoaccount(accountfile, data, n);
        check1 = signupAccount(accountfile, data, n);
        check2 = 0;
        //check choose back or continue
        if (check1 == 0)
            check2 = BackorContinue();
    } while (check1 == 0 && check2 == 1);
    system("cls");
}
//login screen
int LoginScreen(string accountfile, Accounts* data, Accounts& player)
{
    int n = 0;
    int check1, check2;
    do {
        system("cls");
        SetColor(0, 14);
        cout << logo1;
        SetColor(0, 10);
        cout << logo2;
        SetColor(0, 15);
        printRectangle(18, 20, 50, 10);
        //check input information is existed or not
        getinfoaccount(accountfile, data, n);
        check1 = loginAccount(data, n, player);
        check2 = 0;
        //check choose back or continue
        if (check1 == 0)
            check2 = BackorContinue();
    } while (check1 == 0 && check2 == 1);
    if (check1 == 1)
        return 1;
    return 0;
}
//login and sign up system
void Loginbackground(Accounts& player)
{
    Accounts* data = new Accounts[100];
    string accountfile = "Accounts.txt";
    int choice{};
    int n = 0;
    int check{};
    do {
        SetColor(0, 14);
        cout << logo1;
        SetColor(0, 10);
        cout << logo2;
        SetColor(0, 15);
        printRectangle(18, 20, 50, 10);
        //choose option sign up or log in
        GoTo(40, 22);
        cout << "1.Sign up";
        GoTo(40, 24);
        cout << "2.Log in";
        do {
            GoTo(25, 26);
            cout << "Input choice: "; cin >> choice;
        } while (choice != 1 && choice != 2);
        cin.ignore();
        switch (choice) {
        case 1: SignupScreen(accountfile, data); break;                 //sign up screen
        case 2: check = LoginScreen(accountfile, data, player); break;  //login screen
        }
    } while (check != 1);// log in success
    system("cls");
}
//Menu mode background
void Optionbackground(Accounts player)
{
    ShowCur(false);
    SetColor(0, 14);
    cout << logo1;
    SetColor(0, 10);
    cout << logo2;
    SetColor(0, 15);  GoTo(38, 13); cout << "Hi," << player.username << ":3";
    MenuOption(); // system choose mode in menu
}
//Leaderboard
void Rankbackground()
{
    SetColor(0, 15);
    GoTo(15, 0);
    unsigned char Rank[] = R"(
             ____             _
            |  _ \ __ _ _ __ | | __
            | |_) / _` | '_ \| |/ /
            |  _ < (_| | | | |   <
            |_| \_\__,_|_| |_|_|\_\
)";
    cout << Rank;
    printRectangle(10, 6, 70, 25);
    GoTo(44, 33);
    cout << "BACK";
    SetColor(0, 12);
    printRectangle(40, 32, 10, 2);
    int n = 0;
    string accountfile = "Accounts.txt";
    Accounts* data = new Accounts[25];
    //Get data from file and sorting
    getinfoaccount(accountfile, data, n);
    SortbestScore(data, n);
    printRank(data, n);
    int c;
    //Back to menu mode
    do {
        c = _getch();
        //if (c != 13)
            //playSound(OUTREACH);
    } while (c != 13);// Enter
    system("cls");
    //playSound(CLICK);
    delete[] data;
}
//Rule background
void Rulebackground()
{
    SetColor(0, 15);
    GoTo(15, 0);
    unsigned char Rule[] = R"(
                                                ____  _   _ _     _____ ____  
                                               |  _ \| | | | |   | ____/ ___| 
                                               | |_) | | | | |   |  _| \___ \ 
                                               |  _ <| |_| | |___| |___ ___) |
                                               |_| \_\\___/|_____|_____|____/ 
)";
    cout << Rule;
    //print rules
    printRectangle(10, 6, 70, 25);
    SetColor(0, 14); GoTo(28, 7); cout << "HOW TO CATCH LEGENDARY POKEMONS ?";
    SetColor(0, 15); GoTo(12, 9); cout << "There are two modes to catch Legendary pokemon: ";
    GoTo(14, 11); cout << "- Classic mode: You use arrow up,down,left,right or w,a,s,d to move";
    GoTo(11, 12); cout << "the cursor between box.Then, you press Enter to choose 2 box which are";
    GoTo(11, 13); cout << "matching together base on I-Matching,L-Matching,Z-Matching,U-Matching";
    GoTo(11, 14); cout << "When you success matching 2 box, they will be disappeared.When all box";
    GoTo(11, 15); cout << "disappeared, you are success catching RESHIRAM.";
    GoTo(14, 17); cout << "- Advance mode: Advance mode has the same rule to Classic mode. But";
    GoTo(11, 18); cout << "it has some differences.When box is matched, all boxes in its col will";
    GoTo(11, 19); cout << "be moved up.When all box disappeared, you are success catching ZEKROM.";
    GoTo(12, 21); cout << "When catching Pokemon, you can also get points base on type-matching:";
    GoTo(18, 22); cout << "+ I-Matching get 1 point.";
    GoTo(18, 23); cout << "+ L-Matching and Z-Matching get 2 points.";
    GoTo(18, 24); cout << "+ U-Matching get 3 points.";
    SetColor(0, 12); GoTo(12, 25); cout << "But when fail to connect two box,you will lose 2 points.So,carefully."; SetColor(0, 15);
    GoTo(14, 27); cout << "- Your highest points will be saved to your accounts data and your";
    GoTo(11, 28); cout << "Rank will be set. Go to RANK BOARD to see top player";
    SetColor(0, 9);  GoTo(30, 29); cout << "Hope you enjoy the game!!"; SetColor(0, 15);
    GoTo(44, 33); 
    cout << "BACK";
    SetColor(0, 12);
    printRectangle(40, 32, 10, 2);
    int c;
    //Back to menu mode
    do {
        c = _getch();
        //if (c != 13)
            //playSound(OUTREACH);
    } while (c != 13);
    //playSound(CLICK);
    system("cls");
}
//menu exit
void Exitbackground(int& exit)
{
    SetColor(0, 14);
    cout << logo1;
    SetColor(0, 10);
    cout << logo2;
    SetColor(0, 15);
    printRectangle(20, 20, 50, 10);
    printRectangle(25, 25, 15, 4);
    printRectangle(50, 25, 15, 4);
    GoTo(34, 23);
    cout << "Do you sure to exit game ?";
    GoTo(32, 27);
    cout << "YES";
    GoTo(58, 27);
    cout << "NO";
    choiceExit(exit); // option exit or not
}
// print menu option
void MenuOption()
{
    SetColor(0, 15);
    printRectangle(40, 15, 9, 2);
    GoTo(42, 16);
    cout << "CLASSIC";
    SetColor(0, 15);
    printRectangle(40, 18, 9, 2);
    GoTo(42, 19);
    cout << "ADVANCE";
    SetColor(0, 15);
    printRectangle(40, 21, 9, 2);
    GoTo(43, 22);
    cout << "RANKS";
    SetColor(0, 15);
    printRectangle(40, 24, 9, 2);
    GoTo(43, 25);
    cout << "RULES";
    SetColor(0, 15);
    printRectangle(40, 27, 9, 2);
    GoTo(43, 28);
    cout << "EXITS";
    SetColor(0, 15);
}
// System movement for menu mode
int MovementOption()
{
    int c = 1;
    int i = 15;
    SetColor(0, 12);
    printRectangle(40, i, 9, 2);
    while (c)
    {
        //Move cursor
        c = getinputfromuser();
        int j = i;
        switch (c) {
        case 1:  i = i - 3; break;
        case 4:  i = i + 3; break;
        }
        if (i >= 15 && i <= 27) {
            SetColor(0, 15); printRectangle(40, j, 9, 2);
            SetColor(0, 12); printRectangle(40, i, 9, 2);
            //playSound(MOVE);
        }
        else {
            i = j;
            //playSound(OUTREACH);
        }
    }
    system("cls");
    //playSound(MOVE);
    return i;
}
//option of exit
void choiceExit(int& exit)
{
    int c = 1;
    int i = 25;
    SetColor(0, 12);
    printRectangle(25, 25, 15, 4);
    while (c)
    {
        //move cursor
        c = getinputfromuser();
        int j = i;
        switch (c) {
        case 2:  i = i - 25; break;
        case 3:  i = i + 25; break;
        }
        if (i == 25 || i == 50) {
            SetColor(0, 15); printRectangle(j, 25, 15, 4);
            SetColor(0, 12); printRectangle(i, 25, 15, 4);
            //playSound(MOVE);
        }
        else {
            i = j;
            //playSound(OUTREACH);
        }
    }
    system("cls");
    //playSound(MOVE);
    if (i == 25)
        exit = 0;
    else
        exit = 1;
}
//Linked to modes when select mode in menu mode
void SelectOption(int& exit, Accounts& player)
{
    int i = MovementOption();
    switch (i)
    {
        case 15: Classicgamebackground(player); break; // Classic
        case 18: Advancegamebackground(player); break; //ADVANCE
        case 21: Rankbackground(); break; // Leaderboard
        case 24: Rulebackground(); break;       //Rules
        case 27: Exitbackground(exit);  break; // Exit
    }
}
unsigned char logopikachu2[] = R"(
                                    @@                                                                            @@
                                  @@@@                                                                            @@@@
                                 @@@@                                                                              @@@@
                                @@@@                                                                                @@@@
                               @%:.=                                                                                =.:%@
                              @:...*                                                                                *...:@
                             +...:@                                                                                  @:...*
                            +...=                                                                                      =...*
                           +..:###%%@                                                                              @%%###:..*
                           *............* @#=........@@@@@@@                                @@@@@@@........=#@ *............*
                ####@     @:.......................%@@@@@                                      @@@@@%.......................:@     @####
          #*+......#      -................-%%%@@                                                      @@%%%-................-      #......+*#
     #+-..........=**#   @:.++.+............#                                                              #............+.++.:@   #**=..........+*#
 @+:...........::=:...-*#--..**........---.:@                                                              @:.---........**..--#*-...:=::...........:+@
+...........:---:==.....+++*...-.......#@#.#                                                                #.#@#.......-...*+++.....==:---:...........+
@:.......:------:%+.....:+++....###%%+=...:%                                                                %:...=+%%###....+++:.....+%:------:.......:@
 %.....:--+#*---# @-.....-......====+:...++#::--+@                                                    @+--::#++...:+====......-.....-@ #---*#+--:.....%
  =...:-*   +---#@*=-.....-.....===+....:*=......%                                                    %......=*:....+===.....-.....-=*@#---+   *-:...=
   =:+#    @=-------*:...........:.....-:......=%                                                      %=......:-.....:...........:*-------=@    #+:=
           #----%--# #-........----:.........=                                                            =.........;----........-# #--%----#
           +=%  %*#@%*.................:--*@                                                                @*--:.................*%@#*%  %=+
               @####+..................%                                                                        %..................+####@
               @%@@*..................:@                                                                        @:..................*@@%@
                  -....................:%                                                                      %:....................-
                 -.......................+                                                                    +.......................-
                 ::::....................-                                                                    -....................::::
                 #=-------------------::.=                                                                    =.::-------------------=#
                #----=#*####%@%#+=------+#                                                                    #+------=+#%@%####*#=----#
              @#+*#%                #%%*+=+#@                                                              @#+=+*%%#                %#*+#@
    )";
