#include "Randomizer.h"

int URandomizer::GenerateRandomValueForTile(TArray<TArray<ATile*>>& gameBoardTileRef, const int& SIZEGRID)
{
	// ����� �����, �������� ������� ����� 0, � ������ �� ���������� � ������
	TArray<ATile*> zeroIndex;
	for (int ROW = 0; ROW < SIZEGRID; ROW++) {
		for (int COLUMN = 0; COLUMN < SIZEGRID; COLUMN++) {
			if (gameBoardTileRef[ROW][COLUMN]->getValue() == 0) {
				zeroIndex.Add(gameBoardTileRef[ROW][COLUMN]);
			}
		}
	}
	// ���������� ������ �������� ������, �������� ������� ���� 0(���� ����� �������)
	if (zeroIndex.Num() > 0) {
		int RandomIndex = FMath::RandRange(0, zeroIndex.Num() - 1);// ��������� ������
		int RandomValue = FMath::RandRange(1, 10); // ����� ���������� ������ 2 ��� 4 � ������������ ������������
		if (RandomValue > 9) {
			zeroIndex[RandomIndex]->setValue(4);
		}
		else {
			zeroIndex[RandomIndex]->setValue(2);
		}
	}
	return zeroIndex.Num() == 0 ? 0 : zeroIndex.Num() - 1;// ������� ���������� ���������� ��������� �����
}