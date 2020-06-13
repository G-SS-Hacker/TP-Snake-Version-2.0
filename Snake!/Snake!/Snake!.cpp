/*
 * TP Snake! version 2.0
 * Presented by G-SS-Hacker
 * cc BY-NC-SA 4.0
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")	//导入winmm.lib库

#define MAXT 200	//最大尝试次数
#define MAXN 200	//最大蛇长
#define SIZE 10		//一节蛇宽度

 //设置速度（默认为50）
const int speed = 50;

//枚举方向（代替宏定义）
enum Dir
{
	up = 72, down = 80, left = 75, right = 77, w = 'w', a = 'a', s = 's', d = 'd'
};

//坐标（笛卡尔坐标系）
struct Coor
{
	int x;
	int y;
};

//蛇的结构
struct Snake
{
	int n;			//蛇的节数
	enum Dir dir;		//蛇的方向
	struct Coor szb[MAXN];	//蛇坐标
};

//食物的结构
struct Food
{
	int x;
	int y;
	int iseat;		//是否被吃
};

struct Snake snake[2];		//定义一条蛇
struct Food  food;			//定义一个食物

//初始化游戏：设置随机数种子，设置蛇初始长度、位置、方向，设置食物状态（被吃）
void InitGame();
//绘制开始画面
void ShowStartScreen();
//绘制结束画面
void ShowEndScreen();
//绘制游戏画面：画分数、画蛇、画食物
void DrawGame();
//画食物：绿色食物，这条蛇吃素
void DrawFood();
//移动蛇：从蛇头到蛇尾依次移动一格
void MoveSnake();
//产生食物：被吃才产生，随机位置产生，防止食物与蛇重叠
void CreateFood();
//吃掉食物：更新食物状态，增加蛇的长度
void EatFood();
//边界条件：蛇头碰壁、蛇头与蛇身重合
int GameOver();
//检测按键合法性0：不是上下左右
int InvalidKey0(char key);
//检测按键合法性1：不是wasd
int InvalidKey1(char key);
//方向转换器
void DirConverter(char key);
//改变方向：读入按键，设置方向，清空键盘输入缓存
void ChangeDir();
//两数交换
void Swap(int* a, int* b);
//调整堆结构
void HeapAdjust(int arr[], int start, int end);
//堆排序
void HeapSort(int arr[], int N);

int main()
{
	//初始化计数器，排名数组，文件指针
	int cnt = 1;
	int score1[MAXT] = { 0 }, score2[MAXT] = { 0 };
	FILE* fp;

	//初始化窗口，默认640x480像素
	initgraph(640, 480);
	ShowStartScreen();

again:
	InitGame();

	while (1)
	{
		//没有键盘输入时，进行一系列动作
		while (!_kbhit())
		{
			MoveSnake();
			DrawGame();
			CreateFood();
			DrawFood();
			EatFood();
			if (GameOver())
			{
				//记录新分数并堆排序
				score1[cnt - 1] = snake[1].n - 3;
				score2[cnt - 1] = snake[0].n - 3;
				HeapSort(score1, cnt);
				HeapSort(score2, cnt);

				//初始化排行榜文件，检查是否创建成功
				fp = fopen("排行榜.txt", "w");
				if (fp == NULL)
				{
					printf("Fail to open record.txt!\n");
					exit(0);
				}

				//打印排名
				fprintf(fp, "Rank:  P1 records:  P2 records:\n");
				for (int i = 1; i <= cnt; i++)
					fprintf(fp, "%3d%12d%13d\n", i, score1[i - 1], score2[i - 1]);
				cnt++;

				ShowEndScreen();

				goto again;
			}
			Sleep(speed);
		}

		//有键盘输入时，改变蛇的方向
		//一个上面的循环期间只读取键盘的第一个输入
		ChangeDir();
	}

	fclose(fp);
	return 0;
}

//初始化游戏：设置随机数种子，设置蛇初始长度、位置、方向，设置食物状态（被吃）
void InitGame()
{
	//插入音效：Graza the Roof，并循环播放
	mciSendString(L"open GrazetheRoof.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"play bgm repeat", 0, 0, 0);

	//设置随机数种子
	srand((unsigned int)time(NULL));

	//初始化蛇，定义结构体指针
	struct Snake* p;

	p = &snake[0];
	p->n = 3;
	p->dir = right;
	p->szb[0].x = 100;
	p->szb[0].y = 200;
	p->szb[1].x = 90;
	p->szb[1].y = 200;
	p->szb[2].x = 80;
	p->szb[2].y = 200;

	p = &snake[1];
	p->n = 3;
	p->dir = d;
	p->szb[0].x = 100;
	p->szb[0].y = 280;
	p->szb[1].x = 90;
	p->szb[1].y = 280;
	p->szb[2].x = 80;
	p->szb[2].y = 280;

	//初始化食物
	food.iseat = 1;
}

//绘制开始画面
void ShowStartScreen()
{
	RECT r = { 0, 0, 639, 479 };
	drawtext(_T("TP Snake!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	outtextxy(255, 250, L"----- Version  2.0 -----");
	outtextxy(235, 300, L"Press a key to start game");
	_getch();
}

//绘制结束画面
void ShowEndScreen()
{
	RECT r = { 0, 0, 639, 479 };
	drawtext(_T("Game Over!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	outtextxy(230, 300, L"Press a key to restart game");
	_getch();
}

//绘制游戏画面：画分数、画蛇、画食物
void DrawGame()
{
	//清屏
	cleardevice();

	//画分数0
	setcolor(LIGHTRED);
	outtextxy(530, 20, L"P2 Score: ");
	setcolor(WHITE);
	TCHAR s0[6];
	_stprintf_s(s0, _T("%d"), snake[0].n - 3);
	outtextxy(600, 20, s0);

	//画分数1
	setcolor(LIGHTBLUE);
	outtextxy(20, 20, L"P1 Score: ");
	setcolor(WHITE);
	TCHAR s1[6];
	_stprintf_s(s1, _T("%d"), snake[1].n - 3);
	outtextxy(90, 20, s1);

	//画蛇0
	setfillcolor(RED);
	for (int i = 0; i < snake[0].n; i++)
		fillrectangle(snake[0].szb[i].x, snake[0].szb[i].y, snake[0].szb[i].x + SIZE, snake[0].szb[i].y + SIZE);

	//画蛇1
	setfillcolor(BLUE);
	for (int i = 0; i < snake[1].n; i++)
		fillrectangle(snake[1].szb[i].x, snake[1].szb[i].y, snake[1].szb[i].x + SIZE, snake[1].szb[i].y + SIZE);
}

//画食物：绿色食物，这条蛇吃素
void DrawFood()
{
	setfillcolor(GREEN);
	fillroundrect(food.x, food.y, food.x + SIZE, food.y + SIZE, SIZE / 2, SIZE / 2);
}

//移动蛇：从蛇头到蛇尾依次移动一格
void MoveSnake()
{
	//移动蛇0
	for (int i = snake[0].n - 1; i > 0; i--)
	{
		snake[0].szb[i].x = snake[0].szb[i - 1].x;
		snake[0].szb[i].y = snake[0].szb[i - 1].y;
	}

	switch (snake[0].dir)
	{
	case up:
		snake[0].szb[0].y -= SIZE;
		break;
	case down:
		snake[0].szb[0].y += SIZE;
		break;
	case left:
		snake[0].szb[0].x -= SIZE;
		break;
	case right:
		snake[0].szb[0].x += SIZE;
		break;
	}

	//移动蛇1
	for (int i = snake[1].n - 1; i > 0; i--)
	{
		snake[1].szb[i].x = snake[1].szb[i - 1].x;
		snake[1].szb[i].y = snake[1].szb[i - 1].y;
	}

	switch (snake[1].dir)
	{
	case w:
		snake[1].szb[0].y -= SIZE;
		break;
	case s:
		snake[1].szb[0].y += SIZE;
		break;
	case a:
		snake[1].szb[0].x -= SIZE;
		break;
	case d:
		snake[1].szb[0].x += SIZE;
		break;
	}
}

//产生食物：被吃才产生，随机位置产生，防止食物与蛇重叠
void CreateFood()
{
	//检查食物与蛇是否重复
	int flag = 0;

	//当食物已经被吃掉才会产生食物
	while (food.iseat)
	{
		//不断尝试产生食物
		while (1)
		{
			//假设食物没有与蛇重复
			flag = 0;

			//随机产生食物坐标
			food.x = rand() % 64 * 10;
			food.y = rand() % 48 * 10;

			//判断食物是否与蛇0重复
			for (int i = 0; i < snake[0].n; i++)
				if (food.x == snake[0].szb[i].x && food.y == snake[0].szb[i].y)
				{
					flag = 1;
					break;
				}

			//判断食物是否与蛇1重复
			for (int i = 0; i < snake[1].n; i++)
				if (food.x == snake[1].szb[i].x && food.y == snake[1].szb[i].y)
				{
					flag = 1;
					break;
				}

			//假如新产生的食物没有与蛇重复
			if (!flag)
			{
				food.iseat = 0;
				break;
			}
		}
	}
}

//吃掉食物：更新食物状态，增加蛇的长度
void EatFood()
{
	//更新蛇0
	if (snake[0].szb[0].x == food.x && snake[0].szb[0].y == food.y)
	{
		food.iseat = 1;
		snake[0].n++;
	}

	//更新蛇1
	if (snake[1].szb[0].x == food.x && snake[1].szb[0].y == food.y)
	{
		food.iseat = 1;
		snake[1].n++;
	}
}

//边界条件：蛇头碰壁、蛇头与蛇身重合
int GameOver()
{
	//蛇头0碰壁
	if (snake[0].szb[0].x < 0 || snake[0].szb[0].x > 639 || snake[0].szb[0].y < 0 || snake[0].szb[0].y > 479)
		return 1;

	//蛇头1碰壁
	if (snake[1].szb[0].x < 0 || snake[1].szb[0].x > 639 || snake[1].szb[0].y < 0 || snake[1].szb[0].y > 479)
		return 1;

	//蛇头0与蛇身重合：枚举
	for (int i = 1; i < snake[0].n - 1; i++)
		if (snake[0].szb[0].x == snake[0].szb[i].x && snake[0].szb[0].y == snake[0].szb[i].y)
			return 1;

	//蛇头1与蛇身重合：枚举
	for (int i = 1; i < snake[1].n - 1; i++)
		if (snake[1].szb[0].x == snake[1].szb[i].x && snake[1].szb[0].y == snake[1].szb[i].y)
			return 1;

	return 0;
}

//检测按键合法性0：不是上下左右
int InvalidKey0(char key)
{
	return ((key != up) && (key != down) && (key != left) && (key != right));
}

//检测按键合法性1：不是wasd
int InvalidKey1(char key)
{
	return ((key != w) && (key != s) && (key != a) && (key != d));
}

/*
 * 在同一个Sleep期间协调两条蛇的方向改变
 * 理想情况是：在Sleep期间最多读取两条蛇的一次动作
 * 实现：
 * 1.只要满足 既不是上下左右，又不是wasd 就不断_getch()
 * 2.第一个不满足，相应地改变方向，记录flag为0（上下左右）或1（wasd）
 * 3.只要满足 不是0/1 就不断_getch()
 * 4.第一个不满足，相应地改变方向
 * 5.清空按键缓存
 */

 //方向转换器
