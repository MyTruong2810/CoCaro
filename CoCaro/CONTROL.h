#pragma once
#include "CONSTANT_VALUES.h"
#include "MODEL.h"
#include "View.h"


bool StartInGameMENU(int& pos1, _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, int& COLOR, int& save, int& exit);
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();

int SelectMenu(_MENU menu);
void RunMainMenu(bool& run, int option, _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<_PLAYER>& players, int& cl, _POINT _A[][BOARD_SIZE]);
void Update_Rank(vector<_PLAYER>& players, _PLAYER player);
void RunLoad(_POINT _A[][BOARD_SIZE], int option, _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<wstring>& filenamesave, int n, int &COLOR);
void StartGame(_PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<_PLAYER>& players, int& cl);


