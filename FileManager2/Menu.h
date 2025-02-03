#pragma once
#include"IPanel.h"
#include <iostream>

class TMenuClass :public IPanelClass
{
public:
	TMenuClass(TPanelDock panel_dock = tpdBottom) :IPanelClass()
	{
		setPanelDock(panel_dock);
		switch (PanelDock)
		{
		case tpdNone:
			break;
		case tpdLeft:
			break;
		case tpdRight:
			break;
		case tpdTop:			
			setPanelRect({ DefaultPanelLeft, 1,
			MaximumConsoleWidth, MaximumConsoleHeigh }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
			break;
		case tpdBottom:
			setPanelRect({ DefaultPanelLeft, MaximumConsoleHeigh,
			MaximumConsoleWidth, 1 + DefaultTopMenuHeigh }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
			break;
		case tpdMaximize:
			break;
		
		default:
			break;
		}
		
		Changed = true;
	};
	~TMenuClass() {};
	virtual void Refresh() {};
	virtual void Scroll() {};
	virtual void Draw()
	{
		switch (PanelDock)
		{
		case tpdNone:
			break;
		case tpdLeft:
			break;
		case tpdRight:
			break;
		case tpdTop:
			printXY(PanelRect.Left, PanelRect.Top, "  Left    Files    Commands    Options    Right  ", color_cyan, color_black);
			break;
		case tpdBottom:
			printXY(PanelRect.Left, PanelRect.Top, "", 1, 1);
			printf("\t");
			printf("\033[3;47;35mF1 Help\033[0m  ");
			printf("\033[3;47;35mF2 Rename\033[0m  ");
			printf("\033[3;47;35mF3 View\033[0m  ");
			printf("\033[3;47;35mF4 Edit\033[0m  ");
			printf("\033[3;47;35mF5 Copy\033[0m  ");
			printf("\033[3;47;35mF6 Remove\033[0m  ");
			printf("\033[3;47;35mF7 Create\033[0m  ");
			printf("\033[3;47;35mF8 Delete\033[0m  ");
			printf("\033[3;47;35mF9 XXXXX\033[0m  ");
			printf("\033[3;47;35mF10 Exit\033[0m  ");
			break;
		case tpdMaximize:
			break;

		default:
			break;
		}

		setChanged(false);
	};
private:

};