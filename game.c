#include "game.h"

void print_fwchar(int c)
{
	switch (c)
	{
	case 1: printf("１"); break;
	case 2: printf("２"); break;
	case 3: printf("３"); break;
	case 4: printf("４"); break;
	case 5: printf("５"); break;
	case 6: printf("６"); break;
	case 7: printf("７"); break;
	case 8: printf("８"); break;
	case 9: printf("９"); break;
	default: printf("%d", c); break;
	}
}

int menu()
{
	char ch, select = 0;
	setrd(2, 2);
	setcl(MENU_COLOR);
	printf("==== 扫雷 ====");
	setrd(2, 10);
	setcl(TIP_COLOR);
	printf("[↑][↓] 移动");
	setrd(2, 12);
	printf("[Enter] 选择");

print_menu:

	setrd(4, 4);
	if (select == 0) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf(" 1. 开始 ");

	setrd(4, 6);
	if (select == 1) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf(" 2. 设置 ");

	setrd(4, 8);
	if (select == 2) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf(" 3. 退出 ");

	setrd(0, 0);
	while (1)
	{
		if (_kbhit())
			switch (ch = _getch())
			{
			case -32: //方向键
				ch = _getch();
				switch (ch)
				{
				case 72: //上
					if (select == 0)
						select = 2;
					else
						select--;
					goto print_menu;
					break;
				case 80: //下
					if (select == 2)
						select = 0;
					else
						select++;
					goto print_menu;
					break;
				default:
					break;
				}
				break;
			case 13: //回车
				setcl(0x0f);
				system("cls");
				return select;
			default:
				break;
			}
	}
}

void print_tips(int size, int color, char* str)
{
	if (size < 11)
		size = 12;
	setrd(4, size + 4);
	setcl(color);
	printf("%s", str);
	setcl(0x0f);
	printf("           ");
	setrd(0, 0);
}

void clear_tips(int size)
{
	setrd(3, size + 4);
	setcl(0x0f);
	printf("                        ");
	//用空格覆盖
}

void menu_set(int* psize, int* pmine)
{
	char ch, select = 0;
	setrd(2, 2);
	setcl(MENU_COLOR);
	printf("==== 设置 ====");
	setcl(TIP_COLOR);
	setrd(2, 16);
	printf("[ESC]     返回   ");
	goto select_menu;

print_menu_set:

	setrd(3, 4);
	if (select == 0) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf("地图大小");

	setrd(12, 4);
	if (select == 3) setcl(0x1b);
	else setcl(0x0a);
	printf("%3d", *psize);

	setrd(3, 6);
	if (select == 1) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf("地雷个数");

	setrd(12, 6);
	if (select == 4) setcl(0x1b);
	else setcl(0x0a);
	printf("%3d", *pmine);

	setrd(3, 8);
	if (select == 2) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf("返回菜单");

	setrd(0, 0);
	while (1)
	{
		if (_kbhit())
		{
			switch (ch = _getch())
			{
			case -32: //方向键
				ch = _getch();
				switch (ch)
				{
				case 72: //上
					switch (select)
					{
					case 0: select = 2; break;
					case 1: select = 0; break;
					case 2: select = 1; break;
					case 3:
						if (*psize < 20)
						{
							(*psize)++;
							if (*pmine = ((*psize) - 1) * ((*psize) - 1))
								*pmine = (int)(*psize * *psize * 0.2 + 0.5);
						}
						break;
					case 4:
						if (*pmine < 400)
						{
							(*pmine)++;
							if (*pmine > (*psize * *psize))
								(*psize)++;
						}
						break;
					}
					goto print_menu_set;
					break;
				case 80: //下
					switch (select)
					{
					case 0: select = 1; break;
					case 1: select = 2; break;
					case 2: select = 0; break;
					case 3:
						if (*psize > 3)
						{
							(*psize)--;
							if (*pmine > *psize * *psize)
								*pmine = *psize * *psize;
						}
						break;
					case 4: if (*pmine > 1) (*pmine)--; break;
					}
					goto print_menu_set;
				default:
					break;
				case 75:  //左
				case 77:; //右
				}
			case 13:	  //回车
				switch (select)
				{
				case 2: //返回
					return;
				case 0: select = 3;
					goto edit_num;
				case 1: select = 4;
					goto edit_num;
				case 3: select = 0;
					goto select_menu;
				case 4: select = 1;
					goto select_menu;
				}
			edit_num:
				setcl(TIP_COLOR);
				setrd(2, 10);
				printf("[↑][↓]  增/减");
				setrd(2, 12);
				printf("[←]      确定 ");
				setrd(2, 14);
				printf("[Enter]   确定 ");
				goto print_menu_set;
			select_menu:
				setcl(TIP_COLOR);
				setrd(2, 10);
				printf("[↑][↓]  移动  ");
				setrd(2, 12);
				printf("[→]      选择 ");
				setrd(2, 14);
				printf("[Enter]   选择  ");
				goto print_menu_set;
			case 27: //ESC
				return;
			default:
				break;
			}
		}
	}
}

