#define _CRT_SECURE_NO_WARNINGS // отключить предупреждение
#include "utils.h"


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if (size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}


std::string get_textcolor_code(const int textcolor) { // Linux only
	switch (textcolor) {
	case  0: return "30"; // color_black      0
	case  1: return "34"; // color_dark_blue  1
	case  2: return "32"; // color_dark_green 2
	case  3: return "36"; // color_light_blue 3
	case  4: return "31"; // color_dark_red   4
	case  5: return "35"; // color_magenta    5
	case  6: return "33"; // color_orange     6
	case  7: return "37"; // color_light_gray 7
	case  8: return "90"; // color_gray       8
	case  9: return "94"; // color_blue       9
	case 10: return "92"; // color_green     10
	case 11: return "96"; // color_cyan      11
	case 12: return "91"; // color_red       12
	case 13: return "95"; // color_pink      13
	case 14: return "93"; // color_yellow    14
	case 15: return "97"; // color_white     15
	default: return "37";
	}
}
std::string get_backgroundcolor_code(const int backgroundcolor) { // Linux only
	switch (backgroundcolor) {
	case  0: return  "40"; // color_black      0
	case  1: return  "44"; // color_dark_blue  1
	case  2: return  "42"; // color_dark_green 2
	case  3: return  "46"; // color_light_blue 3
	case  4: return  "41"; // color_dark_red   4
	case  5: return  "45"; // color_magenta    5
	case  6: return  "43"; // color_orange     6
	case  7: return  "47"; // color_light_gray 7
	case  8: return "100"; // color_gray       8
	case  9: return "104"; // color_blue       9
	case 10: return "102"; // color_green     10
	case 11: return "106"; // color_cyan      11
	case 12: return "101"; // color_red       12
	case 13: return "105"; // color_pink      13
	case 14: return "103"; // color_yellow    14
	case 15: return "107"; // color_white     15
	default: return  "40";
	}
}

char get_BorderStyleElement_code(const TBorderStyle BorderStyle, const TBorderStyleElement Element) { // Linux only
	switch (BorderStyle)
	{
	case tbsNone: return ' ';
	case tbsSingle:
		switch (Element)
		{
		case tbseRightTopCorner: return SingleBorder_RightTopCorner;
		case tbseRightBottomCorner: return  SingleBorder_RightBottomCorner;
		case tbseLeftBottomCorner:return  SingleBorder_LeftBottomCorner;
		case tbseLeftTopCorner:return SingleBorder_LeftTopCorner;
		case tbseVerticalLine:return  SingleBorder_VerticalLine;
		case tbseHorizontalLine:return SingleBorder_HorizontalLine;
		default: return ' ';
		}

	case tbsDouble:
		switch (Element)
		{
		case tbseRightTopCorner: return DoubleBorder_RightTopCorner;
		case tbseRightBottomCorner: return DoubleBorder_RightBottomCorner;
		case tbseLeftBottomCorner:return DoubleBorder_LeftBottomCorner;
		case tbseLeftTopCorner:return DoubleBorder_LeftTopCorner;
		case tbseVerticalLine:return DoubleBorder_VerticalLine;
		case tbseHorizontalLine:return DoubleBorder_HorizontalLine;
		default: return ' ';
		}
	default: return ' ';
	}

		
}


// печатает текст по координатам заданым цветом и фоном
void printXY(int X, int Y, const char* str,
	int BackGroundColor, int TextColor)
{
	std::cout << CSI <<  get_backgroundcolor_code(BackGroundColor)  << ";"
		<< get_textcolor_code(TextColor) << "m";   // black background / blue text 94m
	std::cout << CSI << Y << ";" << X << "H";     // cursor position		
	std::cout << str;
	std::cout << CSI "0m";       // restore colors 
}



int TransparentDelay(unsigned long long int* Timer, unsigned long long int Delay)
{
	if (*Timer < clock())
	{
		*Timer = clock() + Delay;
		return 1;
	}
	return 0;
}



std::vector<std::string> GetFilesListInDirectory(std::string FilesPath, std::string FilesMask)
{
	//Вспомогательные структуры и дескрипторы
	struct _finddata_t f;
	long long hFile;
	std::vector<std::string> listFileNames;
	FilesPath = FilesPath + "\\" + FilesMask;
	char mbstr[100];
	std::string tmpName;
	std::string tmpSize;
	//std::string dateAjoutSysteme(mbstr);
	//std::cout << dateAjoutSysteme;
	//Открываем текущую директорию
	if ((hFile = _findfirst(FilesPath.c_str(), &f)) != -1L)
	{
		do//В цикле обходим файлы директории
		{
			if (strcmp(f.name, ".") == 0) continue;
			
			std::strftime(mbstr, 100, "%d/%m/%Y|%T", std::localtime(&f.time_write));
			tmpName = f.name;
			tmpName.resize(FileNameLen, ' ');
			if ((f.attrib & _A_SUBDIR)) tmpSize = DirectoryStr;
			else tmpSize = std::to_string(f.size);
			tmpSize.resize(FileSizeLen, ' ');
			listFileNames.push_back(tmpName + "|" + tmpSize + "|" + mbstr);

		} while (_findnext(hFile, &f) == 0);
		//Закрываем директорию
		_findclose(hFile);
	}
	return listFileNames;
}
std::vector<std::string> GetFileContent(std::string FilesName)
{
	std::vector<std::string> Content;
	std::ifstream inFile;
	char line[0XFF];
	inFile.open(FilesName);
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile.getline(line, 0XFF);
			Content.push_back(std::string(line)); 

		}
		inFile.close();
	}
	return Content;
}
std::vector<std::string> GetFileContent(std::string FilesName, int str_size)
{
	std::vector<std::string> Content;
	std::string tmpstr;

	std::ifstream inFile;
	char line[0XFF];
	inFile.open(FilesName);
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile.getline(line, 0XFF);
			tmpstr = std::string(line);
			tmpstr.resize(str_size, ' ');
			Content.push_back(tmpstr); 

		}
		inFile.close();
	}
	return Content;
}