void DirConverter(char key)
{
	switch (key)
	{
	case up:
		if (snake[0].dir != down)
			snake[0].dir = up;
		break;
	case w:
		if (snake[1].dir != s)
			snake[1].dir = w;
		break;
	case down:
		if (snake[0].dir != up)
			snake[0].dir = down;
		break;
	case s:
		if (snake[1].dir != w)
			snake[1].dir = s;
		break;
	case left:
		if (snake[0].dir != right)
			snake[0].dir = left;
		break;
	case a:
		if (snake[1].dir != d)
			snake[1].dir = a;
		break;
	case right:
		if (snake[0].dir != left)
			snake[0].dir = right;
		break;
	case d:
		if (snake[1].dir != a)
			snake[1].dir = d;
		break;
	}
}

//改变方向：读入按键，设置方向，清空键盘输入缓存
void ChangeDir()
{
	char key;

	//读入按键：既不是上下左右，又不是wasd
	do
	{
		//一旦读完全部按键，马上返回
		if (!_kbhit())
			return;

		key = _getch();
	} while (InvalidKey0(key) && InvalidKey1(key));

	int flag = 0;

	//是上下左右之一
	if (!InvalidKey0(key))
		flag = 0;
	//是wasd之一
	if (!InvalidKey1(key))
		flag = 1;

	//相应改变方向
	DirConverter(key);

	//读入按键：第一次是wasd，第二次不是上下左右 || 第一次是上下左右，第二次不是wasd
	do
	{
		//一旦读完全部按键，马上返回
		if (!_kbhit())
			return;

		key = _getch();
	} while ((flag && InvalidKey0(key)) || (!flag && InvalidKey1(key)));

	//相应改变方向
	DirConverter(key);

	//windows提供的API，清空按键缓存
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

//两数交换
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//调整堆结构
void HeapAdjust(int arr[], int n, int i)
{
	int tmp = i;
	//定义左孩子和右孩子
	int l = 2 * i + 1;
	int r = 2 * i + 2;	//二叉树结构

	if (l < n && arr[l] < arr[tmp])
		tmp = l;

	if (r < n && arr[r] < arr[tmp])
		tmp = r;

	if (tmp != i)
	{
		Swap(&arr[i], &arr[tmp]);
		HeapAdjust(arr, n, tmp);	//递归
	}
}

//堆排序（与树数据结构相关的算法：用二叉树实现的堆排序）
void HeapSort(int arr[], int N)
{
	for (int i = N / 2 - 1; i >= 0; i--)  //构建二叉堆
		HeapAdjust(arr, N, i);
	for (int i = N - 1; i > 0; i--)       //不断调整，直到堆的大小为1
	{
		Swap(&arr[0], &arr[i]);
		HeapAdjust(arr, i, 0);
	}
}
