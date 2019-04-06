#define _CRT_SECURE_NO_WARNINGS
#include "chess.h"

int scanFigure(FILE * file, char boardF[8][8][2]) {
	char dataF[2];
	char data;
	int xy[2];
	static int flag = 2;
	fscanf(file, "%c", &dataF[0]);
	if ((int)dataF[0] == -52||dataF[0]=='\n'||dataF[0]==' ') return 0;
	if (dataF[0] != 'W' && dataF[0] != 'B') { printf("error11: %i", (int)dataF[0]);  return -3; }
	fscanf(file, "%c", &dataF[1]);
	if (dataF[1] != 'H' && dataF[1] != 'K' && dataF[1] != 'F' && dataF[1] != 'P' && dataF[1] != 'R' && dataF[1] != 'E') { printf("error12"); _getch(); return -3; }
	if (dataF[1] == 'K')
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) 
				if (dataF[0] == boardF[i][j][0] && dataF[1] == boardF[i][j][1]) return -1;
	fscanf(file, "%c", &data);
	if (data != ':') { printf("error13"); _getch(); return -3; }
	fscanf(file, "%c", &data);
	if (data > 'h' || data < 'a') { printf("error14"); _getch(); return -3; }
	xy[0] = (int)data - ((int)'a');
	fscanf(file, "%c", &data);
	if (data < '1' || data>'8') { printf("error15"); _getch(); return -3; }
	xy[1] = (int)data - ((int)'1');
	if (dataF[1] == 'P')
		if (xy[1] == 0 || xy[1] == 7) { _getch(); return -5; }
	if (boardF[xy[0]][xy[1]][0] != 'N') {/* printf("error15"); _getch();*/ return -3; }
	boardF[xy[0]][xy[1]][0] = dataF[0];
	boardF[xy[0]][xy[1]][1] = dataF[1];
	if (dataF[1] == 'K') {
		return flag++;
	}
	return 1;
}
void ColorFigures(char boardF[8][8][2], int boardP[8][8], char color) {
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if (boardF[i][j][0] == color) {
				if (boardF[i][j][1] == 'K') {
					boardP[i][j] = 3;
				}
				else {
					boardP[i][j] = 2;
				}
			}
			else if (boardF[i][j][0] != 'N') {
				boardP[i][j] = -1;
			}
}
int attackedKing(char boardF[8][8][2], int boardP[8][8], char color) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (boardF[i][j][0] != color && boardF[i][j][0] != 'N') {
				switch (boardF[i][j][1]){
					case 'K':
						if (king(boardP, i, j)) return 1;
						break;
					case 'E':
						if (elephant(boardP, i, j)) return 1;
						break;
					case 'P':
						if (pawn(boardP, i, j, color)) return 1;
						break;
					case 'R':
						if (rook(boardP, i, j)) return 1;
						break;
					case 'F':
						if (rook(boardP, i, j)||elephant(boardP, i, j)) return 1;
						break;
					case 'H':
						if (horse(boardP, i, j)) return 1;
						break;

				}
			}
	return 0;
}
int king(int boardP[8][8], int i, int j) {
	for (int k = i - 1; k < i + 2; k++) {
		if (k < 0) {
			k++;
		}
		if (k > 7) {
			break;
		}
		for (int l = j - 1; l < j + 2; l++) {
			if (l < 0) {
				l++;
			}
			if (l > 7) {
				break;
			}
			if (boardP[k][l] == 3) return 1;
		}
	}
	return 0;
}
int elephant(int boardP[8][8], int i, int j) {
	int k = i+1, l = j+1;
	while (k < 8 && l < 8) {
		if (boardP[k][l] == 3) return 1;
		if (boardP[k][l] == 2 || boardP[k][l] == -1) break;
		k++;
		l++;
	}
	k = i + 1; l = j - 1;
	while (k < 8 && l >= 0) {
		if (boardP[k][l] == 3) return 1;
		if (boardP[k][l] == 2 || boardP[k][l] == -1) break;
		k++;
		l--;
	}
	k = i - 1; l = j - 1;
	while (k >= 0 && l >= 0) {
		if (boardP[k][l] == 3) return 1;
		if (boardP[k][l] == 2 || boardP[k][l] == -1) break;
		k--;
		l--;
	}
	k = i - 1; l = j + 1;
	while (k >= 0 && l < 8) {
		if (boardP[k][l] == 3) return 1;
		if (boardP[k][l] == 2 || boardP[k][l] == -1) break;
		k--;
		l++;
	}
	return 0;
}
int pawn(int boardP[8][8], int i, int j, char color) {
	if (color == 'B') {
		if (i + 1 < 8) {
			if (boardP[i + 1][j + 1] == 3) return 1;
		}
		if (i - 1 < 8) {
			if (boardP[i - 1][j + 1] == 3) return 1;
		}
	}
	if (color == 'W') {
		if (i + 1 < 8) {
			if (boardP[i + 1][j - 1] == 3) return 1;
		}
		if (i - 1 < 8) {
			if (boardP[i - 1][j - 1] == 3) return 1;
		}
	}
	return 0;
}
int rook(int boardP[8][8], int i, int j) {
	int k = 0, l = 0;
	while (k < 8) {
		if (boardP[i][k] == 3) return 1;
		if (boardP[i][k] == 2 || boardP[i][k] == -1) break;
		k++;
	}
	while (l < 8) {
		if (boardP[l][j] == 3) return 1;
		if (boardP[l][j] == 2 || boardP[l][j] == -1) break;
		k++;
	}
	return 0;
}
int horse(int boardP[8][8], int i, int j) {
	if (j + 2 < 8) {
		if (i + 1 < 8) 
			if (boardP[i + 1][j + 2] == 3) return 1;
		if (i - 1 >= 0)
			if (boardP[i - 1][j + 2] == 3) return 1;
	}
	if (j - 2 >= 0) {
		if (i + 1 < 8)
			if (boardP[i + 1][j - 2] == 3) return 1;
		if (i - 1 >= 0)
			if (boardP[i - 1][j - 2] == 3) return 1;
	}
	if (i + 2 < 8) {
		if (j + 1 < 8)
			if (boardP[j + 1][i + 2] == 3) return 1;
		if (j - 1 >= 0)
			if (boardP[j - 1][i + 2] == 3) return 1;
	}
	if (i - 2 >= 0) {
		if (j + 1 < 8)
			if (boardP[j + 1][i - 2] == 3) return 1;
		if (j - 1 >= 0)
			if (boardP[j - 1][i - 2] == 3) return 1;
	}
	return 0;
}