#include "stdh.h"
#include "Game.h"
#include "..\Interface\UIManager.h"
#include "StageGame.h"
#include "..\Interface\UIMenu.h"
#include "..\Interface\UIRoomSettings.h"
#include "..\Interface\UIGame.h"

void StageGame::Init()
{
	UIManager* pUIManager = UIManager::getSingleton();
	GameManager* pManager = GameManager::getSingleton();

	auto pRoomSettings = pUIManager->GetRoomSettings();

	pUIManager->GetGame()->InitGame(pRoomSettings->getFieldSize(),
		pRoomSettings->getPlayerFirst(),
		pRoomSettings->getPlayerSecond());
	pUIManager->GetGame()->OpenUI();
}

void StageGame::Release()
{
	UIManager* pUIManager = UIManager::getSingleton();
	pUIManager->GetGame()->CloseUI();
	pUIManager->GetRoomSettings()->Reset();
}