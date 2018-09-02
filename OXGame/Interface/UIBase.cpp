#include "stdh.h"
#include "UIManager.h"
#include "UIBase.h"

UIBase::UIBase()
	: m_eType(eUI_BASE)
	, m_nPosX(0)
	, m_nPosY(0)
	, m_nWidth(0)
	, m_nHeight(0)
	, m_bHide(false)
	, m_pParent(NULL)
{

}

UIBase::~UIBase()
{
	Destroy();
}

void UIBase::Destroy()
{
	deleteChildAll();
}

bool UIBase::IsInside(int x, int y)
{
	WindowToConsoleCoords(x, y, &x, &y);
	ConvertToWindow(x, y);

	if (x >= 0 && y >= 0 && x <= m_nWidth && y <= m_nHeight)
		return true;
	return false;
}

void UIBase::ConvertToWindow(int &x, int &y)
{
	int	nAbsX, nAbsY;
	GetAbsPos(nAbsX, nAbsY);
	x -= nAbsX;	y -= nAbsY;
}

void UIBase::GetAbsPos(int &nX, int &nY)
{
	if (m_pParent) 
	{ 
		m_pParent->GetAbsPos(nX, nY); 
		nX += m_nPosX; 
		nY += m_nPosY; 
	}
	else 
	{ 
		nX = m_nPosX; 
		nY = m_nPosY; 
	}
}

bool UIBase::addChild(UIBase* pUI)
{
	if (pUI == NULL)
		return false;

	m_vecChilds.push_back(pUI);
	pUI->setParent(this);
	return true;
}

bool UIBase::deleteChild(UIBase* pUI)
{
	child_iter		iter = m_vecChilds.begin();
	child_iter		eiter = m_vecChilds.end();

	for (; iter != eiter; ++iter)
	{
		if ((*iter) == pUI)
		{
			m_vecChilds.erase(iter);
			SAFE_DELETE(pUI);
			return true;
		}
	}

	return false;
}

bool UIBase::deleteChild(int pos)
{
	int size = m_vecChilds.size();
	if (pos >= size || size < 0)
		return false;

	child_iter iter = m_vecChilds.begin();

	UIBase* pDel = (*(iter + pos));
	m_vecChilds.erase(iter + pos);
	SAFE_DELETE(pDel);
	return true;
}

void UIBase::deleteChildAll()
{
	child_iter iter = m_vecChilds.begin();
	child_iter eiter = m_vecChilds.end();

	for (; iter != eiter; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	ClearVector(m_vecChilds);
}

void UIBase::Render()
{
	RenderChilds();
}

void UIBase::RenderChilds()
{
	child_iter iter = m_vecChilds.begin();
	child_iter eiter = m_vecChilds.end();

	for (; iter != eiter; ++iter)
	{
		(*iter)->Render();
	}
}

bool UIBase::OnLeftButtonClickChild(int x, int y)
{
	child_iter iter = m_vecChilds.begin();
	child_iter eiter = m_vecChilds.end();

	for (; iter != eiter; ++iter)
	{
		if((*iter)->IsInside(x, y))
			return (*iter)->OnLeftButtonClick(x, y);
	}

	return false;
}