/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    main.cpp
 *@描述    学生成绩管理系统
 *
 *@作者    GhY
 *@日期    2024年12月5日
 *@版本    v1.0.0
 *
 ****************************************************/
#include "Window.h"

int main()
{
	Window window(502, 420);
	window.show();
	window.messageLoop();
	return 0;
}