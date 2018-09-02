#include "stdh.h"
#include "Game.h"
#include "..\Interface\UIManager.h"
#include "StageMenu.h"
#include "..\Interface\UIMenu.h"
#include "..\Interface\UIRoomSettings.h"

void StageMenu::Init()
{
	UIManager* pUIManager = UIManager::getSingleton();
	GameManager* pManager = GameManager::getSingleton();

	pUIManager->GetMenu()->OpenUI();

	if (!pManager->GameActive())
		pManager->GameLoop();
}

void StageMenu::Release()
{
	UIManager* pUIManager = UIManager::getSingleton();
	pUIManager->GetRoomSettings()->CloseUI();
}