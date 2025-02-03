#define _CRT_SECURE_NO_WARNINGS // отключить предупреждение
// о несовместимости старых версий библиотек и функций


#include <iostream>
#include <stdlib.h>
#include "IPanel.h" 
#include "FileListView.h"
#include <Windows.h> // библиотеки для работы с прерывания клавиатуры
#include <WinUser.h> // библиотеки для работы с прерывания клавиатуры
#include "Menu.h"
#include <fstream>
#include <string>
#include "DialogBox.h"



#include <conio.h>
#include <ctype.h>




//namespace fs = std::filesystem;

using namespace std;

//unsigned long long int start_time = 0;// clock();

class MyAppClass
{
public:
	MyAppClass()
	{
		Panel1 = new FileListViewClass();//PanelClass();
		Panel2 = new FileListViewClass();
		Menu = new TMenuClass();	
		TopMenu = new TMenuClass(tpdTop);
		Panel2->setPanelDock(tpdRight);
		Panel1->setActive(true);
	};
	~MyAppClass()
	{
		if (Panel1 != nullptr) delete Panel1;
		if (Panel2 != nullptr) delete Panel2;
		if (Menu != nullptr) delete Menu;
		if (TopMenu != nullptr) delete TopMenu;
		if (DialogBox1 != nullptr) delete DialogBox1;

	};
	void Draw()
	{
		Panel1->CheckChanges();
		Panel2->CheckChanges();
		Menu->CheckChanges();
		TopMenu->CheckChanges();
		if (DialogBox1 != nullptr) DialogBox1->CheckChanges();
	};
	void ShowDialogBox(std::string _header)
	{
		if (DialogBox1 != nullptr) return;
		DialogBox1 = new MyDialogBoxClass(_header);
		DialogBox1->Draw();
	};
	void ShowMakeDirDialogBox(std::string _header)
	{
		if (DialogBox1 != nullptr) return;
		DialogBox1 = new MakeDirDialogBox(_header);
		DialogBox1->Draw();
	};
	void ShowCopyDialogBox(std::string _header)
	{
		if (DialogBox1 != nullptr) return;
		DialogBox1 = new CopyDialogBox(_header);
		DialogBox1->Draw();
	};
	void ShowRenameDialogBox(std::string _header)
	{
		if (DialogBox1 != nullptr) return;
		DialogBox1 = new RenameDialogBox(_header);
		DialogBox1->Draw();
	};

	void CloseDialogBox()
	{
		if (DialogBox1 != nullptr)
		{
			printXY(70, 1, to_string(DialogBox1->getDialogResult()).c_str(), color_magenta, color_black);
			delete DialogBox1;
			DialogBox1 = nullptr;
		}
		Panel1->setChanged(true);
		Panel2->setChanged(true);
		Menu->setChanged(true);
		TopMenu->setChanged(true);
	};
	void ToglePanel()
	{
		Panel1->setActive(!Panel1->getActive());
		Panel2->setActive(!Panel1->getActive());
	}
	void Scroll(TScrollMove ScrollMove)
	{
		if (Panel1->getActive()) Panel1->Scroll(ScrollMove);
		else Panel2->Scroll(ScrollMove);
	}
	void CursorScroll(TScrollMove ScrollMove)
	{
		if (Panel1->getActive()) Panel1->CursorScroll(ScrollMove);
		else Panel2->CursorScroll(ScrollMove);
	}
	void KeyPress(int vKey)
	{
		if (isDialogBoxOpen())
		{//если диалоговое окно открыто, по нажатия клавиш пробрасываем в него
			DialogBox1->KeyPress(vKey);
		}
		else
		{//если диалоговое окно не открыто, по нажатия клавиш пробрасываем в активную панель
			if (Panel1->getActive()) Panel1->KeyPress(vKey);
			else Panel2->KeyPress(vKey);
		}
	}

	void SymbolPress(int Symbol)
	{
		if (isDialogBoxOpen())
		{//если диалоговое окно открыто, по нажатия клавиш пробрасываем в него
			DialogBox1->SymbolPress(Symbol);
		}
		else
		{//если диалоговое окно не открыто, по нажатия клавиш пробрасываем в командную строку
			////!!!!
		}
	}
	
	bool isDialogBoxOpen() 
	{
		return DialogBox1 != nullptr;
	}
	bool isDialogBoxCanClose()
	{
		if (isDialogBoxOpen())
			return (DialogBox1->getDialogResult() != tdrNone);
		else false;
	}
	
private:
	IPanelClass* Panel1 = nullptr;	// левая панель
	IPanelClass* Panel2 = nullptr;	// правая панель
	IPanelClass* Menu = nullptr;	// Нижнее меню - вообще это скорее hint))) - подсказка по горячим клавишам
	IPanelClass* TopMenu = nullptr;	// Верхнее меню
	IPanelClass* CommandLine = nullptr;	// Командная строка
	IPanelClass* DialogBox1 = nullptr; // диалоговое окно - их будет много... копия, подтверждение удаления, перемещения и т.п.

};



using namespace std;

