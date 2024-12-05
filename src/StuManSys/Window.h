/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    Window.h
 *@描述    主界面类
 *
 *@作者    GhY
 *@日期    2024年12月5日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma once

#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include "Table.h"
#include <iostream>
#include <algorithm>

// 背景图片名的常量
constexpr auto BACKGROUND_IMAGE = L"../data/StuManSys/bg.jpg";

class Window :
    public Widget
{

public:
    // 窗口状态标识，每个状态代表了一个界面
    enum WindowState
    {
        mainWindow = 0,     // 主窗口
        viewStudents,       // 查看学生
        editStudents        // 编辑学生
    };

public:
    Window(int width = 600, int height = 400);
    ~Window();

    /*
     *@bref    显示窗口
     */
    void show() const;

    /*
     *@bref    消息循环
     */
    void messageLoop();

    /*
     *@bref    关闭窗口
     */
    bool close();

    /*
     *@bref    从外部更新数据
     */
    void updateData();

private:

    /*
     *@bref    显示主窗口
     */
    void showMainWindow();

    /*
     *@bref    显示查看学生窗口
     */
    void showViewStudents();

    /*
     *@bref    显示编辑学生窗口
     */
    void showEditStudents();

    /*
     *@bref    判断受否为数字
     */
    bool isNumber(const std::wstring& string);


private:
    // 主窗口按钮
    Button* mainWindow_view;
    Button* mainWindow_edit;
    Button* mainWindow_exit;
    Button* mainWindow_clear;

    // 查看学生窗口按钮
    Button* viewStudents_pageUp;
    Button* viewStudents_pageDown;
    Button* viewStudents_back;
    Button* viewStudents_sort;

    // 编辑学生窗口按钮
    Button* editStudents_add;
    Button* editStudents_delete;
    Button* editStudents_back;
    Button* editStudents_search;

    WindowState state;  // 窗口状态
    Table* table;       // 学生数据表格
    Manager manager;    // 管理器
    HWND hWnd;          // 窗口句柄
    bool isEdit;        // 是否编辑学生
};

