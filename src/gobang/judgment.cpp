#include "judgment.h" 
#include "easyx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "public.h"

extern int g_color;
extern post array[];
extern alph machine_array[];

int victory_judgment(COLORREF cl, int x, int y)
{
    int a, b;
    //定义上下总个数
    int i = 0;
    a = x;
    b = y;

    //先检查上面的
    while (cl == getpixel(a - 3, b - 3 - 25))
    {
        i++;
        b -= 25;
    }
    //还原落子位置
    a = x;
    b = y;
    //再检查下面的
    while (cl == getpixel(a - 3, b - 3 + 25))
    {
        i++;
        b += 25;
    }
    //还原落子位置
    a = x;
    b = y;
    if (i >= 4)
    {
        return 1;
    }

    //定义左右总个数
    int j = 0;
    a = x;
    b = y;
    //先检查左面的
    while (cl == getpixel(a - 3 - 25, b - 3))
    {
        j++;
        a -= 25;
    }
    //还原落子位置
    a = x;
    b = y;
    //再检查下面的
    while (cl == getpixel(a - 3 + 25, b - 3))
    {
        j++;
        a += 25;
    }
    //还原落子位置
    a = x;
    b = y;
    if (j >= 4)
    {
        return 1;
    }

    //定义'\'总个数
    int k = 0;
    a = x;
    b = y;
    //先检查上面的
    while (cl == getpixel(a - 3 - 25, b - 3 - 25))
    {
        k++;
        a -= 25;
        b -= 25;
    }
    //还原落子位置
    a = x;
    b = y;
    //再检查下面的
    while (cl == getpixel(a - 3 + 25, b - 3 + 25))
    {
        k++;
        a += 25;
        b += 25;
    }
    //还原落子位置
    a = x;
    b = y;
    if (k >= 4)
    {
        return 1;
    }


    //定义'/'总个数
    int l = 0;
    a = x;
    b = y;
    //先检查上面的
    while (cl == getpixel(a - 3 + 25, b - 3 - 25))
    {
        l++;
        a += 25;
        b -= 25;
    }
    //还原落子位置
    a = x;
    b = y;
    //再检查下面的
    while (cl == getpixel(a - 3 - 25, b - 3 + 25))
    {
        l++;
        a -= 25;
        b += 25;
    }
    //还原落子位置
    a = x;
    b = y;
    if (l >= 4)
    {
        return 1;
    }
    return 0;
}

void array_gobang_steps()
{
    //主要实现的功能是在黑色的棋上显示白色顺序  在白色棋子上显示黑色的顺序
    for (int i = 0; i <= g_color; i++)
    {
        if (i % 2 == 0)
        {
            setbkcolor(RGB(0, 0, 0));
            char arr[10];
            sprintf_s(arr, "%-2d", i + 1);
            settextcolor(RGB(255, 255, 255));
            settextstyle(15, 0, "宋体");
            outtextxy(array[i].x - 7, array[i].y - 7, arr);
        }
        else
        {
            setbkcolor(RGB(255, 255, 255));
            char arr[10];
            sprintf_s(arr, "%-2d", i + 1);
            settextcolor(RGB(0, 0, 0));
            settextstyle(15, 0, "宋体");
            outtextxy(array[i].x - 7, array[i].y - 7, arr);
        }
    }
    //恢复了背景颜色
    setbkcolor(RGB(249, 237, 225));
}

void man_machine_array_steps()
{
    //  在白色棋子上显示黑色的顺序
    for (int i = 0; i <= g_color; i++)
    {
        if (i % 2 != 0)
        {
            setbkcolor(RGB(255, 255, 255));
            char arr[10];
            sprintf_s(arr, "%-2d", i + 1);
            settextcolor(RGB(0, 0, 0));
            settextstyle(15, 0, "宋体");
            outtextxy(machine_array[i].x - 7, machine_array[i].y - 7, arr);
        }
    }
    //恢复了背景颜色
    setbkcolor(RGB(249, 237, 225));
}

