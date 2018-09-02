#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include "..\Design Classes\SingletonBase.h"
#include "UIBase.h"
#include "UIText.h"
#include "UIButton.h"
#include "UICheckBox.h"
#include "UIEditBox.h"

class UIWindow;
class UIMenu;
class UIRoomSettings;
class UIGame;

class UIManager : public CSingletonBase<UIManager>
{
public:
	UIManager();
	~UIManager();
	
	void Render();
	void MsgProc(int code, int x, int y);

private:
	void InitUIs();

	UIWindow* m_aUIs[eUI_MAX];

public:
	UIMenu* GetMenu() { return reinterpret_cast<UIMenu*>( m_aUIs[eUI_MENU]); }
	UIRoomSettings* GetRoomSettings() { return reinterpret_cast<UIRoomSettings*>(m_aUIs[eUI_ROOM_SETTINGS]); }
	UIGame* GetGame() { return reinterpret_cast<UIGame*>(m_aUIs[eUI_GAME]); }
};

#endif // !_UI_MANAGER_H_
