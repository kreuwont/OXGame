#ifndef _UI_WINDOW_H_
#define _UI_WINDOW_H_

#include "UIBase.h"

class UIWindow : public UIBase
{
public:
	UIWindow() { m_bVisible = false; }
	virtual ~UIWindow() { Destroy(); };

	virtual void Create(int nX, int nY, int nWidth, int nHeight) 
	{
		SetPos(nX, nY); 
		SetSize(nWidth, nHeight);
	}

	virtual void Destroy()
	{
		UIBase::Destroy();
	}

	void RelocateToCenterLine()
	{
		SetPosX(GetCenterBufferLine() - (ConsoleToWindowX(GetWidth()) / 2));
	}

	int GetCenterWindowX()
	{
		return GetWidth() / 2;
	}

	int GetCenterWindowY()
	{
		return GetHeight() / 2;
	}

	//void ResizeToCenterScreen()
	//{
	//	SetPosX(GetCenterBufferScreen() - (ConsoleToWindowX(GetWidth()) / 2));
	//	SetPosY(GetCenterBufferScreen() - (ConsoleToWindowX(GetWidth()) / 2));
	//}

	void setVisible(bool bVisible) { m_bVisible = bVisible; system("cls"); }
	bool isVisible() const { return m_bVisible; }

private:
	bool	m_bVisible;
};

#endif // !_UI_WINDOW_H_
