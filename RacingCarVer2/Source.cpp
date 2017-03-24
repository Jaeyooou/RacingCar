#define _CRT_SECURE_NO_WARNINGS
#include "Util.h"
#include <iostream>
//#include "time.h"
#include "ctime"
#include <cstdlib>

using namespace std;

clock_t start;
double n2o= 0;
double during;
int boardH, boardW;
int score = 0, level = 1;
int point;
double speedgame;
int posCar = 0;
struct car {
	int x;
	int y;
};
car car1, car2, car3;
bool endGame = false;

void DrawGame() {
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
	SetBGColor(0);
	gotoxy(0, boardH - 1);
	printf("\n");
	printf("Level: %d\n", level);
	printf("Score: %d\n", score);
}

void EraseCar(int x, int y) {
	SetBGColor(8);
	x = x * 4 + 6;
	if ((y >= 0) && (y < boardH)) {
		gotoxy(x, y);
		printf(" ");
	}
	if ((y >= -1) && (y + 1 < boardH)) {
		gotoxy(x - 1, y + 1);
		printf(" ");
		gotoxy(x, y + 1);
		printf(" ");
		gotoxy(x + 1, y + 1);
		printf(" ");
	}
	if ((y >= -2) && (y + 2 < boardH)) {
		gotoxy(x, y + 2);
		printf(" ");
	}
	if ((y >= -3) && (y + 3 < boardH)) {
		gotoxy(x - 1, y + 3);
		printf(" ");
		gotoxy(x + 1, y + 3);
		printf(" ");
	}
}

void DrawCar(int x, int y) {
	SetBGColor(8);
	SetColor(14);
	EraseCar(x, y - 1);
	x = x * 4 + 6;
	if ((y >= 0) && (y < boardH)) {
		gotoxy(x, y);
		printf("%c", point + 1);
	}
	if ((y >= -1) && (y + 1 < boardH)) {
		gotoxy(x - 1, y + 1);
		printf("%c", point);
		gotoxy(x, y + 1);
		printf("%c", point);
		gotoxy(x + 1, y + 1);
		printf("%c", point);
	}
	if ((y >= -2) && (y + 2 < boardH)) {
		gotoxy(x, y + 2);
		printf("%c", point);
	}
	if ((y >= -3) && (y + 3 < boardH)) {
		gotoxy(x - 1, y + 3);
		printf("%c", point);
		gotoxy(x + 1, y + 3);
		printf("%c", point);
	}
}

void DrawPlayerCar(int pos) {
	SetBGColor(8);
	SetColor(12);
	int x = 6 + pos*4;
	int y = 12;
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
	boardH = 16;
	point = 219;
	speedgame = 0.3;
	car1.x = (rand() % 3) - 1;
	car1.y = -3;
	car2.y = -4;
	car2.x = 2;
	car3.y = -4;
	car3.x = 2;
}


void MainLoop() {
	//DrawGame();
	//DrawPlayerCar(posCar);
	car1.y += 1;
	if (car2.y != -4) car2.y += 1;
	if (car3.y != -4) car3.y += 1;
	if (car1.y == 5) {
		if (car2.y == -4) {
			car2 = car1;
			car1.x = (rand() % 3) - 1;
			car1.y = -3;
		}
		else {
			car3 = car2;
			car2 = car1;
			car1.x = (rand() % 3) - 1;
			car1.y = -3;
		}
	}
	DrawCar(car1.x, car1.y);
	DrawCar(car2.x, car2.y);
	DrawCar(car3.x, car3.y);
}

void RenderGame() {
	if (checkKey(KEY_LEFT)) {
		EraseCar(posCar, 12);
		posCar--;
		if (posCar < -1) posCar = -1;
		DrawPlayerCar(posCar);
		while (checkKey(KEY_LEFT));
	}
	else if (checkKey(KEY_RIGHT)) {
		EraseCar(posCar, 12);
		posCar++;
		if (posCar > 1) posCar = 1;
		DrawPlayerCar(posCar);
		while (checkKey(KEY_RIGHT));
	}
	else if (checkKey(KEY_UP)) {
		n2o = -0.15;
	}
	else if (checkKey(KEY_ESC)) {
		endGame = true;
	}
	else { n2o = 0; }
	if (((posCar == car3.x) && (car3.y < 16)) || ((posCar==car2.x) && (car2.y >= 9))) endGame = true;
	SetBGColor(0);
	SetColor(12);
	gotoxy(7, boardH);
	printf("%d", level);
	gotoxy(7, boardH + 1);
	printf("%d", score);
}

void Play(double maxValue, void(*gloop) (), void(*rloop) ())
{
	during = (clock() - start) / (double)CLOCKS_PER_SEC;
	if (during > speedgame) {
		start = clock();
		gloop(); // Game loop
		score += 1;
		level = 1 + (score / 100);
		speedgame = (0.35 - level*0.03) + n2o;
	}
	if (!endGame) rloop(); // Render loop
}

int main() {
	
	init();
	printf("...RACING CAR...\n");
	printf("Using Left Arow and Right Arow to control the car. And press SPACE to use N2O\n");
	scanf("");
	ShowCur(false);
	system("cls");
	//example();
	DrawGame();
	DrawPlayerCar(0);
	gotoxy(4, 5);
	SetColor(0);
	printf("READY!");
	start = clock();
	while (during < 2) {
		during = (clock() - start) / (double)CLOCKS_PER_SEC;
	}
	gotoxy(5, 6);
	printf("GO");
	start = clock();
	during = 0;
	while (during < 1) {
		during = (clock() - start) / (double)CLOCKS_PER_SEC;
	}
	DrawGame();
	DrawPlayerCar(0);
	while (!endGame) {
		Play(speedgame, MainLoop, RenderGame);
		//MainLoop();
	}
	gotoxy(0, 19);
	system("pause");
	return 0;
}