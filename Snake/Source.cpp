// SnakeGame.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Source.h"

bool gameOver, exitGame;
int x, y, fruitX, fruitY, score, bestScore = 0;
int tailX[100], tailY[100];
int nTail;
const int width = 20;
const int height = 20;
enum eDirection{STOP=0,UP, DOWN, RIGHT, LEFT};
eDirection dir;

void setup() {
	exitGame = false;
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
}

void draw() {

	system("cls");
	for (int i = 0; i < width+1; i++)
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				std::cout << "#";
			if (i == y && j == x) {
				std::cout << "C";
			}
			else if (i == fruitY && j == fruitX) {
				std::cout << "+";
			}
			else {
				bool printbool = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						std::cout << "+";
						printbool = true;
					}
				}
				if (!printbool){
					std::cout << " ";
				}
			}
			if (j == width - 1)
				std::cout << "#";
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < width + 2; i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Score: "<<score << std::endl;
}

void input() {

	if (_kbhit()) {

		switch (_getch()) {

		case 'a':
			dir = LEFT;
			x--;
			break;

		case 'w':
			dir = UP;
			Sleep(10);
			y--;
			break;
		case 's':
			dir = DOWN;
			y++;
			Sleep(10);
			break;
		case 'd':
			dir = RIGHT;
			x++;
			break;
		case 'x':
			gameOver = true;
			break;

		}
	}


}

void logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (dir)
	{
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	case LEFT:
		x--;
		break;
	default:
		break;
	}
	if (x > width || x < 0||y>height||y<0) {
		gameOver = true;
	}
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY) {
		score = score + 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	while (exitGame == false) {
		setup();
		gameLoop();
		restartScreen();
	}
	return 0;
}

void restartScreen(){
	system("cls");
	for (int i = 0; i < width + 1; i++)
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				std::cout << "#";
			else {
				bool printbool = false;

				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						std::cout << "+";
						printbool = true;
					}
				}
				if (!printbool) {
					std::cout << " ";
				}
			}
			if (j == width - 1)
				std::cout << "#";
		}
		std::cout << std::endl;
	}
	if (score > bestScore) {
		bestScore = score;
	}
		std::cout << "Game Over!" << std::endl;
		std::cout << "Your Score was: " << score << std::endl;
		std::cout << "Your Best Score in this session was: " << bestScore << std::endl;
		std::cout << "Restart? y/n" << std::endl;
		std::string restart = " ";
		std::getline(std::cin, restart);
		if (restart == "n") {
			exitGame = true;
		}
		else return;
	}

void gameLoop()
{
	while (gameOver == false) {
		draw();
		input();
		logic();
		Sleep(10);
	}
}

