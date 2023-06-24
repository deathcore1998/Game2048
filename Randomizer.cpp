

#include "Randomizer.h"

int URandomizer::GenerateRandomValueForTile(TArray<TArray<ATile*>>& GameBoardTileRef, const int& SIZEGRID)
{
	// ����� �����, �������� ������� ����� 0, � ������ �� ���������� � ������
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

	// ���������� ������ �������� ������, �������� ������� ���� 0(���� ����� �������)
	if (ZeroIndex.Num() > 0)
	{
		int RandomIndex = FMath::RandRange(0, ZeroIndex.Num() - 1);// ��������� ������

		int RandomValue = FMath::RandRange(1, 10); // ����� ���������� ������ 2 ��� 4 � ������������ ������������

		if (RandomValue > 9)
		{
			ZeroIndex[RandomIndex]->SetValue(4);
		}
		else
		{
			ZeroIndex[RandomIndex]->SetValue(2);
		}
	}

	return ZeroIndex.Num() == 0 ? 0 : ZeroIndex.Num() - 1;// ������� ���������� ���������� ��������� �����
}