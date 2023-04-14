#include "View.h"
#include <mmsystem.h>//THU VIEN DUNG AM THANH
#include"MODEL.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void ChangeConsole() {
	RECT r;
	HWND consoleWindow = GetConsoleWindow();
	HWND hDesktop = GetDesktopWindow();
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hConsole, FALSE, &font);
	font.dwFontSize.X = 13; // font width
	font.dwFontSize.Y = 16; // font height
	wcscpy_s(font.FaceName, L"Impact"); // font name
	SetCurrentConsoleFontEx(hConsole, FALSE, &font);
	SetConsoleTitleA("Caro Game");
	SetConsoleTextAttribute(hConsole, c_def);
	GetWindowRect(hDesktop, &r);
	MoveWindow(consoleWindow, r.right / 2 - WIDTH / 2, r.bottom / 2 - HEIGHT / 2, WIDTH, HEIGHT, true);
}

void DrawTableLine(int numOfCol, wchar_t mainSym, wchar_t subSym, int width)
{
	for (int i = 0; i < numOfCol - 1; i++)
	{
		for (int i = 0; i < width; i++) wcout << mainSym;
		wcout << subSym;
	}
	for (int i = 0; i < width; i++) wcout << mainSym;
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBoard(int pSize) {
	int iniX = _A[0][0].x, iniY = _A[0][0].y;
	GotoXY(iniX - 2, iniY - 1);
	wcout << TOP_LEFT;
	DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, TOP_CROSS, B_WIDTH);
	wcout << TOP_RIGHT;

	for (int i = 0; i < (BOARD_SIZE - 1) * (B_HEIGHT + 1); i++)
	{
		GotoXY(LEFT, TOP + i + 1);
		if ((i + 1) % (B_HEIGHT + 1) != 0)
		{
			wcout << VERTICAL_LINE;
			DrawTableLine(BOARD_SIZE, SPACE, VERTICAL_LINE, B_WIDTH);
			wcout << VERTICAL_LINE;
		}
		else
		{
			wcout << LEFT_CROSS;
			DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, CROSS, B_WIDTH);
			wcout << RIGHT_CROSS;
		}
	}
	for (int i = 0; i < B_HEIGHT; i++)
	{
		GotoXY(iniX - 2, iniY + (BOARD_SIZE - 1) * (B_HEIGHT + 1) + i);
		wcout << VERTICAL_LINE;
		DrawTableLine(BOARD_SIZE, SPACE, VERTICAL_LINE, B_WIDTH);
		wcout << VERTICAL_LINE;
	}

	GotoXY(iniX - 2, iniY + (BOARD_SIZE - 1) * (B_HEIGHT + 1) + B_HEIGHT);
	wcout << BOTTOM_LEFT;
	DrawTableLine(BOARD_SIZE, HORIZONTAL_LINE, BOTTOM_CROSS, B_WIDTH);
	wcout << BOTTOM_RIGHT;
	GotoXY(_X, _Y);
}


