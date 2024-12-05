#include "Game.h"   
#include <graphics.h>



Game::Game()
{

}

Game::~Game()
{
    Close();
}

void Game::Init()
{
    initgraph(800, 600, EX_DBLCLKS | EX_NOMINIMIZE);

    setbkcolor(BLACK);
    //setbkmode(TRANSPARENT);					//设置输出文字背景为透明
    LOGFONT f;
    getfont(&f);							// 获取当前字体设置
    f.lfHeight = 50;						// 设置字体高度为 48（包含行距）
    _tcscpy(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    setfont(&f);							// 设置字体样式 
}

void Game::FailGame()
{
    BeginBatchDraw();
    setcolor(RED);
    setfont(70, 0, _T("微软雅黑"));
    outtextxy(150, 265, _T("YOU LOSE!"));
    EndBatchDraw();
}

void Game::WinGame()
{
    BeginBatchDraw();
    setcolor(RED);
    setfont(70, 0, _T("微软雅黑"));
    outtextxy(150, 265, _T("YOU WIN!"));
    EndBatchDraw();
    //Close();
}

void Game::Close()
{
    closegraph();
    Sleep(5000);
    exit(0);
}


