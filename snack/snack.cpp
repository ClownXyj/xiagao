// T.cpp : �������̨Ӧ�ó������ڵ㡣
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
	// x����
	int x;
	// y����
	int y;
} Position;

typedef struct Snack
{
	// ����ͼһ�����һ������
	Position pos[MAP_WIDTH * MAP_HEIGHT];

	// ���ӳ���
	int size;
} Snack;

// ��
Snack g_snack;

// ʳ������
Position g_food;

// Ĭ���ƶ�����
KEY g_key = KEY_LEFT;

int g_score;

// ֻ�����ұߺ͵ױ߱߿�
// 
void InitMap()
{
	int i;
	int j;

	// һ��һ�л�  <=
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

	printf("w:�� a:�� s:�� d:��\n");
		printf("made be Ϲ�� \n");
}

void DrawChar(int x, int y, char c)
{								
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(c);
}

// ��������
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

// ����ʳ��
void DrawFood()
{
	DrawChar(g_food.x, g_food.y, '#');
}

// ��ͼ�м䴴�������ڵ㣬һ��ͷ��һ��β��
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

//ȥ������̨���
void InitEnv()
{
	//ȥ������̨���
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

	// ��Ϊ���ƶ�ʱ�����һ���ڵ������գ�������в�Ӱ
	DrawChar(g_snack.pos[g_snack.size -1].x, g_snack.pos[g_snack.size -1].y, ' ');

	// 2  1  0
	//    2  1  0
	for (i = g_snack.size - 1; i > 0; i--)
	{
		g_snack.pos[i].x = g_snack.pos[i - 1].x;
		g_snack.pos[i].y = g_snack.pos[i - 1].y;
	}

	// ��Ч��������·���
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

// ײǽ
int HitWall()
{
	// ͷ����
	if (g_snack.pos[0].x < 0 ||
		g_snack.pos[0].x > MAP_WIDTH ||
		g_snack.pos[0].y < 0 ||
		g_snack.pos[0].y > MAP_HEIGHT)
	{
		return -1;
	}

	return 0;
}

// ���Լ�
int HitSelf()
{
	// ͷ����������������
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

// ��ʳ��
void EatFood()
{

	if (g_snack.pos[0].x == g_food.x && 
		g_snack.pos[0].y == g_food.y)
	{
		InitFood();

		// �µĽڵ�����һ���ڵ��غ�
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
		// ��ⰴ��
		if (_kbhit())
		{
			key = GetKey(_getch());
		}

		// �ƶ���
		SnackMove(key);

		// �˳���Ϸ
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

		// ������
		DrawSnack();

		DrawFood();

		// ��ʱ
		Sleep(20);
	}
}

void Score()
{
	system("cls");
	printf("��Ϸ����\n������%d\n", g_score);
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