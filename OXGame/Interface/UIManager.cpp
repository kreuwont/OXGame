#include "stdh.h"
#include "..\Game Design\Game.h"
#include "UIWindow.h"
#include "UIManager.h"
#include "UIMenu.h"
#include "UIRoomSettings.h"
#include "UIGame.h"

UIManager::UIManager()
{
	InitUIs();
}

UIManager::~UIManager() 
{
	for (int i = 0; i < eUI_MAX; i++)
		SAFE_DELETE(m_aUIs[i]);
}

void UIManager::InitUIs()
{
	m_aUIs[eUI_MENU] = new UIMenu();
	m_aUIs[eUI_MENU]->Create(0, 0, 500, 500);

	m_aUIs[eUI_ROOM_SETTINGS] = new UIRoomSettings;
	m_aUIs[eUI_ROOM_SETTINGS]->Create(0, 0, 500, 500);

	m_aUIs[eUI_GAME] = new UIGame;
	m_aUIs[eUI_GAME]->Create(0, 0, 100500, 100500);
}

void UIManager::MsgProc(int code, int x, int y)
{
	GameManager* pManager = GameManager::getSingleton();
	RECT rect;
	GetWindowRect(pManager->getConsoleHwnd(), &rect);

	if (x <= rect.left || y <= rect.top
		|| x >= rect.right || y >= rect.bottom)
		return;

	int windowX = x - rect.left;
	int windowY = y - rect.top;

	for (int i = 0; i < eUI_MAX; i++)
	{
		if (m_aUIs[i]->isVisible() == false)
			continue;

		switch (code)
		{
		case VK_LBUTTON:
			if (m_aUIs[i]->OnLeftButtonClick(windowX, windowY))
				return;
			break;
		}
	}
}

void UIManager::Render()
{
	for (int i = 0; i < eUI_MAX; i++)
	{
		if (m_aUIs[i]->isVisible() == false)
			continue;

		m_aUIs[i]->Render();
	}
}