void man_array_steps()
{
    //  在黑色棋子上显示白色的顺序
    for (int i = 0; i <= g_color; i++)
    {
        if (i % 2 == 0)
        {
            setbkcolor(RGB(0, 0, 0));
            char arr[10];
            sprintf_s(arr, "%-2d", i + 1);
            settextcolor(RGB(255, 255, 255));
            settextstyle(15, 0, "宋体");
            outtextxy(array[i].x - 7, array[i].y - 7, arr);
        }
    }
    //恢复了背景颜色
    setbkcolor(RGB(249, 237, 225));
}

int shpanduan(COLORREF cl, int x, int y, int q, int p)
{
    //用一个K来体现某一个方向的下一个是背景而不是有另外颜色的(活) K = 1 表示下一个为背景色
    int K = 0;
    int a, b;
    //定义上下总个数
    int i = 0;
    a = x;
    b = y;
    //先检查上面的
    while (cl == getpixel(a - 3, b - 3 - 25))
    {
        i++;
        b -= 25;
    }
    //检查是否下一个是背景色
    if (getpixel(a - 3, b - 3 - 25) == RGB(248, 203, 18) && b - 25 > 350)
    {
        K++;
    }
    //还原落子位置
    a = x;
    b = y;
    //再检查下面的
    while (cl == getpixel(a - 3, b - 3 + 25))
    {
        i++;
        b += 25;
    }
    //检查是否下一个是背景色
    if (getpixel(a - 3, b - 3 + 25) == RGB(248, 203, 18) && b + 35 < 700)
    {
        K++;
    }
    //还原落子位置
    a = x;
    b = y;
    if (i == p - 1 && K == q)
    {
        return 1;      ///////////////////////////////////////////////
    }

    //重置K
    K = 0;
    //定义左右总个数
    int j = 0;
    a = x;
    b = y;
    //先检查左面的
    while (cl == getpixel(a - 3 - 25, b - 3))
    {
        j++;
        a -= 25;
    }
    //检查是否下一个是背景色
    if (getpixel(a - 3 - 25, b - 3) == RGB(248, 203, 18) && a - 35 > 50)
    {
        K++;
    }
    //还原落子位置
    a = x;
    b = y;
    //再检查下面的
    while (cl == getpixel(a - 3 + 25, b - 3))
    {
        j++;
        a += 25;
    }
    //检查是否下一个是背景色
    if (getpixel(a - 3 + 25, b - 3) == RGB(248, 203, 18) && a + 35 < 700)
    {
        K++;
    }
    //还原落子位置
    a = x;
    b = y;
    if (j == p - 1 && K == q)
    {
        return 1;     ////////////////////////////////////////////
    }

    //重置K
    K = 0;
    //定义'\'总个数
    int k = 0;
    a = x;
    b = y;
    //先检查上面的
    while (cl == getpixel(a - 3 - 25, b - 3 - 25))
    {
        k++;
        a -= 25;
        b -= 25;
    }
    //检查是否下一个是背景色
    if (getpixel(a - 3 - 25, b - 3 - 25) == RGB(248, 203, 18) && a - 25 > 50 && b - 25 > 350)
    {
        K++;
    }
    //还原落子位置
    a = x;
    b = y;
    //再检查下面的
    while (cl == getpixel(a - 3 + 25, b - 3 + 25))
    {
        k++;
        a += 25;
        b += 25;
    }
    //检查是否下一个是背景色
    if (getpixel(a - 3 + 25, b - 3 + 25) == RGB(248, 203, 18) && a + 25 < 400 && b + 25 < 700)
    {
        K++;
    }
    //还原落子位置
    a = x;
    b = y;
    if (k == p - 1 && K == q)
    {
        return 1;    //////////////////////////
    }

    //重置K
    K = 0;
    //定义'/'总个数
    int l = 0;
    a = x;
    b = y;
    //先检查上面的
    while (cl == getpixel(a - 3 + 25, b - 3 - 25))
    {
        l++;
        a += 25;
        b -= 25;
    }
    //检查是否下一个是背景色
    if (getpixel(a - 3 + 25, b - 3 - 25) == RGB(248, 203, 18) && a + 25 < 400 && b - 25 > 350)
    {
        K++;
    }
    //还原落子位置
    a = x;
    b = y;
    //再检查下面的
    while (cl == getpixel(a - 3 - 25, b - 3 + 25))
    {
        l++;
        a -= 25;
        b += 25;
    }
    //检查是否下一个是背景色
    if (getpixel(a - 3 - 25, b - 3 + 25) == RGB(248, 203, 18) && a - 25 > 50 && b + 25 < 700)
    {
        K++;
    }
    //还原落子位置
    a = x;
    b = y;
    if (l == p - 1 && K == q)
    {
        return 1;    /////////////////////////////////////////
    }
    return 0;
}

