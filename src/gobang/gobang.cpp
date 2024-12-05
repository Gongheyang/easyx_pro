#include "gobang.h" 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <windows.h>
#include <time.h>

#include "public.h"
#include "easyx.h"
#include "graphics.h"
#include "judgment.h"
#include "public_fun.h"


#pragma comment(lib,"winmm.lib") //背景音乐



static char g_parRootpath[256] = { 0 };

//设置光标
post g_cursor;
//用一个开关来控制游戏的背景音乐;  奇数表示开
int g_bgm_switch = 1;

//人悔了一步棋,机器也要退回上一个的位置
alph g_machine_undo_pos;

//为了防止出现随意悔棋的情况  所以规定每个人只能悔当前下的棋  所以定义一个光标记录将要悔棋的地点
post g_undo_pos;


char* getFileFullPath(char* file)
{
    static char fullpath[256] = { 0 };
    sprintf_s(fullpath, "%s%s", g_parRootpath, file);
    return fullpath;
}

void drawbackgroundtext(const int type)
{
    settextcolor(RGB(0, 0, 0));
    settextstyle(48, 0, TEXT_TYPE);
    setbkmode(TRANSPARENT);
    outtextxy(10, 580, "开始游戏");
    outtextxy(290, 580, "退出游戏");
    outtextxy(10, 640, "温馨提示");
    outtextxy(290, 640, "联系我们");
    outtextxy(10, 700, "挑战人机");
    outtextxy(290, 700, "打赏我们");
    //改变颜色来显示出动态效果
    if (type == 1)
    {
        settextcolor(RGB(255, 0, 0));
        outtextxy(10, 580, "开始游戏");
    }
    if (type == 2)
    {
        settextcolor(RGB(255, 0, 0));
        outtextxy(290, 580, "退出游戏");
    }
    if (type == 3)
    {
        settextcolor(RGB(255, 0, 0));
        outtextxy(10, 640, "温馨提示");
    }
    if (type == 4)
    {
        settextcolor(RGB(255, 0, 0));
        outtextxy(290, 640, "联系我们");
    }
    if (type == 5)
    {
        settextcolor(RGB(255, 0, 0));
        outtextxy(10, 700, "挑战人机");
    }
    if (type == 6)
    {
        settextcolor(RGB(255, 0, 0));
        outtextxy(290, 700, "打赏我们");
    }
    else    // 0
    {
        //nothing
    }
}

