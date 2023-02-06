#include "Myrandom.h"

int Myrandom::check_empty_cell(int* gamefield)
{
	countforrandom = 0;
	for (int i = 0; i < SIZE_ARRAY; ++i)
	{
		if (gamefield[i] == 0)
		{
			arrayforindexrandom[countforrandom++] = i;/////
		}
	}
	return countforrandom;
}

void Myrandom::RandomFilling(int* gamefield)
{
	check_empty_cell(gamefield);
	if (countforrandom == 0)
	{
		return;
	}
	else
	{
		gamefield[arrayforindexrandom[rand() % countforrandom]] = myrand[rand() % 10];
	}
}

