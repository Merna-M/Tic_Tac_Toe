#include <iostream>
#include "TicTacToe.h"

using namespace std;

extern char game_arr[3][3] ;

/*************************************************************************************************************/
/*
a Welcome message displays when the application runs
*/
/*************************************************************************************************************/
void Welcome_Message(void){
    cout << "****************************************************************" << endl;
    cout << "***************************** Welcome **************************" << endl;
    cout << "************************* TIC TAC TOE Game *********************" << endl;
    cout << "****************************************************************" << endl;
    cout << "****************************************************************" << endl;
}

/*************************************************************************************************************/
/*
A function to select the type of game:
1. One player (playing with AI)
2. Two players
*/
/*************************************************************************************************************/
int Select_Game_Type(void){
    int users_option = 0;
    cout                         << endl;
    cout << "Select an option: " << endl;
    cout << "1: One Player     " << endl;
    cout << "2: Two Players    " << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "Your Option: ";
    do{
        cin >> users_option;
        if (users_option != 1 && users_option != 2){
            cout << "\nWrong Option, Your option should be Number 1 OR 2" << endl;
            cout << "Your Option: ";
        }
    }while(users_option != 1 && users_option != 2);
    cout << "----------------------------------------------------------------" << endl;

    return users_option;
}

/*************************************************************************************************************/
/*
X . X wins
O . O wins
0 . No win yet
1 . No win (End of Game)
*/
/*************************************************************************************************************/
char CheckWin(void){
    for(int i=0 ; i<3 ; i++){
        if(game_arr[i][0] != ' ' && game_arr[i][0] == game_arr[i][1] && game_arr[i][0] == game_arr[i][2] ){
            return game_arr[i][0];
        }
        if(game_arr[0][i] != ' ' && game_arr[0][i] == game_arr[1][i] && game_arr[0][i] == game_arr[2][i]){
            return game_arr[0][i];
        }
    }
    if(game_arr[0][0] != ' ' && game_arr[0][0] == game_arr[1][1] && game_arr[0][0] == game_arr[2][2]){
        return game_arr[0][0];
    }
    if(game_arr[2][0] != ' ' && game_arr[0][2] == game_arr[1][1] && game_arr[0][2] == game_arr[2][0]){
        return game_arr[2][0];
    }

    for(int i=0 ; i<3 ; i++){
        for(int j=0 ; j<3 ; j++){
            if(game_arr[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

/*************************************************************************************************************/
/*
A function to display the current board
*/
/*************************************************************************************************************/
void Print_play(){
    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "------------------" << endl;
    for(int i=0 ; i<3 ; i++){
        for(int j=0 ; j<3 ; j++){
            cout << "| " << game_arr[i][j] << " | ";
        }
        cout << "\n------------------" << endl;
    }
}

/*************************************************************************************************************/
/*
A function that takes two inputs from the player
1. row
2. column
*/
/*************************************************************************************************************/
void EnterLocation(char player){
    int row,col;
    do{
        cin >> row;
        cin >> col;
        while(!(row>=1&&row<=3) || !(col>=1&&col<=3)){
            cout << "Please Enter the numbers from 1 -> 3 : ";
            cin >> row;
            cin >> col;
        }
        if (game_arr[row-1][col-1] != ' '){
            cout << "Used slot, Please Enter another play" << endl;
        }
    }while(game_arr[row-1][col-1] != ' ');
    game_arr[row-1][col-1] = player;
}

/*************************************************************************************************************/
/*
If the type of game is two players (two users playing at the same time)
*/
/*************************************************************************************************************/
void TwoPlayers(void){
    int counter = 0;
    // print the current board
    Print_play();
    while(counter < 9){
        char current_player;
        if(counter % 2 == 0)
            // start with X (takes the even counter)
            current_player = 'X';
        else
            current_player = 'O';

        cout << endl;
        cout << "Player " << current_player << "'s Turn :";

        // Current player Enters row and column
        EnterLocation(current_player);

        // Print current board
        Print_play();

        // check if the current player wins
        char check_Win = CheckWin();
        if(check_Win != 0 && check_Win != 1){
                //0 if no player wins yet
            cout << "\nPlayer " << check_Win << " Wins" << endl;
            break;
        }
        counter++;
    }

    //counter = 9 if there is no Win in the game
    if(counter == 9){
        cout << "\nEnd Game" << endl;
        cout << "No one Wins" << endl;
    }
}


/*************************************************************************************************************/
/*
If the type of game is one player (playing with AI)
*/
/*************************************************************************************************************/
void OnePlayer(char player , int level){
    int counter = 0;
    char ai;
    bool minmaxb; //boolean min max
    if(player == 'X'){
        ai = 'O';
        minmaxb = false;
    }else {
        ai = 'X';
        minmaxb = true;
        minimax(level , minmaxb ,true);
    }
    //print the current board
    Print_play();

    while(counter < 9){
        cout << "Player " << player << "'s Turn :";
        EnterLocation(player);

        Print_play();

        char check_Win = CheckWin();

        if(check_Win == player){
            cout << "\nPlayer " << player << " Wins" << endl;
            break;
        }else if(check_Win == 1){
            cout << "\nEnd Game" << endl;
            cout << "No one Wins" << endl;
            break;
        }
        cout << "Player " << ai << "'s Turn :";
        minimax(level , minmaxb ,true);
        Print_play();
        check_Win = CheckWin();

        if(check_Win == ai){
            cout << "\nPlayer " << ai << " Wins" << endl;
            cout << "\nGame Over\n"<<endl;
            break;
        }else if(check_Win == 1){
            cout << "\nEnd Game" << endl;
            cout << "No one Wins" << endl;
            break;
        }
        counter -= 2;
    }
}

/*************************************************************************************************************/

int minimax(int depth, bool isMax , bool first){
    char result = CheckWin(); // 'X' if X , 'O' if O , 1 if end with no winner , 0 if still no winner
	if(result == 'X'){ // maximizing
		result = 2;
	}else if(result == 'O'){ // minimizing
		result = -2;
	}
    if(result != 0 || depth == 0){
        return result;
    }

    if(isMax){
        int maxScore = -1000;
        int row,col;
        for(int i=0 ; i<3 ; i++){
            for(int j=0 ; j<3 ; j++){
                if(game_arr[i][j] == ' '){
                    game_arr[i][j] = 'X';
                    int score = minimax(depth-1,false,false);
                    game_arr[i][j] = ' ';
                    if(score > maxScore){
                        maxScore = score;
                        row = i;
                        col = j;
                    }
                }
            }
        }
        if(first){
            game_arr[row][col] = 'X';
            cout<< row+1 << " " << col+1 << endl;
        }
        return maxScore;
    }
    else{
        int minScore = 1000;
        int row,col;
        for(int i=0 ; i<3 ; i++){
            for(int j=0 ; j<3 ; j++){
                if(game_arr[i][j] == ' '){
                    game_arr[i][j] = 'O';
                    int score = minimax(depth-1,true,false);
                    game_arr[i][j] = ' ';
                    if(score < minScore){
                        minScore = score;
                        row = i;
                        col = j;
                    }
                }
            }
        }
        if(first){
            game_arr[row][col] = 'O';
            cout<< row+1 << " " << col+1 << endl;
        }
        return minScore;
    }
}
