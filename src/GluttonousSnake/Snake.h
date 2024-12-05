/****************************************************
*
*@Copyright (c) 2014-2024, GhY, All rights reserved.
*@文件    Snake.h
*@描述    蛇类，定义蛇的数据结构以及蛇的行为
*
*@作者    GhY
*@日期    2024年11月28日
*@版本    v1.0.0
*
****************************************************/
#ifndef __SNAKE_H__
#define __SNAKE_H__

class Snake
{
public:
	struct node				 //蛇身链表
	{
		int m_x;
		int m_y;
        int m_type;         // 0为蛇身 1为蛇头 2为蛇巴
		struct node *next;  //下个结点
		struct node *prior; //上个结点
	};

public:

	Snake();

    ~Snake();

	void Init();		//初始化蛇的结构
    
	void SnakeAdd();    //添加蛇身

	void SnakeDel();	//释放蛇尾结点（删除蛇尾）

	void SnakeMove();	//蛇身移动一格
    
public:

	int m_toward;		//蛇头朝向
   
	struct node *m_head;
	struct node *m_last;
	struct node *m_now; 

private:

};

#endif  //!__SNAKE_H__
