//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//    date:   2022-5-8
//    author: Akashi (氟氟)
//    github: https://github.com/AkashiNeko/mine
//    QQ:     1006554341
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#include "game.h"

HANDLE h;

void setrd(int x, int y)
{
	COORD rd;
	rd.X = x;
	rd.Y = y;
	SetConsoleCursorPosition(h, rd);
}

void setcl(int color)
{
	SetConsoleTextAttribute(h, color);
}

int game(short map[COL_MAX][COL_MAX], int size, int mine)
{
	int play_ret;
	//打印地图
	do
	{
		short display[COL_MAX][COL_MAX]; //是否显示（遮罩）
		print_map(map, size, display);
		memset(display, 0, sizeof(display));
		memset(map, 0, sizeof(display)); //初始化
		//设置雷
		set_mine(map, size, mine);

		//初始区域
		initial_area(map, size, display);

		//玩家操作
		play_ret = play(map, size, display);
		if (play_ret == 1) //退出
			return 1;
		if (play_ret == 2) //重开
			continue;
	} while (1);

	return 0;
}
int main()
{
	short map[COL_MAX][COL_MAX];
	int size = 15, mine = 40, game_ret;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	system("chcp 65001");
	system("cls");
	system("title 扫雷 - By AkashiNeko");
	memset(map, 0, sizeof(map)); //初始化
	setcl(0x0f);
start:
	switch (menu())
	{
	case 0:
		//开始
		game_ret = game(map, size, mine);
		if (game_ret)
		{
			setcl(0x0f);
			system("cls");
			goto start;
		}
		break;
	case 1:
		//设置
		menu_set(&size, &mine);
		setcl(0x0f);
		system("cls");
		goto start;
		break;
	case 2:
		//退出
		return 0;
	}
	return 0;
}