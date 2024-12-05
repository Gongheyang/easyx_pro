/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@�ļ�    Widget.h
 *@����    �����������
 *
 *@����    GhY
 *@����    2024��12��5��
 *@�汾    v1.0.0
 *
 ****************************************************/
#pragma once

#include <easyx.h>

/*
 *@bref    ����
 */
class Widget
{
public:
    Widget(int x = 0, int y = 0, int width = 100, int height = 60);

    /*
     *@bref    ���ÿؼ�����
     */
    void setRect(int x, int y, int width, int height);

    /*
     *@bref    ��ʾ����
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
    int _x;        // X ����
    int _y;        // Y ����
    int _width;    // ���
    int _height;   // �߶�
};