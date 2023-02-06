#pragma once
#include <iostream>
#include <array>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Rendering
{
private:
	int const SIZE_ARRAY = 16;
	int const SIZE_ROW_OR_COL = 4;

public:
	void startRendering(int* gamefield);	

	void setCursorPosition(int x, int y);	

	void ShowGameField(int* gamefield, const int& score);
};
