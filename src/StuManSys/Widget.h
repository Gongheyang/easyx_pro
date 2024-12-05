/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    Widget.h
 *@描述    部件抽象基类
 *
 *@作者    GhY
 *@日期    2024年12月5日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma once

#include <easyx.h>

/*
 *@bref    基类
 */
class Widget
{
public:
    Widget(int x = 0, int y = 0, int width = 100, int height = 60);

    /*
     *@bref    设置控件矩形
     */
    void setRect(int x, int y, int width, int height);

    /*
     *@bref    显示函数
     */
    virtual void show() const = 0;

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

    void setX(int x);

    void setY(int y);

    void setWidth(int width);

    void setHeight(int height);

protected:
    int _x;        // X 坐标
    int _y;        // Y 坐标
    int _width;    // 宽度
    int _height;   // 高度
};