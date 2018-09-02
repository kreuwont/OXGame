#ifndef _UI_CHECK_BOX_H_
#define _UI_CHECK_BOX_H_

class UIBase;

class UICheckBox : public UIBase
{
public:
	UICheckBox();
	~UICheckBox();

	void Render();
	
	void setText(std::string text) { m_sText = text; }
	std::string getText() const { return m_sText; }

	void setCheck(bool bCheck) { m_bCheck = bCheck; }
	bool isChecked() const { return m_bCheck; }

	bool OnLeftButtonClick(int x, int y);
	
private:
	bool  m_bCheck;
	std::string m_sText;
};

#endif // !_UI_CHECK_BOX_H_
