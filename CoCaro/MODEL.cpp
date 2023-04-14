#include "MODEL.h"
#include "View.h"
void SetPlayer(_PLAYER& _PLAYER1, _PLAYER& _PLAYER2, vector<_PLAYER>& players)
{
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	do
	{
		system("cls");
		wcin.ignore();
		DrawBorder(X_CENTER - 30, Y_CENTER-2, 80, 5, DL_T, c_dblue);
		PrintText(L"ENTER PLAYER1'S NAME (2-10 CHARACTER):  ", 241, X_CENTER-24, Y_CENTER);
		wcin >> _PLAYER1.name;
		_PLAYER1.wins = 0;
	} while (_PLAYER1.name.length() < 2 || _PLAYER1.name.length() > 10);
	
	do
	{
		system("cls");
		DrawBorder(X_CENTER - 30, Y_CENTER - 2, 80, 5, DL_T, c_red);
		PrintText(L"ENTER PLAYER2'S NAME (2-10 CHARACTER):  ", 252, X_CENTER-24 , Y_CENTER);
		wcin >> _PLAYER2.name;
		_PLAYER2.wins = 0;
	} while (_PLAYER2.name.length() < 2 || _PLAYER2.name.length() > 10 || _PLAYER2.name == _PLAYER1.name);
	_PLAYER1 = LoadPlayer(_PLAYER1,players);
	SortPlayerList(players);
	_PLAYER2 = LoadPlayer(_PLAYER2,players);
	SortPlayerList(players);
}
bool CheckNameFile(wstring x)
{
	x = x + L".txt";
	vector<wstring> SAVE;
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = "saveName.txt";
	wstring save1;
	wifstream saveName(filename.c_str());
	saveName.imbue(utf8_locale);
	while (getline(saveName, save1))
	{
		SAVE.push_back(save1);
	}
	for (int i = 0; i < SAVE.size(); i++)
		if (SAVE[i] == x)
		{
			return false;
		}
	return true;
}

void SaveName(_POINT _A[][BOARD_SIZE],wstring &x, _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, int &color)
{
	//Sleep(1000);
	vector<wstring> SAVE;
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = "saveName.txt";
	wifstream saveName(filename.c_str());
	saveName.imbue(utf8_locale);
	while (CheckNameFile(x) == false)
	{
		wcout << "Da ton tai!" << endl << "Nhap lai: ";
		wcin >> x;
	}
	x += L".txt";
	saveName.close();
	wofstream saveName1(filename.c_str(), std::ios_base::app);
	saveName1.imbue(utf8_locale);
	saveName1 << x << "\n";
	wstring filename2 = x;
	wofstream saveName2(filename2.c_str());
	saveName2.imbue(utf8_locale);
	saveName2 << _PLAYER1.name << "\n" << _PLAYER1.wins << "\n";
	saveName2 << _PLAYER2.name << "\n" << _PLAYER2.wins << "\n" << color << "\n";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = HORIZONTAL_SPACE * j + LEFT + 2;
			_A[i][j].y = VERTIAL_SPACE * i + TOP + 1; 
			saveName2 << _A[i][j].c<< "\n";
		}
	}
}

vector<_PLAYER> GetPlayerList()
{
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = PLAYER_LIST;
	wifstream playerList(filename.c_str());
	playerList.imbue(utf8_locale);
	_PLAYER player;
	vector<_PLAYER> players;
	wstring clear;
	wstring name;
	while (getline(playerList, player.name))
	{
		getline(playerList, clear);
		player.rank = stoi(clear);
		player.wins = 0;
		players.push_back(player);
	}
	return players;
}

int CheckPlayerExistence(_PLAYER player, vector<_PLAYER> &players)
{

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].name == player.name) {
			players[i].rank++;
			return i;
		}
	}

	return -1;
}

