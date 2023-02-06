#pragma once
#include <iostream>
#include <array>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Myrandom
{
private:
	static int const SIZE_ARRAY = 16;
	static const int SIZE_FOR_RANDOM = 10;

	const int myrand[SIZE_FOR_RANDOM]{ 2,2,2,2,2,2,2,2,2,4 };

	int countforrandom = 0;

	int arrayforindexrandom[SIZE_ARRAY];

public:
	int check_empty_cell(int* gamefield);

	void RandomFilling(int* gamefield);

};

