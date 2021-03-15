#pragma once
#include <vector>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>

class helper
{
private:
	int x, z, Dollars, y, Bonus, time, tail;
	// x - snake head position
	// z = for random number(pineapple generation)
	// y = tail coordinates time = time tail = snakelenght - 1
	char* map; //Map of game
	bool L, R, D, U, A; //L = LEFT R = RIGHT D = DOWN U = UP A = JUST A BOOL
	std::vector <int> past; //Special vector for deleting old parts
	int mapSize;

public:
	helper();
	bool AcceptInput();
	void DrawScreen();
	void KeyEntry();
	void Pineapple();
	void ChangeDirection(char key);
	~helper();
	void Graphics(); //Drawing game
	void GameLogic(); //Does it need comment?
	int GameOver(); //Game over ?.
	void Start(); //Start -_-
	friend void clearscreen(); //It's actually not like system("cls"),but works almost same
};

