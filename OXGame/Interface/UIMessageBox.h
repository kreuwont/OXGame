#ifndef _UI_MESSAGE_BOX_H_
#define _UI_MESSAGE_BOX_H_

class UIBase;

class UIMessageBox : public UIBase
{
public:
	UIMessageBox(int realX, int realY, int realWidth, int realHeigth, UIBase* pParent);
	~UIMessageBox();

	void Render();

	void setText(std::string text) { m_uiText.setText(text); }
	std::string getText() const { return m_uiText.getText(); }

	bool OnLeftButtonClick(int x, int y);

private:
	UIText m_uiText;
	UIText m_uiClose;
	int m_nFixedX;
};

#endif // !_UI_MESSAGE_BOX_H_
