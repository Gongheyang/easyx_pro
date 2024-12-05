/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    Table.h
 *@描述    表格类
 *
 *@作者    GhY
 *@日期    2024年12月5日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma once

#include "Widget.h"
#include "Manager.h"
#include <sstream>

/*
 *@bref    表格类
 */
class Table :
    public Widget
{
public:
    Table(const Manager& manager, int x = 0, int y = 0, int width = 100, int height = 60);

    /*
     *@bref    显示表格
     */
    void show() const;

    /*
     *@bref    上一页
     */
    void pageUp();

    /*
     *@bref    下一页
     */
    void pageDown();

    /*
     *@bref    显示编辑表格（字符串搜索）
     */
    void showEditTable(const wchar_t* searchTerms);

    /*
     *@bref    显示编辑表格（学号搜索）
     */
    void showEditTable(int id);

    /*
     *@bref    显示编辑表格（下标索引）
     */
    void showTable(int index);

    /*
     *@bref    获取搜索索引
     */
    int getSearchIndex() const;

    /*
     *@bref    设置学生索引
     */
    void setSearchIndex(int index);

private:

    int curIndex;                                   // 当前学生索引
    int searchIndex;                                // 搜索索引
    const Manager& manager;                         // 管理器引用

};

