// snack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

// 游戏功能列表
//1.贪吃蛇上下左右移动
//2.贪吃蛇吃食物长大
//3.贪吃蛇撞墙，吃到自己，gg
//4.游戏结束，打印得分

void Init()
{
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



int main(int argc, char* argv[])
{
	// 初始化，画地图
    Init();
    
	// 游戏的主循环，按键处理，游戏画面刷新，处理撞墙等事件
	GameLoop();
     
	//打印得分
	Score();
	return 0;
}

