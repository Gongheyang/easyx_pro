/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@�ļ�    Student.h
 *@����    ѧ����
 *
 *@����    GhY
 *@����    2024��12��5��
 *@�汾    v1.0.0
 *
 ****************************************************/
#pragma once

#include <string>

/*
 *@bref    ѧ����
 */
class Student
{
public:
    Student()
    {
        _id = 0;
        memset(_name, 0, sizeof(_name));
        memset(_class, 0, sizeof(_class));
        _score = 0;
    }

    Student(unsigned short id, wchar_t* name, wchar_t* cla, unsigned short score)
    {
        _id = id;
        std::wcscpy(_name, name);
        std::wcscpy(_class, cla);
        _score =score;
    }
                                      
	/*
	 *@bref    �����������ʹѧ��������Խ�������
	 */
	bool operator==(const wchar_t* searchTerms) const
	{
		return std::wstring(_name) == searchTerms;
	}

	bool operator==(int id) const
	{
		return id == this->_id;
	}

    /*
     *@bref    ��ѧ����������
     */
	bool operator<(const Student& stu) const
	{
		return (this->_id < stu._id);
	}

    /*
     *@bref    ���ܷ���������
     */
	bool operator>(const Student& stu) const
	{
		return this->_score > stu._score;
	}

    Student& operator=(const Student& o) {
        if (this == &o) {
            return *this; // �������Ҹ�ֵ
        }
        this->_id = o._id;
        std::wcscpy(this->_name, o._name);
        std::wcscpy(this->_class, o._class);
        this->_score = o._score;
        return *this;
    }
public:

    unsigned short _id;		// ѧ��
    wchar_t _name[10];		// ����
    wchar_t _class[10];		// �༶
    unsigned short _score;	// �ܷ�

};