void set_mine(short map[COL_MAX][COL_MAX], int size, int mine)
{
	int i, j, a, b, x, y;
	srand((unsigned)time(NULL));
	for (b = 0; b < mine; b++)
	{
		do
		{
			x = rand() % size;
			y = rand() % size;
		} while (map[x][y] == 9);
		map[x][y] = 9;
	}
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (map[i][j] == 9)
				continue;
			int num[8] = { 0,0,0,0,0,0,0,0 };
			if (i == 0) //上边界
				a = i + 1;
			else if (i == size - 1) //下边界
				a = i - 1;
			else //扫描位置位于非上下边界处
			{
				num[0] = map[i - 1][j];
				num[4] = map[i + 1][j];
				if (j == 0) //非角左边界 5
				{
					num[1] = map[i - 1][j + 1];
					num[2] = map[i][j + 1];
					num[3] = map[i + 1][j + 1];
				}
				else if (i == size - 1) //非角右边界 5
				{
					num[1] = map[i - 1][j - 1];
					num[2] = map[i][j - 1];
					num[3] = map[i + 1][j - 1];
				}
				else //中间区域 8
				{
					for (b = 0; b < 3; b++)
					{
						num[b + 1] = map[i - 1 + b][j - 1];
						num[b + 5] = map[i - 1 + b][j + 1];
					}
				}
				goto mid;
			}
			//扫描位置位于上下边界处
			num[2] = map[a][j];
			if (j == 0) //左角 3
			{
				num[0] = map[i][j + 1];
				num[1] = map[a][j + 1];
			}
			else if (j == size - 1) //右角 3
			{
				num[0] = map[i][j - 1];
				num[1] = map[a][j - 1];
			}
			else //非角边界 5
			{
				num[0] = map[i][j - 1];
				num[1] = map[i][j + 1];
				num[3] = map[a][j - 1];
				num[4] = map[a][j + 1];
			}
		mid:
			for (b = 0; b < 8; b++)
				if (num[b] == 9)
					map[i][j]++;
		}
	}
}

void print_map(short map[COL_MAX][COL_MAX], int size, short display[COL_MAX][COL_MAX])
{
	int i, j;
	setcl(MAP_COLOR);
	for (i = 0; i < size; i++) //打印左右边界
	{
		setrd(2, i + 2);//左边界
		print_fwchar(i + 1);
		setrd(4 + 2 * size, i + 2);
		printf("　"); //右边界
	}
	setrd(2, 1); //打印上边界
	printf("　ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴ");
	setrd(4, size + 2);
	for (i = 0; i < size + 1; i++) //打印下边界
		printf("　");
	setrd(2, 2 + size); //打印左下角
	printf("　");
	setrd(4 + 2 * size, 1); //打印右上角
	printf("　");
	setcl(0x0f); //删除上边界多余部分
	for (i = 0; i < COL_MAX - size - 1; i++)
		printf("　");
	//打印中间区域
	setcl(UNKNOW_COLOR);
	for (i = 0; i < size; i++)
	{
		setrd(4, i + 2);
		for (j = 0; j < size; j++)
			printf("　");
	}
	setcl(MENU_COLOR);
	setrd(12 + size * 2, 2);
	printf("[↑]");
	setrd(8 + size * 2, 4);
	printf("[←][↓][→]");
	setrd(8 + size * 2, 6);
	printf("按方向键移动");
	setrd(9 + size * 2, 8);
	printf("[Ｚ]  标记");
	setrd(9 + size * 2, 10);
	printf("[Ｘ]  排雷");
	setrd(9 + size * 2, 12);
	printf("[Ｒ]  重开");
	setrd(9 + size * 2, 14);
	printf("[Ｅ]  退出");
}

