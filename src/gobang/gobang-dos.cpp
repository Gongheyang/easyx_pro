/*
五子棋 控制台版本   
*/
#include "gobang.h " 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <time.h>
#include <windows.h>

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

	main();

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



void BackGround(unsigned int ForeColor, unsigned int BackGroundColor)  //颜色
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获取控制台的句柄
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//改变当前光标的背景和字体颜色
}

void gotoxy(int x, int y)    //光标函数
{
	HANDLE handle;
	COORD coord;   //获取坐标轴结构体
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获取控制台句柄，值为-11
	SetConsoleCursorPosition(handle, coord);   //移动光标到x，y处
}

void chess_board()//打印棋盘
{
	int i, j;
	for (i = 0; i <= 30; i++)
		for (j = 0; j <= 60; j += 4)
		{
			gotoxy(j, i);
			printf("|");
		}
	for (i = 0; i <= 30; i += 2)
		for (j = 1; j <= 57; j += 4)
		{
			gotoxy(j, i);
			printf("---");
		}
}

void chess_menu()//打印棋盘旁的菜单
{
	int i = 0;
	for (i = 1; i <= 29; i++)
	{
		gotoxy(67, i);
		printf("||");
	}
	for (i = 1; i <= 29; i++)
	{
		gotoxy(89, i);
		printf("||");
	}
	gotoxy(69, 1);
	printf("--------------------");
	gotoxy(69, 29);
	printf("--------------------");
	gotoxy(75, 3);
	printf("模   式");
	gotoxy(75, 20);
	printf("提   示");
}

void red_movexy()//红棋移动光标
{
loop2:
	gotoxy(direct[0], direct[1]);
	char key = 'y';
	int temp;
	while (key != ' ')
	{
		key = _getch();
		switch (key)
		{
		case 'W':
		case 'w':
			direct[1] -= 2;
			if (direct[1] <= 1)
				direct[1] = 1;
			break;
		case 's':
		case 'S':
			direct[1] += 2;
			if (direct[1] >= 29)
				direct[1] = 29;
			break;
		case 'a':
		case 'A':
			direct[0] -= 4;
			if (direct[0] <= 2)
				direct[0] = 2;
			break;
		case 'd':
		case 'D':
			direct[0] += 4;
			if (direct[0] >= 58)
				direct[0] = 58;
			break;
		case 'q':
		case 'Q':
		{
			int message = MessageBox(NULL, "是否确定悔棋？", "友情提示", MB_OKCANCEL);
			if (IDCANCEL == message)
				break;
			if (IDOK == message)
			{
				Regret();
				break;
			}
		}
		}
		gotoxy(direct[0], direct[1]);
	}
	temp = judge_chess(direct[1], direct[0]);
	if (temp == 1)
	{
		gotoxy(70, 22);
		BackGround(4, 0);
		printf("这里已经被人下过了");
		goto loop2;
	}
}

void white_movexy()//白棋移动光标
{
loop1:
	gotoxy(direct[0], direct[1]);
	char key = 'y';
	int temp;
	while (key != '0')
	{
		key = _getch();
		switch (key)
		{
		case 72:
			direct[1] -= 2;
			if (direct[1] <= 1)
				direct[1] = 1;
			break;
		case 80:
			direct[1] += 2;
			if (direct[1] >= 29)
				direct[1] = 29;
			break;
		case 75:
			direct[0] -= 4;
			if (direct[0] <= 2)
				direct[0] = 2;
			break;
		case 77:
			direct[0] += 4;
			if (direct[0] >= 58)
				direct[0] = 58;
			break;
		case 'B':
		case 'b':
		{
			int message = MessageBox(NULL, "是否确定悔棋？", "友情提示", MB_OKCANCEL);
			if (IDCANCEL == message)
				break;
			if (IDOK == message)
			{
				Regret();
				break;
			}
		}
		}
		gotoxy(direct[0], direct[1]);
	}
	temp = judge_chess(direct[1], direct[0]);
	if (temp == 1)
	{
		gotoxy(70, 22);
		BackGround(4, 0);
		printf("这里已经被人下过了");
		goto loop1;
	}
}

