/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@�ļ�    Window.h
 *@����    ��������
 *
 *@����    GhY
 *@����    2024��12��5��
 *@�汾    v1.0.0
 *
 ****************************************************/
#pragma once

#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include "Table.h"
#include <iostream>
#include <algorithm>

// ����ͼƬ���ĳ���
constexpr auto BACKGROUND_IMAGE = L"../data/StuManSys/bg.jpg";

class Window :
    public Widget
{

public:
    // ����״̬��ʶ��ÿ��״̬������һ������
    enum WindowState
    {
        mainWindow = 0,     // ������
        viewStudents,       // �鿴ѧ��
        editStudents        // �༭ѧ��
    };

public:
    Window(int width = 600, int height = 400);
    ~Window();

    /*
     *@bref    ��ʾ����
     */
    void show() const;

    /*
     *@bref    ��Ϣѭ��
     */
    void messageLoop();

    /*
     *@bref    �رմ���
     */
    bool close();

    /*
     *@bref    ���ⲿ��������
     */
    void updateData();

private:

    /*
     *@bref    ��ʾ������
     */
    void showMainWindow();

    /*
     *@bref    ��ʾ�鿴ѧ������
     */
    void showViewStudents();

    /*
     *@bref    ��ʾ�༭ѧ������
     */
    void showEditStudents();

    /*
     *@bref    �ж��ܷ�Ϊ����
     */
    bool isNumber(const std::wstring& string);


private:
    // �����ڰ�ť
    Button* mainWindow_view;
    Button* mainWindow_edit;
    Button* mainWindow_exit;
    Button* mainWindow_clear;

    // �鿴ѧ�����ڰ�ť
    Button* viewStudents_pageUp;
    Button* viewStudents_pageDown;
    Button* viewStudents_back;
    Button* viewStudents_sort;

    // �༭ѧ�����ڰ�ť
    Button* editStudents_add;
    Button* editStudents_delete;
    Button* editStudents_back;
    Button* editStudents_search;

    WindowState state;  // ����״̬
    Table* table;       // ѧ�����ݱ��
    Manager manager;    // ������
    HWND hWnd;          // ���ھ��
    bool isEdit;        // �Ƿ�༭ѧ��
};

