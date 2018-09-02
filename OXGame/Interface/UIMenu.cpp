#include "stdh.h"
#include <functional>
#include "UIManager.h"
#include "UIMenu.h"
#include "UIRoomSettings.h"

bool bRender = true;

UIMenu::UIMenu()
{

}

UIMenu::~UIMenu()
{
	Destroy();
}

void UIMenu::Create(int nX, int nY, int nWidth, int nHeight)
{
	UIWindow::Create(nX, nY, nWidth, nHeight);
	setParent(NULL);
	RelocateToCenterLine();

	std::string text = "Игровое меню";
	int x = GetCenterWindowX() - text.length() / 2;
	m_uiText.SetRealPos(x, 1);
	m_uiText.SetSize(text.length() * 10, 0);
	m_uiText.setText(text);
	m_uiText.setParent(this);

	text = "Играть";
	x = GetCenterWindowX() - (text.length() / 2 + 5);
	m_uiButton.SetRealPos(x, 5);
	m_uiButton.SetSize(122, 50);
	m_uiButton.setText(text);
	m_uiButton.setParent(this);
	m_uiButton.SetFunctionOnL(std::function<void()>([]() { 
		UIManager* pManager = UIManager::getSingleton();
		pManager->GetMenu()->CloseUI();
		pManager->GetRoomSettings()->OpenUI();
	}));

	text = "Выход";
	x = GetCenterWindowX() - (text.length() / 2 + 6); 
	m_btnClose.SetRealPos(x, 9);
	m_btnClose.SetSize(122, 50);
	m_btnClose.setText(text);
	m_btnClose.setParent(this);
	m_btnClose.SetFunctionOnL(std::function<void()>([]() { GameManager::getSingleton()->GameActive() = false; }));
}

void UIMenu::OpenUI()
{
	setVisible(true);
}

void UIMenu::CloseUI()
{
	setVisible(false);
}

void UIMenu::Render()
{
	GameManager* pManager = GameManager::getSingleton();

	if (!bRender)
	{
		for (int i = 0; i < GetWidth(); i++)
		{
			for (int j = 0; j < GetHeight(); j++)
			{
				SetConsoleCursorPosition(pManager->getConsoleHandle(), { (short)GetPosX() + (short)i, (short)GetPosY() + (short)j });
				printf("*");
			}
		}
		bRender = true;
	}
	m_uiText.Render();
	m_uiButton.Render();
	m_btnClose.Render();
}

bool UIMenu::OnLeftButtonClick(int x, int y)
{
	if (!IsInside(x, y))
		return false;

	if (m_uiText.IsInside(x, y))
		return m_uiText.OnLeftButtonClick(x, y);
	else if (m_uiButton.IsInside(x, y))
		return m_uiButton.OnLeftButtonClick(x, y);
	else if (m_btnClose.IsInside(x, y))
		return m_btnClose.OnLeftButtonClick(x, y);
	else
		return UIBase::OnLeftButtonClick(x, y);
}