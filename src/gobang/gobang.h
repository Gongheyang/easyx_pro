/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    gobang.h
 *@描述    欢乐五子棋
 *
 *@作者    GhY
 *@日期    2024年12月4日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma  once
#include "public.h"


//用一个数的奇偶性来判断产生棋子的黑白     偶数表示黑棋    当color == 225的时候表明平局
extern int g_color = 0;

//定义一个稍微大一点的结构体数组来存放每一步棋子顺序(人人)
extern post array[1000] = { 0 };

//定义一个稍微大一点的结构体数组来存放每一步棋子顺序(人机)
extern alph machine_array[1000] = { 0 };



/*
 *@bref    绘制棋盘
 */
void draw_chessboard();

/*
 *@bref	游戏初始化
 */
void initgame();

/*
*@bref    人人游戏进行
*/
void game_start();

/*
*@bref    人机游戏进行
*/
void man_machine_game_start();

/*
 *@bref     游戏结束释放资源
 */
void gameover();

/*
 *@bref    绘制主界面文字
 */
void drawbackgroundtext(const int type);

/*
 *@bref    重新开始
 */
void restart();

/*
 *@bref    主函数
 */
int main();