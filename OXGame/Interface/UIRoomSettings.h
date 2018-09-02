#ifndef _UI_ROOM_SETTINGS__
#define _UI_ROOM_SETTINGS__

#include "UIWindow.h"
#include "UICheckBox.h"
#include "UIText.h"
#include "UIEditBox.h"
#include "UIMessageBox.h"

class UIRoomSettings : public UIWindow
{
public:
	UIRoomSettings();
	~UIRoomSettings();

	void OpenUI();
	void CloseUI();

	void Render();
	void Reset();
	void Create(int nX, int nY, int nWidth, int nHeight);
	bool OnLeftButtonClick(int x, int y);

	int getFieldSize() const { return atoi(m_editSizeble.getInputText().c_str()); }
	std::string getPlayerFirst() const { return m_editFirstPlayer.getInputText(); }
	std::string getPlayerSecond() const { return m_editSecondPlayer.getInputText(); }

private:
	void GameStartClick();

	UIText m_txtHeader;
	UIButton m_btnGameStart;
	UIEditBox m_editFirstPlayer;
	UIEditBox m_editSecondPlayer;
	UIEditBox m_editSizeble;
};

#endif // !_UI_ROOM_SETTINGS__
