#include "stdh.h"
#include "..\Game Design\Game.h"
#include "UIManager.h"
#include "UIBase.h"
#include "UIButton.h"

UIButton::UIButton()
{

}

UIButton::~UIButton()
{
	Destroy();
}

void UIButton::Render()
{
	GameManager* pGameManager = GameManager::getSingleton();
	HANDLE pWndConsole = pGameManager->getConsoleHandle();

	short y = GetRealY();
	SetConsoleCursorPosition(pWndConsole, { (short)GetRealX(), y });
	int braceCount = GetWidth();
	int spaceCount = (braceCount / 2) - (getText().length() / 2);

	char* braceChars = DublicateSymbol("-", braceCount);
	char* spaceChars = DublicateSymbol(" ", spaceCount);
	std::cout << "|" << braceChars << "|" << std::endl;
	SetConsoleCursorPosition(pWndConsole, { (short)GetRealX(), ++y });
	std::cout << "|" << spaceChars << m_sText.c_str() << spaceChars << "|" << std::endl;
	SetConsoleCursorPosition(pWndConsole, { (short)GetRealX(), ++y });
	std::cout << "|" << braceChars << "|" << std::endl;

	delete[] braceChars;
	delete[] spaceChars;
}

int j = 0;

bool UIButton::OnLeftButtonClick(int x, int y)
{
	return UIBase::OnLeftButtonClick(x, y);
}