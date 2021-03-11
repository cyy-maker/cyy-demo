#ifndef game2_h
#define game2_h
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
HWND hwnd1 = NULL;
//游戏正确和错误数
double right1 = 0;
double error = 0;
int q = 0;
//字符结构体
struct target
{
	int x;
	int y;
	char* str;
};
//用户输入值
struct Userkey
{
	int x;
	int y;
	char str[20];
}usersky = { 300,675,"" };
//随机产生字符
void initTarget(struct target words[], int n)
{
	char str[6];
	char ch;
	int m = rand() % 5 + 1;
	for (int i = 0; i < m; i++)
	{
		while (1)
		{
			ch = rand() % 123;
			if ((ch >= 65 && ch <= 90) || ch >= 97)
				break;
		}
		str[i] = ch;
	}
	str[m] = '\0';
	words[n].str = (char*)malloc(sizeof(words[n].str));
	if (str != 0)
		strcpy(words[n].str, str);
	words[n].x = rand() % 550;
	words[n].y = -20;
}
//初始化字符
void CreatTarget(struct target words[])
{
	for (int i = 0; i < 3; i++)
	{
		initTarget(words, i);
		words[i].y = -15 - i * 50;
	}
}
//产生掉落的字符串
void downTarget(struct target words[])
{

	for (int i = 0; i < 3; i++)
	{
		int flag1 = 0;
		words[i].y += 2;
		if (words[i].y > 650 - textheight(words[i].str))
		{
			initTarget(words, i);
			flag1++;
		}
		if (flag1 == 1)
		{
			error++;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		settextcolor(LIGHTCYAN);
		settextstyle(20, 10, "KUNSTLER");
		outtextxy(words[i].x, words[i].y, words[i].str);
	}
	Sleep(30);
}
//键盘输入字符
void Userinput(struct target words[],char ch)
{
		int i;
		if (ch != '\r' && ch != VK_ESCAPE && ch != VK_BACK)
		{
			usersky.str[q++] = ch;
		}
		if (ch == '\r')
		{
			for (i = 0; i < 3; i++)
			{
				if (strcmp(usersky.str, words[i].str) == 0)
				{
					initTarget(words, i);
					right1++;
				}
			}
			q = 0;
			usersky.x = 300;
			memset(usersky.str, 0, 20);//重新定义字符串（清除字符串)
		}
		if (ch == VK_BACK)
		{
			if (ch != 0)
			{
				if(usersky.str[0] != '\0')
					usersky.str[--q] = '\0';
			}
		}
}
//指定位置输出整数
void outtextxy_int(int x, int y, const char* format, int num)
{
	char str[20] = "";
	sprintf(str, format, num);
	outtextxy(x, y, str);
}
//指定位置输出浮点数
void outtextxy_double(int x, int y, const char* format, double num)
{
	char str[20] = "";
	sprintf(str, format, num);
	outtextxy(x, y, str);
}
//画线（窗口布局)
void divWindow()
{
	setlinecolor(GREEN);
	line(0, 650, 800, 650);
	line(600, 0, 600, 650);
	line(600, 200, 800, 200);
}
void drawscore()
{
	settextcolor(LIGHTBLUE);
	settextstyle(25, 0, "STXINWEI");
	outtextxy(650, 25, "打字游戏");
	outtextxy(610, 60, "按回车键结束一");
	outtextxy(610, 95, "次输入");
	outtextxy(610, 130, "按ESC键退出游戏");
	outtextxy(650, 300, "正确数");
	outtextxy_int(650, 350, "%d", right1);
	outtextxy(650, 400, "错误数");
	outtextxy_int(650, 450, "%d", error);
	outtextxy(650, 500, "正确率");
	if (right1 + error == 0)
	{
		outtextxy_double(650, 550, "%.2lf%%", 0.00);
	}
	else
	{
		double num;
		num = (right1 + error);
		outtextxy_double(650, 550, "%.2lf%%", (right1 / num) * 100);
	}
}
#endif