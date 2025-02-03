#pragma once
#include <iostream>
#include <string>
#include "utils.h"
#include <vector>
#include <Windows.h> // библиотеки для работы с прерывания клавиатуры
#include <WinUser.h> // библиотеки для работы с прерывания клавиатуры

#define DefaultPanelLeft		(1)
#define DefaultPanelTop			(1 + DefaultTopMenuHeigh)
#define DefaultPanelWidth		(60)
#define DefaultPanelHeigh		(30)
#define DefaultMenuHeigh		(2)
#define DefaultTopMenuHeigh		(1)
#define DefaultCommandLineHeigh	(1)
#define DefaultButtonWidth		(10)
#define DefaultButtonHeigh		(1)
#define DefaultLabelWidth		(10)
#define DefaultLabelHeigh		(1)
#define DefaultTextBoxWidth		(10)
#define DefaultTextBoxHeigh		(1)


#define MaximumConsoleWidth	(DefaultPanelWidth * 2)
#define MaximumConsoleHeigh	(DefaultTopMenuHeigh + DefaultPanelHeigh + DefaultCommandLineHeigh + DefaultMenuHeigh )

// направление прокрутки панели
enum TScrollMove 	
{
	tsmLeft,
	tsmRight,
	tsmUp,
	tsmDown,
};

// тип панели
enum TPanelType
{
	tptBlankView = 1,
	tptFileListView,
	tptTextView,
	tptInfoView,
	tptMenu,
	tptButton,
	tptLabel,
	tptTextBox,
	tptRadioButton,
	tptCheckBox
};

// тип прилипания панели
enum TPanelDock
{
	tpdNone = 0,
	tpdLeft,
	tpdRight,
	tpdTop,
	tpdBottom,
	tpdMaximize,
	tpdDefault = tpdLeft,
};

enum TDialogResult
{
	tdrNone =0,
	tdrCancel ,
	tdrOK,
	tdrIgnore,
	tdrRetry,
	tdrAbort

};

#define DefaultBackGroundColor			color_dark_blue
#define DefaultTextColor				color_white
#define DefaultSelectedBackGroundColor	color_yellow
#define DefaultSelectedTextColor		color_dark_blue

//Для кнопки
#define DefaultButtonBackGroundColor			color_white 
#define DefaultButtonTextColor					color_black
#define DefaultButtonSelectedBackGroundColor	color_white
#define DefaultButtonSelectedTextColor			color_dark_red 

//Ярлык
#define DefaultLabelBackGroundColor				color_dark_green 
#define DefaultLabelTextColor					color_white
#define DefaultLabelSelectedBackGroundColor		color_dark_green
#define DefaultLabelSelectedTextColor			color_dark_blue 

//Текст
#define DefaultTextBoxBackGroundColor			color_light_gray  
#define DefaultTextBoxTextColor					color_black
#define DefaultTextBoxSelectedBackGroundColor	color_yellow
#define DefaultTextBoxSelectedTextColor			color_dark_red


