/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    judgment.h
 *@描述    欢乐五子棋
 *
 *@作者    GhY
 *@日期    2024年12月4日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma  once         
#include <windows.h>


/*
 *@bref    游戏胜负的判定 返回1表示胜负已定  返回0表示胜负未分
 */
int victory_judgment(COLORREF, int, int);

/*
 *@bref    人人模式游戏结束显示下棋顺序
 */
void array_gobang_steps();

/*
 *@bref    人机模式游戏结束显示机器下棋顺序
 */
void man_machine_array_steps();

/*
 *@bref    人机模式游戏结束显示人下棋顺序
 */
void man_array_steps();

/*
 *@bref    创建一个人机判断 死几活几的通解 参数分别是  颜色,  x坐标,   y坐标,  
 *         死活判断(1代表死,2代表活),  死几或者活几    返回1代表成立,返回0代表不成立
 */
int shpanduan(COLORREF, int, int, int, int);

/*
 *@bref    人机每一步分析可用棋子上的分数值,返回分数最高的就是落子点
 */
int score_analysis_judgment(int, int);
