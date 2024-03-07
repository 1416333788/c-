#include"block.h"
#include"print.h"
#pragma comment (lib,"winmm.lib")//����������Ҫ�Ŀ��ļ�
#include"GAME.h"
#include "global.h"//ȫ�ֱ���ͷ�ļ�
#include"MOVE.h"

//������־
//1.������ʼ������
//2.��ʼ���췽��
//3.ʵ�ַ����ƶ�
//4.�����Ϸ����


IMAGE imgBg;
IMAGE blocks[block_TYPE];
IMAGE GAMEOVER;
bool ismoving = false;
bool isclick = false;

struct blocks maps[ROWS + 2][COLS + 2];

const int off_x = 17;
const int off_y = 274;
const int blocksize = 52;//����ߴ�

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
			/*�Ż���߽���ϱ߽�bug*/

			int col = (mes.x - off_x) / (blocksize + GAP) + 1;
			int row = (mes.y - off_y) / (blocksize + GAP) + 1;


			//�Ż��ұ߽���±߽�bug
			if (col > COLS || row > ROWS)return;



			/*printf(" %d,%d\n", col, row);*/
			/*printf("%d", maps[row][col].type);*//*���Ժ���bugʱ�õ���*/
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
					//������Ч
					///*mciSendString("play res/res/bg.mp3 repeat", 0, 0, 0)���ӳ�*/
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
		//���� 
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
		//ԭʼeasyx���е���ͼƬ���ӻ���ֺڱߣ�����������д�Ľӿ�ʵ�ֱ���͸��


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
		gameinit();//��Ϸ����
		while (1) {
			userclick();//�����û��ĵ��
			check();//����Ƿ��п��������ķ���
			move();//������ƶ�
			if (!ismoving)disappear();//���û�з������ƶ�,��ô����ƥ��ķ���
			restore();	//��ԭû��ƥ��ɹ��ķ���
			updatewindow();// ���´���
			if (!ismoving)updateGame();//������Ϸ��״̬���緽������䣬���������ӵ�
			if (ismoving)Sleep(7);
			if (score > 200)//������Ϸ�Ѷ�
			{
				break;
			}
		}
		gameOver();//������Ϸ
		system("pause");
	}