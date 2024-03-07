#ifndef GLOBAL_H
#define GLOBAL_H
#include <graphics.h>
#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include "tools.h"
#include<math.h>

#include<mmsystem.h>//���ű������ֺ���Ч��ͷ�ļ�

#define block_TYPE 7 //������������ 
#define sizeblock 30 //����ߴ�
#define ROWS 8 //������
#define COLS 8 //������
#define GAP 5 //������

extern IMAGE imgBg;
extern IMAGE blocks[block_TYPE];
extern IMAGE GAMEOVER;
extern bool ismoving; //�ж��ƶ��Ƿ����
extern bool isclick; //�ж��Ƿ�������

struct blocks
{
    int type;//��������
    int x, y;
    int rows, cols;
    int match; //ƥ�����
    int mingdu; //͸����0��255 255��ʾ��ȫ��͸��
};

extern struct blocks maps[ROWS + 2][COLS + 2]; //��ֹ�����������Χ��һȦ

extern const int off_x;
extern const int off_y;
extern const int blocksize;

extern int click; //��ʾ����λ�õĵ�����������2�ε������Żύ��
extern int posX1, posY1;
extern int posX2, posY2;
extern int score;
extern int num;
#endif //GLOBAL_H