void SetColor(int color) {
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void PrintText(wstring text, int color, int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GotoXY(x, y);
	SetColor(color);
	wcout << text;
	SetColor(c_def);
}

void EraseBox(int x, int y, int width, int height, int color) {
	SetColor(color);
	for (int i = 0; i < height; i++) {
		GotoXY(x, y + i);
		for (int j = 0; j < width; j++) {
			wcout << L" ";
		}
	}
	SetColor(c_def);
}

void DrawBigText(string filename, int color, int x, int y) {
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	wifstream stream(filename.c_str());
	stream.imbue(utf8_locale);
	vector<wstring> line1;
	wstring line;
	int count = 0;
	while (getline(stream, line)) {
		line1.push_back(line);
		++count;
	};
	for (int i = 0; i < count; i++) {
		PrintText(line1[i], color, x, y + i);
	}
}

void DrawBigText(string filename, int color, int x, int y, int timer) {
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	wifstream stream(filename.c_str());
	stream.imbue(utf8_locale);
	vector<wstring> line1;
	wstring line;
	int count = 0;
	while (getline(stream, line)) {
		line1.push_back(line);
		++count;
	};
	for (int i = 0; i < count; i++) {
		PrintText(line1[i], color, x, y + i);
		Sleep(timer);
	}
}


void DrawBorder(int x, int y, int width, int height, wchar_t border_type, int color) {
	if (border_type == DL_T) {
		GotoXY(x, y);
		SetColor(color);
		wcout << DL_T_TOPLEFTCORNER;
		for (int i = 1; i < width - 1; i++) wcout << DL_T_HORIZONTAL;
		wcout << DL_T_TOPRIGHTCORNER;
		for (int i = 1; i < height - 1; i++) {
			GotoXY(x, y + i);
			wcout << DL_T_VERTICAL;
			GotoXY(x + width - 1, y + i);
			wcout << DL_T_VERTICAL;
		}
		GotoXY(x, y + height - 1);
		wcout << DL_T_BOTLEFTCORNER;
		for (int i = 1; i < width - 1; i++) wcout << DL_T_HORIZONTAL;
		wcout << DL_T_BOTRIGHTCORNER;
	}
	else if (border_type == DM_T) {
		GotoXY(x, y);
		SetColor(color);
		wcout << DM_T_CORNER;
		for (int i = 1; i < width - 1; i++) wcout << DM_T_HORIZONTAL;
		wcout << DM_T_CORNER;
		for (int i = 1; i < height - 1; i++) {
			GotoXY(x, y + i);
			wcout << DM_T_VERTICAL;
			GotoXY(x + width - 1, y + i);
			wcout << DM_T_VERTICAL;
		}
		GotoXY(x, y + height - 1);
		wcout << DM_T_CORNER;
		for (int i = 1; i < width - 1; i++) wcout << DM_T_HORIZONTAL;
		wcout << DM_T_CORNER;
	}
	SetColor(c_def);
}

void DrawInGameMenuUSING(int pos) {
	if (pos >= 0) {
		DrawBigText("SAVE.txt", pos == 0 ? c_def : c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14);
		DrawBigText("MUTE.txt", pos == 1 ? c_def : c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE);
		DrawBigText("EXIT.txt", pos == 2 ? c_def : c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE * 2);
	}
	else {
		DrawBigText("SAVE.txt", c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14);
		DrawBigText("MUTE.txt", c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE);
		DrawBigText("EXIT.txt", c_gray, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 6, _A[0][BOARD_SIZE - 1].y + 14 + IM_SPACE * 2);
	}
}



void PrintNumber(int number, int x, int y, int color) {
	GotoXY(x, y);
	if (number >= 10) {
		vector<int> v;
		while (number > 0) {
			v.push_back(number % 10);
			number /= 10;
		}
		for (int j = v.size() - 1; j >= 0; j--) {
			for (int k = 0; k < number_font[v[j]].size(); k++) {
				PrintText(number_font[v[j]][k], color, x + (v.size() - j - 1) * number_font[v[(j == v.size() - 1 ? j : j + 1)]].size() + (v.size() - j - 1) * 1, y + k);
			}
		}
	}
	else {
		int num = number % 10;
		for (int i = 0; i < number_font[0].size(); i++)
			PrintText(number_font[0][i], color, x, y + i);
		for (int i = 0; i < number_font[num].size(); i++)
			PrintText(number_font[num][i], color, x + number_font[0].size() + 2, y + i);
	}
}

void TimeUpdate(int& seconds) {
	--seconds;
	if (seconds < 0) return;
	EraseBox(LEFT + B_WIDTH * (BOARD_SIZE / 2), 1, 20, 3, c_def);
	PrintNumber(0, LEFT + B_WIDTH * (BOARD_SIZE / 2) + 1, 1, seconds < 10 ? c_red : c_def);
	EraseBox(LEFT + B_WIDTH * (BOARD_SIZE / 2) + number_font[0][0].size() + 1, 1, number_font[0][0].size() + 1, number_font[0].size(), seconds < 10 ? c_red : c_def);
	DrawBigText("DOUBLE_DOT.txt", (seconds < 10 ? c_red : c_def), LEFT + B_WIDTH * (BOARD_SIZE / 2) + number_font[0][0].size() + 1 + 1, 1);
	PrintNumber(seconds, LEFT + B_WIDTH * (BOARD_SIZE / 2) + 7 + 1, 1, seconds < 10 ? c_red : c_def);
	GotoXY(_X, _Y);
}


void DrawInGameMenu() {
	DrawBigText("IG_TITLE.txt", c_red, _A[0][BOARD_SIZE - 1].x + B_WIDTH * 2 + 9, _A[0][BOARD_SIZE - 1].y + 1);
	DrawInGameMenuUSING(-1);
	DrawBorder(_A[0][BOARD_SIZE - 1].x + B_WIDTH * 3 + 2, _A[0][BOARD_SIZE - 1].y + 11, 36, 18, DL_T, 226);
	GotoXY(_X, _Y);
}

void DrawPlayer(int COLOR) {
	DrawBorder(22, 0, 15, 5, DL_T, c_dblue);
	DrawBorder(67, 0, 15, 5, DL_T, c_dblue);
	PrintText(L"NAME: ", 241, 24, 1);
	PrintText(L"WON: ", 241, 24, 3);
	PrintText(L"NAME: ", 241, 69, 1);
	PrintText(L"WON: ", 241, 69, 3);
	if (COLOR == -1)//NHAN LUOT DANH VAO NEU LOAD GAME
	{
		DrawBigText("O_PLAYER.txt", c_green, LEFT, 0);
		DrawBigText("X_PLAYER.txt", c_gray, LEFT + B_WIDTH * (BOARD_SIZE + 1) + 5, 0);
	}
	else {
		DrawBigText("O_PLAYER.txt", c_gray, LEFT, 0);
		DrawBigText("X_PLAYER.txt", c_red, LEFT + B_WIDTH * (BOARD_SIZE + 1) + 5, 0);
	}
	int tempTime = TIME + 1;
	TimeUpdate(tempTime);
	GotoXY(_X, _Y);
}

int ProcessFinish(int pWhoWin) {
	switch (pWhoWin)
	{
	case -1:
		PlaySound(TEXT("win.wav"), NULL, SND_FILENAME);
		DrawBigText("X_WIN.txt", 228, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 20, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 20, 80);
		break;
	case 1:
		PlaySound(TEXT("win.wav"), NULL, SND_FILENAME);
		DrawBigText("O_WIN.txt", 174, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 20, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 20, 80);
		break;
	case 0:
		PlaySound(TEXT("win.wav"), NULL, SND_FILENAME);
		DrawBigText("DRAW.txt", 158, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 20, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 20, 80);
		break;
	case 2:
		_TURN = -_TURN;
	}
	GotoXY(_X, _Y);
	return pWhoWin;
}

int AskContinue(int pWhoWin) {
	Sleep(400);
	int pos = 0;
	int NAVIGATOR = 0;
	bool change = true;
	do {
		if (change) {
			switch (pos)
			{
			case 0:
				DrawBigText("AGAIN.txt", pWhoWin == -1 ? c_red : (pWhoWin == 1 ? c_lime : c_dblue), _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 7, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 5);
				DrawBigText("RETURN_MENU.txt", c_gray, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 4, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y + 2);
				break;
			case 1:
				DrawBigText("AGAIN.txt", c_gray, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 7, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y - 5);
				DrawBigText("RETURN_MENU.txt", pWhoWin == -1 ? c_red : (pWhoWin == 1 ? c_lime : c_dblue), _A[BOARD_SIZE / 2][BOARD_SIZE / 2].x - 4, _A[BOARD_SIZE / 2][BOARD_SIZE / 2].y + 2);
			}
			change = false;
		}
		NAVIGATOR = 0;
		if ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0)
			NAVIGATOR = 'W';
		else if ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0)
			NAVIGATOR = 'S';
		else if ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0)
			NAVIGATOR = 13;
		if (NAVIGATOR == 'W') { --pos; change = true; while ((GetAsyncKeyState(0x57/*W Keys*/) & (1 << 15)) != 0); }
		else if (NAVIGATOR == 'S') { ++pos; change = true; while ((GetAsyncKeyState(0x53/*S Keys*/) & (1 << 15)) != 0); }
		if (pos > 1) pos = 0;
		else if (pos < 0) pos = 1;
	} while (NAVIGATOR != 13);
	while ((GetAsyncKeyState(VK_RETURN) & (1 << 15)) != 0);
	if (pos == 0) return 'Y';
	return 'N';
	/*return toupper(_getch());*/
}


