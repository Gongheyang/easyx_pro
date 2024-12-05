#include "Snake.h"  
#include <conio.h>  
#include <stdio.h>
#include <stdlib.h>
#include "public.h"


Snake::Snake()
{
    m_head = NULL;
    m_last = NULL;
    m_now = NULL;
}

Snake::~Snake()
{

}

void Snake::Init()			//初始化蛇的结构
{
    if (m_head != NULL)  //重玩游戏时，释放原先的链表所有结点
    {
        for (m_now = m_head->next;m_now->next != NULL;m_now = m_now->next)
        {
            free(m_now->prior);
        }
    }
    m_head = (struct node*)malloc(sizeof(struct node));  //为蛇头分配内存
    m_head->prior = NULL;
    m_head->m_x = 300;
    m_head->m_y = 300;
    m_head->m_type = 1;
    m_now = (struct node*)malloc(sizeof(struct node));
    m_head->next = m_now;
    m_now->prior = m_head;
    m_now->next = NULL;
    m_now->m_x = 300;
    m_now->m_y = 290;
    m_now->m_type = 2;
    m_last = m_now;
    m_toward = DOWN;
}

void Snake::SnakeAdd()
{
    m_now = m_head;			//当前指向蛇头
    m_now->prior = (struct node*)malloc(sizeof(struct node));  //为新增的结点分配内存
    m_now = m_now->prior;	//让当前指向新分配的结点
    m_now->prior = NULL;  //置空当前结点的前趋
    m_now->next = m_head;	//让当前结点的后继指向蛇头

    switch (m_toward)		//根据当前蛇头方向确定新增部分的坐标
    {
    case UP:
        m_now->m_x = m_head->m_x;
        m_now->m_y = m_head->m_y - 10;
        break;
    case DOWN:
        m_now->m_x = m_head->m_x;
        m_now->m_y = m_head->m_y + 10;
        break;
    case LEFT:
        m_now->m_x = m_head->m_x - 10;
        m_now->m_y = m_head->m_y;
        break;
    case RIGHT:
        m_now->m_x = m_head->m_x + 10;
        m_now->m_y = m_head->m_y;
        break;
    }
    m_head->m_type = 0;  //蛇头变蛇身
    m_head = m_now; //设置当前结点为蛇头

}

void Snake::SnakeDel()		//释放蛇尾结点（删除蛇尾）
{
    m_last = m_last->prior;
    free(m_last->next);
    m_last->next = NULL;
}

void Snake::SnakeMove()	//蛇身移动一格
{
    SnakeAdd();		//增加蛇头
    SnakeDel();		//删除蛇尾
}

