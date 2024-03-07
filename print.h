#pragma once
#include <stdio.h>

#include "global.h"
void printscore() {
	char scorestr[16];
	sprintf_s(scorestr, sizeof(scorestr), "%d", score);
	int x_1 = 394 + (75 - strlen(scorestr) * 20) / 2;
	int y_1 = 60;
	outtextxy(x_1, y_1, scorestr);

	char numstr[10];
	sprintf_s(numstr, sizeof(numstr), "%d", num);
	int x_2 = 93;
	int y_2 = 855;
	outtextxy(x_2, y_2, numstr);

}