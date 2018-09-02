#ifndef _UI_BASE_H_
#define _UI_BASE_H_

#include <functional>
#include "..\Utils.h"

class UIBase;

typedef std::function<void()> action_func;
typedef std::vector<UIBase*>::iterator child_iter;

class UIBase
{
public:
	UIBase();
	virtual ~UIBase();

	void Destroy();
	void SetFunctionOnL(action_func func) { m_funcOnL = func; }
	void SetFunctionOnR(action_func func) { m_funcOnR = func; }

	void	SetPos(int x, int y) { m_nPosX = WindowToConsoleX(x); m_nPosY = WindowToConsoleY(y); };
	void	SetPosX(int x) { m_nPosX = WindowToConsoleX(x); }
	void	SetPosY(int y) { m_nPosY = WindowToConsoleY(y); }
	void	SetRealPos(int x, int y) { m_nPosX = x; m_nPosY = y; };
	void	SetRealPosX(int x) { m_nPosX = x; }
	void	SetRealPosY(int y) { m_nPosY = y; }

	void	SetSize(int w, int h) { m_nWidth = WindowToConsoleX(w); m_nHeight = WindowToConsoleY(h); }
	void	SetWidth(int w) { m_nWidth = WindowToConsoleX(w); }
	void	SetHeight(int h) { m_nHeight = WindowToConsoleY(h); }
	void	SetRealSize(int w, int h) { SetRealWidth(w); SetRealHeigth(h); }
	void	SetRealWidth(int w) { m_nWidth = w; }
	void	SetRealHeigth(int h) { m_nHeight = h; }

	void	GetPos(int &x, int &y) { x = m_nPosX; y = m_nPosY; }
	int		GetPosX()	const { return m_nPosX; }
	int		GetPosY()	const { return m_nPosY; }
	int		GetWidth()	const { return m_nWidth; }
	int		GetHeight() const { return m_nHeight; }

	int		GetRealX()
	{
		int nX = GetPosX();
		if (m_pParent != NULL)
		{
			nX += m_pParent->GetRealX();
		}
		return nX;
	}

	int		GetRealY()
	{
		int nY = GetPosY();
		if (m_pParent != NULL)
		{
			nY += m_pParent->GetRealY();
		}
		return nY;
	}

	void setType(eUITypes eType) { m_eType = eType; }
	eUITypes getType() { return m_eType; }

	void setParent(UIBase* parent) { m_pParent = parent; };
	UIBase* getParent() { return m_pParent; }

	void GetAbsPos(int &nX, int &nY);
	void ConvertToWindow(int &x, int &y);
	bool IsInside(int x, int y);

	bool addChild(UIBase* pUI);
	bool deleteChild(UIBase* pUI);
	bool deleteChild(int pos);
	void deleteChildAll();

	virtual bool OnLeftButtonClick(int x, int y) 
	{
		if (IsInside(x, y))
		{
			if (OnLeftButtonClickChild(x, y))
				return true;
		}

		if (IsInside(x, y) && m_funcOnL != NULL)
		{
			m_funcOnL();
			return true;
		}

		return false;
	};

	bool OnLeftButtonClickChild(int x, int y);

	virtual void Render();
	void RenderChilds();

private:
	eUITypes		m_eType;
	int				m_nPosX,
					m_nPosY;
	int				m_nWidth,
					m_nHeight;
	bool			m_bHide;

	action_func		m_funcOnL;
	action_func		m_funcOnR;

	UIBase*			m_pParent;
	std::vector<UIBase*> m_vecChilds;
};

#endif // !_UI_BASE_H_
