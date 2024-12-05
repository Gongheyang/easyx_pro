/****************************************************
 *
 *@功能描述	欢乐五子棋
 *
 *@作者		GongheYang
 *@日期		2021年8月8日
 *
 ****************************************************/
#pragma once
#include <Windows.h>


#define N 65

int status[N][N] = { { 0 }, { 0 } }; //记录棋盘情况,0无，1红棋/玩家，2为白棋/电脑

int flag = 0;//判断输赢

int direct[2] = { 0 };//方向

int Value1[N][N] = { { 0 }, { 0 } }; //计算权值

int Value2[N][N] = { { 0 }, { 0 } }; //计算权值

int regrex(0), regrey(0), regrex1(0), regrey1(0);

int count = 0;//计算棋子数量


void chess_board();//打印棋盘

void red_movexy();//红子棋移动光标

void white_movexy();//白棋移动光标

void red_chess(int x, int y);//红棋

void white_chess(int x, int y);//白棋

void man_man();

void man_machine();//人机对战

int judge_chess(int x, int y);//判断这个位置是否下过

int judge_winner(int x, int y, int temp);//判断输赢

void machine_attack();//电脑进攻权值

void machine_defend();//电脑防守权值

void find_position();//寻找最佳权值

void Regret();//悔棋函数

void welcome();//游戏菜单

char Gametips();//游戏帮助

char Updatediary(); //更新日志

void BackGround(unsigned int ForeColor, unsigned int BackGroundColor); //颜色

int main();