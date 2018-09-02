#include "stdh.h"
#include "..\Game Design\Game.h"
#include "UIManager.h"
#include "UIBase.h"
#include "UICheckBox.h"

UICheckBox::UICheckBox()
	: m_bCheck(false)
{

}

UICheckBox::~UICheckBox()
{
	Destroy();
}

void UICheckBox::Render()
{
	GameManager* pGameManager = GameManager::getSingleton();
	HANDLE pWndConsole = pGameManager->getConsoleHandle();
	short x = (short)GetRealX();
	short y = (short)GetRealY();
	SetConsoleCursorPosition(pWndConsole, { (short)GetRealX(), (short)GetRealY() });

	std::cout << m_sText.c_str();
	if (m_bCheck)
		std::cout << ": v";
	else
		std::cout << ": x";
}

bool UICheckBox::OnLeftButtonClick(int x, int y)
{
	m_bCheck = !m_bCheck;
	return true;
}