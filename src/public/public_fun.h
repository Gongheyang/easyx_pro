/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    public_fun.h
 *@描述    公共函数
 *
 *@作者    GhY
 *@日期    2024年12月4日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma  once    
#include <stdio.h>
#include <string.h>


#define IN
#define OUT 

/*
 *@bref    生成随机数 【x1, x2】
 */
int create_random(int x1, int x2);

/*
 *@bref    获取当前工作目录
 */
void get_current_directory(IN OUT char* root);

/*
 *@bref    获取当前工作目录的上级目录
 */
void get_parent_directory(IN OUT char* root);

void getFileFullPath(IN char* root, IN char* file, OUT char* fullpath);

const char* wctoch(IN wchar_t * wstr);

const wchar_t* chtowc(IN char * ch);