void red_chess(int x, int y)    //打印红棋
{
	BackGround(4, 0);
	regrex = x;//记录上一落子的位置 ,方便悔棋
	regrey = y;
	count++;
	printf("●");
	status[x][y] = 1;
}

void white_chess(int x, int y)  //打印白棋
{
	BackGround(7, 0);
	regrex1 = x;
	regrey1 = y;
	printf("●");
	count++;
	status[x][y] = 2;
}

void machine_chess(int x, int y)    //电脑落子
{
	BackGround(7, 0);
	status[x][y] = 2;
	regrex1 = x;
	regrey1 = y;
	count++;
	gotoxy(y, x);
	printf("●");
}

int judge_chess(int x, int y)   //判断这个地方是否有棋子
{
	if (status[x][y] == 0)
		return 0;
	else
		return 1;
}

int judge_winner(int x, int y, int temp)    //判断输赢
{
	int i, j, n1, n2;
	n1 = n2 = 0;
	for (i = x, j = y + 4; j <= 58; j += 4)//右
	{
		if (status[i][j] == temp)
			n1++;
		else
			break;
	}
	for (i = x, j = y; j >= 2; j -= 4)//左
	{
		if (status[i][j] == temp)
			n2++;
		else
			break;
	}
	if (n1 + n2 >= 5)
		return temp;
	n1 = n2 = 0;
	for (i = x, j = y; i >= 1; i -= 2)//上
	{
		if (status[i][j] == temp)
			n1++;
		else
			break;
	}
	for (i = x + 2, j = y; i <= 30; i += 2)//下
	{
		if (status[i][j] == temp)
			n2++;
		else
			break;
	}
	if (n1 + n2 >= 5)
		return temp;
	n1 = n2 = 0;
	for (i = x - 2, j = y + 4; i >= 1 && j <= 58; i -= 2, j += 4)//右上
	{
		if (status[i][j] == temp)
			n1++;
		else
			break;
	}
	for (i = x, j = y; i <= 30 && j >= 2; i += 2, j -= 4)//左下
	{
		if (status[i][j] == temp)
			n2++;
		else
			break;
	}
	if (n1 + n2 >= 5)
		return temp;
	n1 = n2 = 0;
	for (i = x, j = y; i >= 0 && j >= 0; i -= 2, j -= 4)//左上
	{
		if (status[i][j] == temp)
			n1++;
		else
			break;
	}
	for (i = x + 2, j = y + 4; i <= 30 && j <= 58; i += 2, j += 4)//右下
	{
		if (status[i][j] == temp)
			n2++;
		else
			break;
	}
	if (n1 + n2 >= 5)
		return temp;
	return 0;
}