void DrawExit() {
	DrawBigText("EXITGAME_SCREEN.txt", 225, 40, 10, 50);
}

void ShowHelp()
{
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = "HELP.txt";
	int x = X_CENTER - 10;
	int y = 0;
	wstring line;
	int i = 0;
	wifstream helpFile(filename.c_str());
	helpFile.imbue(utf8_locale);
	/*std::fstream helpFile;
	helpFile.open("Help.txt", std::fstream::in);*/
	system("cls");
	while (getline(helpFile, line))
	{
		PrintText(line, 244, x, y + i);
		i++;
	}
}

void AboutUs()
{
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = "ABOUTUS.txt";
	int x = X_CENTER - 18;
	int y = Y_CENTER / 4;
	wstring line;
	int i = 0;
	wifstream ABOUTUS(filename.c_str());
	ABOUTUS.imbue(utf8_locale);
	/*std::fstream helpFile;
	helpFile.open("Help.txt", std::fstream::in);*/

	system("cls");

	DrawBigText("ABOUTUSBT.txt", 225, 47, 1, 50);
	DrawBigText("ABOUTUS1.txt", c_red, 100, 3);

	DrawBorder(X_CENTER - 10, Y_CENTER - 10, 40, 30, DL_T, c_dblue);
	while (getline(ABOUTUS, line))
	{
		PrintText(line, 244, x + 9, y + i + 10);
		i++;
	}
}
void DrawMenuBackGround()
{

}

