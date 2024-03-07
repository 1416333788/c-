#include "global.h"
#include"GAME.h"
void gameinit() {
	loadimage(&imgBg, "res/res/bg2.png");
	initgraph(485, 917, 1);
	loadimage(&GAMEOVER, "res/res/GAMEOVER.jpg");
	//��ʼ��һ�·���λ��
	char name[100];
	for (int i = 0; i < 7; i++)
	{
		sprintf_s(name, sizeof(name), "res/res/%d.png", i + 1);
		loadimage(&blocks[i], name, blocksize, blocksize, true);//ʵ��ͼƬ����
	}


	//��ʼ�����������
	srand((unsigned int)time(NULL));


	//��ʼ������
	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			maps[i][j].type = rand() % 5 + 1;//������Ϸ�Ѷ�
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
	setFont("Segoe UI Black", 20, 40);//��������


	//���ű�������
	mciSendString("play res/res/bg.mp3 repeat", 0, 0, 0);
	mciSendString("play res/res/start.mp3 ", 0, 0, 0);
}

void gameOver() {
	// ����
	cleardevice();
	// ��Ⱦ����Ļ
	FlushBatchDraw();

	// ��ʾ��Ϸ������ͼƬ
	putimage(0, 0, &GAMEOVER);
	// ��Ⱦ����Ļ
	FlushBatchDraw();
	//������Ч
	mciSendString("play res/res/victory.mp3 repeat", 0, 0, 0);
	// ��ͣ������
	Sleep(3000);

	// �رջ�ͼ�豸����
	closegraph();

	// �˳�����
	exit(0);

}