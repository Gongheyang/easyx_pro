/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    Manager.h
 *@描述    管理器
 *
 *@作者    GhY
 *@日期    2024年12月5日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma once
#include "Student.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>



/*
 *@bref    管理器类
 */
class Manager
{
public:
    Manager();
    ~Manager();

    /*
     *@bref    读取文件到数据
     */
	bool read(const std::string& fileName);				

    /*
     *@bref    写入数据到文件
     */
	void write(const std::string& fileName) const;		

    /*
     *@bref    添加学生
     */
	void addStudent(const Student& student);			

    /*
     *@bref    按学号排序
     */
	void sortById();									
                      
    /*
     *@bref    按总分排序
     */
	void sortByScore();									

    /*
     *@bref    获取学生数据
     */
	const Student& getStudent(int index) const;			

    /*
     *@bref    修改学生
     */
	void setStudent(int index, const Student& student);	
    
    /*
     *@bref    删除学生
     */
	void deleteStudent(int index);						

    /*
     *@bref    学生数量
     */
	int size() const;									

    /*
     *@bref    按姓名搜索学生
     */
	int search(const wchar_t* searchTerms) const;		

    /*
     *@bref    按学号搜索学生
     */
	int search(int id) const;							

    /*
     *@bref    清空所有学生
     */
	void clear();										

    void update();

protected:
	std::vector<Student> m_students;				    // 学生数据


};