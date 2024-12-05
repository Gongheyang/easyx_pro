/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@�ļ�    Button.h
 *@����    ��ť��
 *
 *@����    GhY
 *@����    2024��12��5��
 *@�汾    v1.0.0
 *
 ****************************************************/
#pragma once
#include "Widget.h"
#include <string>


/*
 *@bref    ��ť��
 */
class Button :
    public Widget
{
public:
    Button(int x = 0, int y = 0, int width = 100,
        int height = 60, const std::wstring& text = L"��ť");

    ~Button() {}

    /*
     *@bref    ��ʾ��ť
     */
    void show() const;

    /*
     *@bref    ��ť״̬��true ��ʾ��ť����
     */
    bool state(const ExMessage& msg);

    /*
     *@bref    ��ȡ��ť�ı�
     */
    const std::wstring& getText() const;

    /*
     *@bref    ���ð�ť�ı�
     */
    void setText(const std::wstring& text);

protected:
    /*
     *@bref    �ж�����Ƿ��ڰ�ť����
     */
    bool isIn(const ExMessage& msg) const;


protected:

    std::wstring text;                      // ��ť�ı�
    bool isChange;                          // ��ť״̬�Ƿ�ı�

};

