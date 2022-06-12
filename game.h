#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#define MINE "★"				//雷（明示）
#define SIGN_MINE "☆"			//雷（标记）
#define SPACE "　"				//边界
#define MINE_COLOR 0x40			//雷
#define MENU_COLOR 0x0e			//菜单
#define MAP_COLOR 0x8f			//地图框架
#define UNKNOW_COLOR 0x70		//未知地区
#define SEL_COLOR 0x3f			//菜单选中
#define BG_COLOR 0xf0			//背景
#define TIP_COLOR 0x06			//提示
#define PLR_COLOR 0x60			//玩家操作
#define COL_MAX 21				//地图最大尺寸（不要随便修改）

#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

//设置控制台光标位置
void setrd(int, int);
//设置输出颜色
void setcl(int);
//打印等宽字符
void print_fwchar(int);
//主菜单
int menu();
//设置
void menu_set(int*, int*);
//打印地图
void print_map(short[COL_MAX][COL_MAX], int, short[COL_MAX][COL_MAX]);
//打印提示
void print_tips(int, int, char*);
//放置雷
void set_mine(short[COL_MAX][COL_MAX], int, int);
//打印雷
void print_all_mine(short[COL_MAX][COL_MAX], int, int, short[COL_MAX][COL_MAX]);
//玩家操作
int play(short[COL_MAX][COL_MAX], int, short[COL_MAX][COL_MAX]);
//状态判断
int state(short[COL_MAX][COL_MAX], short[COL_MAX][COL_MAX], int);
//打印地图上的元素
void print_ele(short[COL_MAX][COL_MAX], int, int);
//打印玩家操作
void print_plrcr(int, int, short[COL_MAX][COL_MAX], short[COL_MAX][COL_MAX], int);
//画初始区域
void initial_area(short[COL_MAX][COL_MAX], int, short[COL_MAX][COL_MAX]);
//递归探索
void mine_clearance(int, int, short[COL_MAX][COL_MAX], short[COL_MAX][COL_MAX], int, int);

#endif