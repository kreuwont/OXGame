/*====================================================================================================================================*/
/*														ONLY 3x3																	  */
/*====================================================================================================================================*/
#include "stdh.h"
#include <iomanip>
#include <algorithm>
#include "..\Game Design\Game.h"
#include "UIManager.h"
#include "UIBase.h"
#include "UIGameField.h"

UIGameField::UIGameField()
	: m_bWin(false)
	, m_nChecked(NULL)
	, m_eRole(eROLE_NONE)
	, m_eWinRole(eROLE_NONE)
	, m_bDraw(false)
{
}

UIGameField::~UIGameField()
{
	if (m_nChecked != NULL)
	{
		for (int i = 0; i < m_nSize; i++)
			if (m_nChecked[i] != NULL)
				delete[] m_nChecked[i];

		delete[] m_nChecked;
	}

	Destroy();
}

void UIGameField::SetFieldSize(int size)
{
	m_nSize = size;
	m_nChecked = new int*[m_nSize];

	for (int i = 0; i < m_nSize; i++)
		m_nChecked[i] = new int[m_nSize];

	for (int i = 0; i < m_nSize; i++)
		for (int j = 0; j < m_nSize; j++)
			m_nChecked[i][j] = eROLE_NONE;
}

void UIGameField::Render()
{
	GameManager* pGameManager = GameManager::getSingleton();
	HANDLE pWndConsole = pGameManager->getConsoleHandle();

	char symbol;
	int x = GetRealX(), y = GetRealY();
	SetConsoleCursorPosition(pWndConsole, { (short)x, (short)y });

	for (int i = 0; i < m_nSize; i++)
	{
		for (int j = 0; j <= m_nSize * 4; j++)
		{
			std::cout << "-";
		}

		y++;
		SetConsoleCursorPosition(pWndConsole, { (short)x, (short)y });
		for (int j = 0; j < m_nSize; j++)
		{
			symbol = m_nChecked[i][j] == eROLE_NONE ? ' ' : m_nChecked[i][j] == eROLE_X ? 'X' : 'O';
			std::cout << "|" << std::setw(2) << symbol << std::setw(2);
			if (j == m_nSize - 1)
				std::cout << "|";
		}

		y++;
		SetConsoleCursorPosition(pWndConsole, { (short)x, (short)y });
		if (i == m_nSize - 1)
			for (int j = 0; j <= m_nSize * 4; j++)
				std::cout << "-";
	}
}

bool UIGameField::OnLeftButtonClick(int x, int y)
{
	int col, row;

	col = (WindowToConsoleX(x) - GetRealX()) / 4;
	row = (WindowToConsoleY(y) - GetRealY()) / 2;

	if (col < 0 || col >= m_nSize)
		return false;

	if (row < 0 || row >= m_nSize)
		return false;

	if (m_nChecked[row][col] != eROLE_NONE)
		return false;

	m_nChecked[row][col] = m_eRole;
	CheckWin();
	CheckDraw();

	if (!m_bWin && !m_bDraw)
	{
		m_eRole = m_eRole == eROLE_O ? eROLE_X : eROLE_O;
	}
	else
	{
		m_eWinRole = m_eRole;
		m_eRole = eROLE_NONE;
	}
	return true;
}

bool UIGameField::CheckSum(int sum)
{
	if (sum == 3)
	{
		m_bWin = true;
		return true;
	}
	else if (sum == -3)
	{
		m_bWin = true;
		return true;
	}
	return false;
}

void UIGameField::CheckWin()
{
	int sum = 0;

#pragma region SHIT_CODE
	for (int i = 0; i < m_nSize; i++)
	{
		sum = 0;
		for (int j = 0; j < m_nSize; j++)
			sum += m_nChecked[j][i];

		if (CheckSum(sum))
			return;
	}

	for (int i = 0; i < m_nSize; i++)
	{
		sum = 0;
		for (int j = 0; j < m_nSize; j++)
			sum += m_nChecked[i][j];

		if (CheckSum(sum))
			return;
	}

	sum = 0;
	for (int i = 0; i < m_nSize; i++)
		sum += m_nChecked[i][i];

	if (CheckSum(sum))
		return;

	sum = 0;
	for (int i = 0; i < m_nSize; i++)
		sum += m_nChecked[i][m_nSize - (i + 1)];

	CheckSum(sum);
#pragma endregion
}

void UIGameField::ResetField()
{
	for (int i = 0; i < m_nSize; i++)
		for (int j = 0; j < m_nSize; j++)
			m_nChecked[i][j] = eROLE_NONE;
	
	m_bWin = false;
	m_eRole = eROLE_NONE;
	m_eWinRole = eROLE_NONE;
}

void UIGameField::CheckDraw()
{
	int count = 0;

	for (int i = 0; i < m_nSize; i++)
		for (int j = 0; j < m_nSize; j++)
			if (m_nChecked[i][j] != eROLE_NONE)
				count++;

	if(count == m_nSize*m_nSize && !m_bWin)
		m_bDraw = true;
}