void machine_attack()   //电脑进攻权值
{
	int i1, j1;
	int k1, k2, k;
	for (int i = 1; i <= 30; i += 2)
	{
		for (int j = 2; j <= 58; j += 4)
		{
			if (status[i][j])
				Value1[i][j] = 0;
			if (status[i][j] == 0)
			{
				k1 = k2 = 0;
				for (i1 = i, j1 = j - 4; j1 >= 2; j1 -= 4)      //往左数寻找电脑棋子数
				{
					if (status[i1][j1] == 2)
						k1++;
					else
						break;
				}
				for (i1 = i, j1 = j + 4; j1 <= 58; j1 += 4)     //往右数寻找电脑棋子数
				{
					if (status[i1][j1] == 2)
						k2++;
					else
						break;
				}
				k = k1 > k2 ? k1 : k2;
				k1 = k2 = 0;
				for (i1 = i - 2, j1 = j; i1 >= 1; i1 -= 2)      //往上数寻找电脑棋子数
				{
					if (status[i1][j1] == 2)
						k1++;
					else
						break;
				}
				for (i1 = i + 2, j1 = j; i1 <= 30; i1 += 2)     //往下数寻找电脑棋子数
				{
					if (status[i1][j1] == 2)
						k2++;
					else
						break;
				}
				k1 = k1 > k2 ? k1 : k2;
				k = k > k1 ? k : k1;
				k1 = k2 = 0;
				for (i1 = i - 2, j1 = j - 4; i1 >= 0 && j1 >= 0; i1 -= 2, j1 -= 4)      //往左上数寻找电脑棋子数
				{
					if (status[i1][j1] == 2)
						k1++;
					else
						break;
				}
				for (i1 = i + 2, j1 = j + 4; i1 <= 30 && j1 <= 58; i1 += 2, j1 += 4)    //往右下数寻找电脑棋子数
				{
					if (status[i1][j1] == 2)
						k2++;
					else
						break;
				}
				k1 = k1 > k2 ? k1 : k2;
				k = k > k1 ? k : k1;
				k1 = k2 = 0;
				for (i1 = i + 2, j1 = j - 4; i1 <= 30 && j1 >= 2; i1 += 2, j1 -= 4)     //往左下数寻找电脑棋子数
				{
					if (status[i1][j1] == 2)
						k1++;
					else
						break;
				}
				for (i1 = i - 2, j1 = j + 4; i1 >= 1 && j1 <= 58; i1 -= 2, j1 += 4)     //往右上数寻找电脑棋子数
				{
					if (status[i1][j1] == 2)
						k2++;
					else
						break;
				}
				k1 = k1 > k2 ? k1 : k2;
				k = k > k1 ? k : k1;
				switch (k)
				{
				case 3:
					Value1[i][j] = 15;
					break;
				case 4:
					Value1[i][j] = 25;
					break;
				default:
					Value1[i][j] = 3 + 2 * k;
					break;
				}
			}
		}
	}
}

void machine_defend()       //防守权值
{
	int i1, j1;
	int k1, k2, k;
	for (int i = 1; i <= 30; i += 2)
	{
		for (int j = 2; j <= 58; j += 4)
		{
			if (status[i][j])
				Value2[i][j] = 0;
			if (status[i][j] == 0)
			{
				k1 = k2 = 0;
				for (i1 = i, j1 = j - 4; j1 >= 2; j1 -= 4)      //往左数寻找玩家棋子数
				{
					if (status[i1][j1] == 1)
						k1++;
					else
						break;
				}
				for (i1 = i, j1 = j + 4; j1 <= 58; j1 += 4)     //往右数寻找玩家棋子数
				{
					if (status[i1][j1] == 1)
						k2++;
					else
						break;
				}
				k = k1 > k2 ? k1 : k2;
				k1 = k2 = 0;
				for (i1 = i - 2, j1 = j; i1 >= 1; i1 -= 2)      //往上数寻找玩家棋子数
				{
					if (status[i1][j1] == 1)
						k1++;
					else
						break;
				}
				for (i1 = i + 2, j1 = j; i1 <= 30; i1 += 2)     //往下数寻找玩家棋子数
				{
					if (status[i1][j1] == 1)
						k2++;
					else
						break;
				}
				k1 = k1 > k2 ? k1 : k2;
				k = k > k1 ? k : k1;
				k1 = k2 = 0;
				for (i1 = i - 2, j1 = j - 4; i1 >= 1 && j1 >= 2; i1 -= 2, j1 -= 4)      //往左上数寻找玩家棋子数
				{
					if (status[i1][j1] == 1)
						k1++;
					else
						break;
				}
				for (i1 = i + 2, j1 = j + 4; i1 <= 30 && j1 <= 58; i1 += 2, j1 += 4)    //往右下数寻找玩家棋子数
				{
					if (status[i1][j1] == 1)
						k2++;
					else
						break;
				}
				k1 = k1 > k2 ? k1 : k2;
				k = k > k1 ? k : k1;
				k1 = k2 = 0;
				for (i1 = i + 2, j1 = j - 4; i1 <= 30 && j1 >= 2; i1 += 2, j1 -= 4)     //往左下数寻找玩家棋子数
				{
					if (status[i1][j1] == 1)
						k1++;
					else
						break;
				}
				for (i1 = i - 2, j1 = j + 4; i1 >= 1 && j1 <= 58; i1 -= 2, j1 += 4)     //往右上数寻找玩家棋子数
				{
					if (status[i1][j1] == 1)
						k2++;
					else
						break;
				}
				k1 = k1 > k2 ? k1 : k2;
				k = k > k1 ? k : k1;
				switch (k)
				{
				case 3:
					Value2[i][j] = 10;
					break;
				case 4:
					Value2[i][j] = 20;
					break;
				default:
					Value2[i][j] = 2 + k * 2;
				}
			}
		}
	}
}