// Абстрактный интерфейс графического объекта (панели)
class IPanelClass
{
public:
	IPanelClass()
	{
		PanelType = tptBlankView;
		PanelDock = tpdLeft;
		BackGroundColor = DefaultBackGroundColor;
		TextColor = DefaultTextColor;
		SelectedBackGroundColor = DefaultSelectedBackGroundColor;
		SelectedTextColor = DefaultSelectedTextColor;

		setPanelRect({ DefaultPanelLeft, DefaultPanelTop,
			DefaultPanelLeft + DefaultPanelWidth,
			DefaultPanelTop + DefaultPanelHeigh }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
		Header = " Blank "; // текст заголовка	
		Footer = " Blank "; // текст нижнего колонтитула		
		ScrollCoord = { 0,0 };
		Context.empty();
		DialogResult = tdrNone;
		Active = false;
		CanActive = true;
		BorderStyle = tbsDouble;
		setChanged(true);
	};
	virtual ~IPanelClass() {};

	virtual void Refresh() = 0;
	virtual void Draw() = 0;	
	virtual void SymbolPress(int Symbol) {};
	virtual void KeyPress(int vKey) {};	
	void setPanelType(TPanelType _PanelType)
	{
		PanelType = _PanelType;
		setChanged(true);
	}
	TPanelType getPanelType() const
	{
		return PanelType;
	}
	void setPanelDock(TPanelDock _PanelDock)
	{
		PanelDock = _PanelDock;
		setPanelRect({ DefaultPanelLeft + DefaultPanelWidth + 1, DefaultPanelTop,
			DefaultPanelLeft + 1 + DefaultPanelWidth * 2,
			DefaultPanelTop + DefaultPanelHeigh });
		setChanged(true);
	}
	void setBackGroundColor(int Value)
	{
		BackGroundColor = Value;
		setChanged(true);
	}
	void setTextColor(int Value)
	{
		TextColor = Value;
		setChanged(true);
	}
	void setSelectedBackGroundColor(int Value)
	{
		SelectedBackGroundColor = Value;
		setChanged(true);
	}
	void setSelectedTextColor(int Value)
	{
		SelectedTextColor = Value;
		setChanged(true);
	}
	void setPanelRect(SMALL_RECT Value)
	{
		PanelRect = Value;
		setChanged(true);
	}     //SHORT Left;	SHORT Top; SHORT Right; SHORT Bottom;
	void setPanelRect(SHORT Left, SHORT Top, SHORT Right, SHORT Bottom)
	{
		PanelRect = { Left,  Top,  Right,  Bottom };
		setChanged(true);
	}     //SHORT Left;	SHORT Top; SHORT Right; SHORT Bottom;
	static SMALL_RECT CreateRect(SHORT Left, SHORT Top, SHORT Right, SHORT Bottom)
	{
		SMALL_RECT tmpRect{ Left,  Top,  Right,  Bottom };
		return tmpRect;
	}
	virtual void Scroll(TScrollMove ScrollMove)
	{
		switch (ScrollMove)
		{
		case tsmLeft:
			if (ScrollCoord.X > ScrollLeftLimit) ScrollCoord.X--;
			break;
		case tsmRight:
			if (ScrollCoord.X < ScrollRightLimit) ScrollCoord.X++;
			break;
		case tsmUp:
			if (ScrollCoord.Y > ScrollUpLimit) ScrollCoord.Y--;
			break;
		case tsmDown:
			if (ScrollCoord.Y < ScrollDownLimit) ScrollCoord.Y++;
			break;
		default:
			return;
			break;
		}
		setChanged(true);
	};
	virtual void CursorScroll(TScrollMove ScrollMove)
	{
		switch (ScrollMove)
		{
		case tsmLeft:
			if (CursorCoord.X > ScrollLeftLimit) CursorCoord.X--;
			break;
		case tsmRight:
			if (CursorCoord.X < ScrollRightLimit) CursorCoord.X++;
			break;
		case tsmUp:
			if (CursorCoord.Y > CursorUpLimit) CursorCoord.Y--;
			else if (CursorCoord.Y + ScrollCoord.Y > ScrollUpLimit) Scroll(ScrollMove);
			break;
		case tsmDown:
			if (CursorCoord.Y < CursorDownLimit) CursorCoord.Y++;
			else if (CursorCoord.Y + ScrollCoord.Y <= ScrollDownLimit) Scroll(ScrollMove);
			break;
		default:
			return;
			break;
		}
		setChanged(true);
	};
	virtual void CheckChanges()
	{
		//Refresh();
		if (Changed)
		{
			Draw();
			Changed = false;
		}
	}
	void setHeader(std::string Value) // текст заголовка	
	{
		Header = Value;
		setChanged(true);
	}
	std::string getHeader() // текст заголовка	
	{
		return Header;
	}
	void setFooter(std::string Value) // текст нижнего колонтитула
	{
		Footer = Value;
		setChanged(true);
	}
	void setActive(bool Value) // Активность панели
	{
		Active = Value;
		setChanged(true);
	}
	bool getActive() const // Активность панели
	{
		return Active;
	}
	void setCanActive(bool Value) // Активность панели
	{
		CanActive = Value;
		setChanged(true);
	}
	bool getCanActive() const // Активность панели
	{
		return CanActive;
	}

	void setChanged(bool Value) // Активность панели
	{
		Changed = Value;
	}
	void setBorderStyle(TBorderStyle Value) // Активность панели
	{
		BorderStyle = Value;
		setChanged(true);
	}
	TBorderStyle getBorderStyle() const // Активность панели
	{
		return BorderStyle;
	}
	TDialogResult getDialogResult()
	{
		return DialogResult;
	};
	void setDialogResult(TDialogResult Value)
	{
		DialogResult = Value;
	};

	const std::vector<std::string> getContext() const
	{
		return Context;
	}

	void setContext(std::vector<std::string> Value) 
	{
		 Context= Value;
		 setChanged(true);
	}
protected:
	bool Changed;			// флаг изменено ли содержимое панели
	TPanelType PanelType;	// тип панели
	TPanelDock PanelDock;	// прилипание панели
	TBorderStyle BorderStyle; // тип рамки вокруг окна
	int BackGroundColor;	//
	int TextColor;			//
	int SelectedBackGroundColor;	//
	int SelectedTextColor;	//
	SMALL_RECT PanelRect;	// Left, Right, Top, Bottom
	std::string Header;		// текст заголовка	
	std::string Footer;		// текст нижнего колонтитула
	COORD ScrollCoord = { 0,0 };		// позиция окна прокрутки
	COORD CursorCoord = { 1,1 };		// позиция курсора
	std::vector<std::string> Context;	// содержимое панели
	bool Active;			// активная панель
	bool CanActive;
	SHORT ScrollLeftLimit = 0;
	SHORT ScrollRightLimit = 0;
	SHORT ScrollUpLimit = 0;
	SHORT ScrollDownLimit = 0;

	SHORT CursorLeftLimit = 2;
	SHORT CursorRightLimit = 2;
	SHORT CursorUpLimit = 2;
	SHORT CursorDownLimit = 2;
	TDialogResult DialogResult;

}; // IPanelClass



class PanelClass : public IPanelClass
{
public:
	PanelClass()
	{
		PanelType = tptBlankView;
		PanelDock = tpdLeft;
		BackGroundColor = DefaultBackGroundColor;
		TextColor = DefaultTextColor;
		SelectedBackGroundColor = DefaultSelectedBackGroundColor;
		SelectedTextColor = DefaultSelectedTextColor;

		setPanelRect({ DefaultPanelLeft, DefaultPanelTop,
			DefaultPanelLeft + DefaultPanelWidth,
			DefaultPanelTop + DefaultPanelHeigh }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
		Header = " Panel "; // текст заголовка	
		Footer = " Info "; // текст нижнего колонтитула
		Changed = true;
		ScrollCoord = { 0,0 };
		

		Active = false;
		setFileName(std::string("d:\\Help_FM.txt"));
		Refresh();
	}
	virtual ~PanelClass() {};

	virtual void Refresh() 
	{
		Context = GetFileContent(getFileName(), PanelRect.Right - PanelRect.Left - 2);

	};
	virtual void Scroll(TScrollMove ScrollMove) {};
	virtual void ShowHeader()
	{
		if (getActive())
		{
			std::cout << CSI << get_backgroundcolor_code((int)SelectedBackGroundColor) << ";"
				<< get_textcolor_code((int)SelectedTextColor) << "m";   // black background / blue text 94m
		}
		else
		{
			std::cout << CSI << get_backgroundcolor_code((int)BackGroundColor) << ";"
				<< get_textcolor_code((int)TextColor) << "m";   // black background / blue text 94m
		}
		std::cout << CSI << PanelRect.Top << ";" <<
			(PanelRect.Right + PanelRect.Left) / 2 - Header.size() / 2 << "H"; // Move to 0x0
		std::cout << Header;
	} // текст заголовка	

	virtual void ShowFooter()
	{		
		std::cout << CSI << PanelRect.Bottom << ";" <<
			(PanelRect.Right + PanelRect.Left) / 2 - Footer.size() / 2 << "H"; // Move to 0x0
		std::cout << Footer;
	}
	virtual void ShowCursor()
	{
		//std::cout << CSI << CursorCoord.Y << ";" << PanelRect.Left + 1 << "H"; // Move to 0x0
		//std::cout << "-->";
	}
	virtual void ShowContent(int Y)
	{
		if (Y + ScrollCoord.Y < Context.size())
		{
			std::cout << Context[Y + ScrollCoord.Y].c_str();
		}
		else
		{
			std::cout << CSI << PanelRect.Top + Y + 1 << ";" << PanelRect.Left + 1 << "H"; // Move to 0x0
			for (int i = 0; i < PanelRect.Right - PanelRect.Left - 2; i++)
			{
				std::cout << " ";
			}
		}
	}

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
					<< get_textcolor_code((int)TextColor ) << "m";   // black background / blue text 94m
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
	}
	void setFileName(std::string Value)
	{
		FileName = Value;
		setChanged(true);
	}
	std::string getFileName()
	{
		return FileName;
	}
protected:
	std::string FileName; 
};


