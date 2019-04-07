#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include "chess.h"
FILE * input;
char boardWithFigures[8][8][2];
int move[2][2];
int boardOfPossibility[8][8];
int main() {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			boardWithFigures[i][j][0] = 'N';
			boardWithFigures[i][j][1] = 'N';
			boardOfPossibility[i][j] = 0;
		}
	}
	if ((input = fopen("input.txt", "r")) == NULL) return 0;
	char dataF[2];
	char data;
	int xy[2];
	fscanf(input, "%c", &dataF[0]);
	if (dataF[0] != 'W' && dataF[0] != 'B') { printf("error1"); _getch(); return 0; }
	fscanf(input, "%c", &dataF[1]);
	if (dataF[1] != 'H') { printf("error2"); _getch(); return 0; }
	fscanf(input, "%c", &data);
	if (data != ':') { printf("error3"); _getch(); return 0; }
	fscanf(input, "%c", &data);
	if (data > 'h' || data < 'a') { printf("error4"); _getch(); return 0; }
	xy[0] = (int)data - ((int)'a');
	fscanf(input, "%c", &data);
	if (data < '1' || data>'8') { printf("error5"); _getch(); return 0; }
	xy[1] = (int)data - ((int)'1');
	move[0][0] = xy[0];
	move[0][1] = xy[1];
	fscanf(input, "%c", &data);
	if (data != '-') { printf("error6"); _getch(); return 0; }
	fscanf(input, "%c", &data);
	if (data > 'h' || data < 'a') { printf("error7"); _getch(); return 0; }
	xy[0] = (int)data - ((int)'a');
	fscanf(input, "%c", &data);
	if (data < '1' || data>'8') { printf("error8"); _getch();  return 0; }
	xy[1] = (int)data - ((int)'1');
	move[1][0] = xy[0];
	move[1][1] = xy[1];
	if (((abs(move[0][0] - move[1][0]) == 1 && abs(move[0][1] - move[1][1]) == 2) || (abs(move[0][1] - move[1][1]) == 1 && abs(move[0][0] - move[1][0]) == 2))==NULL) { printf("UNACCESSABLE MOVE"); _getch(); return 0; }
	boardWithFigures[move[0][0]][move[0][1]][0] = dataF[0];
	boardWithFigures[move[0][0]][move[0][1]][1] = dataF[1];
	//printf("YES: %c%c:%i%i-%i%i", dataF[0], dataF[1], move[0][0], move[0][1], move[1][0], move[1][1]);
	int locale=0;
	while (!feof(input)) {
		switch (scanFigure(input, boardWithFigures)) {
			case -1:
				printf("A lot of kings");
				_getch();
				return 0;
			case -2:
				printf("You can't place two figures in one square");
				_getch();
				return 0;
			case -3:
				printf("Uncorrect input");
				_getch();
				return 0;
			case -4:
				printf("Kings can't stay near");
				_getch();
				return 0;
			case -5:
				printf("Pawns can't be placed on 1 and 8 horizontal");
				_getch();
				return 0;
			case 3:
				locale = 1;
				break;

		}
	}
	if (locale == 0) {
		printf("No kings");
		_getch();
		return 0;
	}
	//printf("\n");
	if (boardWithFigures[move[1][0]][move[1][1]][0] == dataF[0]) {
		printf("You can't walk on square with your figure");
		_getch();
		return 0;
	}
	/*for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 2; k++) {
				printf("%c", boardWithFigures[j][i][k]);
			}
			printf(" ");
		}
		printf("\n");
	}*/
	boardWithFigures[move[1][0]][move[1][1]][0] = dataF[0];
	boardWithFigures[move[1][0]][move[1][1]][1] = 'H';
	boardWithFigures[move[0][0]][move[0][1]][0] = 'N';
	boardWithFigures[move[0][0]][move[0][1]][1] = 'N';
	/*for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 2; k++) {
				printf("%c", boardWithFigures[j][i][k]);
			}
			printf(" ");
		}
		printf("\n");
	}*/
	ColorFigures(boardWithFigures, boardOfPossibility, dataF[0]);
	if (attackedKing(boardWithFigures, boardOfPossibility, dataF[0])) {
		printf("Your king will be under attack, after this turn");
	}
	else {
		printf("You can do this turn");
	}
	/*for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			printf("%i ", boardOfPossibility[j][i]);
		}
		printf("\n");
	}*/
	_getch();
}