int main()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("mode 650");
	setcursor(0, 0); // убираем курсор из консоли

	//setlocale(LC_ALL, "rus");
	MyAppClass App;

	int ch;

	do
	{
		//if (TransparentDelay(&start_time, 10000));
		App.Draw();
		if (App.isDialogBoxOpen())
		{
			ch = _getch();

			if (ch == 224) { // if the first value is esc
				ch = _getch(); // skip the [
				switch (ch) { // the real value
				case 'H':
					// code for arrow up
					printXY(70, 1, "up", color_orange, color_blue);
					break;
				case 'P':
					// code for arrow down
					printXY(70, 1, "down", color_orange, color_blue);
					break;
				case 'M':
					// code for arrow right
					printXY(70, 1, "right", color_orange, color_blue);
					break;
				case 'K':
					// code for arrow left
					printXY(70, 1, "left", color_orange, color_blue);
					break;
				}
				
			}
			else App.SymbolPress(ch);
			
		}
		Sleep(100);
		/*if (GetAsyncKeyState(VK_ESCAPE) && GetAsyncKeyState(VK_SHIFT))
		{
			break;
		}*/
		if (App.isDialogBoxCanClose()) 
		{
			App.CloseDialogBox();
		}

		if (GetAsyncKeyState(VK_ESCAPE))
		{			
			App.CloseDialogBox();
		}
		if (GetAsyncKeyState(VK_F1))
		{
			MessageBox(NULL,  
				(LPCWSTR)L"This is File Manager.\n Navigation\n ->  - Right\n <-  - Left\n ^ - Up\n v - Down\n Tab - Switch Panels\n",
				(LPCWSTR)L"HELP",  
				MB_OK | MB_ICONINFORMATION);  
		}
		if (GetAsyncKeyState(VK_F2))
		{			
			//App.ShowDialogBox("RENAME"); 
			App.ShowRenameDialogBox("RENAME");
			//MessageBox(NULL,
			//	(LPCWSTR)L" Which file do you want to rename?",
			//	(LPCWSTR)L"RENAME",
			//	MB_OK | MB_ICONQUESTION);
		}
		if (GetAsyncKeyState(VK_F3))
		{
			MessageBox(NULL,
				(LPCWSTR)L" View file ",
				(LPCWSTR)L"VIEW",
				MB_OK | MB_ICONINFORMATION); 
		}
		if (GetAsyncKeyState(VK_F4))
		{
			MessageBox(NULL, 
				(LPCWSTR)L" Create new file ",
				(LPCWSTR)L"EDIT",
				MB_OK | MB_ICONINFORMATION); 
		}
		if (GetAsyncKeyState(VK_F5)) 
		{
			//App.ShowDialogBox("COPY");
			App.ShowCopyDialogBox("COPY");
			
		}
		if (GetAsyncKeyState(VK_F6)) 
		{
			App.ShowDialogBox("REMOVE");
			//MessageBox(NULL, 
			//	(LPCWSTR)L" Which file do you want to remove? ",
			//	(LPCWSTR)L"REMOVE",
			//	MB_OK | MB_ICONQUESTION); 
		}
		if (GetAsyncKeyState(VK_F7))
		{
			/*MessageBox(NULL,
				(LPCWSTR)L" ERROR ",
				(LPCWSTR)L"XXXXX",
				MB_OK | MB_ICONERROR);*/
			App.ShowMakeDirDialogBox("CREATE");
		}
		if (GetAsyncKeyState(VK_F8)) 
		{ 
			App.ShowDialogBox("DELETE");
			//MessageBox(NULL,
			//	(LPCWSTR)L" Do you want delete all? ",
			//	(LPCWSTR)L"DELETE",
			//	MB_OK | MB_ICONQUESTION); 
		}
		if (GetAsyncKeyState(VK_F9))
		{
			MessageBox(NULL,
				(LPCWSTR)L" ERROR ",
				(LPCWSTR)L"XXXXX",
				MB_OK | MB_ICONERROR);
		}
		if (GetAsyncKeyState(VK_F10)) // F10 Exit
		{
			system("cls");
			break;
			//App.ShowDialogBox("DELETE");
			/*int message = MessageBox(NULL,
				(LPCWSTR)L" Do you want to exit?",
				(LPCWSTR)L"EXIT",
				MB_YESNO | MB_ICONQUESTION);
			
			switch (message)
			{
			case IDYES:
				MessageBox(NULL, (LPCWSTR)L" You press yes", (LPCWSTR)L"Exit", MB_OK | MB_ICONQUESTION);
				break;
			case IDNO:
				MessageBox(NULL, (LPCWSTR)L" You press no", (LPCWSTR)L"Exit", MB_OK | MB_ICONQUESTION);
				break;
			default:
				break;
			}*/
			//break;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{

		}
		if (GetAsyncKeyState(VK_TAB))
		{
			if (App.isDialogBoxOpen())
			{
				App.KeyPress(VK_TAB);
			}
			else App.ToglePanel();
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{

		}
		if (GetAsyncKeyState(VK_UP))
		{
			if (!App.isDialogBoxOpen())
			{
				App.CursorScroll(tsmUp);
			}
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (!App.isDialogBoxOpen())
			{
				App.CursorScroll(tsmDown);
			}
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			//if (App.isDialogBoxOpen())
			//{
			//	App.KeyPress(VK_RETURN);
			//}
			/*else */App.KeyPress(VK_RETURN);
		}
	} while (1);
	return 0;
}