void print_all_mine(short map[COL_MAX][COL_MAX], int size, int state, short display[COL_MAX][COL_MAX])
{
	int i, j;
	if (state)
	{
		print_tips(size, 0x0a, "排雷成功!");
		setcl(0xaf);
		for (i = 0; i < size; i++) //打印左右边界
		{
			setrd(2, i + 2);//左边界
			print_fwchar(i + 1);
			setrd(4 + 2 * size, i + 2);
			printf("　"); //右边界
		}
		setrd(2, 1); //打印上边界
		printf("　ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴ");
		setrd(4, size + 2);
		for (i = 0; i < size + 1; i++) //打印下边界
			printf("　");
		setrd(2, 2 + size); //打印左下角
		printf("　");
		setrd(4 + 2 * size, 1); //打印右上角
		printf("　");
		setcl(0x0f); //删除上边界多余部分
		for (i = 0; i < COL_MAX - size - 1; i++)
			printf("　");
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				if (map[i][j] == 9)
				{
					setrd(4 + j * 2, i + 2);
					setcl(0xfd);
					printf(MINE);
				}
				else
				{
					print_ele(map, i, j);
				}
			}
		}
	}
	else
	{
		print_tips(size, 0x0c, "排雷失败!");
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				if (display[i][j] == 2 || map[i][j] == 9)
				{
					setrd(4 + j * 2, i + 2);
					if (display[i][j] == 2 && map[i][j] != 9)		 //标记错误
					{
						setcl(0xfc);
						printf(SIGN_MINE);
					}
					else if (display[i][j] != 2 && map[i][j] == 9)	 //雷未标记
					{
						setcl(0x40);
						printf(MINE);
					}
					else											 //标记正确
					{
						setcl(0xa0);
						printf(MINE);
					}
				}
				else
				{
					print_ele(map, i, j);
				}
			}
		}
	}
	setrd(0, 0);
}

void print_ele(short map[COL_MAX][COL_MAX], int i, int j)
{
	setrd(4 + j * 2, i + 2);
	if (map[i][j] == 0)
	{
		setcl(BG_COLOR);
		printf(SPACE);
	}
	else if (map[i][j] == 9)
	{
		setcl(MINE_COLOR);
		printf(MINE);
	}
	else
	{
		setcl(BG_COLOR + map[i][j]);
		print_fwchar(map[i][j]);
	}
}

int play(short map[COL_MAX][COL_MAX], int size, short display[COL_MAX][COL_MAX])
{
	char ch;
	int over = 0;
	struct coordinate {
		int x;
		int y;
	}plr; //player
	//设置玩家初始坐标
	plr.x = size / 2;
	plr.y = size / 2;
	print_plrcr(plr.x, plr.y, map, display, 1);
	while (1)
	{
		if (_kbhit())
		{
			switch (ch = _getch())
			{
			case -32:
				if (over)
					break;
				ch = _getch();
				print_plrcr(plr.x, plr.y, map, display, 0); //清除原位置
				switch (ch)
				{
				case 72: //上
					if (plr.x == 0)
						plr.x = size - 1;
					else
						plr.x--;
					print_plrcr(plr.x, plr.y, map, display, 1);
					print_tips(size, 0x07, "向上移动");
					break;
				case 80: //下
					if (plr.x == size - 1)
						plr.x = 0;
					else
						plr.x++;
					print_plrcr(plr.x, plr.y, map, display, 1);
					print_tips(size, 0x07, "向下移动");
					break;
				case 75: //左
					if (plr.y == 0)
						plr.y = size - 1;
					else
						plr.y--;
					print_plrcr(plr.x, plr.y, map, display, 1);
					print_tips(size, 0x07, "向左移动");
					break;
				case 77: //右
					if (plr.y == size - 1)
						plr.y = 0;
					else
						plr.y++;
					print_plrcr(plr.x, plr.y, map, display, 1);
					print_tips(size, 0x07, "向右移动");
					break;
				}
				break;

			case 90:  //Z
			case 122: //z
				if (over)
				{
					clear_tips(size);
					return 2;
				}
				switch (display[plr.x][plr.y])
				{
				case 2:
					display[plr.x][plr.y] = 0;
					print_plrcr(plr.x, plr.y, map, display, 1);
					print_tips(size, 0x07, "取消标记");
					break;
				case 0:
					display[plr.x][plr.y] = 2;
					print_plrcr(plr.x, plr.y, map, display, 1);
					print_tips(size, 0x07, "标记雷");
					break;
				case 1:
					print_tips(size, 0x0c, "该位置无法标记雷");
					break;
				}
				if (state(map, display, size)) //排雷成功
				{
					print_all_mine(map, size, 1, display);
					over = 1;
				}
				break;
			case 88:  //X
			case 120: //x 
				if (over)
				{
					clear_tips(size);
					return 2;
				}
				switch (display[plr.x][plr.y])
				{
				case 0:
					if (map[plr.x][plr.y] == 9)
					{
						print_all_mine(map, size, 0, display);
						over = 1;
						break;
					}
					else //无雷处，搜索四周
					{
						mine_clearance(plr.x, plr.y, map, display, size, 1);
					}
					print_plrcr(plr.x, plr.y, map, display, 1);
					print_tips(size, 0x07, "排雷");
					break;
				case 1:
					print_tips(size, 0x0c, "该位置已被排查过了");
					break;
				case 2:
					print_tips(size, 0x0c, "请先按[Ｚ]取消标记");
					break;
				}
				break;
			case 82:  //R
			case 114: //r
				clear_tips(size);
				return 2;
			case 69:  //E
			case 101: //e
			case 27:  //ESC
				return 1;
			}
		}
	}
}