void find_position()//找到最有价值的位置
{
	int k1 = 0, k2 = 0;
	int i, j, max = 0;
	for (i = 1; i <= 30; i += 2)
		for (j = 2; j <= 58; j += 4)
		{
			if (max <= Value1[i][j])
			{
				max = Value1[i][j];
				k1 = i;
				k2 = j;
			}
		}
	for (i = 1; i <= 30; i += 2)
		for (j = 2; j <= 58; j += 4)
		{
			if (max <= Value2[i][j])
			{
				max = Value2[i][j];
				k1 = i;
				k2 = j;
			}
		}
	direct[1] = k1;  //将找到的位置传给光标
	direct[0] = k2;
}

void man_man()//人人对战模式
{
loop5:
	system("cls");
	char key;
	int control;
	gotoxy(2, 3);
	printf("1.红 子 先 手");

	gotoxy(2, 5);
	printf("2.白 子 先 手");

	gotoxy(2, 7);
	printf("(输入相应序号选择)");
	key = _getch();
	system("cls");
	if (key == '1')
		control = 1;
	else if (key == '2')
		control = -1;
	else
		goto loop5;
	gotoxy(70, 5);
	printf("   人 人 对 战    ");
	direct[1] = 15;
	direct[0] = 30;
	chess_board();
	chess_menu();
	while (flag == 0)
	{
		if (control == 1)
		{
			gotoxy(70, 22);
			BackGround(6, 0);
			printf("   红 子 执 手    ");
			red_movexy();
			red_chess(direct[1], direct[0]);
			flag = judge_winner(direct[1], direct[0], 1);
		}
		else
		{
			gotoxy(70, 22);
			BackGround(6, 0);
			printf("   白 子 执 手    ");
			white_movexy();
			white_chess(direct[1], direct[0]);
			flag = judge_winner(direct[1], direct[0], 2);
		}
		control = -control;
	}
	if (flag == 1)
	{
		BackGround(7, 0);
		MessageBox(NULL, "游戏结束，红子胜利", "五子棋游戏", MB_OK);
	}
	if (flag == 2)
	{
		MessageBox(NULL, "游戏结束，白子胜利", "五子棋游戏", MB_OK);
	}
	if (count >= 225)
	{
		MessageBox(NULL, "游戏结束，平局", "五子棋游戏", MB_OK);
	}
    main();
}

