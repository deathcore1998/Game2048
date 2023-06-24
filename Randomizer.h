
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tile.h"
#include "Randomizer.generated.h"

UCLASS()
class GAME2048_API URandomizer : public UObject
{
	GENERATED_BODY()

public:

	int GenerateRandomValueForTile(TArray<TArray<ATile*>>& GameBoardTileRef, const int& SIZEGRID);
};
