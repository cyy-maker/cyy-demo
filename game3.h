#ifndef game3_h
#define game3_h
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define MAX 1000
HWND hwnd2,hwnd3;
int a = 0;
typedef struct pointXY
{
	int x;
	int y;
}mypoint;
//蛇
struct mySnake
{
	int num;
	mypoint xy[MAX];
	char postion;
}snake;
//食物
struct myFood
{
	mypoint foodxy;
	int flag;
	int eatGrade;
}food;
//枚举方向
enum movePostion { right, left, down, up };
//初始化蛇
void initSnake()
{
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;
	snake.num = 3;
	snake.postion = right;
	food.flag = 0;
}
//画蛇
void drawSnake()
{
	setlinecolor(RED);
	setfillcolor(LIGHTCYAN);
	fillrectangle(snake.xy[0].x, snake.xy[0].y, snake.xy[0].x + 10, snake.xy[0].y + 10);
	for (int i = 1; i < snake.num; i++)
	{
		setlinecolor(RED);
		setfillcolor(GREEN);
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}
//手动
void keyDown1()
{
	if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
	{

		if (snake.postion != down)
		{
			snake.postion = up;
		}
	}
	if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
	{
		if (snake.postion != up)
		{
			snake.postion = down;
		}
	}
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
	{
		if (snake.postion != right)
		{
			snake.postion = left;
		}
	}
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
	{
		if (snake.postion != left)
		{
			snake.postion = right;
		}
	}
}
//自动斜
void keyDown()
{
	static char userkey = '\0';
	switch (snake.postion)
	{
	case right:
	case left:
		if (food.foodxy.y > snake.xy[0].y)
		{
			userkey = 80;
		}
		else if (food.foodxy.y < snake.xy[0].y)
		{
			userkey = 72;
		}
		break;
	case up:
	case down:
		if (food.foodxy.x > snake.xy[0].x)
		{
			userkey = 77;
		}
		else if (food.foodxy.x < snake.xy[0].x)
		{
			userkey = 75;
		}
		break;
	}
	switch (userkey)
	{
	case 72:
		snake.postion = up;
		break;
	case 80:
		snake.postion = down;
		break;
	case 75:
		snake.postion = left;
		break;
	case 77:
		snake.postion = right;
		break;
	}
	if (food.foodxy.x == snake.xy[0].x && snake.postion == up && food.foodxy.y > snake.xy[0].y)
	{
		userkey = 77;
	}
	if (food.foodxy.x == snake.xy[0].x && snake.postion == down && food.foodxy.y < snake.xy[0].y)
	{
		userkey = 75;
	}
	if (food.foodxy.y == snake.xy[0].y && snake.postion == right && food.foodxy.x < snake.xy[0].x)
	{
		userkey = 72;
	}
	if (food.foodxy.y == snake.xy[0].y && snake.postion == left && food.foodxy.x > snake.xy[0].x)
	{
		userkey = 80;
	}
}
void snakeF()
{
	if (food.foodxy.x == snake.xy[0].x && snake.postion == up && food.foodxy.y > snake.xy[0].y)
	{
		snake.postion = right;
		if (snake.xy[0].y == 0)
		{
			snake.postion = right;
		}
		if (snake.xy[0].y == 790)
		{
			snake.postion = left;
		}
	}
	if (food.foodxy.x == snake.xy[0].x && snake.postion == down && food.foodxy.y < snake.xy[0].y)
	{
		snake.postion = right;
		if (snake.xy[0].y == 0)
		{
			snake.postion = right;
		}
		if (snake.xy[0].y == 790)
		{
			snake.postion = left;
		}
	}
	if (food.foodxy.y == snake.xy[0].y && snake.postion == right && food.foodxy.x < snake.xy[0].x)
	{
		snake.postion = down;
		if (snake.xy[0].x == 0)
		{
			snake.postion = down;
		}
		if (snake.xy[0].y == 690)
		{
			snake.postion = up;
		}

	}
	if (food.foodxy.y == snake.xy[0].y && snake.postion == left && food.foodxy.x > snake.xy[0].x)
	{
		snake.postion = down;
		if (snake.xy[0].x == 0)
		{
			snake.postion = down;
		}
		if (snake.xy[0].y == 690)
		{
			snake.postion = up;
		}
	}
}
//自动横
void key_down()
{
	if (food.foodxy.y > snake.xy[0].y)
	{
		if (food.foodxy.x > snake.xy[0].x)
			snake.postion = right;
		if (food.foodxy.x < snake.xy[0].x)
			snake.postion = left;
		if (food.foodxy.x == snake.xy[0].x)
			snake.postion = down;
	}
	if (food.foodxy.y < snake.xy[0].y)
	{
		if (food.foodxy.x > snake.xy[0].x)
			snake.postion = right;
		if (food.foodxy.x < snake.xy[0].x)
			snake.postion = left;
		if (food.foodxy.x == snake.xy[0].x)
			snake.postion = up;
	}
	snakeF();
}
//移动蛇（自动）
void moveSnake()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	keyDown();
	switch (snake.postion)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	}
}
//移动蛇（手动）
void moveSnake1()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	keyDown1();
	switch (snake.postion)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	}
}
//初始化食物
void initFood()
{
	food.foodxy.x = rand() % 79 * 10;
	food.foodxy.y = rand() % 69 * 10;
	food.flag = 1;
	//食物不能出现在蛇身上
	for (int i = 0; i < snake.num; i++)
	{
		if (food.foodxy.x == snake.xy[i].x && food.foodxy.y == snake.xy[i].y)
		{
			food.foodxy.x = rand() % 79 * 10;
			food.foodxy.y = rand() % 69 * 10;
		}
	}
}
//画食物
void drawFood()
{
	setfillcolor(RED);
	fillrectangle(food.foodxy.x, food.foodxy.y, food.foodxy.x + 10, food.foodxy.y + 10);
}
//蛇吃食物
void eatFood()
{
	if (snake.xy[0].x == food.foodxy.x && snake.xy[0].y == food.foodxy.y)
	{
		snake.num++;
		food.eatGrade += 10;
		food.flag = 0;
		
	}
	if (food.flag == 0)
	{
			initFood();
	}
}
//显示分数
void showScore()
{
	char grade[100] = { 0 };
	sprintf(grade, "%d", food.eatGrade);
	setbkcolor(TRANSPARENT);
	settextcolor(LIGHTGRAY);
	outtextxy(680, 20, "分数:");
	outtextxy(720, 20, grade);
}
//游戏结束
int snakeDie()
{
	if (snake.xy[0].x < 0 || snake.xy[0].x > 800 || snake.xy[0].y < 0 || snake.xy[0].y >700)
	{
		return 1;
	}
	//for (int i = 1; i < snake.num; i++)
	//{
	//	if (snake.xy[0].x == snake.xy[i].x && snake .xy[0].y == snake.xy[i].y)
	//	{
	//		return 1;
	//	}
	//}
	return 0;
}
//穿墙
void crossWall()
{
	if (snake.xy[0].x < 0)
	{
		snake.xy[0].x = 790;
	}
	if (snake.xy[0].x > 800)
	{
		snake.xy[0].x = 10;
	}
	if (snake.xy[0].y < 0)
	{
		snake.xy[0].y = 690;
	}
	if (snake.xy[0].y > 700)
	{
		snake.xy[0].y = 10;
	}
}
int snakeDie_1()
{
	/*if (snake.xy[0].x < 0 || snake.xy[0].x > 800 || snake.xy[0].y < 0 || snake.xy[0].y >700)
	{
		return 1;
	}*/
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x && snake .xy[0].y == snake.xy[i].y)
		{
			return 1;
		}
	}
	return 0;
}
#endif