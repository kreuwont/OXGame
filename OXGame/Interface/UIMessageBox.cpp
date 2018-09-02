#include "stdh.h"
#include "..\Game Design\Game.h"
#include "UIManager.h"
#include "UIBase.h"
#include "UIText.h"
#include "UIButton.h"
#include "UIMessageBox.h"

UIMessageBox::UIMessageBox(int realX, int realY, int realWidth, int realHeigth, UIBase* pParent)
{
	setParent(pParent);
	SetRealPos(realX, realY);
	SetRealSize(realWidth, realHeigth);

	int centerX = realWidth / 2;
	int centerY = realHeigth / 2;
	m_nFixedX = GetRealX() + centerX;
	m_uiText.SetRealPos(m_nFixedX, GetRealY() + centerY - 1);
	//m_uiClose.setParent(this);
	m_uiClose.setText("X");
	m_uiClose.SetRealPos(GetRealX() + realWidth - 3, realY + 2);
	m_uiClose.SetRealSize(1, 1);
	m_uiClose.SetFunctionOnL(std::function<void()>([pParent, this]()
	{
		pParent->deleteChild(this);
		system("cls");
	}));
}

UIMessageBox::~UIMessageBox()
{
	Destroy();
}

void UIMessageBox::Render()
{
	GameManager* pGameManager = GameManager::getSingleton();
	HANDLE pWndConsole = pGameManager->getConsoleHandle();
	short x = (short)GetRealX();
	short y = (short)GetRealY();
	SetConsoleCursorPosition(pWndConsole, { x, y });

	for (int i = 0; i < GetHeight(); i++)
	{
		for (int j = 0; j < GetWidth(); j++)
		{
			if (!(i == 0 || i + 1 == GetHeight()) 
				&& (j == 0 || j + 1 == GetWidth()))
			{
				std::cout << "|";
				SetConsoleCursorPosition(pWndConsole, { (short)(x + GetWidth() - 1), y });
				std::cout << "|";
				break;
			}

			std::cout << "-";
		}

		y++;
		SetConsoleCursorPosition(pWndConsole, { x, y });
	}

	m_uiText.SetRealPosX(m_nFixedX - (m_uiText.getText().length() / 2));
	m_uiText.Render();
	m_uiClose.Render();
}

bool UIMessageBox::OnLeftButtonClick(int x, int y)
{
	if (m_uiClose.IsInside(x, y))
		return m_uiClose.OnLeftButtonClick(x, y);
	return true;
}