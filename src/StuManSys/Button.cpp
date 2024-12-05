#include "Button.h"



Button::Button(int x, int y, int width, 
    int height, const std::wstring& text) 
    : Widget(x, y, width, height)
    , text(text)
    , isChange(false)
{
}

void Button::show() const
{
	// 设置样式
	setlinestyle(PS_SOLID, 2);
	setfillcolor(CYAN);
	settextstyle(25, 0, L"微软雅黑");

	// 绘制按钮
	fillrectangle(_x, _y, _x + _width, _y + _height);

	// 绘制文本
	RECT rect = { _x, _y, _x + _width, _y + _height };
	drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

bool Button::state(const ExMessage& msg) 
{
	if (msg.message == WM_MOUSEMOVE && isIn(msg))	// 按钮悬浮
	{
		// 设置样式
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"微软雅黑");

		// 绘制按钮
		fillrectangle(_x, _y, _x + _width, _y + _height);

		// 绘制文本
		RECT rect = { _x, _y, _x + _width, _y + _height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		isChange = true;
		return false;
	}
	else if ((msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) && isIn(msg))	// 按钮被点击
	{
		// 设置样式
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"微软雅黑");

		// 绘制按钮
		fillrectangle(_x, _y, _x + _width, _y + _height);

		// 绘制文本
		RECT rect = { _x, _y, _x + _width, _y + _height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		isChange = true;
		return true;
	}
	else	// 在按钮状态改变的时候，恢复按钮原来的状态，防止屏闪
	{
		if (isChange)
		{
			show();
			isChange = false;
		}
		return false;
	}
}

const std::wstring& Button::getText() const
{
	return text;
}

void Button::setText(const std::wstring& text)
{
	this->text = text;
}

bool Button::isIn(const ExMessage& msg) const
{
	if (msg.x >= this->_x && msg.x <= this->_x + _width && msg.y >= this->_y && msg.y <= this->_y + _height)
	{
		return true;
	}
	return false;
}
