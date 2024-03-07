#include"block.h"
#include"print.h"
#pragma comment (lib,"winmm.lib")//播放音乐需要的库文件
#include"GAME.h"
#include "global.h"//全局变量头文件
#include"MOVE.h"

//开发日志
//1.创建初始话窗口
//2.开始建造方块
//3.实现方块移动
//4.设计游戏机制


IMAGE imgBg;
IMAGE blocks[block_TYPE];
IMAGE GAMEOVER;
bool ismoving = false;
bool isclick = false;

struct blocks maps[ROWS + 2][COLS + 2];

const int off_x = 17;
const int off_y = 274;
const int blocksize = 52;//方块尺寸

int click;
int posX1, posY1;
int posX2, posY2;
int score;
int num;

void boom() {
	if (num <= 0)return;
	int i = rand() % 8 + 1;
	for (size_t j = 1; j <= COLS; j++)
	{
		maps[i][j].match += 1;
		
	}
	num -= 1;
}

void userclick() {
	ExMessage mes;
	/*
		maps[i][j].x = off_x+(i-1)*(blocksize+GAP);
		maps[i][j].y = off_y+(j-1)*(blocksize+GAP);
	*/

	if (peekmessage(&mes) && mes.message == WM_LBUTTONDOWN) {
		if (mes.x > 163 && mes.x < 313 && mes.y>777 && mes.y < 898)
		{
			boom();
		}
			if (mes.x < off_x || mes.y < off_y)return;
			/*优化左边界和上边界bug*/

			int col = (mes.x - off_x) / (blocksize + GAP) + 1;
			int row = (mes.y - off_y) / (blocksize + GAP) + 1;


			//优化右边界和下边界bug
			if (col > COLS || row > ROWS)return;



			/*printf(" %d,%d\n", col, row);*/
			/*printf("%d", maps[row][col].type);*//*测试函数bug时用到的*/
			click++;
			if (click == 1)
			{
				posX1 = col;
				posY1 = row;

			}
			else if (click == 2) {
				posX2 = col;
				posY2 = row;

				if (abs(posX2 - posX1) + abs(posY1 - posY2) == 1) {
					exchange(posX1, posY1, posX2, posY2);
					click = 0;
					isclick = true;
					//播放音效
					///*mciSendString("play res/res/bg.mp3 repeat", 0, 0, 0)有延迟*/
				}
				else {
					click = 1;
					posX1 = posX2;
					posY1 = posY2;
				}
			}
		}

	}


	void updatewindow() {
		putimage(0, 0, &imgBg);
		BeginBatchDraw();
		//插入 
		for (int i = 1; i <= ROWS; i++)
		{
			for (int j = 1; j <= COLS; j++)
			{
				if (maps[i][j].type != 0)
				{
					putimageTMD(maps[i][j].x, maps[i][j].y, &blocks[maps[i][j].type - 1], maps[i][j].mingdu);
				}
			}
		}

		printscore();
		FlushBatchDraw();
		//原始easyx库中调用图片叠加会出现黑边，调用其他人写的接口实现背景透明


	}


	void check() {
		for (int i = 1; i <= ROWS; i++)
		{
			for (int j = 1; j <= COLS; j++)
			{
				if (maps[i][j].type == maps[i + 1][j].type &&
					maps[i][j].type == maps[i - 1][j].type) {
					maps[i][j].match++;
					maps[i][j].match++;
					maps[i - 1][j].match++;
					maps[i + 1][j].match++;

				}

				if (maps[i][j].type == maps[i][j - 1].type &&
					maps[i][j].type == maps[i][j + 1].type)
				{
					maps[i][j].match++;
					maps[i][j + 1].match++;
					maps[i][j - 1].match++;

				}
			}

		}
	}




	int main() {
		gameinit();//游戏进入
		while (1) {
			userclick();//处理用户的点击
			check();//检查是否有可以消除的方块
			move();//方块的移动
			if (!ismoving)disappear();//如果没有方块在移动,那么消除匹配的方块
			restore();	//还原没有匹配成功的方块
			updatewindow();// 更新窗口
			if (!ismoving)updateGame();//更新游戏的状态，如方块的下落，分数的增加等
			if (ismoving)Sleep(7);
			if (score > 200)//调整游戏难度
			{
				break;
			}
		}
		gameOver();//结束游戏
		system("pause");
	}