#ifndef _UI_MENU_H_
#define _UI_MENU_H_

#include "UIWindow.h"
#include "UIButton.h"
#include "UIText.h"

class UIWindow;
class UIText;
class UIButton;

class UIMenu : public UIWindow
{
public:
	UIMenu();
	~UIMenu();

	void OpenUI();
	void CloseUI();

	void Render();
	void Create(int nX, int nY, int nWidth, int nHeight);
	bool OnLeftButtonClick(int x, int y);

private:
	UIText m_uiText;
	UIButton m_uiButton;
	UIButton m_btnClose;
};

#endif // _UI_MENU_H_