_MENU MainMenu()
{
	_MENU menu;

	menu.options = 7;
	menu.x = X_CENTER - 7;
	menu.y = Y_CENTER + 9;
	menu.cursorColor = 244;
	system("cls");
	DrawBigText("CARO.txt", 225, 38, 1, 50);
	DrawBigText("MENUDS1.txt", c_red, 45, 9);
	DrawBigText("MENUDS2.txt", c_def, 67, 15);
	DrawBigText("MENUDS3.txt", c_green, 85, 9);
	DrawBigText("MENUDS4.txt", c_green, 100, 30);
	DrawBigText("MENUDS4.txt", c_red, 25, 30);
	DrawBorder(menu.x - 9, Y_CENTER + 5 - 2, 45, 15, DL_T, c_dblue);
	PrintText(L"***************************", 241, menu.x, menu.y - 3);
	PrintText(L"*      WELCOME TO OUR CARO GAME     *", 241, menu.x - 5, menu.y - 2);
	PrintText(L"***************************", 241, menu.x, menu.y - 1);
	PrintText(L"       PLAYER vs PLAYER        ", 241, menu.x, menu.y);
	PrintText(L"       PLAYER vs COMPUTER         ", 241, menu.x, menu.y + 1);
	PrintText(L"       LOAD GAME         ", 241, menu.x, menu.y + 2);
	PrintText(L"       RANKING         ", 241, menu.x, menu.y + 3);
	PrintText(L"       HELP           ", 241, menu.x, menu.y + 4);
	PrintText(L"       ABOUT US        ", 241, menu.x, menu.y + 5);
	PrintText(L"       EXIT GAME       ", 241, menu.x, menu.y + 6);
	return menu;
}
void ShowRank()
{
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = PLAYER_LIST_OUT;
	int x = X_CENTER + 5;
	int y = Y_CENTER / 4 + 10;
	int n = 225;
	wstring line;
	int i = 0;
	wifstream RANK(filename.c_str());
	RANK.imbue(utf8_locale);
	/*std::fstream helpFile;
	helpFile.open("Help.txt", std::fstream::in);*/

	system("cls");
	DrawBigText("TOPRANK.txt", 228, 55, 1, 50);
	DrawBorder(X_CENTER - 9, Y_CENTER - 10, 30, 20, DL_T, 224);
	while (getline(RANK, line))
	{
		PrintText(line, n++, x, y + i);
		if (i % 2 == 0) i++;
		else
			i += 5;
	}
	PrintText(L"BACK TO MENU - ESC", 224, x - 8, y + i);
}
void ShowPlayerInfo(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2)
{

	PrintText(_PLAYER1.name, 241, 30, 1);
	PrintText(_PLAYER2.name, 241, 75, 1);
	PrintText(to_wstring(_PLAYER1.wins), 241, 30, 3);
	PrintText(to_wstring(_PLAYER2.wins), 241, 75, 3);
	GotoXY(_X, _Y);
}

void Loadedfile(int& n, vector<wstring>& filenamesave)
{
	n = 0;
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = "saveName.txt";
	int x = X_CENTER - 18;
	int y = Y_CENTER / 4;
	wstring line;
	wifstream SAVEFILE(filename.c_str());
	SAVEFILE.imbue(utf8_locale);
	/*std::fstream helpFile;
	helpFile.open("Help.txt", std::fstream::in);*/

	system("cls");
	DrawBigText("Loadfilemenu.txt", 228, 55, 1, 50);
	DrawBorder(X_CENTER - 20, Y_CENTER - 13, 57, 30, DL_T, c_red);
	while (getline(SAVEFILE, line))
	{
		filenamesave.push_back(line);
		n++;
	}
}
_MENU SaveFileMenu(int& n, vector<wstring>& filenamesave)
{
	_MENU menu;
	menu.x = X_CENTER - 5;
	menu.y = Y_CENTER - 10;
	menu.cursorColor = 244;
	Loadedfile(n, filenamesave);
	menu.options = n + 1;
	for (int i = 0; i < n; i++)
		PrintText(filenamesave[i], 241, X_CENTER + 2, menu.y + i);
	PrintText(L"BACK TO MENU", 226, X_CENTER + 2, menu.y + n);
	return menu;
}




