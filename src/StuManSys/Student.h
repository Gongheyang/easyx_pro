/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    Student.h
 *@描述    学生类
 *
 *@作者    GhY
 *@日期    2024年12月5日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma once

#include <string>

/*
 *@bref    学生类
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
	 *@bref    重载运算符，使学生对象可以进行排序
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
     *@bref    按学号升序排序
     */
	bool operator<(const Student& stu) const
	{
		return (this->_id < stu._id);
	}

    /*
     *@bref    按总分升序排序
     */
	bool operator>(const Student& stu) const
	{
		return this->_score > stu._score;
	}

    Student& operator=(const Student& o) {
        if (this == &o) {
            return *this; // 处理自我赋值
        }
        this->_id = o._id;
        std::wcscpy(this->_name, o._name);
        std::wcscpy(this->_class, o._class);
        this->_score = o._score;
        return *this;
    }
public:

    unsigned short _id;		// 学号
    wchar_t _name[10];		// 姓名
    wchar_t _class[10];		// 班级
    unsigned short _score;	// 总分

};