void SavePlayer(_PLAYER player, vector<_PLAYER>& players)
{
	system("cls");
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = PLAYER_LIST;
	wofstream playerListout(filename.c_str(),std::ios_base::app);
	playerListout.imbue(utf8_locale);
	players = GetPlayerList();
	int exist = CheckPlayerExistence(player,players);
	if (exist == -1)
	{
		players.push_back(player);
		players[players.size() - 1].rank = 0;
		playerListout << player.name << "\n" << player.rank << "\n";
	}
	else
		players[exist].wins = player.wins;
}

_PLAYER LoadPlayer(_PLAYER player, vector<_PLAYER> &players)
{
	players = GetPlayerList();
	int exist = CheckPlayerExistence(player,players);

	if (exist == -1)
	{
		player.wins = 0;
		SavePlayer(player,players);;
			return player;
	}
	else
		return players[exist];
}

/*void SetPlayerRank(_PLAYER& player)
{
	int exist = CheckPlayerExistence(player);
	player.rank = exist + 1;
}*/

void SortPlayerList(vector<_PLAYER>& playerList)
{
	_PLAYER key;
	for (int i=0;i< playerList.size()-1;i++)
		for (int j=i+1;j< playerList.size();j++)
			if (playerList[i].rank < playerList[j].rank)
			{
				key = playerList[i];
				playerList[i] = playerList[j];
				playerList[j] = key;
			}
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename1 = PLAYER_LIST;
	string filename = PLAYER_LIST_OUT;
	wofstream playerListout(filename.c_str());
	playerListout.imbue(utf8_locale);
	wofstream playerList1(filename1.c_str());
	playerList1.imbue(utf8_locale);
	for (int i = 0; i < 3; i++)
		playerListout << playerList[i].name << endl << playerList[i].rank << endl;
	for (int i = 0; i < playerList.size(); i++)
	playerList1<<playerList[i].name << endl << playerList[i].rank << endl;
}
void Update_Rank(vector<_PLAYER>& players, _PLAYER player)
{
	for (int i = 0; i < players.size(); i++)
		if (players[i].name == player.name)
			players[i].rank += 2;
	SortPlayerList(players);
}
void ResetData() {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = HORIZONTAL_SPACE * j + LEFT + 2; // Trùng với hoành độ màn hình bàn cờ
			_A[i][j].y = VERTIAL_SPACE * i + TOP + 1; // Trùng với tung độ màn hình bàn cờ
			_A[i][j].c = 0; // 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy 
			//định như sau: -1 là lượt X đánh, 1 là lượt O đánh

		}
	}
	_TURN = -1;
	_COMMAND = -1;
	_X = _A[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1].x; _Y = _A[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1].y;

}
void LoadData(_POINT _A[][BOARD_SIZE],int &cl) {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = HORIZONTAL_SPACE * j + LEFT + 2;
			_A[i][j].y = VERTIAL_SPACE * i + TOP + 1;
			if (_A[i][j].c == -1) {
				GotoXY(_A[i][j].x, _A[i][j].y);
				SetColor(c_red);
				wcout << X_SYM;
				SetColor(c_def);
			}
			else if (_A[i][j].c == 1) {
				GotoXY(_A[i][j].x, _A[i][j].y);
				SetColor(c_green);
				wcout << O_SYM;
				SetColor(c_def);
			}
		}
	}
	_TURN = -cl;
	_COMMAND = -1;
	_X = _A[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1].x; _Y = _A[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1].y;

}

void GabageCollect() {
	// Cleaning resources if needed
}

void ExitGame() {
	system("cls");
	GabageCollect();
}

int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == -1) _A[i][j].c = -1;
				else _A[i][j].c = 1;
				return _A[i][j].c;
			}
		}
	}
	return 0;
}

void PrintWinner(int whoWin, int color) {
	SetColor(color);
	if (whoWin == -1)
		wcout << X_SYM;
	else
		wcout << O_SYM;
	SetColor(c_def);
}

