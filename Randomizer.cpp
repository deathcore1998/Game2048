

#include "Randomizer.h"

int URandomizer::GenerateRandomValueForTile(TArray<TArray<ATile*>>& GameBoardTileRef, const int& SIZEGRID)
{
	// ѕоиск €чеек, значение которых равно 0, и запись их указателей в массив
	TArray<ATile*> ZeroIndex;
	for (int ROW = 0; ROW < SIZEGRID; ROW++)
	{
		for (int COLUMN = 0; COLUMN < SIZEGRID; COLUMN++)
		{
			if (GameBoardTileRef[ROW][COLUMN]->GetValue() == 0)
			{
				ZeroIndex.Add(GameBoardTileRef[ROW][COLUMN]);
			}
		}
	}

	// ѕрисвоение нового значени€ €чейке, значение которой было 0(если такие имеютс€)
	if (ZeroIndex.Num() > 0)
	{
		int RandomIndex = FMath::RandRange(0, ZeroIndex.Num() - 1);// случайный индекс

		int RandomValue = FMath::RandRange(1, 10); // „исло присвоени€ €чейке 2 или 4 с определенной веро€тностью

		if (RandomValue > 9)
		{
			ZeroIndex[RandomIndex]->SetValue(4);
		}
		else
		{
			ZeroIndex[RandomIndex]->SetValue(2);
		}
	}

	return ZeroIndex.Num() == 0 ? 0 : ZeroIndex.Num() - 1;// возврат количества оставшихс€ свободных €чеек
}