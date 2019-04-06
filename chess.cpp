#define _CRT_SECURE_NO_WARNINGS
#include "chess.h"

int scanFigure(FILE * file, char boardF[8][8][2]) {
	char dataF[2];
	char data;
	int xy[2];
	static int flag = 2;
	fscanf(file, "%c", &dataF[0]);
	if (dataF[0] != 'W' && dataF[0] != 'B') { /*printf("error11: %c", dataF[0]);*/ return 0; }
	fscanf(file, "%c", &dataF[1]);
	if (dataF[1] != 'H' && dataF[1] != 'K' && dataF[1] != 'F' && dataF[1] != 'P' && dataF[1] != 'R' && dataF[1] != 'E') { printf("error12"); _getch(); return 0; }
	if (dataF[1] == 'K')
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) 
				if (dataF[0] == boardF[i][j][0] && dataF[1] == boardF[i][j][1]) return -1;
	fscanf(file, "%c", &data);
	if (data != ':') { printf("error13"); _getch(); return 0; }
	fscanf(file, "%c", &data);
	if (data > 'h' || data < 'a') { printf("error14"); _getch(); return 0; }
	xy[0] = (int)data - ((int)'a');
	fscanf(file, "%c", &data);
	if (data < '1' || data>'8') { printf("error15"); _getch(); return 0; }
	xy[1] = (int)data - ((int)'1');
	if (boardF[xy[0]][xy[1]][0] != 'N') {/* printf("error15"); _getch();*/ return -2; }
	boardF[xy[0]][xy[1]][0] = dataF[0];
	boardF[xy[0]][xy[1]][1] = dataF[1];
	if (dataF[1] == 'K') {
		return flag++;
	}
	return 1;
}