void initgame()
{
    //设置窗口大小
    initgraph(500, 750);

    // 获得窗口句柄
    HWND hWnd = GetHWnd();

    // 使用 API 函数修改窗口名称
    SetWindowText(hWnd, "休闲五子棋");

    //设置背景颜色
    setbkcolor(RGB(249, 237, 225));    //目的是为了让显示的文字看起来没有边框

    //加载图片
    IMAGE backgrand;
    loadimage(&backgrand, getFileFullPath("/data/gobang/back.jpg"), 500, 750);
    putimage(0, 0, &backgrand);
    drawbackgroundtext(0);

    //游戏界面选择
    MOUSEMSG m;        // 定义鼠标消息

B:

    cleardevice(); //防止残留文字 
    //避免黑屏
    putimage(0, 0, &backgrand);
    drawbackgroundtext(0);

    while (true)
    {
        // 获取一条鼠标消息
        m = GetMouseMsg();

        //清除上一下鼠标缓存
        FlushMouseMsgBuffer();

        switch (m.uMsg)
        {
        case WM_MOUSEMOVE:
            do
            {
                if (m.x >= 10 && m.x <= 200 && m.y >= 580 && m.y <= 620)  //(10, 580, 200, 620)   开始游戏
                {
                    drawbackgroundtext(1);
                    break;
                }
                if (m.x >= 290 && m.x <= 480 && m.y >= 580 && m.y <= 620)  // (290, 580, 480, 620)  退出游戏
                {
                    drawbackgroundtext(2);
                    break;
                }
                if (m.x >= 10 && m.x <= 200 && m.y >= 640 && m.y <= 680) //  (10, 640, 200, 680)  温馨提示
                {
                    drawbackgroundtext(3);
                    break;
                }
                if (m.x >= 290 && m.x <= 480 && m.y >= 640 && m.y <= 680)  // (290, 640, 480, 680)   联系我们
                {
                    drawbackgroundtext(4);
                    break;
                }
                if (m.x >= 10 && m.x <= 200 && m.y >= 700 && m.y <= 740) //  (10,700,200,740) 进入人机挑战
                {
                    drawbackgroundtext(5);
                    break;
                }
                if (m.x >= 290 && m.x <= 480 && m.y >= 700 && m.y <= 740) //  (290,700,480,740) 打赏我们
                {
                    drawbackgroundtext(6);
                    break;
                }
                drawbackgroundtext(0);
            } while (0);
            break;
        case WM_LBUTTONDOWN:      //长是190  宽是40
            do
            {
                if (m.x >= 10 && m.x <= 200 && m.y >= 580 && m.y <= 620)  //(10, 580, 200, 620)   开始游戏
                {
                    goto A;
                }
                if (m.x >= 290 && m.x <= 480 && m.y >= 580 && m.y <= 620)  // (290, 580, 480, 620)  退出游戏
                {
                    //先释放资源
                    closegraph();
                    exit(0);
                }
                if (m.x >= 290 && m.x <= 480 && m.y >= 640 && m.y <= 680)  // (290, 640, 480, 680)   联系我们
                {
                    IMAGE call;
                    loadimage(&call, getFileFullPath("/data/gobang/Contact.jpg"), 500, 750);
                    putimage(0, 0, &call);
                    settextcolor(RGB(0, 0, 0));
                    settextstyle(40, 0, TEXT_TYPE);
                    outtextxy(60, 620, TEXT_CONTINUE_GAME);

                    system("pause");
                    goto B;
                }
                if (m.x >= 10 && m.x <= 200 && m.y >= 640 && m.y <= 680) //  (10, 640, 200, 680)  游戏说明 温馨提示
                {
                    IMAGE explain;
                    loadimage(&explain, getFileFullPath("/data/gobang/description.jpg"), 500, 750);
                    putimage(0, 0, &explain);
                    system("pause");
                    goto B;
                }
                if (m.x >= 290 && m.x <= 480 && m.y >= 700 && m.y <= 740) //  (290,700,480,740) 打赏我们
                {
                    IMAGE help;
                    loadimage(&help, getFileFullPath("/data/gobang/Reward.jpg"), 500, 750);
                    putimage(0, 0, &help);
                    settextcolor(RGB(0, 0, 0));
                    settextstyle(40, 0, TEXT_TYPE);
                    outtextxy(60, 620, TEXT_CONTINUE_GAME);

                    system("pause");
                    goto B;
                }
                if (m.x >= 10 && m.x <= 200 && m.y >= 700 && m.y <= 740) //  (10,700,200,740) 进入人机挑战
                {
                    man_machine_game_start();
                    break;
                }
            } while (0);
            break;
        default:
            //避免黑屏
            putimage(0, 0, &backgrand);
            drawbackgroundtext(0);
            break;
        }
    }

A:
    return;

}

void draw_chessboard()
{
    // 绘制棋盘 
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID);
    setfillcolor(RGB(248, 203, 18));
    fillrectangle(25, 325, 425, 725); //计算而来的
    for (int i = 1; i < 15; i++)
    {
        for (int j = 1; j < 15; j++)
        {
            rectangle(25 + j * 25, 325 + i * 25, 50 + j * 25, 350 + i * 25);  //棋盘左上是50 350

        }
    }
}