int score_analysis_judgment(int x, int y)
{
    /*
    ———————————————————————————
    主要思想
    电脑白子  自己黑子
    白子连成五子    +10000    阻黑子连成五子    +1000
    白子连成活四    +200      阻黑子连成活四    +100
    白子连成死四    +50       阻黑子连成死四    +20
    白子连成活三    +30       阻黑子连成活三    +10
    白子连成死三    +8        阻黑子连成死三    +5
    白子连成活二    +2        阻黑子连成活二    +1
    白子连成死二    +2        阻黑子连成死二    +1
    白子连成活一    +1        阻黑子连成活一    +0
    白子连成死一    +1        阻黑子连成死一    +0
    ———————————————————————————
    */

    int a = x;
    int b = y;
    //定义一个得分
    int score = 0;

    //白子连成五子    +10000
    if (victory_judgment(RGB(255, 255, 255), a, b))    //这个函数只是i的值与k的值不一样 所以可以加两个变量在函数里面
    {
        score += 10000;
    }
    //阻碍黑子连成五子    +1000
    if (victory_judgment(RGB(0, 0, 0), a, b))
    {
        score += 1000;
    }
    //白子连成活四    +200
    if (shpanduan(RGB(255, 255, 255), a, b, 2, 4))
    {
        score += 200;
    }
    //阻碍黑子连成活四    +100
    if (shpanduan(RGB(0, 0, 0), a, b, 2, 4))
    {
        score += 100;
    }
    //白子连成死四    +50
    if (shpanduan(RGB(255, 255, 255), a, b, 1, 4))
    {
        score += 50;
    }
    //阻碍黑子连成死四    +20
    if (shpanduan(RGB(0, 0, 0), a, b, 1, 4))
    {
        score += 20;
    }
    //白子连成活三    +30
    if (shpanduan(RGB(255, 255, 255), a, b, 2, 3))
    {
        score += 30;
    }
    //阻碍黑子连成活三    +10
    if (shpanduan(RGB(0, 0, 0), a, b, 2, 3))
    {
        score += 10;
    }
    //白子连成死三    +8
    if (shpanduan(RGB(255, 255, 255), a, b, 1, 3))
    {
        score += 8;
    }
    //阻碍黑子连成死三    +5
    if (shpanduan(RGB(0, 0, 0), a, b, 1, 3))
    {
        score += 5;
    }
    //白子连成活二    +2
    if (shpanduan(RGB(255, 255, 255), a, b, 2, 2))
    {
        score += 2;
    }
    //阻碍黑子连成活二    +1
    if (shpanduan(RGB(0, 0, 0), a, b, 2, 2))
    {
        score += 1;
    }
    //白子连成死二    +2
    if (shpanduan(RGB(255, 255, 255), a, b, 1, 2))
    {
        score += 2;
    }
    //阻碍黑子连成死二    +1
    if (shpanduan(RGB(0, 0, 0), a, b, 1, 2))
    {
        score += 1;
    }
    //白子连成活一    +1
    if (shpanduan(RGB(255, 255, 255), a, b, 2, 1))
    {
        score += 1;
    }
    /* //阻碍黑子连成活一    +0
    if()
    {
    score += 0;
    }*/
    //白子连成死一    +1
    if (shpanduan(RGB(255, 255, 255), a, b, 1, 1))
    {
        score += 1;
    }
    /* //阻碍黑子连成死一    +0
    if()
    {
    score += 0;
    }*/

    return score;
}

