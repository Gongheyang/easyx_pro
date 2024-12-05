/****************************************************
*
*@Copyright (c) 2014-2024, GhY, All rights reserved.
*@文件    GluttonousSnake.cpp
*@描述    贪吃蛇
*
*@作者    GhY
*@日期    2024年11月28日
*@版本    v1.0.0
*
****************************************************/
#pragma once
#include <stdio.h>
#include <conio.h>
#include <time.h>   
#include <graphics.h>
#include "Snake.h"
#include "Game.h"
#include "GameArea.h"
#include "public.h"
#include "GluttonousSnake.h"



Game		game;		//用于初始化游戏、设置游戏相关参数
GameArea	area;		//用于初始化游戏区域，设置，改变游戏区域相关参数
ManageArea	manager;	//用于初始化管理区域，设置管理区相关参数
Snake		s;			//用于初始化蛇，数据化蛇，操作蛇


void MessageDispose()
{
    char c;
    s.m_now = NULL;
    bool Keepdown = false;

    while (true)
    {
        Keepdown = false;  //是否持续按W A S D 中的一个按键
        if (_kbhit())
        {
            switch (c = _getch())  //处理按键消息（W A S D）
            {
            case 'w':
            case 'W':
                if (s.m_toward == UP) {
                    Keepdown = true;
                }
                else if (s.m_toward != DOWN && s.m_toward != UP) {
                    s.m_toward = UP;
                }
                break;
            case 's':
            case 'S':
                if (s.m_toward == DOWN) {
                    Keepdown = true;
                }
                else if (s.m_toward != UP && s.m_toward != DOWN) {
                    s.m_toward = DOWN;
                }
                break;
            case 'a':
            case 'A':
                if (s.m_toward == LEFT) {
                    Keepdown = true;
                }
                else if (s.m_toward != RIGHT&&s.m_toward != LEFT) {
                    s.m_toward = LEFT;
                }
                break;
            case 'd':
            case 'D':
                if (s.m_toward == RIGHT) {
                    Keepdown = true;
                }
                else if (s.m_toward != LEFT && s.m_toward != RIGHT) {
                    s.m_toward = RIGHT;
                }
                break;
            case 'p':
            case 'P':
                manager.m_pause = !manager.m_pause;	//设置暂停或开始
                manager.DisplayPause();	//显示暂停或开始
                break;
            case 'r':
            case 'R':
                ReInit();
                break;
            default:
                break;
            }
        }
        if (true == manager.m_pause)	//如果暂停，直接进行下次循环
        {
            continue;
        }

        BeginBatchDraw();
        switch (area.m_game[s.m_head->m_x / 10][s.m_head->m_y / 10].ReturnFull())	//检测蛇头遇到的情况
        {
        case 2:				
            //遇到食物，蛇身加长
            area.ChangeColor(s.m_head->m_x / 10, s.m_head->m_y / 10, BLUE);
            s.SnakeAdd();	//蛇增长
            area.ChangeColor(s.m_head->m_x / 10, s.m_head->m_y / 10, BLUE);
            area.DelFood();	//删除食物
            if (area.CreatFood() == false)	//创建新食物,并检查是否通关
            {
                game.WinGame();			//游戏通关（当地图没地方创建食物时）
            }
            manager.ScoreAdd(1);		//加一分
            break;
        case 0:
            area.m_game[s.m_last->m_x / 10][s.m_last->m_y / 10].setfull(0);				//设置蛇尾经过处无障碍
            area.ChangeColor(s.m_last->m_x / 10, s.m_last->m_y / 10, BLACK);
            s.SnakeMove();  //蛇移动一次
            area.ChangeColor(s.m_head->m_x / 10, s.m_head->m_y / 10, BLUE);
            area.m_game[s.m_head->next->m_x / 10][s.m_head->next->m_y / 10].setfull(1);	//设置蛇头经过处有障碍
            break;
        case 1:				
            //遇到障碍物
            game.FailGame();
            area.ChangeColor(s.m_head->m_x / 10, s.m_head->m_y / 10, RGB(255, 127, 39));
            {
                char c = ' ';
                while (c != 'r' && c != 'R')  //当游戏失败时，按R键可重新进行游戏
                {
                    if (_kbhit())
                    {
                        c = _getch();
                    }
                    Sleep(10);
                }
            }
            ReInit(); //重新开始游戏
            break;
        }
        FlushBatchDraw();
        EndBatchDraw();

        if (Keepdown == false)
        {
            Sleep(100);
            manager.TimeAdd(0.1);	//增加时间
        }
        else						//当持续按下按方向键时
        {
            Sleep(40);				//适当休眠可以增加游戏流畅性
            manager.TimeAdd(0.04);  //增加时间
        }
    }
}


void ReInit()
{  
    Start();
}

void Start()
{
    area.Init();        //初始化游戏区
    s.Init();           //初始化蛇
    manager.Init();     //初始化管理区

                        //绘制蛇的开始状态
    s.m_now = s.m_head;
    area.ChangeColor(s.m_now->m_x / 10, s.m_now->m_y / 10, BLUE);
    s.m_now = s.m_last;
    area.ChangeColor(s.m_now->m_x / 10, s.m_now->m_y / 10, BLUE);
}

int main(void)
{
    game.Init();		    //初始化游戏参数、设置

    HWND hwd = GetHWnd();
    SetWindowTextW(hwd, _T("贪吃蛇"));

    Start();
    MessageDispose();
    game.Close();
    return 0;
}
