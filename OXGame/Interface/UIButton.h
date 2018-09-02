#ifndef _UI_BUTTON_H_
#define _UI_BUTTON_H_

class UIBase;

class UIButton : public UIBase
{
public:
	UIButton();
	~UIButton();

	void Render();

	void setText(std::string text) { m_sText = text; }
	std::string getText() const { return m_sText; }

	bool OnLeftButtonClick(int x, int y);

private:
	
	std::string m_sText;
	COLOR m_iBackColor;
	COLOR m_iTextColor;
};

#endif // !_UI_BUTTON_H_
