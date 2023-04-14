#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <codecvt>
#include <fstream>
#include <vector>
#include <fcntl.h>
#include <io.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
//Constant Values
#define SPACE 32
#define BOARD_SIZE 16
#define LEFT 10
#define TOP 5
#define WIDTH 1050
#define HEIGHT 700
#define X_CENTER WIDTH / 16 + 2
#define Y_CENTER HEIGHT / 32
#define HORIZONTAL_LINE (wchar_t)0x2550
#define VERTICAL_LINE (wchar_t)0x2551
#define TOP_RIGHT (wchar_t)0x2557
#define TOP_LEFT (wchar_t)0x2554
#define BOTTOM_LEFT (wchar_t)0x255A
#define BOTTOM_RIGHT (wchar_t)0x255D
#define TOP_CROSS (wchar_t)0x2566
#define BOTTOM_CROSS (wchar_t)0x2569
#define	LEFT_CROSS (wchar_t)0x2560
#define RIGHT_CROSS (wchar_t)0x2563
#define CROSS (wchar_t)0x256B
#define HORIZONTAL_SPACE 5
#define VERTIAL_SPACE 2
// BOX value
#define B_WIDTH 4
#define B_HEIGHT 1
#define IM_SPACE 5
// Color settings
#define c_red 244
#define c_green 250
#define c_def 240
#define c_cyan 251
#define c_dblue 241
#define c_lblue 243
#define c_blue 249
#define c_yellow 254
#define c_orange 246
#define c_lime 242
#define c_gray 248
#define c_purple 245
// Drawing
#define X_SYM (wchar_t)0x0058
#define O_SYM (wchar_t)0x004F
// Box Drawing
#define DL_T 1
#define DL_T_VERTICAL (wchar_t)0x2551
#define DL_T_HORIZONTAL (wchar_t)0x2550
#define DL_T_TOPLEFTCORNER (wchar_t)0x2554
#define DL_T_TOPRIGHTCORNER (wchar_t)0x2557
#define DL_T_BOTLEFTCORNER (wchar_t)0x255A
#define DL_T_BOTRIGHTCORNER (wchar_t)0x255D
#define DM_T 2
#define DM_T_CORNER (wchar_t)0x255A
#define DM_T_HORIZONTAL (wchar_t)0x2550
#define DM_T_VERTICAL (wchar_t)0x2551
// CLOCK VALUE
#define TIME 10
struct _POINT {
	int x, y, c;
}; // x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
extern _POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
extern int _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
extern int _COMMAND; // Biến nhận giá trị phím người dùng nhập
extern int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ


extern vector<vector<wstring>> number_font; //Vector chứa font số

struct _MENU
{
	int options;	 //So chuc nang cua Menu
	int x;			 // Toa do cua diem bat 
	int y;			 //dau cua chuc nang dau tien
	int cursorColor; //Mau con tro chon menu
};

struct _PLAYER
{
	wstring name; //Ten nguoi choi
	int wins = 0;	 //Dem so tran thang
	int rank; //Xep hang cua nguoi choi
};

#pragma comment (lib,"winmm.lib") //dung cho PlaySoundA()
#define ENTER 13
#define ESC 27
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77

#define PLAYER_LIST "PlayerList.txt" //Thong tin cac player da choi 
#define PLAYER_LIST_OUT "PlayerListout.txt" //Thong tin cac player da choi game


