#ifndef GLOBAL_H
#define GLOBAL_H
#include <graphics.h>
#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include "tools.h"
#include<math.h>

#include<mmsystem.h>//播放背景音乐和音效的头文件

#define block_TYPE 7 //方块类型数量 
#define sizeblock 30 //方块尺寸
#define ROWS 8 //方块行
#define COLS 8 //方块列
#define GAP 5 //方块间隔

extern IMAGE imgBg;
extern IMAGE blocks[block_TYPE];
extern IMAGE GAMEOVER;
extern bool ismoving; //判断移动是否结束
extern bool isclick; //判断是否点击两次

struct blocks
{
    int type;//方块类型
    int x, y;
    int rows, cols;
    int match; //匹配次数
    int mingdu; //透明度0—255 255表示完全不透明
};

extern struct blocks maps[ROWS + 2][COLS + 2]; //防止方块溢出给外围加一圈

extern const int off_x;
extern const int off_y;
extern const int blocksize;

extern int click; //表示相邻位置的单机次数，第2次单击，才会交换
extern int posX1, posY1;
extern int posX2, posY2;
extern int score;
extern int num;
#endif //GLOBAL_H