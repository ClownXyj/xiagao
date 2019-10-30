// snack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
// 游戏功能列表
//1.贪吃蛇上下左右移动
//2.贪吃蛇吃食物长大
//3.贪吃蛇撞墙，吃到自己，gg
//4.游戏结束，打印得分


//定义地图的大小
#define MAP_WIDTH 60
#define MAP_HEIGHT 20  



typedef struct Position
{
	// x坐标
	int x;
	// y坐标
	int y;
} Position;

typedef struct Snack
{
	// 跟地图一样大的一个数组
	Position pos[MAP_WIDTH * MAP_HEIGHT];

	// 身子长度
	int size;
} Snack;

// 蛇
Snack g_snack;

// 食物坐标
Position g_food;

void DrawChar(int x, int y, char c)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(c);
}

void InitMap()
{
	int i;
	int j;

	// 一行一行画  <=
	for (i = 0; i <= MAP_HEIGHT; i++)
	{
		for (j = 0; j <= MAP_WIDTH; j++)
		{
			if (j == MAP_WIDTH)
			{
				printf("|\n");
			}
			else if (i == MAP_HEIGHT)
			{
				printf("-");
			}
			else
			{
				printf(" ");
			}
		}
	}
}

void InitFood()
{
	srand((unsigned int)time(NULL));
	g_food.x = rand() % MAP_WIDTH;
	g_food.y = rand() % MAP_HEIGHT;
}

// 绘制食物
void DrawFood()
{
	DrawChar(g_food.x, g_food.y, '#');
}

// 地图中间创建两个节点，一个头，一个尾巴
void InitSnack()
{
	g_snack.size = 2;
	g_snack.pos[0].x = MAP_WIDTH / 2;
	g_snack.pos[0].y = MAP_HEIGHT / 2;

	g_snack.pos[1].x = MAP_WIDTH / 2 - 1;
	g_snack.pos[1].y = MAP_HEIGHT / 2;
}



void DrawSnack()
{
	int i;

	for (i = 0; i < g_snack.size; i++)
	{
		// head
		if (i == 0)
		{
			DrawChar(g_snack.pos[i].x, g_snack.pos[i].y, '*');
		}
		else
		{
			DrawChar(g_snack.pos[i].x, g_snack.pos[i].y, '#');
		}
	}
}

void GameLoop()
{
    while (1)
	{
	//延时
	Sleep(100);
	
	}

}

void Score()
{

}




void Init()
{

	// 初始化，画地图
	InitMap();
	InitSnack();
	DrawSnack();
   //初始化食物
	InitFood();
	DrawFood();
}








int main(int argc, char* argv[])
{
    Init();    
	// 游戏的主循环，按键处理，游戏画面刷新，处理撞墙等事件
	GameLoop();
     
	//打印得分
	Score();
	return 0;
}

