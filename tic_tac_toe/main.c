#include <stdio.h>

/*a struct to define the name and symbol
of each player whether X or Y*/
typedef struct User
{
    unsigned char symbol;
    unsigned char name[10];

}User;
/*Global Variables*/

//array to hold the printed values (numbers or the symbols X & Y)
unsigned char game_arr[9];

//array to hold the order of the game (X starts then Y)
unsigned char game_order[]={'X','O','X','O','X','O','X','O','X'};

//counter to count the number of plays as the game ends at the 9th play
int Counter=0;

//2 players
User user1 , user2;

/*----------- Prototyoes --------------*/
int Check_index(unsigned char index);
int Check_Win(unsigned char user);
void Single_Game(void);


int main()
{
    unsigned char user_symbol,i , User_opt_YN = 'y';
    printf("#################### TIC TAC TOE GAME ########################\n\n");
    /*Infinite loop that only breaks when the players presses any button but y & Y */
    while(User_opt_YN == 'y' || User_opt_YN == 'Y')
    {
        //fill the array with the numbers from 1 to 9 in Ascii
        for(i=0 ; i<9 ; i++)
        {
            game_arr[i] = i + 49; // 0 = 48 in ascii and the numbers starts from 1 not 0
        }
        //Ask players to enter their data
        printf("User 1 Please Enter your Name : ");
        gets(user1.name);
        printf("User 1 PLease Enter a symbol <X/O> : ");
        //if the entered data is correct put it in the struct if not keep asking for the right data
        do{
            scanf("%c",&user_symbol);
            fflush(stdin);
            if(user_symbol == 'x' || user_symbol == 'X')
            {
                user1.symbol = 'X';
                user2.symbol = 'O';
            }
            else if(user_symbol == 'o' || user_symbol == 'O')
            {
                user1.symbol = 'O';
                user2.symbol = 'X';
            }
            else
            {
                printf("Please Enter a correct symbol <X/x or O/o> \n");
            }
        }
        while(user_symbol != 'x' && user_symbol != 'X' && user_symbol != 'o' && user_symbol != 'O');
        printf("User 2 Please Enter your name : ");
        gets(user2.name);
        printf("\n%s : Will be an %c",user1.name,user1.symbol);
        printf("\n%s : Will be an %c",user2.name,user2.symbol);
        printf("\n\n LET THE GAME BEGIN \n\n");

        //calling the function of a single game
        Single_Game();
        scanf("%c",&User_opt_YN);
        fflush(stdin);
    }


    return 0;
}

/*
FUNCTION NAME        : Check_index
FUNCTION DESCRIPTION : used to check if the entered value is entered before or not (returns 0 if not used)
*/
int Check_index(unsigned char index)
{
    int i,check=0;
    index = index - 48; //subtract to convert from ascii to decimal
    //index-1 as the numbers start from 1 not 0

    /*check if the number in the array has been replaced with a symbol (used before)*/
    if(game_arr[index-1] == 'X' || game_arr[index-1]=='O')
    {
        check = 1;
    }
    return check;
}

/*
FUNCTION NAME        : Check_Win
FUNCTION DESCRIPTION : used to check if the player won or not (returns 1 if he won)
*/
int Check_Win(unsigned char user)
{
    int check=0;
    /* check all the conditions that could lead to a win*/
    if((game_arr[0]==user && game_arr[1]==user && game_arr[2]==user) ||
       (game_arr[3]==user && game_arr[4]==user && game_arr[5]==user) ||
       (game_arr[6]==user && game_arr[7]==user && game_arr[8]==user) ||
       (game_arr[0]==user && game_arr[3]==user && game_arr[6]==user) ||
       (game_arr[1]==user && game_arr[4]==user && game_arr[7]==user) ||
       (game_arr[2]==user && game_arr[5]==user && game_arr[8]==user) ||
       (game_arr[0]==user && game_arr[4]==user && game_arr[8]==user) ||
       (game_arr[2]==user && game_arr[4]==user && game_arr[6]==user))
    {
        check = 1;
    }
    return check;
}

/*
FUNCTION NAME        : Single_Game
FUNCTION DESCRIPTION : used to loop at the same game till it's finished by a win
or the player wants to end the game
*/
void Single_Game(void)
{
    unsigned char user_option; //hold the entered value by the user
    /*infinite loop that breaks when the player enters e/E */
    while(user_option != 'e' && user_option != 'E')
    {
        printf("\t%c\t|\t%c\t|\t%c\n",game_arr[0],game_arr[1],game_arr[2]);
        printf("     -----------|---------------|-----------\n");
        printf("\t%c\t|\t%c\t|\t%c\n",game_arr[3],game_arr[4],game_arr[5]);
        printf("     -----------|---------------|-----------\n");
        printf("\t%c\t|\t%c\t|\t%c\n",game_arr[6],game_arr[7],game_arr[8]);
        printf("\nPress <e/E> to Exit the game\n\n");


        //counter = 9 when the game finishes with no winner
        if(Counter >= 9)
        {
            printf("The Game is Over , There is No Winner \nIf you Want to play again Press <y/Y> :");
            user_option='e'; // e to stop the current game
            Counter =0;     // counter = 0 to start the game over again
        }
        else
        {
            //ask the player to enter the number
            printf("Player_%c , your turn: \n",game_order[Counter]);
            scanf("%c",&user_option);
            fflush(stdin);
            //allowed numbers is from 1 to 9
            if(user_option>='1' && user_option<='9')
            {
                if(Check_index(user_option) == 0)    //check if the number entered has been used before
                {
                    //put X or O according to the order (even -> X | odd -> Y)
                    game_arr[user_option-49]=game_order[Counter];

                    //check if the last play leads to a win
                    if(Check_Win(game_order[Counter]) == 1)
                    {
                        //printing the winner
                        printf("Player_%c Wins\n",game_order[Counter]);
                        printf("Congratulations ");
                        if(user1.symbol == game_order[Counter])
                        {
                            puts(user1.name);
                        }
                        else
                        {
                            puts(user2.name);
                        }
                        printf("\n\n");
                        Counter = 0;
                        //asking if the player wants to play again
                        printf("Want to play again ? to play press <y/Y>");
                        break;
                    }
                    //there is no win in the last play
                    else
                    {
                        //increment Counter for the next play
                        Counter++;
                    }
                }
                //the entered number has been used before
                else
                {
                    printf("The number you entered is already used , Enter another number : \n");
                }
            }
            //e if the game is needed to be ended
            else if(user_option == 'e' || user_option == 'E')
            {
                printf("Want to play again ? to play press <y/Y>");
                Counter=0;
                break;
            }
            //the entered value is unknown
            else
            {
                printf("Please Enter a number from 1 to 9\nPress <e/E> to Exit\n");
            }
        }
    }
}
