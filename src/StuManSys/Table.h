/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@�ļ�    Table.h
 *@����    �����
 *
 *@����    GhY
 *@����    2024��12��5��
 *@�汾    v1.0.0
 *
 ****************************************************/
#pragma once

#include "Widget.h"
#include "Manager.h"
#include <sstream>

/*
 *@bref    �����
 */
class Table :
    public Widget
{
public:
    Table(const Manager& manager, int x = 0, int y = 0, int width = 100, int height = 60);

    /*
     *@bref    ��ʾ���
     */
    void show() const;

    /*
     *@bref    ��һҳ
     */
    void pageUp();

    /*
     *@bref    ��һҳ
     */
    void pageDown();

    /*
     *@bref    ��ʾ�༭����ַ���������
     */
    void showEditTable(const wchar_t* searchTerms);

    /*
     *@bref    ��ʾ�༭���ѧ��������
     */
    void showEditTable(int id);

    /*
     *@bref    ��ʾ�༭����±�������
     */
    void showTable(int index);

    /*
     *@bref    ��ȡ��������
     */
    int getSearchIndex() const;

    /*
     *@bref    ����ѧ������
     */
    void setSearchIndex(int index);

private:

    int curIndex;                                   // ��ǰѧ������
    int searchIndex;                                // ��������
    const Manager& manager;                         // ����������

};

