#include <iostream>
#include "TicTacToe.h"

using namespace std;

char game_arr[3][3] = {{' ',' ',' '},
                       {' ',' ',' '},
                       {' ',' ',' '}};

int main()
{
    // Display the welcome message
    Welcome_Message();
    bool playing = true;
    while(playing){
        // choose one player or two players
        int Game_Type = Select_Game_Type();

        // One player option:
        if(Game_Type == 1){
            char player;
            cout << "Choose a player <X/O>: ";
            cin >> player;
            while(player!= 'X'&& player != 'O'){
                cout << "\nWrong Option" << endl;
                cout << "Choose a player <X/O>: ";
                cin >> player;
            }
            cout << "----------------------------------------------------------------" << endl;
            cout << "Choose the Level: " << endl;
            cout << "1: Easy           " << endl;
            cout << "2: Medium         " << endl;
            cout << "3: Hard           " << endl;
            cout << "Your Option: ";

            int level;
            cin >> level;
            while(level != 1 && level != 2 && level != 3){
                cout << "\nWrong Option" << endl;
                cout << "Choose a number from 1 -> 3: ";
                cin >> level;
            }

            if(level == 1){
                OnePlayer(player,1);
            }else if(level == 2){
            OnePlayer(player,1000);
            }else {
                OnePlayer(player,400000000);
            }

        }
        // Two players option
        else {
            TwoPlayers();
        }
        cout << "Do you want to play Again? <y/n>: ";
        char c;
        cin >> c;
        while(c != 'y' && c!= 'Y' && c!= 'n' && c!= 'N'){
            cout << "\nWrong Option\nDo you want to play Again? <y/n>: ";
            cin >> c;
        }
        if(c== 'n' || c=='N'){
            cout << "Good Bye :) " << endl;
            break;
        }else {
            // clear the array for a new game
            for(int i=0 ; i<3 ; i++){
                for(int j=0 ; j<3 ; j++){
                    game_arr[i][j] = ' ';
                }
            }
        }
    }

    return 0;
}