void HoverWinner(int x, int y, int i, int WhoWin, int color) {
	switch (i)
	{
	case 0: // Hang ngang
		for (int i = 0; i < 5; i++)
			if (_A[x][y + i].c == WhoWin) {
				GotoXY(_A[x][y + i].x, _A[x][y + i].y);
				PrintWinner(WhoWin, color);
			}
		break;
	case 1: // Hang doc
		for (int i = 0; i < 5; i++)
			if (_A[x + i][y].c == WhoWin) {
				GotoXY(_A[x + i][y].x, _A[x + i][y].y);
				PrintWinner(WhoWin, color);
			}
		break;
	case 2: // Duong cheo phai
		for (int i = 0; i < 5; i++)
			if (_A[x + i][y + i].c == WhoWin) {
				GotoXY(_A[x + i][y + i].x, _A[x + i][y + i].y);
				PrintWinner(WhoWin, color);
			}
		break;
	case 3: /// Duong cheo trai
		for (int i = 0; i < 5; i++)
			if (_A[x + i][y - i].c == WhoWin) {
				GotoXY(_A[x + i][y - i].x, _A[x + i][y - i].y);
				PrintWinner(WhoWin, color);
			}
		break;
	}
}

bool CheckWinCondition(int winner) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (_A[i][j].c == -winner) {
				if (_A[i][j + 1].c == -winner && j + 4 < BOARD_SIZE && j - 1 >= 0) {
					int dem = 0;
					for (int k = 0; k < 4; ++k) dem += _A[i][j + k].c;
					if (dem == -winner * 4 && (_A[i][j + 4].c == 0 || _A[i][j - 1].c == 0)) return 0;
				}
				else if (_A[i + 1][j].c == -winner && i + 4 < BOARD_SIZE && i - 1 >= 0) {
					int dem = 0;
					for (int k = 0; k < 4; ++k) dem += _A[i + k][j].c;
					if (dem == -winner * 4 && (_A[i + 4][j].c == 0 || _A[i - 1][j].c == 0)) return 0;
				}
				else if (_A[i + 1][j + 1].c == -winner && i + 4 < BOARD_SIZE && j + 4 < BOARD_SIZE && i - 1 >= 0 && j - 1 >= 0) {
					int dem = 0;
					for (int k = 0; k < 4; ++k) dem += _A[i + k][j + k].c;
					if (dem == -winner * 4 && (_A[i + 4][j + 4].c == 0 || _A[i - 1][j - 1].c == 0)) return 0;
				}
				else if (_A[i + 1][j - 1].c == -winner && i + 4 < BOARD_SIZE && j - 4 >= 0 && i - 1 >= 0 && j + 1 < BOARD_SIZE) {
					int dem = 0;
					for (int k = 0; k < 4; ++k) dem += _A[i + k][j - k].c;
					if (dem == -winner * 4 && (_A[i + 4][j - 4].c == 0 || _A[i - 1][j + 4].c == 0)) return 0;
				}
			}
		}
	}
	return 1;
} // Kiem tra truong hop ko chan hai dau nhung nguoi choi kia da co 4 o

