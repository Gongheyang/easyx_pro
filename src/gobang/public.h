/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    public.h
 *@描述    欢乐五子棋
 *
 *@作者    GhY
 *@日期    2024年12月4日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma  once



//设置光标结构体类型
typedef struct
{
    int x;
    int y;
} post;

//设置人机结构体类型
typedef struct
{
    int x;
    int y;
    int score;
} alph;



#define TEXT_CONTINUE_GAME  "(请按任意键继续游戏)"
#define TEXT_TYPE           "华文新魏"
#define TEXT_TIMETOCHESS    "轮到棋子:"
