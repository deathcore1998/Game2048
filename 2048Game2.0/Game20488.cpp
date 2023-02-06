#include "Game20488.h"

Game2048::Game2048()
{
	StartGame();
}

void Game2048::StartGame()
{
	score = 0;
	tempscore = 0;
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		gamefield[i] = 0;
	}
	random.RandomFilling(gamefield);
	random.RandomFilling(gamefield);

	rendering.startRendering(gamefield);
	Storagegamefield();
}

void Game2048::ÑheckEndGame()
{
	int countforrandom = random.check_empty_cell(gamefield);
	int sum_index = 0;

	if (countforrandom == 0)
	{
		for (int i = 0; i <= SIZE_ROW_OR_COL * 2; i += SIZE_ROW_OR_COL)
		{
			for (int j = 0; j < SIZE_ROW_OR_COL; j++)
			{
				sum_index = i + j;
				if (j != 3)
				{
					if (gamefield[sum_index] == gamefield[sum_index + 1] or gamefield[sum_index] == gamefield[sum_index + SIZE_ROW_OR_COL])
					{
						return;
					}
				}
				else
				{
					if (gamefield[sum_index] == gamefield[sum_index + SIZE_ROW_OR_COL])
					{
						return;
					}
				}
			}
		}

		for (int i = 12; i < 14; i++)//íèæíÿÿ ñòðî÷êà
		{
			if (gamefield[i] == gamefield[i + 1])
			{
				return;
			}
		}
		printf("\t\t\t\t\x1B[31mÈãðà îêîí÷åíà!\033[0m\n");
	}
}

void Game2048::MovePush(int index1, int index2)
{
	if (gamefield[index1] == gamefield[index2] && gamefield[index1] > 0)
	{
		score += gamefield[index1] * 2;
		gamefield[index1] = -(gamefield[index2] * 2);
		gamefield[index2] = 0;
		checkmove = true;
	}
	if (gamefield[index1] == 0 && gamefield[index2] != 0)
	{
		swap(gamefield[index1], gamefield[index2]);
		checkmove = true;
	}
}

void Game2048::PushLeft()
{
	Storagegamefield();
	for (int i = 0; i < SIZE_ARRAY; i += SIZE_ROW_OR_COL)
	{
		int temp = 0;
		for (int j = i; j < 3 + i; j++)
		{
			MovePush(j, j + 1);

			if (j == 2 + i && temp != 2)
			{
				temp++;
				j = i - 1;
			}
		}
	}
	CheckMoveFunction();
}

void Game2048::PushRight()
{
	Storagegamefield();
	for (int i = 0; i < SIZE_ARRAY; i += SIZE_ROW_OR_COL)
	{
		int temp = 0;
		for (int j = 3 + i; j > i; j--)
		{
			MovePush(j, j - 1);

			if (j == 1 + i && temp != 2)
			{
				temp++;
				j = 3 + i + 1;
			}
		}
	}
	CheckMoveFunction();
}

void Game2048::PushUp()
{
	Storagegamefield();
	for (int i = 0; i < SIZE_ROW_OR_COL; i++)
	{
		int temp = 0;
		for (int j = i; j <= SIZE_ROW_OR_COL * 2 + i; j += SIZE_ROW_OR_COL)
		{
			MovePush(j, j + SIZE_ROW_OR_COL);

			if (j == 8 + i && temp != 2)
			{
				temp++;
				j = i - SIZE_ROW_OR_COL;
			}
		}
	}
	CheckMoveFunction();
}

void Game2048::PushDown()
{
	Storagegamefield();
	for (int i = 0; i < SIZE_ROW_OR_COL; i++)
	{
		int temp = 0;
		for (int j = SIZE_ROW_OR_COL * 3 + i; j >= SIZE_ROW_OR_COL; j -= SIZE_ROW_OR_COL)
		{
			MovePush(j, j - SIZE_ROW_OR_COL);

			if (j == SIZE_ROW_OR_COL + i && temp != 2)
			{
				temp++;
				j = SIZE_ARRAY + i;
			}
		}
	}
	CheckMoveFunction();
}

void Game2048::CancelPush()
{
	rendering.setCursorPosition(30, 0);

	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		gamefield[i] = earlygamefield[i];
	}
	score = earlyscore;

	rendering.ShowGameField(gamefield, score);
}

void Game2048::Storagegamefield()
{
	for (int i = 0; i < SIZE_ARRAY; i++)
	{
		tempgamefield[i] = gamefield[i];
	}
	tempscore = score;
}

void Game2048::CheckMoveFunction()
{
	if (checkmove)
	{
		for (int i = 0; i < SIZE_ARRAY; i++)
		{
			earlygamefield[i] = tempgamefield[i];
		}
		earlyscore = tempscore;
		random.RandomFilling(gamefield);
		checkmove = false;
	}
	else
	{
		ÑheckEndGame();
	}
	rendering.ShowGameField(gamefield, score);
}