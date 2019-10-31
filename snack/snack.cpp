// T.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>

#define MAP_WIDTH 60
#define MAP_HEIGHT 20

typedef enum KEY {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_QUIT,
	KEY_UNKNOWN
} KEY;


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

// 默认移动方向
KEY g_key = KEY_LEFT;

int g_score;

// 只绘制右边和底边边框
// 
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
				printf("|");
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
		printf("\n");
	}

	printf("w:上 a:左 s:下 d:右\n");
		printf("made be 瞎搞 \n");
}

void DrawChar(int x, int y, char c)
{								
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(c);
}

// 绘制蛇身
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

void InitFood()
{
	srand((unsigned int)time(NULL));
	g_food.x = rand() % MAP_WIDTH;
	g_food.y = rand() % MAP_HEIGHT;
}

//去掉控制台光标
void InitEnv()
{
	//去掉控制台光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}


KEY GetKey(int key)
{
	switch (key)
	{
	case 'W':
	case 'w':
		return KEY_UP;
	case 'a':
	case 'A':
		return KEY_LEFT;
	case 's':
	case 'S':
		return KEY_DOWN;
	case 'd':
	case 'D':
		return KEY_RIGHT;
	case 'q':
	case 'Q':
		return KEY_QUIT;
	default:
		return KEY_UNKNOWN;
	}
}


void SnackMove(KEY key)
{
	int i;
	int delta_x = 0;
	int delta_y = 0;

	// 因为蛇移动时，最后一个节点必须清空，否则会有残影
	DrawChar(g_snack.pos[g_snack.size -1].x, g_snack.pos[g_snack.size -1].y, ' ');

	// 2  1  0
	//    2  1  0
	for (i = g_snack.size - 1; i > 0; i--)
	{
		g_snack.pos[i].x = g_snack.pos[i - 1].x;
		g_snack.pos[i].y = g_snack.pos[i - 1].y;
	}

	// 有效按键则更新方向
	if (key != KEY_UNKNOWN && key != KEY_QUIT)
	{
		g_key = key;
	}

	switch (g_key)
	{
	case KEY_UP:
		delta_x = 0;
		delta_y = -1;
		break;
	case KEY_LEFT:
		delta_x = -1;
		delta_y = 0;
		break;
	case KEY_RIGHT:
		delta_x = 1;
		delta_y = 0;
		break;
	case KEY_DOWN:
		delta_x = 0;
		delta_y = 1;
		break;
	default:
		delta_x = 0;
		delta_y = 0;
		break;
	}
	g_snack.pos[0].x += delta_x;
	g_snack.pos[0].y += delta_y;
}

// 撞墙
int HitWall()
{
	// 头出界
	if (g_snack.pos[0].x < 0 ||
		g_snack.pos[0].x > MAP_WIDTH ||
		g_snack.pos[0].y < 0 ||
		g_snack.pos[0].y > MAP_HEIGHT)
	{
		return -1;
	}

	return 0;
}

// 吃自己
int HitSelf()
{
	// 头碰到身体其他部分
	int i;

	for (i = 1; i < g_snack.size; i++)
	{
		if (g_snack.pos[0].x == g_snack.pos[i].x &&
			g_snack.pos[0].y == g_snack.pos[i].y)
		{
			return -1;
		}
	}

	return 0;
}

// 吃食物
void EatFood()
{

	if (g_snack.pos[0].x == g_food.x && 
		g_snack.pos[0].y == g_food.y)
	{
		InitFood();

		// 新的节点跟最后一个节点重合
		g_snack.pos[g_snack.size].x = g_snack.pos[g_snack.size - 1].x;
		g_snack.pos[g_snack.size].y = g_snack.pos[g_snack.size - 1].y;
		g_snack.size++;

		g_score += 250;
	}
}

void GameLoop()
{
	KEY key = KEY_UNKNOWN;

	while (1)
	{
		// 检测按键
		if (_kbhit())
		{
			key = GetKey(_getch());
		}

		// 移动蛇
		SnackMove(key);

		// 退出游戏
		if (key == KEY_QUIT)
		{
			return;
		}
		
		if (HitWall() || HitSelf())
		{
			// game over
			return;
		}

		EatFood();

		// 绘制蛇
		DrawSnack();

		DrawFood();

		// 延时
		Sleep(20);
	}
}

void Score()
{
	system("cls");
	printf("游戏结束\n分数：%d\n", g_score);
}

int main(int argc, char* argv[])
{
	InitEnv();

	InitMap();

	InitSnack();

	InitFood();

	GameLoop();

	Score();

	return 0;
}