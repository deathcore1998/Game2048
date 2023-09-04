#include "Randomizer.h"

int URandomizer::GenerateRandomValueForTile(TArray<TArray<ATile*>>& gameBoardTileRef, const int& SIZEGRID)
{
	// ѕоиск €чеек, значение которых равно 0, и запись их указателей в массив
	TArray<ATile*> zeroIndex;
	for (int ROW = 0; ROW < SIZEGRID; ROW++) {
		for (int COLUMN = 0; COLUMN < SIZEGRID; COLUMN++) {
			if (gameBoardTileRef[ROW][COLUMN]->getValue() == 0) {
				zeroIndex.Add(gameBoardTileRef[ROW][COLUMN]);
			}
		}
	}
	// ѕрисвоение нового значени€ €чейке, значение которой было 0(если такие имеютс€)
	if (zeroIndex.Num() > 0) {
		int RandomIndex = FMath::RandRange(0, zeroIndex.Num() - 1);// случайный индекс
		int RandomValue = FMath::RandRange(1, 10); // „исло присвоени€ €чейке 2 или 4 с определенной веро€тностью
		if (RandomValue > 9) {
			zeroIndex[RandomIndex]->setValue(4);
		}
		else {
			zeroIndex[RandomIndex]->setValue(2);
		}
	}
	return zeroIndex.Num() == 0 ? 0 : zeroIndex.Num() - 1;// возврат количества оставшихс€ свободных €чеек
}