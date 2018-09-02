#ifndef __GAME_H__
#define __GAME_H__

#include "..\Design Classes\SingletonBase.h"

class Stage
{
public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Run() {}
};

class GameManager : public CSingletonBase<GameManager>
{
public:
	GameManager(void);
	~GameManager(void);

	void Run();
	void CreateStage();
	void GoStage();
	void GameLoop();
	void ResetTitle();
	void SetNextStage(eGameStages e1stStage, eGameStages e2stStage);

	bool isCorrectStage(eGameStages stage);
	inline bool& GameActive() { return m_bGameActive; }

	HANDLE getConsoleHandle() const { return m_hConsole; }
	HWND getConsoleHwnd() const { return m_hWhdConsole; }
	eGameStages getCurStage() const { return m_eCurStage; }
	eGameStages getNextStage() const { return m_eNextStage; }

private:
	eGameStages m_eCurStage;
	eGameStages m_eNextStage;
	eGameStages m_e2ndNextStage;
	Stage* m_pCurStage;

	bool m_bGameActive;
	HANDLE m_hConsole;
	HWND   m_hWhdConsole;
	std::vector<Stage*> m_vecStage;
};

#endif // !__GAME_H__

