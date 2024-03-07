#include "global.h"
#include"GAME.h"
void gameinit() {
	loadimage(&imgBg, "res/res/bg2.png");
	initgraph(485, 917, 1);
	loadimage(&GAMEOVER, "res/res/GAMEOVER.jpg");
	//初始化一下方块位置
	char name[100];
	for (int i = 0; i < 7; i++)
	{
		sprintf_s(name, sizeof(name), "res/res/%d.png", i + 1);
		loadimage(&blocks[i], name, blocksize, blocksize, true);//实现图片缩放
	}


	//初始化随机数种子
	srand((unsigned int)time(NULL));


	//初始化方块
	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			maps[i][j].type = rand() % 5 + 1;//设置游戏难度
			maps[i][j].rows = i;
			maps[i][j].cols = j;
			maps[i][j].x = off_x + (j - 1) * (blocksize + GAP);
			maps[i][j].y = off_y + (i - 1) * (blocksize + GAP);
			maps[i][j].match = 0;
			maps[i][j].mingdu = 255;
		}

	}
	click = 0;
	score = 0;
	num = 5;
	setFont("Segoe UI Black", 20, 40);//设置字体


	//播放背景音乐
	mciSendString("play res/res/bg.mp3 repeat", 0, 0, 0);
	mciSendString("play res/res/start.mp3 ", 0, 0, 0);
}

void gameOver() {
	// 清屏
	cleardevice();
	// 渲染到屏幕
	FlushBatchDraw();

	// 显示游戏结束的图片
	putimage(0, 0, &GAMEOVER);
	// 渲染到屏幕
	FlushBatchDraw();
	//播放音效
	mciSendString("play res/res/victory.mp3 repeat", 0, 0, 0);
	// 暂停三秒钟
	Sleep(3000);

	// 关闭绘图设备环境
	closegraph();

	// 退出程序
	exit(0);

}