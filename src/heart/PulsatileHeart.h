/****************************************************
 *
 *@Copyright (c) 2014-2024, GhY, All rights reserved.
 *@文件    PulsatileHeart.h
 *@描述    跳动的心
 *
 *@作者    GhY
 *@日期    2024年12月5日
 *@版本    v1.0.0
 *
 ****************************************************/
#pragma once
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "graphics.h"



double screen_x(double x);

double screen_y(double y);


/*
 *@bref    生成数据
 */
void create_data();

/*
 *@bref    绘制心
 */
void drawheart();