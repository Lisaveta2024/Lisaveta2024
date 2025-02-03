#pragma once
//ѕодключение библиотек
#include "IPanel.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <io.h>
#include <regex>

//ќписание класса
class FileListViewClass : public PanelClass
{
public:
	FileListViewClass() : PanelClass()
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
		//Header = " Panel "; // текст заголовка	
		//Footer = " Info "; // текст нижнего колонтитула
		Changed = true;
		FilePath = "c:";
		FileMask = "*.*";
		CursorLeftLimit = 2;
		CursorRightLimit = PanelRect.Right - PanelRect.Left - 2;
		CursorUpLimit = 3;
		CursorDownLimit = PanelRect.Bottom - PanelRect.Top;
		CursorCoord.Y = CursorUpLimit;
		CursorCoord.X = CursorLeftLimit;
		Refresh();
	};
	virtual ~FileListViewClass() {};

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
		Footer = Context[CursorCoord.Y + ScrollCoord.Y - 3];
		Footer.resize(FileNameLen);
		Footer = " " + std::regex_replace(Footer, std::regex("^ +| +$|( ) +"), "$1") + " ";
		setChanged(true);
	};

	virtual void KeyPress(int vKey)
	{
		switch (vKey)
		{
		case VK_RETURN:	
		{

			std::string tmp = Context[CursorCoord.Y + ScrollCoord.Y - 3];
			if (std::string::npos != tmp.find(DirectoryStr))
			{// это директори€, можем в нее переходить
				tmp.resize(FileNameLen);
				tmp = std::regex_replace(tmp, std::regex("^ +| +$|( ) +"), "$1");
				if (tmp == "..")
				{
					tmp = getFilePath();
					int index = tmp.find_last_of("\\", -1);
					tmp.resize(index);
					setFilePath(tmp);
				}
				else setFilePath(getFilePath() + "\\" + tmp);
				//std::cout << CSI << PanelRect.Bottom + 5 << ";" << PanelRect.Left << "H";
				//std::cout << getFilePath();
				CursorCoord.Y = CursorUpLimit;
				CursorCoord.X = CursorLeftLimit;
			}
		}
			break;
		default:
			break;
		}
	};

	virtual void ShowContent(int Y)
	{
		if (Y == 0)
		{
			std::cout << "        Name            |     Size    |   Date   |  Time  ";
		}
		else if (Y + ScrollCoord.Y <= Context.size())
		{
			if ((CursorCoord.Y + ScrollCoord.Y - 2) == (Y + ScrollCoord.Y))
			{
				std::cout << CSI << get_backgroundcolor_code((int)SelectedBackGroundColor) << ";"
					<< get_textcolor_code((int)SelectedTextColor) << "m";   // black background / blue text 94m
			}
			std::cout << Context[Y + ScrollCoord.Y - 1];
			//std::cout << CSI << (int)SelectedBackGroundColor << ";"
			//	<< (int)SelectedTextColor << "m";   // black background / blue text 94m
		}
		else
		{
			std::cout << CSI << PanelRect.Top + Y + 1 << ";" << PanelRect.Left + 1	<< "H"; // Move to 0x0
			for (int i = 0; i < PanelRect.Right - PanelRect.Left - 2; i++)
			{
				std::cout << " ";
			}
		}
	}

	virtual void Refresh()
	{
		Context = GetFilesListInDirectory(FilePath, FileMask);
		Header = " " + FilePath + "\\" + FileMask + " ";
		Footer = " [Selected file] ";
		ScrollDownLimit = Context.size();
		CursorLeftLimit = 2;
		CursorRightLimit = PanelRect.Right - PanelRect.Left - 2;
		CursorUpLimit = 3;
		CursorDownLimit = PanelRect.Bottom - PanelRect.Top;
		if (Context.size() < CursorDownLimit) CursorDownLimit = Context.size() + CursorUpLimit-1;
	};
	void setFilePath(std::string Value)
	{
		FilePath = Value;
		setChanged(true);
		Refresh();
	}
	void setFileMask(std::string Value)
	{
		FileMask = Value;
		setChanged(true);
	}
	std::string getFilePath()
	{
		return FilePath;
	}
	std::string getFileMask()
	{
		return FileMask;
	}
private:

	std::string FilePath;
	std::string FileMask;
};
