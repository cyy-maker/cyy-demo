#define  _CRT_SECURE_NO_WARNINGS
#include "caidan.h"
#include "game1.h"
#include "game2.h"
#include "game3.h"
#include <conio.h>
//游戏一
void game_1()
{
	srand((unsigned)time(0));
	hwnd = initgraph(800, 700);
	struct Board* pBoard = CreatBoard(300, 685, 1, WHITE, 200, 15);
	struct Ball* pBall = CreatBall(400, 400, 10, 1, -1, CYAN);
	IMAGE n;
	loadimage(&n, "2.jpg", 800, 700);
	initMap();
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		putimage(0, 0, &n);
		drawMap();
		drawBoard(pBoard);
		drawBall(pBall);
		if (Timer(1, 0))
		{
			if (_kbhit())
			{
				moveBall(pBall, pBoard);
			}
		}
		keyDown(pBoard);
		if (die(pBall))
		{
			MessageBox(hwnd, "you die!", "消息", MB_OK);
			break;
		}
		if (GameOver())
		{
			MessageBox(hwnd, "you win!", "消息", MB_OK);
			break;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}
//游戏2
void game_2()
{
	srand((unsigned)time(NULL));
	hwnd1 = initgraph(800, 700);
	struct target words[3];
	CreatTarget(words);
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		divWindow();
		downTarget(words);
		if (_kbhit())
		{
			char ch = _getch();
			Userinput(words, ch);
			if (ch == VK_ESCAPE)
			{
				right1 = 0;
				error = 0;
				MessageBox(hwnd1, "游戏结束!", "消息", MB_OK);
				break;
			}
		}
		outtextxy(usersky.x, usersky.y, usersky.str);
		drawscore();
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}
//游戏三1
void game_3_1()
{
	srand((unsigned)time(NULL));
	hwnd2 = initgraph(800, 700);
	setbkcolor(WHITE);
	cleardevice();
	initSnake();
	BeginBatchDraw();
	while (1)
	{
		cleardevice(); //刷掉路径
		if (snakeDie())
		{
			food.eatGrade = 0;
			MessageBox(hwnd2, "游戏结束!", "消息", MB_OK);
			break;
		}
		eatFood();
		drawFood();
		drawSnake();
		showScore();
		moveSnake();
		Sleep(50);
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}
//游戏三2
void game_3_2()
{
	srand((unsigned)time(NULL));
	hwnd3 = initgraph(800, 700);
	setbkcolor(WHITE);
	cleardevice();
	initSnake();
	BeginBatchDraw();
	while (1)
	{
		cleardevice();  //刷掉路径
		if (snakeDie_1())
		{
			food.eatGrade = 0;
			MessageBox(hwnd3, "游戏结束!", "消息", MB_OK);
			break;
		}
		eatFood();
		drawFood();
		drawSnake();
		showScore();	
		if (_kbhit())
		{
			moveSnake1();
		}
		crossWall();
		
		Sleep(110);
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}
//小菜单
void caidan1()
{
	initgraph(800, 700);
	IMAGE m;
	loadimage(&m, "picture.jpg", 800, 700);
	struct button* game3_1 = CreatButton(300, 200, 200, 50, YELLOW, "  自动  ");
	struct button* game3_2 = CreatButton(300, 300, 200, 50, YELLOW, "  手动  ");
	struct button* return_1 = CreatButton(300, 400, 200, 50, YELLOW, "  返回  ");
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		putimage(0, 0, &m);
		DrawButton(game3_1);
		DrawButton(game3_2);
		DrawButton(return_1);
		MOUSEMSG m = GetMouseMsg();
		if (clickbutton(game3_1, m))
		{
			game_3_1();
			break;
		}
		if (clickbutton(game3_2, m))
		{
			game_3_2();
			break;
		}
		if (clickbutton(return_1, m))
		{
			a = 1;
			break;
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}
//菜单功能
void caidan()
{
	initgraph(800, 700);
	IMAGE m;
	loadimage(&m, "picture.jpg", 800, 700);
	struct button* game1 = CreatButton(300, 200, 200, 50, YELLOW, "开始游戏1");
	struct button* game2 = CreatButton(300, 300, 200, 50, YELLOW, "开始游戏2");
	struct button* game3 = CreatButton(300, 400, 200, 50, YELLOW, "开始游戏3");
	struct button* close = CreatButton(300, 500, 200, 50, YELLOW, "退出游戏");
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		putimage(0, 0, &m);
		DrawButton(game1);
		DrawButton(game2);
		DrawButton(game3);
		DrawButton(close);
		MOUSEMSG m = GetMouseMsg();
		if (clickbutton(game1, m))
		{
			game_1();
			break;
		}
		if (clickbutton(game2, m))
		{
			game_2();
			break;
		}
		if (clickbutton(game3, m))
		{
			while (1)
			{
				caidan1();
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));//清除缓存
				if (a)
				{
					a = 0;
					break;
				}
			}
			break;
		}
		if (clickbutton(close, m))
		{
			exit(0);
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}
int main()
{
	while (1)
	{
		caidan();
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));//清除缓存
	}
	return 0;
}