#include "CONTROL.h"
#include <mmsystem.h>
vector<wstring>sf;
int n = 0;
int kt;//CHON MENU LOAD GAME
int cl = 0;//lUOT DANH LOAD FILE LUU TRUNG VOI MAU X - O
void StartGame(_PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<_PLAYER>& players, int& cl, int bot)
{
	system("cls");
	PlaySound(TEXT("NoSound.wav"), NULL, SND_FILENAME);
	DrawBigText("LOADING.txt", 245, X_CENTER - 35, 15);
	for (int i = 0; i < 10; i++)
	{
		DrawBigText("LOADING1.txt", 245, X_CENTER + i * 4 + 23, 15);
		Sleep(200);
	}
	system("cls");
	GetFont();
	//LAP LAI HAI LAN DE HIEN THI KHONG BI CHE BOI BAN CO
	if (cl != 0)
	{
		LoadData(_A, cl);
		DrawPlayer(cl);
	}
	else
	{
		ResetData();
		DrawPlayer(cl);
	}
	DrawBoard(BOARD_SIZE);

	if (cl != 0)
	{
		LoadData(_A, cl);
	}
	else ResetData();
	DrawInGameMenu();
	if (bot == 2)
		ShowPlayerInfovsBot(_A, _PLAYER1, _PLAYER2);
	else
		ShowPlayerInfo(_A, _PLAYER1, _PLAYER2);
}

bool StartInGameMENU(int& pos1, _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, int& COLOR, int& save, int& exit) {
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));//KHONG NHAP KI TU THUA BO NHO DEM
	Sleep(50);
	int pos = 0;
	int NAVIGATE = 0;
	bool change = true;
	while (true) {
		if (change) {
			DrawInGameMenuUSING(pos);
			change = false;
		}
		NAVIGATE = 0;
		if ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0)
			NAVIGATE = 'W';
		else if ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0)
			NAVIGATE = 'S';
		else if ((GetAsyncKeyState(VK_SPACE) & (1 << 15)) != 0)//IN GAME MENU NHAN NUT SPACE DE CHON 
			NAVIGATE = 32;
		else if ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0)
			NAVIGATE = 27;
		// NAVIGATE = toupper(_getch());
		switch (NAVIGATE)
		{
		case 'W':
			--pos;
			change = true;
			while ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0);
			break;
		case 'S':
			++pos;
			change = true;
			while ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0);
			break;
		case 32:
			if (pos == 0) {
				save = 1;
				return 0;
				break;
			}
			else if (pos == 1) {
				GotoXY(_X, _Y);
				pos1++;
				return 0;
				break;
			}
			else if (pos == 2) {
				ExitGame();
				exit = 1;
				return 0;
			}
			change = true;
			while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0);
			break;
		case 27:
			change = true;
			while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0);
			DrawInGameMenuUSING(-1);
			return 1;
		}
		if (pos > 2) pos = 0;
		else if (pos < 0) pos = 2;
	}
	return 1;
}

void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x) {
		_X += HORIZONTAL_SPACE;
		GotoXY(_X, _Y);
	}
}
void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= HORIZONTAL_SPACE;
		GotoXY(_X, _Y);
	}
}
void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y) {
		_Y += VERTIAL_SPACE;
		GotoXY(_X, _Y);
	}
}
void MoveUp() {
	if (_Y > _A[0][0].y) {
		_Y -= VERTIAL_SPACE;
		GotoXY(_X, _Y);
	}
}

int SelectMenu(_MENU menu)
{
	int cursor = 1;
	char key = 0;

	PrintText(L"▀▀ ▀▀", menu.cursorColor, menu.x - 1, menu.y);

	do
	{
		key = 0;
		if ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0)
			key = 13;
		else if ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0)
			key = 'W';
		else if ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0)
			key = 'S';
		else if ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0)
			key = 27;
		if (key == 'W' && cursor > 1)
		{
			PrintText(L"        ", menu.cursorColor, menu.x - 1, menu.y + cursor - 1);
			cursor--;
			PrintText(L"▀▀ ▀▀", menu.cursorColor, menu.x - 1, menu.y + cursor - 1);
			while ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0);
		}
		else if (key == 'S' && cursor < menu.options)
		{
			PrintText(L"        ", menu.cursorColor, menu.x - 1, menu.y + cursor - 1);
			cursor++;
			PrintText(L"▀▀ ▀▀", menu.cursorColor, menu.x - 1, menu.y + cursor - 1);
			while ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0);
		}
		else if (key == ESC)
		{
			return -1;
		}


	} while (key != ENTER);
	return cursor;
}

void RunMainMenu(bool& run, int option, _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<_PLAYER>& players, int& cl, _POINT _A[][BOARD_SIZE])
{
	switch (option)
	{
	case 1:
		SetPlayer(_PLAYER1, _PLAYER2, players);
		run = false;
		break;

	case 2:
		/*
			Danh voi may
		*/
		SetPlayervsBot(_PLAYER1, _PLAYER2, players);
		run = false;
		break;
	case 3:
		Loadedfile(n, sf);
		kt = SelectMenu(SaveFileMenu(n, sf));
		if (kt == n + 1 || kt == -1) break;// NEU CHON BACK TO MENU
		RunLoad(_A, kt, _PLAYER1, _PLAYER2, sf, n, cl);
		run = false;
		break;
	case 4:
		ShowRank();
		while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) == 0);
		break;
	case 5:
		ShowHelp();
		while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) == 0);
		break;
	case 6:
		AboutUs();
		while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) == 0);
		break;
	case 7:case -1:
		ExitGame();
		DrawExit();
		Sleep(100);
		run = false;
		break;
	}
}
void RunLoad(_POINT _A[][BOARD_SIZE], int option, _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<wstring>& filenamesave, int n, int& COLOR)
{
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	wstring filename = filenamesave[option - 1];
	wifstream save(filename.c_str());
	save.imbue(utf8_locale);
	getline(save, _PLAYER1.name);
	save >> _PLAYER1.wins;
	save.ignore();
	getline(save, _PLAYER2.name);
	save >> _PLAYER2.wins;
	save >> COLOR;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			save >> _A[i][j].c;
	}
}