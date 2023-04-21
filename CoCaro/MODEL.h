#pragma once
#include "CONSTANT_VALUES.h"
#include "View.h"


void ResetData();

void GabageCollect();

void ExitGame();

int CheckBoard(int pX, int pY);

void PrintWinner(int whoWin, int color);

void HoverWinner(int x, int y, int i, int WhoWin, int color);

bool CheckWinCondition(int winner);

int CheckWin(int x, int y, int& x_Won, int& y_Won, int& i_Won);

int TestBoard();


void TimeUpdating(high_resolution_clock::time_point& iniTime, int& seconds);

void GetFont();
void SetPlayer(_PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<_PLAYER>& players);
vector<_PLAYER> GetPlayerList();

int CheckPlayerExistence(_PLAYER player, vector<_PLAYER>& players);
void SavePlayer(_PLAYER player, vector<_PLAYER>& players);

_PLAYER LoadPlayer(_PLAYER player, vector<_PLAYER>& players);
void SortPlayerList(vector<_PLAYER>& playerList);
void SaveName(_POINT _A[][BOARD_SIZE], wstring& x, _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, int& color);
bool CheckNameFile(wstring x);
void LoadData(_POINT _A[][BOARD_SIZE], int& cl);

_POINT computerPoint();
_POINT minDistance(_POINT point);
_POINT closetCenter();
void SetPlayervsBot(_PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<_PLAYER>& players);
