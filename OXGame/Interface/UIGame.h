#ifndef _UI_GAME_H_
#define _UI_GAME_H_

#include "UIWindow.h"
#include "UIButton.h"
#include "UIText.h"
#include "UIGameField.h"

class UIGame : public UIWindow
{
public:
	UIGame();
	~UIGame();

	void OpenUI();
	void CloseUI();

	void Render();
	void InitGame(int fieldSize, std::string firstPlayer, std::string secondPlayer);
	void Create(int nX, int nY, int nWidth, int nHeight);
	bool OnLeftButtonClick(int x, int y);

private:
	void UpdateRoleText();

private:
	bool m_bWin;
	eGameRole m_eCurRole;
	UIText m_txtTimer;
	UIText m_txtRole;
	time_t m_tGameTime;
	UIGameField m_fieldMain;
	std::string m_strFirstPlayer;
	std::string m_strSecondPlayer;
	UIButton m_btnBack;
	UIButton m_btnSpace;
};

#endif