#include "stdh.h"
#include <functional>
#include "UIManager.h"
#include "UIRoomSettings.h"

UIRoomSettings::UIRoomSettings()
{

}

UIRoomSettings::~UIRoomSettings()
{
	Destroy();
}

void UIRoomSettings::OpenUI()
{
	setVisible(true);
}

void UIRoomSettings::CloseUI()
{
	setVisible(false);
}

void UIRoomSettings::Reset()
{
	m_editFirstPlayer.setEditText("");
	m_editSecondPlayer.setEditText("");
}

void UIRoomSettings::Create(int nX, int nY, int nWidth, int nHeight)
{
	UIWindow::Create(nX, nY, nWidth, nHeight);
	setParent(NULL); 
	RelocateToCenterLine();

	std::string text = "Настройка комнаты";
	int x = GetCenterWindowX() - text.length() / 2;
	m_txtHeader.SetRealPos(x, 1);
	m_txtHeader.SetSize(text.length() * 10, 0);
	m_txtHeader.setText(text);
	m_txtHeader.setParent(this);

	text = "Имя 1-ого игрока";
	x = GetCenterWindowX() - (text.length() / 2) - 2;
	m_editFirstPlayer.SetRealPos(x, 3);
	m_editFirstPlayer.setEditWidth(15);
	m_editFirstPlayer.SetSize(text.length() * 10, 0);
	m_editFirstPlayer.setText(text);
	m_editFirstPlayer.setParent(this);

	text = "Имя 2-ого игрока";
	x = GetCenterWindowX() - (text.length() / 2) - 2;
	m_editSecondPlayer.SetRealPos(x, 5);
	m_editSecondPlayer.setEditWidth(15);
	m_editSecondPlayer.SetSize(text.length() * 10, 0);
	m_editSecondPlayer.setText(text);
	m_editSecondPlayer.setParent(this);

	text = "Размерность сетки";
	x = GetCenterWindowX() - (text.length() / 2);
	m_editSizeble.SetRealPos(x, 7);
	m_editSizeble.setEditWidth(3);
	m_editSizeble.SetSize(text.length() * 10, 0);
	m_editSizeble.setText(text);
	m_editSizeble.setEditText("3");
	m_editSizeble.ReadOnly() = true;
	m_editSizeble.setParent(this);

	text = "Начать игру";
	x = GetCenterWindowX() - (text.length() / 2) - 2;
	m_btnGameStart.SetRealPos(x, 9);
	m_btnGameStart.SetSize(122, 50);
	m_btnGameStart.setText(text);
	m_btnGameStart.setParent(this);
	m_btnGameStart.SetFunctionOnL(std::function<void()>([&x, this]() {
		this->GameStartClick();
	}));
}

void UIRoomSettings::Render()
{
	m_txtHeader.Render();
	m_editFirstPlayer.Render();
	m_editSecondPlayer.Render();
	m_editSizeble.Render();
	m_btnGameStart.Render();

	UIBase::Render();
}

bool UIRoomSettings::OnLeftButtonClick(int x, int y)
{
	if (!IsInside(x, y))
		return false;

	if (m_editFirstPlayer.IsInside(x, y))
		return m_editFirstPlayer.OnLeftButtonClick(x, y);
	else if (m_editSecondPlayer.IsInside(x, y))
		return m_editSecondPlayer.OnLeftButtonClick(x, y);
	else if (m_editSizeble.IsInside(x, y))
		return m_editSizeble.OnLeftButtonClick(x, y);
	else if (m_btnGameStart.IsInside(x, y))
		return m_btnGameStart.OnLeftButtonClick(x, y);
	else
		return UIBase::OnLeftButtonClick(x, y);
}

void UIRoomSettings::GameStartClick()
{
	if (getPlayerFirst().size() < 1
		|| getPlayerFirst().size() > 15
		|| getPlayerSecond().size() < 1
		|| getPlayerSecond().size() > 15)
	{
		UIMessageBox* msgBox = new UIMessageBox(GetCenterWindowX() - 20, 14, 45, 8, this);
		msgBox->setText("Имя игрока должно содержать до 15 символов.");
		this->addChild(msgBox);
		return;
	}

	if (getFieldSize() != 3)
	{
		UIMessageBox* msgBox = new UIMessageBox(GetCenterWindowX() - 20, 14, 45, 8, this);
		msgBox->setText("В данный момент доступно только поле 3х3.");
		this->addChild(msgBox);
		return;
	}

	GameManager* pManager = GameManager::getSingleton();
	pManager->SetNextStage(eGAME_STAGE_PLAY, eGAME_STAGE_MENU);
	pManager->Run();
}