#include "GameArea.h"
#include <graphics.h>
#include <time.h>



Cell::Cell()  //构造函数
{
    m_x = 0, m_y = 0, m_full = 0;
    m_color = BLACK;
}

void Cell::setxy(short x, short y)
{
    m_x = x, m_y = y;
}

void Cell::setfull(short full)
{
    m_full = full;
}

void Cell::LaserDisplay()
{
    IMAGE image(10, 10);
    SetWorkingImage(&image);
    DWORD* pMem = GetImageBuffer(&image);
    for (int i = 0; i < 10 * 10; i++)
        pMem[i] = BGR(RGB(0, 0, i * 256 / (10 * 10)));
    SetWorkingImage(NULL);
    putimage(m_x, m_y, &image);
}

short Cell::ReturnFull()  //返回格子状态
{
    return m_full;
}

void Cell::display(COLORREF color)
{
    m_color = color;

    //if (m_full == 1)
    //{    
    //    setfillcolor(m_color);
    //    setfillstyle(BS_SOLID);
    //    bar(m_x, m_y, m_x + 7, m_y + 7);
    //} 
    //else
    //{
    //    setcolor(m_color);
    //    setfillstyle(BS_NULL);
    //    fillcircle(m_x + 4, m_y + 4, 4);
    //}

    switch (m_full)
    {
    case 1:
        setfillcolor(m_color);
        setfillstyle(BS_SOLID);
        bar(m_x, m_y, m_x + 7, m_y + 7);
        break;
    case 3:
        setcolor(m_color);
        setfillstyle(BS_SOLID);
        fillcircle(m_x - 2, m_y - 2, 1);
        fillcircle(m_x + 2, m_y - 2, 1);
        fillcircle(m_x + 4, m_y + 4, 4);
        break;
    //case 5:
    //    break;
    default:
        setcolor(m_color);
        setfillstyle(BS_NULL);
        fillcircle(m_x + 4, m_y + 4, 4);
        break;
    }
}



GameArea::GameArea()
{
    memset(m_game, 0, sizeof(m_game));
}

GameArea::~GameArea()
{

}

bool GameArea::CreatFood()
{
    srand(time(NULL));			//初始化随机数种子
    m_random1 = rand() % 58 + 1;		//随机生成一个0 - 58的整数
    m_random2 = rand() % 58 + 1;		//随机一个0 - 58的整数

    //检查生成的食物坐标是否在障碍上
    if (m_game[m_random2][m_random2].m_full == 0)
    {
        m_game[m_random1][m_random2].display(GREEN);
        m_game[m_random1][m_random2].m_full = 2;
        return true;
    }
    //如果随机的食物正好出现在蛇身上，则进入下面的循环寻找可以生成食物的地方
    for (m_random1 = 1;m_random1 < 59;m_random1++)
    {
        for (m_random2 = 1;m_random2 < 59;m_random2++)
        {
            if (m_game[m_random2][m_random2].m_full == 0)
            {
                m_game[m_random1][m_random2].display(GREEN);
                m_game[m_random1][m_random2].m_full = 2;
                return true;
            }
        }
    } 

    //如果没有找到可以生成食物的地方，则通关
    return false;  //返回false即表示通关
}

void GameArea::DelFood()	//删除食物
{
    m_game[m_random1][m_random2].m_full = 0;  //设置为0即代表格子属性为空
}

void GameArea::ChangeColor(int flag1, int flag2, COLORREF color)  //设置指定格子的颜色
{
    m_game[flag1][flag2].display(color);
}

