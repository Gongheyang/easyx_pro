/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    Game.h
 *@描述    游戏类，用来初始化游戏的参数，及实现其他游戏操作
 *
 *@作者    GhY
 *@日期    2024年11月28日
 *@版本    v1.0.0
 *
 ****************************************************/
#ifndef __GAME_H__
#define __GAME_H__

class Game
{
public:
    Game();

    ~Game();

    /*
     *@bref    初始化游戏参数、设置
     */
    void Init();

    /*
     *@bref    游戏失败显示的画面
     */
    void FailGame();

    /*
     *@bref    游戏胜利时显示的画面
     */
    void WinGame();


    void Close();

};

#endif // !__GAME_H__

