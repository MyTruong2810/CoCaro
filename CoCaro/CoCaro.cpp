#include "View.h"
#include "CONSTANT_VALUES.h"
#include "CONTROL.h"
#include "MODEL.h"
_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
int _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ
vector<vector<wstring>> number_font; // Vector chứa font số
_PLAYER _PLAYER1, _PLAYER2;
vector<_PLAYER> players;
wstring x;
int exit1 = 0;//LUU NEU CHON THOAT TRONG MENUINGAME
int COLOR = 0;//MAU THE HIEN LUOT DANH DAU TIEN = LUOT DANH DAU TIEN
char c = 'x';
int main()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	FixConsoleWindow();
	ChangeConsole();
	int posis = 0;
	int save = 0;
	int seconds;
	bool validEnter;
	bool inGame = false;
	bool TimeSwitch = false;
	int winner;
	_POINT mark_point = { 0, 0 };
	while (true)
	{
		bool inMenu = true;
		int option = -2;
		do
		{
			PlaySoundA("nhacnen.wav", NULL, SND_ASYNC | SND_LOOP);
			option = SelectMenu(MainMenu());
			if (c == 'N') wcin.ignore();
			RunMainMenu(inMenu, option, _PLAYER1, _PLAYER2, players, COLOR, _A);
		} while (inMenu);
		inGame = true;
		if (option == 7 || option == -1)
			return 0;
		if (_PLAYER1.name == L"*BOT*") option = 2;
		StartGame(_PLAYER1, _PLAYER2, players, COLOR, option);
		int checkload = COLOR;
		COLOR = 0;
		seconds = TIME;
		inGame = true;
		TimeSwitch = false;
		int check_turn = -1;
		int count_turn = 0;
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		while (inGame)
		{
			TimeSwitch = false;
			_COMMAND = 0;
			COLOR = 1;
			if ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0)
				_COMMAND = 13;
			else if ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0)
				_COMMAND = 'W';
			else if ((GetAsyncKeyState(0x41/*A Keys*/) & (1 << 15)) != 0)
				_COMMAND = 'A';
			else if ((GetAsyncKeyState(0x44/*D Keys*/) & (1 << 15)) != 0)
				_COMMAND = 'D';
			else if ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0)
				_COMMAND = 'S';
			else if ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0)
				_COMMAND = 27;
			else if ((GetAsyncKeyState(VK_SHIFT) & (1 << 15)) != 0)// TRUY CAP MENU NHAN NUT SHIFT
				_COMMAND = 10;
			//_COMMAND = toupper(_getch());
			if (option == 2 && _TURN == 1) {
				_POINT comp_point = { 0, 0 };
				if (check_turn == -1) {
					comp_point = minDistance(mark_point);
					count_turn++;
					check_turn *= -1;
				}
				if (check_turn == 1) {
					comp_point = closetCenter();
					if (count_turn >= 2)
					{
						check_turn *= -1;
						count_turn = 0;
					}
				}
				int x_cPoint = comp_point.x;
				int y_cPoint = comp_point.y;
				_X = _A[x_cPoint][y_cPoint].x;
				_Y = _A[x_cPoint][y_cPoint].y;
				GotoXY(_X, _Y);
				_COMMAND = 13;
			}
			if (seconds <= 0) _COMMAND = -1;
			if (_COMMAND == 10) {
				StartInGameMENU(posis, _PLAYER1, _PLAYER2, COLOR, save, exit1);
				if (save == 1)
				{
					DrawBorder(60, 38, 30, 4, DL_T, 228);
					PrintText(L"NameFile: ", 244, 63, 39);
					wcin >> x;
					SaveName(_A, x, _PLAYER1, _PLAYER2, COLOR);
					system("cls");
					ExitGame();
					DrawExit();
					return 0;
				}
				//DOI MAU NUT MUTE
				if (posis % 2 != 0) DrawBigText("MUTE.txt", c_dblue, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE);
				else
					DrawBigText("MUTE.txt", c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE);
				if (exit1 != 0)
				{
					ExitGame();
					DrawExit();
					return 0;
				}
				t1 = high_resolution_clock::now();
				while ((GetAsyncKeyState(VK_ESCAPE) & (1 << 15)) != 0) TimeUpdating(t1, seconds);
			}
			else
			{
				if (_COMMAND == 'A') {
					MoveLeft(); while ((GetAsyncKeyState(0x41/*A Keys*/) & (1 << 15)) != 0) TimeUpdating(t1, seconds);
				}
				else if (_COMMAND == 'W') {
					MoveUp(); while ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0) TimeUpdating(t1, seconds);

				}
				else if (_COMMAND == 'S') {
					MoveDown(); while ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0) TimeUpdating(t1, seconds);

				}
				else if (_COMMAND == 'D') {
					MoveRight(); while ((GetAsyncKeyState(0x44/*D Keys*/) & (1 << 15)) != 0) TimeUpdating(t1, seconds);
				}
				else if (_COMMAND == 13) {
					switch (CheckBoard(_X, _Y)) {
					case -1:
						validEnter = true;
						SetColor(c_red);
						wcout << X_SYM;
						COLOR = -1;//LUU LUOT DANH NEU CO LOAD GAME
						if (posis % 2 == 0) PlaySound(TEXT("tick.wav"), NULL, SND_FILENAME);
						DrawBigText("O_PLAYER.txt", c_green, LEFT, 0);
						DrawBigText("X_PLAYER.txt", c_gray, LEFT + B_WIDTH * (BOARD_SIZE + 1) + 5, 0);
						SetColor(c_def);
						break;
					case 1:
						validEnter = true;
						SetColor(c_green);
						wcout << O_SYM;
						COLOR = 1;
						if (posis % 2 == 0) PlaySound(TEXT("tick.wav"), NULL, SND_FILENAME);
						DrawBigText("O_PLAYER.txt", c_gray, LEFT, 0);
						DrawBigText("X_PLAYER.txt", c_red, LEFT + B_WIDTH * (BOARD_SIZE + 1) + 5, 0);
						SetColor(c_def);
						break;
					case 0:
						validEnter = false;
					}

					if (validEnter) {
						winner = ProcessFinish(TestBoard());
						switch (winner)
						{
						case -1:
							_PLAYER2.wins++;
							players = GetPlayerList();//lAY LAI DANH SACH NEU LOAD GAME
							Update_Rank(players, _PLAYER2);
							do
							{
								c = AskContinue(winner);
							} while (c != 'Y' && c != 'N');
							if (c == 'Y') {
								seconds = TIME + 1;
								COLOR = 0;

								StartGame(_PLAYER1, _PLAYER2, players, COLOR, option);
							}
							else {
								COLOR = 0;
								seconds = TIME;
								inGame = false;
							}
							break;

						case 1:

							_PLAYER1.wins++;
							players = GetPlayerList();
							Update_Rank(players, _PLAYER1);
							do
							{
								c = AskContinue(winner);
							} while (c != 'Y' && c != 'N');
							if (c == 'Y') {
								seconds = TIME + 1;
								COLOR = 0;

								StartGame(_PLAYER1, _PLAYER2, players, COLOR, option);
							}
							else {
								COLOR = 0;
								seconds = TIME;
								inGame = false;
							}
							break;
						case 0:
							do
							{
								c = AskContinue(winner);
							} while (c != 'Y' && c != 'N');
							if (c == 'Y') {
								seconds = TIME + 1;
								COLOR = 0;
								StartGame(_PLAYER1, _PLAYER2, players, COLOR, option);
							}
							else {
								COLOR = 0;
								seconds = TIME;
								inGame = false;
							}
							break;
						default:
							seconds = TIME + 1;
							t1 = high_resolution_clock::now();
							TimeUpdate(seconds);
							TimeSwitch = true;
							break;
						}
					}
				}
				else if (_COMMAND == -1) {
					winner = -_TURN;
					ProcessFinish(winner);
					switch (winner)
					{
					case -1:
						_PLAYER2.wins++;
						players = GetPlayerList();
						Update_Rank(players, _PLAYER2);
						do
						{
							c = AskContinue(winner);
						} while (c != 'Y' && c != 'N');
						if (c == 'Y') {
							seconds = TIME + 1;
							COLOR = 0;

							StartGame(_PLAYER1, _PLAYER2, players, COLOR, option);
						}
						else {
							COLOR = 0;
							seconds = TIME;
							inGame = false;
						}
						break;
					case 1:
						_PLAYER1.wins++;
						players = GetPlayerList();
						Update_Rank(players, _PLAYER1);
						do
						{
							c = AskContinue(winner);
						} while (c != 'Y' && c != 'N');
						if (c == 'Y') {
							seconds = TIME + 1;
							COLOR = 0;

							StartGame(_PLAYER1, _PLAYER2, players, COLOR, option);
						}
						else {
							COLOR = 0;
							seconds = TIME;
							inGame = false;
						}
						break;
					case 0:
						do
						{
							c = AskContinue(winner);
						} while (c != 'Y' && c != 'N');
						if (c == 'Y') {
							seconds = TIME + 1;
							COLOR = 0;
							StartGame(_PLAYER1, _PLAYER2, players, COLOR, option);

						}
						else {
							COLOR = 0;
							inGame = false;
						}
						break;
					}
				}
				if (!TimeSwitch)
					TimeUpdating(t1, seconds);
			}
		}
	}
}


