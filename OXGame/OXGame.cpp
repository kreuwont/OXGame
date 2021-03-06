// OXGame.cpp : Defines the entry point for the console application.
//

#include "stdh.h"
#include <locale>
#include "Game Design\Game.h"

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "RUSSIAN");

	GameManager* pGameManager = GameManager::getSingleton();
	pGameManager->CreateStage();
	pGameManager->SetNextStage(eGAME_STAGE_INIT, eGAME_STAGE_MENU);
	pGameManager->Run();

    return 0;
}

