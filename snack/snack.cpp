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
// ��Ϸ�����б�
//1.̰�������������ƶ�
//2.̰���߳�ʳ�ﳤ��
//3.̰����ײǽ���Ե��Լ���gg
//4.��Ϸ��������ӡ�÷�


//�����ͼ�Ĵ�С
#define MAP_WIDTH 60
#define MAP_HEIGHT 20  



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

int g_score;

// ʳ������
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

	// һ��һ�л�  <=
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

void SnackMove(int key)
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


	switch (key)
	{
	case 'W':
	case 'w':
		delta_x = 0;
		delta_y = -1;
		break;
	case 'a':
	case 'A':
		delta_x = -1;
		delta_y = 0;
		break;
	case 'd':
	case 'D':
		delta_x = 1;
		delta_y = 0;
		break;
	case 's':
	case 'S':
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



void UpdateScreen()
{
  DrawSnack();
}


// ��ʳ��
void EatFood()
{
	
	if (g_snack.pos[0].x == g_food.x && 
		g_snack.pos[0].y == g_food.y)
	{
	    InitFood();
    	g_snack.size++;
		// �µ�β�ڵ��ʳ�������һ��
		g_snack.pos[g_snack.size].x = g_food.x;
		g_snack.pos[g_snack.size].y = g_food.y;

	    
	
	}
}

void GameLoop()
{
	int key  =0;

    while (1)
	{
    // �����������


	//����Ƿ��а�������
		if (_kbhit())
		{
		  key = _getch();
		}

	//��q�˳���Ϸ
        if (key == 'q' ||  key == 'Q')
		{
		  return;
		}
    EatFood();
	SnackMove(key);
	// ����ײǽ�¼�


	//���»���
		UpdateScreen();


	//��ʱ
	Sleep(100);
	
	}

}

void Score()
{

}




void Init()
{

	// ��ʼ��������ͼ
	InitMap();
	InitSnack();

	DrawSnack();
   //��ʼ��ʳ��
	InitFood();
   
	DrawFood();
	
}








int main(int argc, char* argv[])
{
    Init();    
	// ��Ϸ����ѭ��������������Ϸ����ˢ�£�����ײǽ���¼�
 
	GameLoop();
     
	//��ӡ�÷�
	Score();
	return 0;
}

