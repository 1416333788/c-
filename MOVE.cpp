#include"MOVE.h"
#include "global.h"

void exchange(int col1, int row1, int col2, int row2) {
	struct blocks temp = maps[row1][col1];
	maps[row1][col1] = maps[row2][col2];
	maps[row2][col2] = temp;

	maps[row1][col1].rows = row1;
	maps[row1][col1].cols = col1;
	maps[row2][col2].rows = row2;
	maps[row2][col2].cols = col2;


}
void restore() {
	//发生移动后进行
	if (isclick && !ismoving)
	{
		int count = 0;
		for (int i = 1; i <= ROWS; i++)
		{
			for (int j = 1; j <= COLS; j++)
			{
				count += maps[i][j].match;
			}
		}
		//如果没有匹配到消除的正确模式就还原
		if (count == 0) {
			exchange(posX1, posY1, posX2, posY2);
		}
		isclick = false;
	}

}

void move() {
	ismoving = false;
	for (int i = ROWS; i > 0; i--)
	{
		for (int j = 0; j <= COLS; j++)
		{
			struct blocks* p = &maps[i][j];

			int x = off_x + (p->cols - 1) * (blocksize + GAP);
			int y = off_y + (p->rows - 1) * (blocksize + GAP);
			int dx, dy;
			for (int k = 0; k < 4; k++)//k用来控制方块移动速度
			{
				dx = p->x - x;
				dy = p->y - y;

				if (dx)p->x -= dx / abs(dx);
				if (dy)p->y -= dy / abs(dy);
			}
			if (dx || dy)ismoving = true;
		}

	}

}