void man_machine()//人机对战模式
{
loop6:
    system("cls");
    char key;
    int control;
    gotoxy(2, 3);
    printf("1.玩 家 先 手（玩家为红子）");

    gotoxy(2, 5);
    printf("2.电 脑 先 手（电脑为白子）");

    gotoxy(2, 7);
    printf("(输入相应序号选择)");
    key = _getch();
    system("cls");
    if (key == '1')
        control = 1;
    else if (key == '2')
    {
        control = 1;
        machine_chess(13, 26);
    }
    else
        goto loop6;
    gotoxy(70, 5);
    printf("   人 机 对 战    ");
    direct[1] = 15;
    direct[0] = 30;
    chess_board();
    chess_menu();
    while (flag == 0)
    {
        if (control == 1)
        {
            gotoxy(70, 22);
            BackGround(6, 0);
            printf("   玩 家 执 手    ");
            red_movexy();
            red_chess(direct[1], direct[0]);
            flag = judge_winner(direct[1], direct[0], 1);
        }
        else
        {
            gotoxy(70, 22);
            BackGround(6, 0);
            printf("   电 脑 执 手    ");
            machine_defend();
            machine_attack();
            find_position();
            machine_chess(direct[1], direct[0]);
            flag = judge_winner(direct[1], direct[0], 2);
        }
        control = -control;
    }
    gotoxy(8, 18);
    if (flag == 1)
    {
        BackGround(7, 0);
        MessageBox(NULL, "太厉害了，您竟然战胜了电脑!", "五子棋游戏", MB_OK);
    }
    if (flag == 2)
    {
        MessageBox(NULL, "游戏结束，您输给了电脑", "五子棋游戏", MB_OK);
    }
    if (count >= 225)
    {
        MessageBox(NULL, "平局", "五子棋游戏", MB_OK);
    }
    main();  //返回主菜单
}

void Regret()//悔棋函数
{
	gotoxy(regrey, regrex);
	BackGround(0, 0);
	printf(" ");
	status[regrex][regrey] = 0;
	gotoxy(regrey1, regrex1);
	BackGround(0, 0);
	printf(" ");
	status[regrex1][regrey1] = 0;
	count -= 2;
}

void welcome()//游戏菜单
{
	int k;
	system("cls");
	for (k = 2; k <= 16; k += 2)//游戏菜单
	{
		gotoxy(5, k);
		printf("|-----------------|");
	}
	gotoxy(5, 3);
	printf("|  五 子 棋 游 戏 |");

	gotoxy(5, 5);
	printf("|     菜    单    |");

	gotoxy(5, 7);
	printf("|  1.人 人 对 战  |");

	gotoxy(5, 9);
	printf("|  2.人 机 对 战  |");

	gotoxy(5, 11);
	printf("|  3.游 戏 帮 助  |");

	gotoxy(5, 13);
	printf("|  4.更 新 日 志  |");

	gotoxy(5, 15);
	printf("|  5.退 出 游 戏  |");

	gotoxy(5, 18);
	printf("温馨提示:输入菜单对应序号进行操作");

	gotoxy(5, 20);
	printf("祝您游戏愉快！");

	gotoxy(20, 20);
}

char Gametips()//游戏帮助
{
	int key(0);

	system("cls");

	gotoxy(2, 3);
	printf("游戏操作：");

	gotoxy(4, 5);
	printf("① 红色棋子WASD移动光标选择下棋位置,按空格键确认,按Q悔棋");

	gotoxy(4, 7);
	printf("② 白色棋子↑↓←→移动光标选择下棋位置,按0确认,按B悔棋");

	gotoxy(2, 19);
	printf("（按E键返回，按其它任意键退出）");

	return _getch();
}

char Updatediary()//更新日志
{
	system("cls");

	gotoxy(2, 3);
	printf("(暂时没有)");

	gotoxy(2, 5);
	printf("（按E键返回，按其它任意键退出）");

	return _getch();
}


int main()
{
    system("title 五子棋");
    system("mode con cols=92 lines=33");
    char choose, temp;
loop:
    welcome();
    choose = _getch();
    switch (choose)
    {
    case '1':
        man_man();
        break;
    case '2':
        man_machine();
        break;
    case '3':
        temp = Gametips();
        if (temp == 'E' || temp == 'e')
            goto loop;
        break;
    case '4':
        temp = Updatediary();
        if (temp == 'E' || temp == 'e')
            goto loop;
        break;
    case '5':
        int message = MessageBox(NULL, "是否退出？", "友情提示", MB_OKCANCEL);
        if (IDCANCEL == message)
            goto loop;
        if (IDOK == message)
        {
            break;
        }
    }
}