void game_start()
{
    //加载背景音乐                                                
    mciSendString("open \"../data/gobang/bgm1.mp3\" alias bg", NULL, 0, NULL);
    mciSendString("play bg repeat", NULL, 0, NULL);
C:
    //显示背景音乐开关
    IMAGE bg;
    loadimage(&bg, getFileFullPath("/data/gobang/back.jpg"), 500, 750);
    putimage(0, 0, &bg);

    //绘制棋盘
    draw_chessboard();

    //黑子先手  游戏开始光标默认在正中间
    //绘制光标
    g_cursor.x = 225;
    g_cursor.y = 525;     // 这个坐标是推出来的 就是最中心的坐标
    setlinecolor(RED);
    setlinestyle(PS_DOT);
    rectangle(g_cursor.x - 15, g_cursor.y - 15, g_cursor.x + 15, g_cursor.y + 15);


    //定义一个有225个元素的结构体数组来代表光标的所有分布的可能性
    post master[225];
    //填充电脑位置     //棋盘左上是50 350
    int index = 0; //定义结构体数组的下标
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= 15; j++)
        {
            //25 + j * 25, 325 + i * 25,  //棋盘左上是50 350
            master[index].x = 25 + j * 25;
            master[index].y = 325 + i * 25;
            index++;
        }
    }


    //清除上一下鼠标缓存
    FlushMouseMsgBuffer();

    MOUSEMSG m;        // 定义鼠标消息
    int pn = 0;
    while (true)
    {
        //按下esc返回游戏界面
        if (_kbhit())
        {
            char key;
            key = _getch();
            switch (key)
            {
            case 27:  //‌ESC键的键值是27‌
            {
                //重置color
                g_color = 0;
                //音乐暂停
                mciSendString("close bg", NULL, 0, NULL);   //竟然神奇的把pause改成close就可以消除按下esc会页面在点击开始游戏直接出来棋子的bug
                restart();
            }
            default:
                break;
            }
        }
        //清除上一下鼠标缓存
        FlushMouseMsgBuffer();  //让光标更加灵活

        //获取一条鼠标消息
        m = GetMouseMsg();

        //是否暂停音乐
        if (g_bgm_switch % 2 == 0)
        {
            settextcolor(RGB(0, 0, 0));
            settextstyle(20, 0, "楷体");
            outtextxy(25, 730, "背景音乐: OFF");
            mciSendString("pause bg", NULL, 0, NULL);
        }
        else
        {
            settextcolor(RGB(0, 0, 0));
            settextstyle(20, 0, "楷体");
            outtextxy(25, 730, "背景音乐: ON");
            mciSendString("resume bg", NULL, 0, NULL);
        }

        //显示提示黑子先手或者显示提示当前将要下的棋子颜色 
        do
        {
            settextcolor(RGB(0, 0, 0));
            settextstyle(20, 0, "楷体");
            if (g_color == 0)
            {
                outtextxy(30, 300, "黑子先手!");
                break;
            }
            if (pn == 0)      //刷一下该区域背景，处理文字无法消除问题
            {
                IMAGE dt;
                loadimage(&dt, getFileFullPath("/data/gobang/defect.jpg"), 106, 22);
                putimage(30, 300, &dt);
                pn++;
            }
            if (g_color % 2 != 0)
            {
                outtextxy(30, 300, TEXT_TIMETOCHESS);
                //提示落子颜色
                setfillcolor(WHITE);
                setlinecolor(WHITE);
                fillcircle(130, 310, 10);
            }
            else
            {
                outtextxy(30, 300, TEXT_TIMETOCHESS);
                //提示落子颜色
                setfillcolor(BLACK);
                setlinecolor(BLACK);
                fillcircle(130, 310, 10);
            }
        } while (0);

        switch (m.uMsg)
        {
        case WM_MOUSEMOVE:
            for (int i = 0; i < 225; i++)
            {
                if ((m.x >= master[i].x - 10 && m.x <= master[i].x + 10) && (m.y >= master[i].y - 10 && m.y <= master[i].y + 10))        //   m.x == master[i].x && m.y == master[i].y
                {
                    //(m.x >= master[i].x - 5 && m.x <= master[i].x + 5) && (m.y >= master[i].y - 5 && m.y <= master[i].y + 5)
                    setlinecolor(RGB(248, 203, 18));
                    rectangle(g_cursor.x - 15, g_cursor.y - 15, g_cursor.x + 15, g_cursor.y + 15);
                    g_cursor.x = master[i].x;
                    g_cursor.y = master[i].y;
                    setlinecolor(RED);
                    setlinestyle(PS_DOT);
                    rectangle(g_cursor.x - 15, g_cursor.y - 15, g_cursor.x + 15, g_cursor.y + 15);
                }
            }
            break;
        case WM_MBUTTONDOWN:
            if (m.mkShift)
            {
                g_bgm_switch++;        // 如果按下中键同时按下shift就决定音乐是否暂停(先按住shift在按住鼠标中键)
                Sleep(100);
                break;
            }
            if (m.mkCtrl)
            {
                //如果按下中键同时按下ctrl就重新开始游戏
                g_color = 0;  //重置颜色
                IMAGE backgrand;
                loadimage(&backgrand, getFileFullPath("/data/gobang/back.jpg"), 500, 750);
                putimage(0, 0, &backgrand);           //重置画面
                goto C;
            }
            exit(0);   //设置强制退出游戏功能
        case WM_LBUTTONUP:
            //不可以重复下棋  通过getpixel这个函数来实现
            if (getpixel(g_cursor.x - 3, g_cursor.y - 3) == RGB(0, 0, 0) || getpixel(g_cursor.x - 3, g_cursor.y - 3) == RGB(255, 255, 255))
            {
                break;
            }
            if (g_color % 2 == 0)
            {
                //把下的棋的顺序保存在array数组里面
                array[g_color] = g_cursor;

                setfillcolor(BLACK);
                setlinecolor(BLACK);
                fillcircle(g_cursor.x, g_cursor.y, 10);
                PlaySound(getFileFullPath("/data/gobang/drop.wav"), NULL, SND_FILENAME | SND_ASYNC);

                COLORREF hei = getpixel(g_cursor.x - 3, g_cursor.y - 3);
                //胜负判断
                int a = victory_judgment(hei, g_cursor.x, g_cursor.y);
                if (a == 1)
                {
                    settextcolor(RGB(0, 0, 0));
                    settextstyle(30, 0, "楷体");
                    outtextxy(100, 160, TEXT_CONTINUE_GAME);
                    outtextxy(150, 200, "恭喜黑棋获胜!");
                    char str[30];
                    sprintf_s(str, "大战了 %d 回合!", g_color / 2 + 1);
                    outtextxy(145, 230, str);
                    PlaySound(getFileFullPath("/data/gobang/ying.wav"), NULL, SND_FILENAME | SND_ASYNC);

                    //显示棋子顺序
                    array_gobang_steps();

                    //重置color
                    g_color = 0;
                    system("pause");
                    goto C;
                }
                //加入平局的判断
                if (a == 0 && g_color == 224)   //因为color最大值是224
                {
                    settextcolor(RGB(0, 0, 0));
                    settextstyle(30, 0, "宋体");
                    outtextxy(100, 160, TEXT_CONTINUE_GAME);
                    outtextxy(210, 200, "平局!");
                    PlaySound(getFileFullPath("/data/gobang/ying.wav"), NULL, SND_FILENAME | SND_ASYNC);

                    //显示棋子顺序
                    array_gobang_steps();

                    //重置color
                    g_color = 0;
                    system("pause");
                    goto C;
                }
            }
            else
            {
                //把下的棋的顺序保存在array数组里面
                array[g_color] = g_cursor;

                setfillcolor(WHITE);
                setlinecolor(WHITE);
                fillcircle(g_cursor.x, g_cursor.y, 10);
                PlaySound(getFileFullPath("/data/gobang/drop.wav"), NULL, SND_FILENAME | SND_ASYNC);

                COLORREF bai = getpixel(g_cursor.x - 3, g_cursor.y - 3);
                //胜负判断
                int b = victory_judgment(bai, g_cursor.x, g_cursor.y);
                if (b == 1)
                {
                    settextcolor(RGB(0, 0, 0));
                    settextstyle(30, 0, "楷体");
                    outtextxy(100, 160, TEXT_CONTINUE_GAME);
                    outtextxy(150, 200, "恭喜白棋获胜!");
                    char str[30];
                    sprintf_s(str, "大战了 %d 回合!", g_color / 2 + 1);
                    outtextxy(145, 230, str);
                    PlaySound(getFileFullPath("/data/gobang/ying.wav"), NULL, SND_FILENAME | SND_ASYNC);

                    //显示棋子顺序
                    array_gobang_steps();

                    //重置color
                    g_color = 0;
                    system("pause");
                    goto C;
                }
                //加入平局的判断
                if (b == 0 && g_color == 224)
                {
                    settextcolor(RGB(0, 0, 0));
                    settextstyle(30, 0, "宋体");
                    outtextxy(100, 160, TEXT_CONTINUE_GAME);
                    outtextxy(210, 200, "平局!");
                    PlaySound(getFileFullPath("/data/gobang/ying.wav"), NULL, SND_FILENAME | SND_ASYNC);

                    //显示棋子顺序
                    array_gobang_steps();

                    //重置color
                    g_color = 0;
                    system("pause");
                    goto C;
                }
            }

            //把当前下的棋保存在huixy中
            g_undo_pos.x = g_cursor.x;
            g_undo_pos.y = g_cursor.y;
            g_color++;
            Sleep(100);
            break;
        case WM_RBUTTONDOWN:   //设置悔棋功能
            //保证是悔的上一颗的棋
            if (g_undo_pos.x == g_cursor.x && g_undo_pos.y == g_cursor.y && getpixel(g_cursor.x - 3, g_cursor.y - 3) != RGB(248, 203, 18))
            {
                setfillcolor(RGB(248, 203, 18));
                setlinecolor(RGB(248, 203, 18));
                fillcircle(g_cursor.x, g_cursor.y, 10);
                setlinecolor(BLACK);

                for (int i = 1; i < 15; i++)
                {
                    for (int j = 1; j < 15; j++)
                    {
                        rectangle(25 + j * 25, 325 + i * 25, 50 + j * 25, 350 + i * 25);

                    }
                }
                g_color--;
                break;
            }
        }

        //来一个重新检查  主要是让白棋不存在中心有黑线的情况
        for (int i = 0; i < 255; i++)
        {
            if (getpixel(master[i].x - 3, master[i].y - 3) == RGB(0, 0, 0))
            {
                setfillcolor(RGB(0, 0, 0));
                setlinecolor(RGB(0, 0, 0));
                fillcircle(master[i].x, master[i].y, 10);
            }
            if (getpixel(master[i].x - 3, master[i].y - 3) == RGB(255, 255, 255))
            {
                setfillcolor(RGB(255, 255, 255));
                setlinecolor(RGB(255, 255, 255));
                fillcircle(master[i].x, master[i].y, 10);
            }
        }
    }
}

