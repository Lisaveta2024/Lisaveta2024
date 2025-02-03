#pragma once
#include "IPanel.h"

class TButton : public IPanelClass
{
public:
	TButton()
	{
		PanelType = tptButton;
		PanelDock = tpdNone;
		BackGroundColor = DefaultButtonBackGroundColor;
		TextColor = DefaultButtonTextColor;
		SelectedBackGroundColor = DefaultButtonSelectedBackGroundColor;
		SelectedTextColor = DefaultButtonSelectedTextColor;

		setPanelRect({ 1, 1,
			1 + DefaultButtonWidth,
			1 + DefaultButtonHeigh }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
		Header = ""; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула		
		ScrollCoord = { 0,0 };
		Context.empty(); 
		Context.push_back(" Button ");
		Context[0].resize(PanelRect.Right - PanelRect.Left);
		Active = false;
		BorderStyle = tbsNone; 
		setChanged(true);
	};
	TButton(const SMALL_RECT panelrect, std::string name = " Button ", bool selected = false, TDialogResult tdialogresult = tdrCancel,
		int backgroundcolor = DefaultButtonBackGroundColor,int textcolor = DefaultButtonTextColor,
		int selectedbackgroundcolor = DefaultButtonSelectedBackGroundColor,
		int selectedtextcolor = DefaultButtonSelectedTextColor)
	{
		PanelType = tptButton;
		PanelDock = tpdNone;
		BackGroundColor = backgroundcolor ;
		TextColor = textcolor;
		SelectedBackGroundColor = selectedbackgroundcolor;
		SelectedTextColor = selectedtextcolor;
		setPanelRect(panelrect);		
		Header = ""; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула		
		ScrollCoord = { 0,0 };
		Context.empty();
		Context.push_back(name);
		Context[0].resize(PanelRect.Right - PanelRect.Left);
		Active = selected;
		BorderStyle = tbsNone;
		setDialogResult(tdialogresult);
		setChanged(true);
	};
	virtual ~TButton() {};
	virtual void KeyPress(int vKey)
	{
		switch (vKey)
		{
		case VK_RETURN:
		{

			
		}
		case VK_TAB:
		{


		}
		break;
		default:
			break;
		}
	};
	virtual void Draw()
	{
		if(Active) printXY(PanelRect.Left, PanelRect.Top, Context[0].c_str(), SelectedBackGroundColor, SelectedTextColor);
		else printXY(PanelRect.Left, PanelRect.Top, Context[0].c_str(), BackGroundColor, TextColor); 
		
	}

	virtual void Refresh() {};
private:

};


class TLabel : public IPanelClass
{
public:
	TLabel()
	{
		PanelType = tptLabel;
		PanelDock = tpdNone;
		BackGroundColor = DefaultLabelBackGroundColor;
		TextColor = DefaultLabelTextColor;
		SelectedBackGroundColor = DefaultLabelSelectedBackGroundColor;
		SelectedTextColor = DefaultLabelSelectedTextColor;

		setPanelRect({ 1, 1,
			1 + DefaultLabelWidth,
			1 + DefaultLabelHeigh }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom;
		Header = ""; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула		
		ScrollCoord = { 0,0 };
		Context.empty();
		Context.push_back(" Label ");
		Context[0].resize(PanelRect.Right - PanelRect.Left);
		Active = false;
		BorderStyle = tbsNone;
		setChanged(true);
	};
	TLabel(const SMALL_RECT panelrect, std::string name = "Label", bool selected = false,
		int backgroundcolor = DefaultLabelBackGroundColor, int textcolor = DefaultLabelTextColor,
		int selectedbackgroundcolor = DefaultLabelSelectedBackGroundColor,
		int selectedtextcolor = DefaultLabelSelectedTextColor)
	{
		PanelType = tptLabel;
		PanelDock = tpdNone;
		BackGroundColor = backgroundcolor;
		TextColor = textcolor;
		SelectedBackGroundColor = selectedbackgroundcolor;
		SelectedTextColor = selectedtextcolor;
		setPanelRect(panelrect);
		Header = ""; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула		
		ScrollCoord = { 0,0 };
		Context.empty();
		Context.push_back(name);
		Context[0].resize(PanelRect.Right - PanelRect.Left);
		Active = selected;
		CanActive = false;
		BorderStyle = tbsNone;
		setChanged(true);
	};
	virtual ~TLabel() {};
	virtual void KeyPress(int vKey)
	{
		switch (vKey)
		{
		case VK_RETURN:
		{


		}
		case VK_TAB:
		{


		}
		break;
		default:
			break;
		}
	};
	virtual void Draw()
	{
		if (Active) printXY(PanelRect.Left, PanelRect.Top, Context[0].c_str(), SelectedBackGroundColor, SelectedTextColor);
		else printXY(PanelRect.Left, PanelRect.Top, Context[0].c_str(), BackGroundColor, TextColor);

	}

	virtual void Refresh() {};
private:

};


class TTextBox : public IPanelClass
{
public:
	TTextBox()
	{
		PanelType = tptTextBox;
		PanelDock = tpdNone;
		BackGroundColor = DefaultTextBoxBackGroundColor;
		TextColor = DefaultTextBoxTextColor;
		SelectedBackGroundColor = DefaultTextBoxSelectedBackGroundColor;
		SelectedTextColor = DefaultTextBoxSelectedTextColor;

		setPanelRect({ 1, 1,
			1 + DefaultTextBoxWidth, 
			1 + DefaultTextBoxHeigh }); //SHORT Left; SHORT Top; SHORT Right; SHORT Bottom; 
		Header = ""; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула		
		ScrollCoord = { 0,0 };
		Context.empty();
		Context.push_back(" _____________________________________________ ");
		//Context[0].resize(PanelRect.Right - PanelRect.Left);
		Active = false;
		BorderStyle = tbsNone;
		setChanged(true);
	};
	TTextBox(const SMALL_RECT panelrect, std::string name = "FileName: ", bool selected = false,
		int backgroundcolor = DefaultTextBoxBackGroundColor, int textcolor = DefaultTextBoxTextColor,
		int selectedbackgroundcolor = DefaultTextBoxSelectedBackGroundColor,
		int selectedtextcolor = DefaultTextBoxSelectedTextColor)
	{
		PanelType = tptTextBox;
		PanelDock = tpdNone;
		BackGroundColor = backgroundcolor;
		TextColor = textcolor;
		SelectedBackGroundColor = selectedbackgroundcolor;
		SelectedTextColor = selectedtextcolor;
		setPanelRect(panelrect);
		Header = ""; // текст заголовка	
		Footer = ""; // текст нижнего колонтитула		
		ScrollCoord = { 0,0 };
		Context.empty();
		Context.push_back(name);
		//Context[0].resize(PanelRect.Right - PanelRect.Left);
		Active = selected;
		BorderStyle = tbsNone;
		setChanged(true);
	};
	virtual ~TTextBox() {};
	virtual void KeyPress(int vKey)
	{
		switch (vKey)
		{
		case VK_RETURN:
		{


		}
		case VK_TAB:
		{


		}
		break;
		default:
			break;
		}
	};
	virtual void Draw()
	{
		if (Active)
		{
			setcursor(true, 1);
			for (size_t i = 0; i < PanelRect.Right - PanelRect.Left; i++)			
				printXY(PanelRect.Left + i, PanelRect.Top, " ", SelectedBackGroundColor, SelectedTextColor);
			
			printXY(PanelRect.Left, PanelRect.Top, Context[0].c_str(), SelectedBackGroundColor, SelectedTextColor);			
		}
		else
		{
			for (size_t i = 0; i < PanelRect.Right - PanelRect.Left; i++)
				printXY(PanelRect.Left + i, PanelRect.Top, " ", BackGroundColor, SelectedTextColor);
			printXY(PanelRect.Left, PanelRect.Top, Context[0].c_str(), BackGroundColor, TextColor);
		}
				




	}

	virtual void Refresh() {};
private:
	
};