void GameArea::Init()					//初始化GAME区域
{
    int flag1 = 0, flag2 = 0;	//标识变量 

    BeginBatchDraw();		    //开始批量绘图 
    setfillstyle(BLACK);	    //设置当前颜色
    setfillcolor(BLACK);        //置黑背景
    bar(0, 0, 600, 600);		//画无边框填充矩形（在这里的用途是用黑色清空游戏区域）
    for (flag1 = 0;flag1 < 60;flag1++)
    {
        for (flag2 = 0;flag2 < 60;flag2++)
        {
            if (flag1 == 0 || flag1 == 59 || flag2 == 0 || flag2 == 59)	//创建边界
            {
                m_game[flag1][flag2].setfull(1);
                m_game[flag1][flag2].setxy(flag1 * 10, flag2 * 10);
                m_game[flag1][flag2].display(RGB(255, 0, 0));
            }
            else														//创建游戏区域
            {
                m_game[flag1][flag2].setfull(0);
                m_game[flag1][flag2].setxy(flag1 * 10, flag2 * 10);
                m_game[flag1][flag2].display(BLACK);
            }
        }
    }
    CreatFood();
    EndBatchDraw();

    BeginBatchDraw();		    //开始批量绘图 
    setfillcolor(BLACK);        //重置置黑背景色 
    EndBatchDraw();
}



ManageArea::ManageArea()
{

}

ManageArea::~ManageArea()
{

}

void ManageArea::TimeAdd(double add)	//增加时间（可在类外直接调用实现动态刷新时间）
{
    m_time += add;
    DisplayTime();
}
void ManageArea::ScoreAdd(short add)	//增加分数（可在类外直接调用实现动态刷新分数）
{
    m_score += add;
    DisplayScore();
}
void ManageArea::DisplayPause()			//显示暂停或者开始
{
    BeginBatchDraw();
    _stprintf(m_str_score, _T("%d"), m_score);
    setfont(25, 0, _T("微软雅黑"));
    setfillcolor(m_bgcolor);
    bar(625, 440, 800, 465);
    setcolor(BLUE);
    if (m_pause)
        outtextxy(625, 440, _T("开始（P键）"));
    else
        outtextxy(625, 440, _T("暂停（P键）"));
    EndBatchDraw();
}

void ManageArea::Init()
{
    m_time = 0.0;
    m_score = 0;
    m_old_score = 0;
    m_leave = 1;
    m_pause = false;
    _stprintf(m_str_score, _T("%d"), m_score);  //格式化转换类型 
    _stprintf(m_str_old_score, _T("%d"), m_old_score);
    _stprintf(m_str_time, _T("%.1lf"), m_time);
    m_bgcolor = BLACK;

    BeginBatchDraw();
    setfillstyle(BLACK);
    bar(601, 0, 800, 600);

    setfont(60, 0, _T("微软雅黑"));
    setcolor(GREEN);
    outtextxy(625, 30, _T("贪吃蛇"));

    setfont(25, 0, _T("微软雅黑"));
    setcolor(BLUE);
    outtextxy(625, 280, _T("最高分："));
    outtextxy(625, 380, _T("时间："));
    outtextxy(625, 410, _T("分数："));
    outtextxy(625, 440, _T("暂停（P键）"));
    outtextxy(625, 470, _T("重新游戏（R键）"));
    setcolor(RED);
    outtextxy(710, 281, m_str_score);
    outtextxy(680, 381, m_str_time);
    outtextxy(680, 411, m_str_score);
    //outtextxy(720, 400, m_str_leave);      
    
    setfont(30, 0, _T("微软雅黑"));
    setcolor(RGB(128, 0, 255));
    outtextxy(625, 540, _T("制作："));
    setcolor(RGB(255, 0, 0));
    outtextxy(700, 541, _T("YGH"));
    EndBatchDraw();
}

void ManageArea::DisplayTime()
{
    BeginBatchDraw();
    _stprintf(m_str_time, _T("%.1lf"), m_time);
    setfont(25, 0, _T("微软雅黑"));
    setfillcolor(m_bgcolor);
    bar(680, 380, 800, 405);
    setcolor(RED);
    outtextxy(680, 381, m_str_time);
    EndBatchDraw();
}

void ManageArea::DisplayScore()
{
    BeginBatchDraw();
    _stprintf(m_str_score, _T("%d"), m_score);
    setfont(25, 0, _T("微软雅黑"));
    setfillcolor(m_bgcolor);
    bar(680, 410, 800, 435);
    setcolor(RED);
    outtextxy(680, 411, m_str_score);
    EndBatchDraw();
}



