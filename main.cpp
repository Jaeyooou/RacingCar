#include "func.h"

int boardH, boardW;
int score, level;
int point;

void DrawPath() {
	SetBGColor(8);
	for (int i = 0; i < boardW; i++) {
		for (int j = 0; j < boardH; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
	for (int i = 0; i < boardH; i++) {
		SetColor(9);
		gotoxy(0, i);
		printf("%c", 179);
		gotoxy(4, i);
		printf("%c", 179);
		gotoxy(8, i);
		printf("%c", 179);
		gotoxy(boardW - 1, i);
		printf("%c", 179);
	}
}

void DrawCar(int x, int y) {
	SetColor(14);
	if (y >= 0) {
		gotoxy(x, y);
		printf("%c", point + 1);
	}
	if (y >= -1) {
		gotoxy(x - 1, y + 1);
		printf("%c", point);
		gotoxy(x, y + 1);
		printf("%c", point);
		gotoxy(x + 1, y + 1);
		printf("%c", point);
	}
	if (y >= -2) {
		gotoxy(x, y + 2);
		printf("%c", point);
	}
	if (y >= -3) {
		gotoxy(x - 1, y + 3);
		printf("%c", point);
		gotoxy(x + 1, y + 3);
		printf("%c", point);
	}
}

void DrawPlayerCar(int x, int y) {
	SetColor(12);
	gotoxy(x, y);
	printf("%c", point + 1);
	gotoxy(x - 1, y + 1);
	printf("%c", point);
	gotoxy(x, y + 1);
	printf("%c", point);
	gotoxy(x + 1, y + 1);
	printf("%c", point);
	gotoxy(x, y + 2);
	printf("%c", point);
	gotoxy(x - 1, y + 3);
	printf("%c", point);
	gotoxy(x + 1, y + 3);
	printf("%c", point);
}

void init() {
	boardW = 13;
	boardH = 12;
	point = 219;
}

void example() {
	DrawPath();
	DrawPlayerCar(6, 8);
	DrawCar(2, 4);
	DrawCar(10, 0);
	SetBGColor(0);
	gotoxy(0, boardH - 1);
	printf("\n");
	printf("Level: %d\n", level);
	printf("Score: %d\n", score);
}

int main()
{
	init();
	printf("...RACING CAR...\n");
	printf("Using Left Arow and Right Arow to control the car. And press SPACE to use N2O\n");
	scanf("");
	ShowCur(false);
	system("cls");
	example();
	system("pause");
	return 0;
}