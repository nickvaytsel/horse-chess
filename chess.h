#pragma once
#include <stdio.h>
#include <string.h>
#include <conio.h>

int scanFigure(FILE * file, char boardF[8][8][2]); 
void ColorFigures(char boardF[8][8][2], int boardP[8][8], char color);
void sameColorFigures(char boardF[8][8][2], int boardP[8][8], char color);
int attackedKing(char boardF[8][8][2], int boardP[8][8], char color);
int king(int boardP[8][8], int i, int j);
int elephant(int boardP[8][8], int i, int j);
int pawn(int boardP[8][8], int i, int j, char color);
int rook(int boardP[8][8], int i, int j);
int horse(int boardP[8][8], int i, int j);