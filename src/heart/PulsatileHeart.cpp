#include "PulsatileHeart.h"
#include <windows.h>
#include <mmsystem.h>
#include "public_fun.h"
#pragma comment( lib, "winmm.lib")

const int xScreen = 1200;
const int yScreen = 960;
const double PI = 3.142653515926;
const double e = 2.71828;
const double averag_distance = 0.162;
const int quantity = 506;
const int circles = 210;
const int frames = 20;


struct Point {
    double x, y;
    COLORREF color;
};

COLORREF colors[256] = {
    RGB(255,32,83),
    RGB(252,222,250),
    RGB(255,0,0),
    RGB(255,0,0),
    RGB(255,2,2),
    RGB(255,0,8),
    RGB(255,5,5),
};

Point origin_points[quantity];
Point points[circles * quantity];

IMAGE images[frames];


double screen_x(double x) {
	x += xScreen / 2;
	return x;
}

double screen_y(double y) {
	y = -y + yScreen / 2;
	return y;
}

void create_data()
{
	int index = 0;
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	for (double radian = 0.1; radian <= 2 * PI; radian += 0.005)
	{
		x2 = 16 * pow(sin(radian), 3);
		y2 = 13 * cos(radian) - 5 * cos(2 * radian) - 2 * cos(3 * radian) - cos(4 * radian);
		double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		if (distance > averag_distance) {

			x1 = x2, y1 = y2;
			origin_points[index].x = x2;
			origin_points[index++].y = y2;
		}
	}
	index = 0;
	for (double size = 0.l, lightness = 1.5; size <= 20; size += 0.1)
	{
		double success_p = 1 / (1 + pow(e, 8 - size / 2));
		if (lightness > 1)
			lightness -= 0.0025;
		for (int i = 0; i < quantity; ++i)
		{
			if (success_p > create_random(0, 100) / 100.0)
			{
				COLORREF color = colors[create_random(0, 6)];
				points[index].color = RGB(GetRValue(color) / lightness, GetGValue(color) / lightness, GetBValue(color) / lightness);
				points[index].x = size * origin_points[i].x + create_random(-4, 4);
				points[index++].y = size * origin_points[i].y + create_random(-4, 4);
			}
		}
	}
	int points_size = index;
	for (int frame = 0; frame < frames; ++frame)
	{
		images[frame] = IMAGE(xScreen, yScreen);
		SetWorkingImage(&images[frame]);
		for (index = 0; index < points_size; ++index)
		{
			double x = points[index].x, y = points[index].y;
			double distance = sqrt(pow(x, 2) + pow(y, 2));
			double diatance_increase = -0.0009 * distance * distance + 0.35714 * distance + 5;
			double x_increase = diatance_increase * x / distance / frames;
			double y_increase = diatance_increase * y / distance / frames;
			points[index].x += x_increase;
			points[index].y += y_increase;
			setfillcolor(points[index].color);
			solidcircle(screen_x(points[index].x), screen_y(points[index].y), 1);
		}
		for (double size = 17; size < 23; size += 0.3)
		{
			for (index = 0; index < quantity; ++index)
			{
				if ((create_random(0, 100) / 100.0 > 0.6 && size >= 20) || (size < 20 && create_random(0, 100) / 100.0>0.95))
				{

					double x, y;
					if (size >= 20)
					{
						x = origin_points[index].x * size + create_random(-frame * frame / 5 - 15, frame * frame / 5 + 15);
						y = origin_points[index].y * size + create_random(-frame * frame / 5 - 15, frame * frame / 5 + 15);
					}
					else
					{
						x = origin_points[index].x * size + create_random(-5, 5);
						y = origin_points[index].y * size + create_random(-5, 5);
					}
					setfillcolor(colors[create_random(0, 6)]);
					solidcircle(screen_x(x), screen_y(y), 1);
				}
			}
		}
	}

	SetWorkingImage();
}


void drawheart()
{
    initgraph(xScreen, yScreen);

    // 获得窗口句柄
    HWND hWnd = GetHWnd();
    // 使用 API 函数修改窗口名称
    SetWindowText(hWnd, L"Heart");

    char rootpath[256] = { 0 };
    char filepath[256] = { 0 };

    get_parent_directory(rootpath);
    getFileFullPath(rootpath, "/data/Canon.mp3", filepath);

    wchar_t bgm[256] = { 0 };
    const wchar_t* mmm = chtowc(filepath);
    swprintf_s(bgm, L"open %s alias mymusic", chtowc(filepath));
    // 打开音乐   
    mciSendString(bgm, NULL, 0, NULL);

    BeginBatchDraw();
    srand(time(0));
    create_data();

    // 播放音乐
    mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);
    bool extend = true, shrink = false;
    for (int frame = 0; !_kbhit();)
    {
        putimage(0, 0, &images[frame]);
        FlushBatchDraw();
        Sleep(25);
        cleardevice();
        if (extend)
            frame == 19 ? (shrink = true, extend = false) : ++frame;
        else
            frame == 0 ? (shrink = false, extend = true) : --frame;
    }
    EndBatchDraw();
    // 停止播放并关闭音乐
    mciSendString(_T("stop mymusic"), NULL, 0, NULL);
    mciSendString(_T("close mymusic"), NULL, 0, NULL);
    cleardevice();

    //保存绘制的图像
    //saveimage(_T("/../data/heart.png"), images);
    closegraph();

}
