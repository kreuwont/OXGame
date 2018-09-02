#include "stdh.h"
#include "Game.h"
#include "..\Interface\UIManager.h"
#include "StageLoad.h"
#include "StageMenu.h"
#include "StageGame.h"

HWND GetConsoleHwnd(void);

GameManager::GameManager(void)
	: m_eCurStage(eGAME_STAGE_NONE)
	, m_eNextStage(eGAME_STAGE_NONE)
	, m_e2ndNextStage(eGAME_STAGE_NONE)
	, m_pCurStage(NULL)
{
	GameActive() = false;
	m_hWhdConsole = GetConsoleHwnd();
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ClearVector(m_vecStage);
}

GameManager::~GameManager(void)
{
	std::vector<Stage*>::iterator iter = m_vecStage.begin();
	std::vector<Stage*>::iterator iterEnd = m_vecStage.end();

	for (iter; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	ClearVector(m_vecStage);
}

void GameManager::CreateStage()
{
	DEF_CREATE_OBJECT(m_vecStage, StageLoad);
	DEF_CREATE_OBJECT(m_vecStage, StageMenu);
	DEF_CREATE_OBJECT(m_vecStage, StageGame);
}

void GameManager::GoStage()
{
	if (m_eNextStage <= eGAME_STAGE_NONE)
		return;

	if (m_pCurStage != NULL)
		m_pCurStage->Release();

	m_eCurStage = m_eNextStage;
	m_pCurStage = m_vecStage[m_eCurStage];
	if (m_pCurStage != NULL)
		m_pCurStage->Init();

	m_eNextStage = m_e2ndNextStage;
	m_e2ndNextStage = eGAME_STAGE_NONE;
}

void GameManager::SetNextStage(eGameStages e1stStage, eGameStages e2stStage)
{
	if (m_eCurStage == e1stStage)
		return;

	if (isCorrectStage(e1stStage) == true)
		m_eNextStage = e1stStage;

	if (isCorrectStage(e2stStage) == true)
		m_e2ndNextStage = e2stStage;
}

bool GameManager::isCorrectStage(eGameStages stage)
{
	if (stage <= eGAME_STAGE_NONE || stage >= eGAME_STAGE_MAX)
		return false;

	if (stage >= m_vecStage.size())
		return false;

	if (m_vecStage[stage] == NULL)
		return false;

	return true;
}

void GameManager::Run()
{
	if (m_eNextStage != eGAME_STAGE_NONE)
		GoStage();

	if (m_pCurStage != NULL)
		m_pCurStage->Run();
}

void GameManager::ResetTitle()
{
	system("title OX Game");
}

int fps = 0;
bool bTime = false;

void CalcFps()
{
	while (GameManager::getSingleton()->GameActive())
	{
		Sleep(1000);
		bTime = true;
	}
}


void GameManager::GameLoop()
{
	GameActive() = true;

	UIManager* pManager = UIManager::getSingleton();

	std::thread th(&CalcFps);

	int bLeftState = 0;
	while (GameActive())
	{
		if (bTime)
		{
			SetConsoleCursorPosition(GameManager::getSingleton()->getConsoleHandle(), { 0, 0 });
			std::cout << "FPS : " << fps;
			fps = 0;
			bTime = false;
		}

		int value = GetAsyncKeyState(VK_LBUTTON);
		if (value != 0)
			bLeftState = -1;
		else if (value == 0 && bLeftState == -1)
			bLeftState = 1;

		if(bLeftState == 1)
		{
			POINT pos;
			GetCursorPos(&pos);
			pManager->MsgProc(VK_LBUTTON, pos.x, pos.y);
			bLeftState = 0;
		}

		pManager->Render();
		++fps;
		//Sleep(3);
	}

	th.detach();
}

// From MSDN
HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024
	HWND hwndFound;
	char pszNewWindowTitle[MY_BUFSIZE];

	char pszOldWindowTitle[MY_BUFSIZE];


	GetConsoleTitleA(pszOldWindowTitle, MY_BUFSIZE);

	wsprintfA(pszNewWindowTitle, "%d/%d",
		GetTickCount(),
		GetCurrentProcessId());

	SetConsoleTitleA(pszNewWindowTitle);
	Sleep(40);

	hwndFound = FindWindowA(NULL, pszNewWindowTitle);
	SetConsoleTitleA(pszOldWindowTitle);

	return(hwndFound);
}
