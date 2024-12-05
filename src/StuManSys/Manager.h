/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@�ļ�    Manager.h
 *@����    ������
 *
 *@����    GhY
 *@����    2024��12��5��
 *@�汾    v1.0.0
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
 *@bref    ��������
 */
class Manager
{
public:
    Manager();
    ~Manager();

    /*
     *@bref    ��ȡ�ļ�������
     */
	bool read(const std::string& fileName);				

    /*
     *@bref    д�����ݵ��ļ�
     */
	void write(const std::string& fileName) const;		

    /*
     *@bref    ���ѧ��
     */
	void addStudent(const Student& student);			

    /*
     *@bref    ��ѧ������
     */
	void sortById();									
                      
    /*
     *@bref    ���ܷ�����
     */
	void sortByScore();									

    /*
     *@bref    ��ȡѧ������
     */
	const Student& getStudent(int index) const;			

    /*
     *@bref    �޸�ѧ��
     */
	void setStudent(int index, const Student& student);	
    
    /*
     *@bref    ɾ��ѧ��
     */
	void deleteStudent(int index);						

    /*
     *@bref    ѧ������
     */
	int size() const;									

    /*
     *@bref    ����������ѧ��
     */
	int search(const wchar_t* searchTerms) const;		

    /*
     *@bref    ��ѧ������ѧ��
     */
	int search(int id) const;							

    /*
     *@bref    �������ѧ��
     */
	void clear();										

    void update();

protected:
	std::vector<Student> m_students;				    // ѧ������


};