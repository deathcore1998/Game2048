#pragma once
#include <iostream>
#include <array>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "Myrandom.h"
#include "Rendering.h"

using namespace std;


class Game2048
{
private:
	Myrandom random;
	Rendering rendering;

	static int const SIZE_ARRAY = 16;
	static int const SIZE_ROW_OR_COL = 4;
	int score;
	int earlyscore;
	int tempscore;

	int gamefield[SIZE_ARRAY];
	int earlygamefield[SIZE_ARRAY];
	int tempgamefield[SIZE_ARRAY];
	bool checkmove = false;

public:
	Game2048();

	void StartGame();

	void ÑheckEndGame();

	void MovePush(int index1, int index2);	

	void PushLeft();	

	void PushRight();	

	void PushUp();	

	void PushDown();	

	void CancelPush();	

	void Storagegamefield();	

	void CheckMoveFunction();
};

