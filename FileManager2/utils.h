#pragma once
//#include <WinBase.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <io.h>
#include <time.h>
#include <windows.h>
#include <string>


//#include "FileListView.h"
#include <fstream>

// тип рамки вокруг окна
enum TBorderStyle
{
	tbsNone,
	tbsSingle,
	tbsDouble,
};

// тип элемента рамки 
enum TBorderStyleElement
{
	tbseRightTopCorner,
	tbseRightBottomCorner,
	tbseLeftBottomCorner,
	tbseLeftTopCorner,
	tbseVerticalLine,
	tbseHorizontalLine,
};




#define FileNameLen		(24)
#define FileSizeLen		(13)
#define DirectoryStr	"<DIR>"


#define ESC "\x1b"
#define CSI "\x1b["

#define DoubleBorder_RightTopCorner		(char)187
#define DoubleBorder_RightBottomCorner	(char)188
#define DoubleBorder_LeftBottomCorner	(char)200
#define DoubleBorder_LeftTopCorner		(char)201
#define DoubleBorder_VerticalLine		(char)186
#define DoubleBorder_HorizontalLine		(char)205

#define SingleBorder_RightTopCorner		(char)191
#define SingleBorder_RightBottomCorner	(char)217
#define SingleBorder_LeftBottomCorner	(char)192
#define SingleBorder_LeftTopCorner		(char)218
#define SingleBorder_VerticalLine		(char)179
#define SingleBorder_HorizontalLine		(char)196

#define color_black      (0)
#define color_dark_blue  (1)
#define color_dark_green (2)
#define color_light_blue (3)
#define color_dark_red   (4)
#define color_magenta    (5)
#define color_orange     (6)
#define color_light_gray (7)
#define color_gray       (8)
#define color_blue       (9)
#define color_green     (10)
#define color_cyan      (11)
#define color_red       (12)
#define color_pink      (13)
#define color_yellow    (14)
#define color_white		(15)
//
std::string get_textcolor_code(const int textcolor);
std::string get_backgroundcolor_code(const int backgroundcolor);
char get_BorderStyleElement_code(const TBorderStyle BorderStyle, const TBorderStyleElement Element);

//string get_print_color(const int textcolor) { // Linux only
//    return "\033["+get_textcolor_code(textcolor)+"m";
//}
//string get_print_color(const int textcolor, const int backgroundcolor) { // Linux only
//    return "\033["+get_textcolor_code(textcolor)+";"+get_backgroundcolor_code(backgroundcolor)+"m";
//}
//
//void print_color(const int textcolor) {
//#if defined(_WIN32)
//    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(handle, textcolor);
//#elif defined(__linux__)
//    cout << get_print_color(textcolor);
//#endif // Windows/Linux
//}
//void print_color(const int textcolor, const int backgroundcolor) {
//#if defined(_WIN32)
//    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(handle, backgroundcolor << 4 | textcolor);
//#elif defined(__linux__)
//    cout << get_print_color(textcolor, backgroundcolor);
//#endif // Windows/Linux
//}
//void print_color_reset() {
//#if defined(_WIN32)
//    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(handle, 7); // reset color
//#elif defined(__linux__)
//    cout << "\033[0m"; // reset color
//#endif // Windows/Linux
//}
//
//void println(const string& s = "") {
//    cout << s << endl;
//}
//void print(const string& s = "") {
//    cout << s;
//}
//void print(const string& s, const int textcolor) {
//    print_color(textcolor);
//    cout << s;
//    print_color_reset();
//}
//void print(const string& s, const int textcolor, const int backgroundcolor) {
//    print_color(textcolor, backgroundcolor);
//    cout << s;
//    print_color_reset();
//}
//void print_no_reset(const string& s, const int textcolor) { // print with color, but don't reset color afterwards (faster)
//    print_color(textcolor);
//    cout << s;
//}
//void print_no_reset(const string& s, const int textcolor, const int backgroundcolor) { // print with color, but don't reset color afterwards (faster)
//    print_color(textcolor, backgroundcolor);
//    cout << s;
//}
//
//

















//описание глобальных функций
void printXY(int X, int Y, const char* str,
	int BackGroundColor, int TextColor);

int TransparentDelay(unsigned long long int* Timer, unsigned long long int Delay);


// ќбъ€вление функций 
std::vector<std::string> GetFilesListInDirectory(std::string FilesPath, std::string FilesMask);

std::vector<std::string> GetFileContent(std::string FilesName);
std::vector<std::string> GetFileContent(std::string FilesName, int str_size); 


void setcursor(bool visible, DWORD size); // set bool visible = 0 - invisible, bool visible = 1 - visible
