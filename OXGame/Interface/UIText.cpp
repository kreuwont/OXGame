#include "stdh.h"
#include "..\Game Design\Game.h"
#include "UIManager.h"
#include "UIBase.h"
#include "UIText.h"

UIText::UIText()
{

}

UIText::~UIText()
{
	Destroy();
}

void UIText::Render()
{
	GameManager* pGameManager = GameManager::getSingleton();
	HANDLE pWndConsole = pGameManager->getConsoleHandle();
	SetConsoleCursorPosition(pWndConsole, { (short)GetRealX(), (short)GetRealY() });

	std::cout << m_sText.c_str();
}