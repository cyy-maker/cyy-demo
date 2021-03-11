#ifndef game1_h
#define game1_h
#include <graphics.h>
#include <time.h>
#include "caidan.h"
int map[5][8];
HWND hwnd = NULL;
//初始化地图
void initMap()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
		{
			map[i][j] = rand() % 4;
		}
}
//画地图
void drawMap()
{
	setlinestyle(PS_SOLID, 2);
	setlinecolor(BLACK);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
		{
			int x = 100 * j;
			int y = 25 * i;
			switch (map[i][j])
			{
			case 0:
				break;
			case 1:
				setfillcolor(YELLOW);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 2:
				setfillcolor(GREEN);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 3:
				setfillcolor(RED);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			}
		}
}
struct Board
{
	int x;
	int y;
	int speed;
	COLORREF color;
	int width;
	int height;
};
//初始化木板
struct Board* CreatBoard(int x, int y, int speed, COLORREF color, int width, int height)
{
	struct Board* pBoard = (struct Board*)malloc(sizeof(struct Board));
	if (pBoard != NULL)
	{
		pBoard->x = x;
		pBoard->y = y;
		pBoard->speed = speed;
		pBoard->color = color;
		pBoard->width = width;
		pBoard->height = height;
		return pBoard;
	}

}
//画木板
void drawBoard(struct Board* pBoard)
{
	setfillcolor(pBoard->color);
	fillrectangle(pBoard->x, pBoard->y, pBoard->x + pBoard->width, pBoard->y + pBoard->height);
}
//按键移动
void keyDown(struct Board* pBoard)
{
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT) && pBoard->x >= 0)
	{
		pBoard->x -= pBoard->speed;
	}
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT) && pBoard->x <= 600)
	{
		pBoard->x += pBoard->speed;
	}
}
struct Ball
{
	int x;
	int y;
	int r;
	int dx;
	int dy;
	COLORREF color;
};
//初始化小球
struct Ball* CreatBall(int x, int y, int r, int dx, int dy, COLORREF color)
{
	struct Ball* pBall = (struct Ball*)malloc(sizeof(struct Ball));
	if (pBall != NULL)
	{
		pBall->x = x;
		pBall->y = y;
		pBall->r = r;
		pBall->dx = dx;
		pBall->dy = dy;
		pBall->color = color;
		return pBall;
	}
}
//画小球
void drawBall(struct Ball* pBall)
{
	setfillcolor(pBall->color);
	setlinestyle(PS_SOLID, 2);
	setlinecolor(WHITE);
	fillcircle(pBall->x, pBall->y, pBall->r);
}
//打在木板上
int  HitBoardup(struct Ball* pBall, struct Board* pBoard)
{
	if (pBall->y + pBall->r == pBoard->y)
		if (pBall->x >= pBoard->x && pBall->x + pBall->r <= pBoard->x + pBoard->width)
			return 1;
	return 0;
}
//游戏失败
int die(struct Ball* pBall)
{
	if (pBall->y > 800 - 25)
		return 1;
	return 0;
}
//打在砖块
int HitBricks(struct Ball* pBall)
{
	int balli = (pBall->y - pBall->r) / 25;
	int ballj = pBall->x / 100;
	if (balli < 5 && ballj < 8 && map[balli][ballj] != 0)
	{
		map[balli][ballj] = 0;
		return 1;
	}
	return 0;
}
//小球移动
void moveBall(struct Ball* pBall, struct Board* pBoard)
{
	if (pBall->x - pBall->r <= 0 || pBall->x + pBall->r >= 800)
	{
		pBall->dx = -pBall->dx;
	}
	if (pBall->y - pBall->r <= 0|| HitBoardup(pBall, pBoard) || HitBricks(pBall))
	{
		pBall->dy = -pBall->dy;
	}
	pBall->x += pBall->dx;
	pBall->y += pBall->dy;
}
//定时器
int Timer(time_t num, int id)
{
	static time_t start[10];
	time_t end = clock();
	if (end - start[id] > num)
	{
		start[id] = end;
		return 1;
	}
	return 0;
}
//游戏结束
int GameOver()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
		{
			if (map[i][j] != 0)
				return 0;
		}
	return 1;
}
#endif