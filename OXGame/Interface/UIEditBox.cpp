#include "stdh.h"
#include "..\Game Design\Game.h"
#include "UIManager.h"
#include "UIBase.h"
#include "UIEditBox.h"

UIEditBox::UIEditBox()
	: m_nEditWidth(0)
	, m_sText("")
	, m_sEditText("")
	, m_bFocus(false)
	, m_bReadOnly(false)
{

}

UIEditBox::~UIEditBox()
{
	Destroy();
}

void UIEditBox::Render()
{
	GameManager* pGameManager = GameManager::getSingleton();
	HANDLE pWndConsole = pGameManager->getConsoleHandle();

	if (!m_bFocus || m_bReadOnly)
	{
		short x = (short)GetRealX();
		short y = (short)GetRealY();
		SetConsoleCursorPosition(pWndConsole, { x, y });

		std::cout << m_sText.c_str();

		if(m_sEditText == "")
			std::cout << ": " << DublicateSymbol("_", m_nEditWidth);
		else
			std::cout << ": " << m_sEditText.c_str();
	}
	else
	{
		short x = GetRealX() + (short)m_sText.length() + 2;
		short y = (short)GetRealY();

		SetConsoleCursorPosition(pWndConsole, { x, y });
		if (m_sEditText == "")
		{
			std::cout << DublicateSymbol(" ", m_nEditWidth);
			SetConsoleCursorPosition(pWndConsole, { x, y });
		}
		
		char* text = new char[m_nEditWidth + 1];
		fgets(text, m_nEditWidth, stdin);
		m_sEditText = text == "\n" ? "" : text;
		delete[] text;

		system("cls");
		m_bFocus = false;
	}
}

bool UIEditBox::OnLeftButtonClick(int x, int y)
{
	UIManager* pManager = UIManager::getSingleton();

	if (m_bReadOnly)
		return true;

	if (!m_bFocus)
	{
		m_bFocus = true;
		Render();
	}

	return true;
}