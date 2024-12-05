#include "Widget.h"

Widget::Widget(int x, int y, int width, int height) 
    : _x(x)
    , _y(y)
    , _width(width)
    , _height(height)
{
}

int Widget::getX() const
{
	return _x;
}

int Widget::getY() const
{
	return _y;
}

int Widget::getWidth() const
{
	return _width;
}

int Widget::getHeight() const
{
	return _height;
}

void Widget::setX(int x)
{
	this->_x = x;
	show();
}

void Widget::setY(int y)
{
	this->_y = y;
	show();
}

void Widget::setWidth(int width)
{
	this->_width = width;
	show();
}

void Widget::setHeight(int height)
{
	this->_height = height;
	show();
}

void Widget::setRect(int x, int y, int width, int height)
{
	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;
	show();
}