void print_plrcr(int x, int y, short map[COL_MAX][COL_MAX], short display[COL_MAX][COL_MAX], int plr)
{
	setrd(4 + y * 2, 2 + x);
	if (plr == 1) //放置用户操作
	{
		switch (display[x][y])
		{
		case 0:
			setcl(PLR_COLOR);
			printf("　");
			break;
		case 1:
			if (map[x][y] == 0)
			{
				setcl(PLR_COLOR);
				printf(SPACE);
			}
			else
			{
				setcl(PLR_COLOR + map[x][y]);
				print_fwchar(map[x][y]);
			}
			break;
		case 2:
			setcl(PLR_COLOR);
			printf(SIGN_MINE);
			break;
		}
	}
	else
	{
		switch (display[x][y])
		{
		case 0:
			setcl(UNKNOW_COLOR);
			printf("　");
			break;
		case 1:
			print_ele(map, x, y);
			break;
		case 2:
			setcl(UNKNOW_COLOR);
			printf(SIGN_MINE);
			break;
		}
	}
	setrd(4 + y * 2, 2 + x);
}

void initial_area(short map[COL_MAX][COL_MAX], int size, short display[COL_MAX][COL_MAX])
{
	int i, j, r, zero = 0;
	short arr[400][2];
	srand((unsigned)time(NULL));
	for (i = 0; i < size; i++) //判断是否有空位
	{
		for (j = 0; j < size; j++)
		{
			if (map[i][j] == 0)
			{
				arr[zero][0] = i;
				arr[zero][1] = j;
				zero++;
			}
		}
	}
	if (zero == 0)
		return;
	r = rand() % zero;
	i = arr[r][0];
	j = arr[r][1];
	mine_clearance(i, j, map, display, size, 1);
}

void mine_clearance(int x, int y, short map[COL_MAX][COL_MAX], short display[COL_MAX][COL_MAX], int size, int start)
{
	if (map[x][y] == 9) //检测位置存在雷
		return;
	if (display[x][y] == 0)
		display[x][y] = 1;
	print_ele(map, x, y);

	//向上搜索
	if (x != 0 && display[x - 1][y] == 0) 
	{
		if (map[x][y] == 0 || (map[x - 1][y] == 0 && start == 1))
		{
			if (map[x - 1][y] == 0)
			{
				mine_clearance(x - 1, y, map, display, size, 0);
			}
			else if (map[x - 1][y] < 9)
			{
				display[x - 1][y] = 1;
				print_ele(map, x - 1, y);
			}
		}
	}

	//向下搜索
	if (x != size - 1 && display[x + 1][y] == 0) 
	{
		if (map[x][y] == 0 || (map[x + 1][y] == 0 && start == 1))
		{
			if (map[x + 1][y] == 0)
			{
				mine_clearance(x + 1, y, map, display, size, 0);
			}
			else if (map[x + 1][y] < 9)
			{
				display[x + 1][y] = 1;
				print_ele(map, x + 1, y);
			}
		}
	}

	//向左搜索
	if (y != 0 && display[x][y - 1] == 0) 
	{
		if (map[x][y] == 0 || (map[x][y - 1] == 0 && start == 1))
		{
			if (map[x][y - 1] == 0)
			{
				mine_clearance(x, y - 1, map, display, size, 0);
			}
			else if (map[x][y - 1] < 9)
			{
				display[x][y - 1] = 1;
				print_ele(map, x, y - 1);
			}
		}
	}

	//向右搜索
	if (y != size - 1 && display[x][y + 1] == 0) 
	{
		if (map[x][y] == 0 || (map[x][y + 1] == 0 && start == 1))
		{
			if (map[x][y + 1] == 0)
			{
				mine_clearance(x, y + 1, map, display, size, 0);
			}
			else if (map[x][y + 1] < 9)
			{
				display[x][y + 1] = 1;
				print_ele(map, x, y + 1);
			}
		}
	}
}

int state(short map[COL_MAX][COL_MAX], short display[COL_MAX][COL_MAX], int size)
{
	int s1 = 1, s2 = 1, i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (map[i][j] == 9)
				if (display[i][j] != 2)
					return 0; //位置上有雷但未标注
				else //display[i][j] == 2
					continue; //位置上有雷且标注
			else // map[i][j] != 9
				if (display[i][j] == 2)
					return 0; //位置上无雷但标注
	return 1; //地雷全部标注正确，游戏结束
}