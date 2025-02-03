#pragma once
#include"IPanel.h"
#include "Control.h" 
#include<iostream>
#include<vector>


class IDialogBoxData
{
public:
	IDialogBoxData();
	~IDialogBoxData();

private:

};



class MyDialogBoxClass: public PanelClass
{
public:	
	MyDialogBoxClass(std::string _Header = "Dialog box")
	{
		BorderStyle = tbsDouble;
		PanelType = tptBlankView;
		PanelDock = tpdLeft;
		BackGroundColor = color_dark_green;
		TextColor = color_white;
		SelectedBackGroundColor = color_dark_green;
		SelectedTextColor = color_white;

		setPanelRect({ 10, 5,
			10 + 100,
			5 + 20 }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
		Header = " " + _Header  + " "; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула
		Changed = true;
		ScrollCoord = { 0,0 };
		

		/*Controls.push_back(new TButton( CreateRect( PanelRect.Left + 40, PanelRect.Bottom - 2, PanelRect.Left + 50, PanelRect.Bottom - 1 ), " OK "));
		Controls.push_back(new TButton(CreateRect(PanelRect.Left + 55, PanelRect.Bottom - 2, PanelRect.Left + 65, PanelRect.Bottom - 1), " Cancel "));
		Controls.push_back(new TLabel(CreateRect(PanelRect.Left + 5, PanelRect.Top + 2, PanelRect.Left + 25, PanelRect.Top + 3), "Copy from: "));
		Controls.push_back(new TTextBox(CreateRect(PanelRect.Left + 5, PanelRect.Top + 4, PanelRect.Left + 55, PanelRect.Top + 6), ""));
		Controls.push_back(new TLabel(CreateRect(PanelRect.Left + 5, PanelRect.Top + 6, PanelRect.Left + 25, PanelRect.Top + 7), "Copy to: "));
		Controls.push_back(new TTextBox(CreateRect(PanelRect.Left + 5, PanelRect.Top + 8, PanelRect.Left + 55, PanelRect.Top + 10), ""));*/

		Active = false;
		setFileName(std::string(""));
		Context.clear();
		Refresh();
	};
	~MyDialogBoxClass()
	{
		auto it = Controls.begin();
		for (; it != Controls.end(); it++)
		{
			if (*it != nullptr) delete *it;
			*it = nullptr;
		}
		Controls.clear();
	};
	virtual void Refresh() {};
	virtual void Draw()
	{
		setcursor(0, 0); // убираем курсор из консоли
		std::cout << ESC "(0";        // Enter Line drawing mode
		//if (getActive())
		//{
		//	std::cout << CSI << (int)SelectedBackGroundColor << ";"
		//		<< (int)SelectedTextColor << "m";   // black background / blue text 94m
		//}
		//else
		{
			std::cout << CSI << get_backgroundcolor_code((int)BackGroundColor) << ";"
				<< get_textcolor_code((int)TextColor) << "m";   // black background / blue text 94m
		}
		std::cout << CSI << PanelRect.Top << ";" << PanelRect.Left << "H"; // Move to 0x0
		// Верхняя рамка
		std::cout << DoubleBorder_LeftTopCorner;
		for (int i = 0; i < PanelRect.Right - PanelRect.Left - 2; i++)
			std::cout << DoubleBorder_HorizontalLine;
		std::cout << DoubleBorder_RightTopCorner;
		// Вертикальные границы
		for (size_t y = 0; y < PanelRect.Bottom - PanelRect.Top - 1; y++)
		{
			std::cout << CSI << PanelRect.Top + y + 1 << ";" << PanelRect.Left << "H"; // Move to 0x0
			std::cout << DoubleBorder_VerticalLine;

			std::cout << ESC "(B";       // exit line drawing mode
			ShowContent(y);

			std::cout << ESC "(0";        // Enter Line drawing mode
			//if (getActive())
			//{
			//	std::cout << CSI << (int)SelectedBackGroundColor << ";"
			//		<< (int)SelectedTextColor << "m";   // black background / blue text 94m
			//}
			//else
			{
				std::cout << CSI << get_backgroundcolor_code((int)BackGroundColor) << ";"
					<< get_textcolor_code((int)TextColor) << "m";   // black background / blue text 94m
			}
			std::cout << CSI << PanelRect.Top + y + 1 << ";" << PanelRect.Right - 1 << "H"; // Move to 0x0
			std::cout << DoubleBorder_VerticalLine; //"Vertical Bar"
		}

		// нижний колонтитул
		std::cout << CSI << PanelRect.Bottom << ";" << PanelRect.Left << "H"; // Move to 0x0
		std::cout << DoubleBorder_LeftBottomCorner;
		for (int i = 0; i < PanelRect.Right - PanelRect.Left - 2; i++)
			std::cout << DoubleBorder_HorizontalLine;
		std::cout << DoubleBorder_RightBottomCorner;

		std::cout << ESC "(B";       // exit line drawing mode		
		// Заголовок
		ShowHeader();
		// нижний колонтитул
		ShowFooter();
		std::cout << ESC "(0";        // Enter Line drawing mode

		std::cout << CSI "0m";       // restore colors 
		std::cout << ESC "(B";       // exit line drawing mode
		ShowCursor();
		ShowControls(); //  Рисуем элементы управления
	}
	virtual void ShowControls()  
	{
		auto it = Controls.begin();
		for (; it != Controls.end(); it++)
		{
			if (*it != nullptr) (*it)->Draw();			
		}
	};
	virtual void SymbolPress(int Symbol)
	{
		if ((Symbol == '\r') || (Symbol == '\n'))
		{
			setDialogResult(tdrOK);
			return;
		}
		
		if ((Symbol == 0) || (Symbol == 9) || (Symbol == '\r') || (Symbol == '\n')) return;
		auto it = Controls.begin();
		for (; it != Controls.end(); it++)
		{
			if (*it != nullptr)
			{
				if ((*it)->getActive())
				{
					if ((*it)->getPanelType() == tptTextBox)
					{
						auto tmp = (*it)->getContext();
						tmp[0].push_back((char)Symbol);
						(*it)->setContext(tmp);
						(*it)->Draw();
					}
				}
			}
		}
	}
	virtual void KeyPress(int vKey)
	{
		if (vKey == VK_TAB)
		{
			bool hasCanActiveControls = false;
			auto it = Controls.begin(); // проверим что есть элементы, которые могут быть активными (кроме label)
			for (; it != Controls.end(); it++)
			{
				if (*it != nullptr)
				{
					if ((*it)->getActive())
					{
						hasCanActiveControls = true;
						break;
					}
				}
			}
			if (!hasCanActiveControls) return;
			it = Controls.begin();
			for (; it != Controls.end(); it++)
			{
				if (*it != nullptr)
				{
					if ((*it)->getActive())
					{
						//printXY(1, 1, (*it)->getContext()[0].c_str(), color_red, color_black);
						(*it)->setActive(false);
						do
						{
							if (++it == Controls.end()) it = Controls.begin();
						} while (!(*it)->getCanActive());
						//if (++it == Controls.end()) it = Controls.begin();						
						(*it)->setActive(true);
						setChanged(true);
						break;
					}
				}

			}
		}

		if (vKey == VK_RETURN)
		{
			auto it = Controls.begin(); 
			for (; it != Controls.end(); it++)
			{
				if (*it != nullptr)
				{
					if ((*it)->getActive())
					{
						if ((*it)->getDialogResult() != tdrNone)
						{
							setDialogResult((*it)->getDialogResult());
						}
					}
				}
			}
		}
	
		
	};

protected: 
	
	std::vector<IPanelClass*> Controls;
};//MyDialogBoxClass


class MakeDirDialogBox : public  MyDialogBoxClass
{
public:
	MakeDirDialogBox(std::string _Header = "MakeDirDialogbox")
	{
		BorderStyle = tbsDouble;
		PanelType = tptBlankView;
		PanelDock = tpdLeft;
		BackGroundColor = color_dark_green;
		TextColor = color_white;
		SelectedBackGroundColor = color_dark_green;
		SelectedTextColor = color_white;

		setPanelRect({ 10, 5,
			10 + 100,
			5 + 20 }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
		Header = " " + _Header + " "; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула
		Changed = true;
		ScrollCoord = { 0,0 };


		Controls.push_back(new TButton(CreateRect(PanelRect.Left + 40, PanelRect.Bottom - 2, PanelRect.Left + 50, PanelRect.Bottom - 1), " OK ", true, tdrOK));
		Controls.push_back(new TButton(CreateRect(PanelRect.Left + 55, PanelRect.Bottom - 2, PanelRect.Left + 65, PanelRect.Bottom - 1), " Cancel "));
		Controls.push_back(new TLabel(CreateRect(PanelRect.Left + 5, PanelRect.Top + 2, PanelRect.Left + 25, PanelRect.Top + 3), "Make dir: "));
		Controls.push_back(new TTextBox(CreateRect(PanelRect.Left + 5, PanelRect.Top + 4, PanelRect.Left + 55, PanelRect.Top + 6), ""));
		Active = false;
		setFileName(std::string(""));
		Context.clear();
		Refresh();
	};
	~MakeDirDialogBox() {};

private:

}; //MakeDirDialogBox


class CopyDialogBox : public  MyDialogBoxClass
{
public:
	CopyDialogBox(std::string _Header = "CopyDialogbox")
	{
		BorderStyle = tbsDouble;
		PanelType = tptBlankView;
		PanelDock = tpdLeft;
		BackGroundColor = color_dark_green;
		TextColor = color_white;
		SelectedBackGroundColor = color_dark_green;
		SelectedTextColor = color_white;

		setPanelRect({ 10, 5,
			10 + 100,
			5 + 20 }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
		Header = " " + _Header + " "; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула
		Changed = true;
		ScrollCoord = { 0,0 };


		Controls.push_back(new TButton(CreateRect(PanelRect.Left + 40, PanelRect.Bottom - 2, PanelRect.Left + 50, PanelRect.Bottom - 1), " OK ", true, tdrOK));
		Controls.push_back(new TButton(CreateRect(PanelRect.Left + 55, PanelRect.Bottom - 2, PanelRect.Left + 65, PanelRect.Bottom - 1), " Cancel "));
		Controls.push_back(new TLabel(CreateRect(PanelRect.Left + 5, PanelRect.Top + 2, PanelRect.Left + 25, PanelRect.Top + 3), "Copy from: "));
		Controls.push_back(new TTextBox(CreateRect(PanelRect.Left + 5, PanelRect.Top + 4, PanelRect.Left + 55, PanelRect.Top + 6), ""));
		Controls.push_back(new TLabel(CreateRect(PanelRect.Left + 5, PanelRect.Top + 6, PanelRect.Left + 25, PanelRect.Top + 7), "Copy to: "));
		Controls.push_back(new TTextBox(CreateRect(PanelRect.Left + 5, PanelRect.Top + 8, PanelRect.Left + 55, PanelRect.Top + 10), ""));

		Active = false;
		setFileName(std::string(""));
		Context.clear();
		Refresh();
	};
	~CopyDialogBox() {};

private:

};


class RenameDialogBox : public  MyDialogBoxClass
{
public:
	RenameDialogBox(std::string _Header = "RenameDialogbox")
	{
		BorderStyle = tbsDouble;
		PanelType = tptBlankView;
		PanelDock = tpdLeft;
		BackGroundColor = color_dark_green;
		TextColor = color_white;
		SelectedBackGroundColor = color_dark_green;
		SelectedTextColor = color_white;

		setPanelRect({ 10, 5,
			10 + 100,
			5 + 20 }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
		Header = " " + _Header + " "; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула
		Changed = true;
		ScrollCoord = { 0,0 };


		Controls.push_back(new TButton(CreateRect(PanelRect.Left + 40, PanelRect.Bottom - 2, PanelRect.Left + 50, PanelRect.Bottom - 1), " OK ", true, tdrOK));
		Controls.push_back(new TButton(CreateRect(PanelRect.Left + 55, PanelRect.Bottom - 2, PanelRect.Left + 65, PanelRect.Bottom - 1), " Cancel "));
		Controls.push_back(new TLabel(CreateRect(PanelRect.Left + 5, PanelRect.Top + 2, PanelRect.Left + 25, PanelRect.Top + 3), "Rename file : "));
		Controls.push_back(new TTextBox(CreateRect(PanelRect.Left + 5, PanelRect.Top + 4, PanelRect.Left + 55, PanelRect.Top + 6), ""));
		Controls.push_back(new TLabel(CreateRect(PanelRect.Left + 5, PanelRect.Top + 6, PanelRect.Left + 25, PanelRect.Top + 7), "Rename to: "));
		Controls.push_back(new TTextBox(CreateRect(PanelRect.Left + 5, PanelRect.Top + 8, PanelRect.Left + 55, PanelRect.Top + 10), ""));

		Active = false;
		setFileName(std::string(""));
		Context.clear();
		Refresh();
	};
	~RenameDialogBox() {}; 

private:

};
