/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    Button.h
 *@描述    按钮类
 *
 *@作者    GhY
 *@日期    2024年12月5日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma once
#include "Widget.h"
#include <string>


/*
 *@bref    按钮类
 */
class Button :
    public Widget
{
public:
    Button(int x = 0, int y = 0, int width = 100,
        int height = 60, const std::wstring& text = L"按钮");

    ~Button() {}

    /*
     *@bref    显示按钮
     */
    void show() const;

    /*
     *@bref    按钮状态，true 表示按钮按下
     */
    bool state(const ExMessage& msg);

    /*
     *@bref    获取按钮文本
     */
    const std::wstring& getText() const;

    /*
     *@bref    设置按钮文本
     */
    void setText(const std::wstring& text);

protected:
    /*
     *@bref    判断鼠标是否在按钮里面
     */
    bool isIn(const ExMessage& msg) const;


protected:

    std::wstring text;                      // 按钮文本
    bool isChange;                          // 按钮状态是否改变

};

