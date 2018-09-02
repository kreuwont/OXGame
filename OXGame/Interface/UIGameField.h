#ifndef _UI_GAME_FIELD_H_
#define _UI_GAME_FIELD_H_

class UIBase;

class UIGameField : public UIBase
{
public:
	UIGameField();
	~UIGameField();

	void Render();
	bool OnLeftButtonClick(int x, int y);

	void SetRole(eGameRole role) { m_eRole = role; }
	void SetFieldSize(int size);

	bool isWin() const { return m_bWin; }
	bool isDraw() const { return m_bDraw; }
	eGameRole getWinRole() const { return m_eWinRole; }

	void ResetField();

private:
	void CheckWin();
	void CheckDraw();
	bool CheckSum(int sum);

private:
	eGameRole m_eRole;
	eGameRole m_eWinRole;
	bool m_bWin;
	bool m_bDraw;
	int m_nSize;
	int **m_nChecked;
};

#endif // _UI_GAME_FIELD_H_