int CheckWin(int x, int y, int& x_Won, int& y_Won, int& i_Won) {
	int dem[4] = { 0,0,0,0 };
	/*
	0: Hang ngang
	1: Hang doc
	2: Hang cheo phai
	3: Hang cheo trai
	*/
	// Check ngang
	for (int i = 0; y + i < BOARD_SIZE && i < 5; i++) {
		dem[0] += _A[x][y + i].c;
	}
	// Check doc
	for (int i = 0; x + i < BOARD_SIZE && i < 5; i++) {
		dem[1] += _A[x + i][y].c;
	}
	// Check cheo phai
	for (int i = 0; x + i < BOARD_SIZE && y + i < BOARD_SIZE && i < 5; i++) {
		dem[2] += _A[x + i][y + i].c;
	}
	// Check cheo trai
	for (int i = 0; x + i < BOARD_SIZE && y - i >= 0 && i < 5; i++) {
		dem[3] += _A[x + i][y - i].c;
	}
	for (int i = 0; i < 4; i++) {
		if (abs(dem[i]) == 5) {
			x_Won = x; y_Won = y; i_Won = i;
			//HoverWinner(x, y, i, dem[i] / 5, (dem[i] / 5 == -1 ? 228 : 234));
			return dem[i] / 5;
		}

		else if (abs(dem[i]) == 4) {
			switch (i)
			{
			case 0:
				if (y > 0 && y < BOARD_SIZE - 4)
					if (_A[x][y - 1].c == 0 && _A[x][y + 4].c == 0) {
						x_Won = x; y_Won = y; i_Won = i;
						///HoverWinner(x, y, i, dem[i] / 4, (dem[i] / 4 == -1 ? 228 : 234));
						return dem[i] / 2;
					}
				break;
			case 1:
				if (x > 0 && x < BOARD_SIZE - 4)
					if (_A[x - 1][y].c == 0 && _A[x + 4][y].c == 0) {
						x_Won = x; y_Won = y; i_Won = i;
						//HoverWinner(x, y, i, dem[i] / 4, (dem[i] / 4 == -1 ? 228 : 234));
						return dem[i] / 2;
					}
				break;
			case 2:
				if (x - 1 >= 0 && y - 1 >= 0 && x + 4 < BOARD_SIZE && y + 4 < BOARD_SIZE)
					if (_A[x - 1][y - 1].c == 0 && _A[x + 4][y + 4].c == 0) {
						x_Won = x; y_Won = y; i_Won = i;
						//HoverWinner(x, y, i, dem[i] / 4, (dem[i] / 4 == -1 ? 228 : 234));
						return dem[i] / 2;
					}
				break;
			case 3:
				if (x - 1 >= 0 && y + 1 < BOARD_SIZE && x + 4 < BOARD_SIZE && y - 4 >= 0)
					if (_A[x - 1][y + 1].c == 0 && _A[x + 4][y - 4].c == 0) {
						x_Won = x; y_Won = y; i_Won = i;
						//HoverWinner(x, y, i, dem[i] / 4, (dem[i] / 4 == -1 ? 228 : 234));
						return dem[i] / 2;
					}
				break;
			}
		}
	}
	return 0;
}

int TestBoard() {
	int DrawChecker = 0;
	int winner, x_won, y_won, i_won;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c != 0) {
				winner = CheckWin(i, j, x_won, y_won, i_won);
				if (winner == 1 || winner == -1) {
					HoverWinner(x_won, y_won, i_won, winner, winner == -1 ? 228 : 234);
					return winner;
				}

				else if (winner == 2 || winner == -2) {
					if (CheckWinCondition(winner / 2))
					{
						HoverWinner(x_won, y_won, i_won, winner / 2, winner / 2 == -1 ? 228 : 234);
						return winner / 2;
					}
				}
				else
					++DrawChecker;
			}
		}
	}
	if (DrawChecker == BOARD_SIZE * BOARD_SIZE)
		return 0;
	return 2;
}

void TimeUpdating(high_resolution_clock::time_point& iniTime, int& seconds) {
	high_resolution_clock::time_point finalTime = high_resolution_clock::now();
	duration<double> time_span = finalTime - iniTime;
	if (time_span.count() >= 1) {
		iniTime = finalTime;
		TimeUpdate(seconds);
	}
}

void GetFont() {
	const locale empty_locale = locale::empty();
	typedef codecvt_utf8<wchar_t> converter_type;
	const converter_type* converter = new converter_type;
	const locale utf8_locale = locale(empty_locale, converter);
	string filename = "NUMBER_FONT.txt";
	wifstream stream(filename.c_str());
	stream.imbue(utf8_locale);
	wstring line;
	vector<wstring> line1;
	int count = 0;
	while (getline(stream, line)) {
		line1.push_back(line);
		++count;
	}
	for (int i = 0; i < line1[0].size(); i++) {
		if (line1[0][i] != ' ' && line1[0][i] != 12288) {
			for (int j = i; j < line1[0].size(); j++) {
				if (line1[0][j] == ' ' || line1[0][j] == 12288) {
					vector<wstring> v;
					for (int k = 0; k < count; k++) {
						v.push_back(line1[k].substr(i, j - i));
					}
					number_font.push_back(v);
					i = j;
					break;
				}
			}
		}
	}
}