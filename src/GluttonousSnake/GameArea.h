/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    GameArea.h
 *@描述    游戏格子、区域类
 *
 *@作者    GhY
 *@日期    2024年11月28日
 *@版本    v1.0.0
 *
 ****************************************************/
#ifndef __GAMEAREA_H__
#define __GAMEAREA_H__
#include <stdio.h>
#include <conio.h>    
#include <wtypes.h>



////////////////////////////////////////////
//格子类，定义一个格子的属性及行为
////////////////////////////////////////////
class Cell
{
public:

	Cell();  //构造函数
    
	friend class GameArea;  //设置友元函数

	void setxy(short x, short y);   //设置格子左上角坐标
    
	void setfull(short full);  //设置格子属性，0为空，1为障碍，2为食物 3为蛇头 4为蛇身 5为蛇巴
    
	void display(COLORREF color);  //设置格子颜色并显示
    
	void LaserDisplay();  //显示镭射状态的格子
    
	short ReturnFull();  //返回格子状态
    

private:

	short m_x;			//格子的左上角X坐标
	short m_y;			//格子的左上角Y坐标
	short m_full;		//0为空，1为阻挡，2为食物 3为蛇头 4为蛇身 5为尾巴
	COLORREF m_color;	//格子颜色
};


////////////////////////////////////////////
//游戏区类，编写有关游戏区的一些操作
////////////////////////////////////////////
class GameArea  //游戏区域
{
public:
    GameArea();
    ~GameArea();

	friend void MessageDispose();	//设置友元函数

	void Init();				    //初始化GAME区域

	bool CreatFood();               //产生随机食物
    
	void DelFood();	                //删除食物

    void ChangeColor(int flag1, int flag2, COLORREF color);  //设置指定格子的颜色

public:
	Cell m_game[60][60];			//定义游戏区域（由360个格子组成）
    
private:

	int m_random1, m_random2;
};


////////////////////////////////////////////
//管理区类，定义管理区域的相关操作
////////////////////////////////////////////
class ManageArea  
{
public:
    ManageArea();
    ~ManageArea();

	friend void MessageDispose();

	void TimeAdd(double add);	//增加时间（可在类外直接调用实现动态刷新时间）
    
	void ScoreAdd(short add);	//增加分数（可在类外直接调用实现动态刷新分数）
    
	void DisplayPause();		//显示暂停或者开始

	void Init();  //初始化管理界面

private:

	void DisplayTime();  //显示当前耗时
    
	void DisplayScore();  //显示当前分数

private:

	double	m_time;     // 时间
    short	m_score;    // 分数
	short	m_leave;
	bool	m_pause;
    TCHAR	m_str_leave[2];
    TCHAR   m_str_time[33], m_str_score[5]; 
    short	m_old_score;    // 历史最高分数
    TCHAR   m_str_old_score[5]; // 历史最高分
	COLORREF m_bgcolor;

	
};


#endif   //!__GAMEAREA_H__
