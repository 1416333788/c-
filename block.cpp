#include "global.h"//全局变量头文件
#include"block.h"
#include"MOVE.h"
void disappear() {
	for (int i = 0; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
			if (maps[i][j].match && maps[i][j].mingdu > 10) {
				maps[i][j].mingdu -= 10;//调整消除方块速率
				ismoving = true;
			}
	}

}
void updateGame() {
	//下沉
	//实现过程为下方扫描后进行向列上搜寻
	for (int i = ROWS; i > 0; i--)
	{
		for (int j = 1; j <= COLS; j++) {
			if (maps[i][j].match) {
				for (int k = i - 1; k > 0; k--)
				{
					if (maps[k][j].match == 0) {
						exchange(j, k, j, i);
						break;
					}

				}
			}

		}

	}
	/*生成新的方块实现降落处理*/
	for (size_t j = 1; j <= COLS; j++)
	{
		int n = 0;//记录消掉个数
		for (size_t i = ROWS; i >= 1; i--)
		{
			if (maps[i][j].match)
			{
				maps[i][j].type = rand() % 5 + 1;
				maps[i][j].match = 0;
				maps[i][j].y = off_y - (n + 1) * (sizeblock + 5);
				n++;
				maps[i][j].mingdu = 255;

			}
		}
		score += n;
	}

}