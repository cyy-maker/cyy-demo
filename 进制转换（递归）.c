#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void convto(char* s, int n, int b)
int main()
{
	char s[80];
	int base, old;//数 ，进制
	printf("请输入十进制数：");
	scanf_s("%d", &old);
	printf("请输入转换的进制：");
	scanf_s("%d", &base);
	convto(s, old, base);
	printf("%s\n", s);
	return 0;
}
void convto(char* s, int n, int b)
{
	char bit[] = "0123456789ABCDEF";   
	int len;
	if (n == 0)
	{
		strcpy(s,"");
		return;
	}
	convto(s, n / b, b);   //递归调用
	len = strlen(s);
	s[len] = bit[n % b];
	s[len + 1] = '\0';
}
