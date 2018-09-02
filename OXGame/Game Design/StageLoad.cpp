#include "stdh.h"
#include "Game.h"
#include "StageLoad.h"

void StageLoad::LoadWork()
{
	UpdateProgressValue(10);
	Sleep(545);
	UpdateProgressValue(50);
	Sleep(1000);
	UpdateProgressValue(40);
}

void StageLoad::UpdateProgressValue(int val)
{
	int persentVal = m_nLoadPersent.load() + val;
	if (persentVal > 100)
		persentVal = 100;

	m_nLoadPersent = persentVal;
	system("cls");

	int width, heigth;
	GameManager* pGameManager = GameManager::getSingleton();
	HANDLE hWndConsole = pGameManager->getConsoleHandle();
	ConsoleSize(hWndConsole, &width, &heigth);
	if (GetLastError() != NOT_ERROR)
	{
		width = 250;
		heigth = 100;
	}

	COORD coords;
	coords.X = 1;
	coords.Y = heigth / 2 - 3;
	SetConsoleCursorPosition(hWndConsole, coords);

	std::cout << persentVal << "% completed: ";
	std::cout << std::string(persentVal, '|').c_str();
	std::cout.flush();
}

void StageLoad::Init()
{
	system("title Загрузка");
	m_nLoadPersent = 0;
	/* ============= Some work ================= */
	std::thread th(&StageLoad::LoadWork, this);
	th.join();
	/* ========================================= */

	GameManager* pGameManager = GameManager::getSingleton();
	pGameManager->SetNextStage(eGAME_STAGE_MENU, eGAME_STAGE_NONE);
	pGameManager->GoStage();
}

void StageLoad::Release()
{
	GameManager* pGameManager = GameManager::getSingleton();
	pGameManager->ResetTitle();
	system("cls");
}
