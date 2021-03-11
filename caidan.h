#ifndef caidan_h
#define caidan_h
#include <stdio.h>
#include <graphics.h>
#include <string.h>
struct button
{
	int x;
	int y;
	int width;
	int height;
	COLORREF color;
	char* pText;
};
//初始化按钮
struct button* CreatButton(int x, int y, int width, int height, COLORREF color, const char* pText)
{
	struct button* pB = (struct button*)malloc(sizeof(struct button));
	if (pB != NULL )
	{
		pB->x = x;
		pB->y = y;
		pB->width = width;
		pB->height = height;
		pB->color = color;
		pB->pText = (char*)malloc(strlen(pText + 1));
		if(pB->pText != NULL)
			strcpy(pB->pText, pText);
	}
	return pB;
}
//画按钮
void DrawButton(struct button* pB)
{
	setfillcolor(pB->color);
	settextstyle(35, 0, "隶书");
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(pB->x,pB->y,pB->x + pB->width,pB->y + pB->height);
	outtextxy(pB->x + 25,pB->y + 10,pB->pText);
}
//判断鼠标是否在按钮中
int mouseinbutton(struct button* pB, MOUSEMSG m)
{
	if (pB->x <= m.x && pB->x + pB->width >= m.x && pB->y <= m.y && pB->y + pB->height >= m.y)
	{
		pB->color = RED;
		return 1;
	}
	pB->color = YELLOW;
	return 0;
}
//点击鼠标
int clickbutton(struct button* pB, MOUSEMSG m)
{
	if (mouseinbutton(pB, m) && m.uMsg == WM_LBUTTONDOWN)
		return 1;
	return 0;
}
#endif