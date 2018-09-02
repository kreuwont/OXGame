#ifndef _UI_EDIT_BOX_H_
#define _UI_EDIT_BOX_H_

class UIBase;

class UIEditBox : public UIBase
{
public:
	UIEditBox();
	~UIEditBox();

	void setEditWidth(int width) { m_nEditWidth = width; }

	void setText(std::string text) { m_sText = text; }
	void setEditText(std::string text) { m_sEditText = text; }
	std::string getText() const { return m_sText; }
	std::string getInputText() const { return m_sEditText; }

	bool& ReadOnly() { return m_bReadOnly; }

	void setFocus(bool bFocus) { m_bFocus = bFocus; }
	bool isFocus() const { return m_bFocus; }

	void Render();
	bool OnLeftButtonClick(int x, int y);

private:
	bool m_bFocus;
	bool m_bReadOnly;
	int m_nEditWidth;
	std::string m_sText;
	std::string m_sEditText;
};

#endif //_UI_EDIT_BOX_H_