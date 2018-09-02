#include "stdh.h"
#include <functional>
#include <time.h>
#include <sstream>
#include "UIManager.h"
#include "UIGame.h"
#include "UIRoomSettings.h"

UIGame::UIGame()
	: m_eCurRole(eROLE_NONE)
	, m_tGameTime(0)
	, m_bWin(false)
{
}

UIGame::~UIGame()
{
	Destroy();
}

void UIGame::Create(int nX, int nY, int nWidth, int nHeight)
{
	UIWindow::Create(nX, nY, nWidth, nHeight);
	setParent(NULL);
	RelocateToCenterLine();

	m_fieldMain.setParent(this);
	m_fieldMain.SetRole(m_eCurRole);

	std::string text = "Вы в игре: 00:00";
	std::string text2 = "Ходит игрок: ?";

	int x = GetCenterWindowX() - (text.length() + text2.length()) / 2;
	m_txtTimer.SetRealPos(x, 1);
	m_txtTimer.SetRealSize(text.length(), 1);
	m_txtTimer.setText(text);
	m_txtTimer.setParent(this);

	x = x + m_txtTimer.GetWidth() + 5;
	m_txtRole.SetRealPos(x, 1);
	m_txtRole.SetRealSize(text2.length(), 1);
	m_txtRole.setText(text2);
	m_txtRole.setParent(this);

	text = "В меню";
	text2 = "Закрыть игру";
	x = GetCenterWindowX() - (text.length() + text2.length() / 2) - 5;
	m_btnBack.SetRealPos(x, GetСonsoleBottomBuffer() - 4);
	m_btnBack.SetRealSize(text.length() + 8, 3);
	m_btnBack.setText(text);
	m_btnBack.setParent(this);
	m_btnBack.SetFunctionOnL(std::function<void()>([&x, this]() {
		GameManager* pManager = GameManager::getSingleton();
		pManager->SetNextStage(eGAME_STAGE_MENU, eGAME_STAGE_PLAY);
		pManager->Run();
	}));

	x = x + m_btnBack.GetWidth() + 5;
	m_btnSpace.SetRealPos(x, GetСonsoleBottomBuffer() - 4);
	m_btnSpace.SetRealSize(text2.length() + 8, 3);
	m_btnSpace.setText(text2);
	m_btnSpace.setParent(this);
	m_btnSpace.SetFunctionOnL(std::function<void()>([&x, this]() {
		GameManager::getSingleton()->GameActive() = false;
	}));
}

void UIGame::InitGame(int fieldSize, std::string firstPlayer, std::string secondPlayer)
{
	if (fieldSize < 3 || fieldSize > 10)
		fieldSize = 3;

	int width = fieldSize * 4;
	int heigth = fieldSize * 2;

	m_fieldMain.SetFieldSize(fieldSize);
 	m_fieldMain.SetRealPos(WindowToConsoleX(GetCenterBufferLine()) - (width / 2) - GetRealX(), WindowToConsoleY(GetCenterBufferColoumn()) - (heigth / 2) - GetRealY());
	m_fieldMain.SetRealSize(width, heigth);

	m_strFirstPlayer = firstPlayer;
	m_strSecondPlayer = secondPlayer;
}

void UIGame::OpenUI()
{
	setVisible(true);
	m_eCurRole = eROLE_X;
	m_tGameTime = time(NULL);
	m_fieldMain.SetRole(m_eCurRole);
	UpdateRoleText();
}

void UIGame::CloseUI()
{
	setVisible(false);
	m_eCurRole = eROLE_NONE;
	m_fieldMain.ResetField();
	m_bWin = false;
	m_tGameTime = 0;
	UIBase::deleteChildAll();
}

void UIGame::Render()
{
	if (!m_bWin)
	{
		time_t localTime = time(NULL);
		time_t deltaTime = localTime - m_tGameTime;

		if (deltaTime < 0)
		{
			deltaTime = localTime;
		}
		else
		{
			int mm = (int)deltaTime / 60;
			int ss = (int)deltaTime % 60;
			char str[32];
			sprintf(str, "Вы в игре: %.2d:%.2d", mm, ss);
			m_txtTimer.setText(str);
		}

		m_fieldMain.Render();
	}

	m_txtTimer.Render();
	m_txtRole.Render();
	m_btnBack.Render();
	m_btnSpace.Render();

	UIBase::Render();
}

bool UIGame::OnLeftButtonClick(int x, int y)
{
	if (!IsInside(x, y))
		return false;

	if (m_fieldMain.IsInside(x, y))
	{
		bool result = m_fieldMain.OnLeftButtonClick(x, y);
		if (result == false)
			return false;

		m_eCurRole = m_eCurRole == eROLE_X ? eROLE_O : eROLE_X;
		UpdateRoleText();

		if (m_fieldMain.isWin())
		{
			m_txtTimer.SetRealPosX(m_txtTimer.GetPosX() + (m_txtRole.GetWidth() / 2));
			m_txtRole.setText("");
			system("cls");

			UIMessageBox* msgBox = new UIMessageBox(GetCenterWindowX() - 20, 14, 40, 8, this);
			std::stringstream stringStream;
			stringStream << "Победил игрок: " << (m_fieldMain.getWinRole() == eROLE_X ? m_strFirstPlayer : m_strSecondPlayer);
			msgBox->setText(stringStream.str());
			this->addChild(msgBox);
			m_bWin = true;
			return true;
		}
		else if (m_fieldMain.isDraw())
		{
			m_txtTimer.SetRealPosX(m_txtTimer.GetPosX() + (m_txtRole.GetWidth() / 2));
			m_txtRole.setText("");
			system("cls");

			UIMessageBox* msgBox = new UIMessageBox(GetCenterWindowX() - 20, 14, 40, 8, this);
			msgBox->setText("Ничья");
			this->addChild(msgBox);
			m_bWin = true;
			return true;
		}
		return true;
	}
	else if (m_btnBack.IsInside(x, y))
		return m_btnBack.OnLeftButtonClick(x, y);
	else if (m_btnSpace.IsInside(x, y))
		return m_btnSpace.OnLeftButtonClick(x, y);
	else
		UIBase::OnLeftButtonClick(x, y);

	return true;
}

void UIGame::UpdateRoleText()
{
	GameManager* pGameManager = GameManager::getSingleton();
	HANDLE pWndConsole = pGameManager->getConsoleHandle();

	std::stringstream stringStream;
	stringStream << "Ходит игрок: " << (m_eCurRole == eROLE_X ? m_strFirstPlayer : m_strSecondPlayer);
	m_txtRole.setText(stringStream.str());

	/* Костыль */
	short x = (short)m_txtRole.GetRealX();
	short y = (short)m_txtRole.GetRealY();
	SetConsoleCursorPosition(pWndConsole, { x, y });
	std::cout << "                              ";
}