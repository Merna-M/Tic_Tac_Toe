#ifndef _TICTACTOE_H
#define _TICTACTOE_H






void Welcome_Message(void);
int Select_Game_Type(void);
char CheckWin(void);
void EnterLocation(void);
void TwoPlayers(void);
void Print_play();
int minimax(int depth, bool isMax, bool first);
void OnePlayer(char player , int level);

#endif // _TICTACTOE_H
