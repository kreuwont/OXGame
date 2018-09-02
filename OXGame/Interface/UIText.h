#ifndef _UI_TEXT_H_
#define _UI_TEXT_H_

class UIBase;

class UIText : public UIBase
{
public:
	UIText();
	~UIText();

	void Render();

	void setText(std::string text) { m_sText = text; }
	std::string getText() const { return m_sText;	}

private:
	std::string m_sText;
	COLOR m_iBackColor;
	COLOR m_iTextColor;
};

#endif // !_UI_TEXT_H_