void man_machine_game_start()
{
    //加载背景音乐
    mciSendString("open \"../data/gobang/bgm.mp3\" alias bg", NULL, 0, NULL);
    mciSendString("play bg repeat", NULL, 0, NULL);
C:
    //显示背景
    IMAGE bg;
    loadimage(&bg, getFileFullPath("/data/gobang/back.jpg"), 500, 750);
    putimage(0, 0, &bg);

    //绘制棋盘
    draw_chessboard();

    //黑子先手  游戏开始光标默认在正中间
    //绘制光标
    g_cursor.x = 225;
    g_cursor.y = 525;     // 这个坐标是推出来的 就是最中心的坐标
    setlinecolor(RED);
    setlinestyle(PS_DOT);
    rectangle(g_cursor.x - 15, g_cursor.y - 15, g_cursor.x + 15, g_cursor.y + 15);

    //初始化人机
    //加载每个点并且把分数搞成0
    alph alphcat[225];
    //填充电脑位置     //棋盘左上是50 350
    int inde = 0; //定义结构体数组的下标
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= 15; j++)
        {
            //25 + j * 25, 325 + i * 25,  //棋盘左上是50 350
            alphcat[inde].x = 25 + j * 25;
            alphcat[inde].y = 325 + i * 25;
            alphcat[inde].score = 0;
            inde++;
        }
    }

    //定义一个有225个元素的结构体数组来代表光标的所有分布的可能性
    post master[225];
    //填充电脑位置     //棋盘左上是50 350
    int index = 0; //定义结构体数组的下标
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= 15; j++)
        {
            //25 + j * 25, 325 + i * 25,  //棋盘左上是50 350
            master[index].x = 25 + j * 25;
            master[index].y = 325 + i * 25;
            index++;
        }
    }

    //清除上一下鼠标缓存
    FlushMouseMsgBuffer();

    MOUSEMSG m;        // 定义鼠标消息
    int pn = 0;

    while (true)
    {
        //按下esc返回游戏界面
        if (_kbhit())
        {
            char key;
            key = _getch();
            switch (key)
            {
            case 27:
            {
                //重置color
                g_color = 0;
                //音乐暂停
                mciSendString("close bg", NULL, 0, NULL);   //竟然神奇的把pause改成close就可以消除按下esc会页面在点击开始游戏直接出来棋子的bug
                restart();
            }
            }
        }
        //清除上一下鼠标缓存
        FlushMouseMsgBuffer();  //让光标更加灵活

        //获取一条鼠标消息
        m = GetMouseMsg();

        //显示背景音乐开关, 是否暂停音乐
        if (g_bgm_switch % 2 == 0)
        {
            settextcolor(RGB(0, 0, 0));
            settextstyle(20, 0, "楷体");
            outtextxy(25, 730, "背景音乐: OFF");
            mciSendString("pause bg", NULL, 0, NULL);
        }
        else
        {
            settextcolor(RGB(0, 0, 0));
            settextstyle(20, 0, "楷体");
            outtextxy(25, 730, "背景音乐: ON");
            mciSendString("resume bg", NULL, 0, NULL);
        }

        //显示提示黑子先手或者显示提示当前将要下的棋子颜色 
        do
        {
            settextcolor(RGB(0, 0, 0));
            settextstyle(20, 0, "楷体");
            if (g_color == 0)
            {
                outtextxy(30, 300, "黑子先手!");
                break;
            }
            if (pn == 0)
            {
                IMAGE dt;
                loadimage(&dt, getFileFullPath("/data/gobang/defect.jpg"), 106, 22);
                putimage(30, 300, &dt);
                pn++;
            }
            if (g_color % 2 != 0)
            {
                outtextxy(30, 300, TEXT_TIMETOCHESS);
                //提示落子颜色
                setfillcolor(WHITE);
                setlinecolor(WHITE);
                fillcircle(130, 310, 10);
            }
            else
            {
                outtextxy(30, 300, TEXT_TIMETOCHESS);
                //提示落子颜色
                setfillcolor(BLACK);
                setlinecolor(BLACK);
                fillcircle(130, 310, 10);
            }
        } while (0);

        switch (m.uMsg)
        {
        case WM_MOUSEMOVE:
            for (int i = 0; i < 225; i++)
            {
                if ((m.x >= master[i].x - 10 && m.x <= master[i].x + 10) && (m.y >= master[i].y - 10 && m.y <= master[i].y + 10))
                {
                    setlinecolor(RGB(248, 203, 18));
                    rectangle(g_cursor.x - 15, g_cursor.y - 15, g_cursor.x + 15, g_cursor.y + 15);
                    g_cursor.x = master[i].x;
                    g_cursor.y = master[i].y;
                    setlinecolor(RED);
                    setlinestyle(PS_DOT);
                    rectangle(g_cursor.x - 15, g_cursor.y - 15, g_cursor.x + 15, g_cursor.y + 15);
                }
            }
            break;
        case WM_MBUTTONDOWN:
            if (m.mkShift)
            {
                g_bgm_switch++;        // 如果按下中键同时按下shift就决定音乐是否暂停(先按住shift在按住鼠标中键)
                Sleep(100);
                break;
            }
            if (m.mkCtrl)
            {
                //如果按下中键同时按下ctrl就重新开始游戏
                g_color = 0;  //重置颜色
                IMAGE backgrand;
                loadimage(&backgrand, getFileFullPath("/data/gobang/back.jpg"), 500, 750);
                putimage(0, 0, &backgrand);           //重置画面
                goto C;
            }
            exit(0);   //设置强制退出游戏功能
        case WM_LBUTTONUP:
        {
            //不可以重复下棋  通过getpixel这个函数来实现
            if (getpixel(g_cursor.x - 3, g_cursor.y - 3) == RGB(0, 0, 0) || getpixel(g_cursor.x - 3, g_cursor.y - 3) == RGB(255, 255, 255))
            {
                break;
            }
            //把下的棋的顺序保存在array数组里面
            array[g_color] = g_cursor;

            setfillcolor(BLACK);
            setlinecolor(BLACK);
            fillcircle(g_cursor.x, g_cursor.y, 10);
            PlaySound(getFileFullPath("/data/gobang/drop.wav"), NULL, SND_FILENAME | SND_ASYNC);
            COLORREF hei = getpixel(g_cursor.x - 3, g_cursor.y - 3);
            //胜负判断
            int a = victory_judgment(hei, g_cursor.x, g_cursor.y);
            if (a == 1)
            {
                settextcolor(RGB(0, 0, 0));
                settextstyle(30, 0, "楷体");
                outtextxy(100, 160, TEXT_CONTINUE_GAME);
                outtextxy(55, 200, "太厉害了，您竟然战胜了电脑!");
                char str[30];
                sprintf_s(str, "大战了 %d 回合!", g_color / 2 + 1);
                outtextxy(110, 230, str);
                PlaySound(getFileFullPath("/data/gobang/ying.wav"), NULL, SND_FILENAME | SND_ASYNC);

                //显示棋子顺序
                man_array_steps();
                man_machine_array_steps();

                //重置color
                g_color = 0;
                system("pause");
                goto C;
            }
            //加入平局的判断
            if (a == 0 && g_color == 224)   //因为color最大值是224
            {
                settextcolor(RGB(0, 0, 0));
                settextstyle(30, 0, "宋体");
                outtextxy(100, 160, TEXT_CONTINUE_GAME);
                outtextxy(146, 200, "我和你五五开!");
                PlaySound(getFileFullPath("/data/gobang/ying.wav"), NULL, SND_FILENAME | SND_ASYNC);

                //显示棋子顺序
                man_array_steps();
                man_machine_array_steps();

                //重置color
                g_color = 0;
                system("pause");
                goto C;
            }

            //把当前下的棋保存在huixy中
            g_undo_pos.x = g_cursor.x;
            g_undo_pos.y = g_cursor.y;
            g_color++;
            Sleep(200);
        }
        case 1:
        {
            for (int i = 0; i < 225; i++)
            {
                if (RGB(0, 0, 0) != getpixel(alphcat[i].x - 3, alphcat[i].y - 3) && \
                    RGB(255, 255, 255) != getpixel(alphcat[i].x - 3, alphcat[i].y - 3)/*当前落棋点没有落棋 (这个点的颜色是背景色)*/)
                {
                    //RGB(255, 255, 255) != getpixel(alphcat[i].x - 3, alphcat[i].y - 3)
                    alphcat[i].score = score_analysis_judgment(alphcat[i].x, alphcat[i].y);
                }
            }
            //再来选出一个得分最大的,如果得分一样就随机从最大的一个选一个
            alph alphmax;
            alphmax.score = alphcat[0].score;
            for (int i = 1; i < 225; i++)
            {
                if (alphcat[i].score >= alphmax.score)
                {
                    alphmax = alphcat[i];
                }
            }

            // 把下的棋的顺序保存在array数组里面
            machine_array[g_color] = alphmax;

            //根据这个点画白棋
            setfillcolor(WHITE);
            setlinecolor(WHITE);
            fillcircle(alphmax.x, alphmax.y, 10);
            PlaySound(getFileFullPath("/data/gobang/drop.wav"), NULL, SND_FILENAME | SND_ASYNC);
            for (int i = 0; i < 225; i++)
            {
                alphcat[i].score = 0;
            }
            COLORREF bai = getpixel(alphmax.x - 3, alphmax.y - 3);
            //胜负判断
            int b = victory_judgment(bai, alphmax.x, alphmax.y);
            if (b == 1)
            {
                settextcolor(RGB(0, 0, 0));
                settextstyle(30, 0, "楷体");
                outtextxy(100, 160, TEXT_CONTINUE_GAME);
                outtextxy(80, 200, "游戏结束，您输给了电脑!");
                char str[30];
                sprintf_s(str, "大战了 %d 回合!", g_color / 2 + 1);
                outtextxy(140, 230, str);
                PlaySound(getFileFullPath("/data/gobang/ying.wav"), NULL, SND_FILENAME | SND_ASYNC);

                //显示棋子顺序
                man_array_steps();
                man_machine_array_steps();

                //重置color
                g_color = 0;
                system("pause");
                goto C;
            }
            //加入平局的判断
            if (b == 0 && g_color == 224)   //因为color最大值是224
            {
                settextcolor(RGB(0, 0, 0));
                settextstyle(30, 0, "宋体");
                outtextxy(100, 160, TEXT_CONTINUE_GAME);
                outtextxy(146, 200, "我和你五五开!");
                PlaySound(getFileFullPath("/data/gobang/ying.wav"), NULL, SND_FILENAME | SND_ASYNC);

                //显示棋子顺序
                man_array_steps();
                man_machine_array_steps();

                //重置color
                g_color = 0;
                system("pause");
                goto C;
            }
            //把当前下的棋保存在rjhuixy中
            g_machine_undo_pos.x = alphmax.x;
            g_machine_undo_pos.y = alphmax.y;
            g_color++;
            Sleep(200);
            break;
        }
        case WM_RBUTTONDOWN:   //设置悔棋功能
                               //保证是悔的上一颗的棋
            if (g_undo_pos.x == g_cursor.x && g_undo_pos.y == g_cursor.y && getpixel(g_cursor.x - 3, g_cursor.y - 3) != RGB(248, 203, 18))
            {
                //悔自己的黑棋
                setfillcolor(RGB(248, 203, 18));
                setlinecolor(RGB(248, 203, 18));
                fillcircle(g_cursor.x, g_cursor.y, 10);
                //机器也要悔一步棋
                setfillcolor(RGB(248, 203, 18));
                setlinecolor(RGB(248, 203, 18));
                fillcircle(g_machine_undo_pos.x, g_machine_undo_pos.y, 10);

                //重新画棋盘
                setlinecolor(BLACK);
                for (int i = 1; i < 15; i++)
                {
                    for (int j = 1; j < 15; j++)
                    {
                        rectangle(25 + j * 25, 325 + i * 25, 50 + j * 25, 350 + i * 25);
                    }
                }
                g_color -= 2;
                break;
            }
        }
        //来一个重新检查  主要是让白棋不存在中心有黑线的情况
        for (int i = 0; i < 255; i++)
        {
            if (getpixel(master[i].x - 3, master[i].y - 3) == RGB(0, 0, 0))
            {
                setfillcolor(RGB(0, 0, 0));
                setlinecolor(RGB(0, 0, 0));
                fillcircle(master[i].x, master[i].y, 10);
            }
            if (getpixel(master[i].x - 3, master[i].y - 3) == RGB(255, 255, 255))
            {
                setfillcolor(RGB(255, 255, 255));
                setlinecolor(RGB(255, 255, 255));
                fillcircle(master[i].x, master[i].y, 10);
            }
        }
    }
}

void gameover()
{
    //游戏结束释放资源
    cleardevice();
    closegraph();

}

void restart()
{
    g_color = 0;
    memset(array, 0, sizeof(array));
    memset(machine_array, 0, sizeof(machine_array));

    gameover();

    initgame();

    game_start();

    gameover();

}

int main()
{
    get_parent_directory(g_parRootpath);

    initgame();

    game_start();

    gameover();

    //system("pause");

    return 0;
}

