
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Randomizer.h"
#include "GameBoard.generated.h"

UCLASS()
class GAME2048_API AGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGameBoard();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	void CreatingElementsOnTheBoard();

	TArray<TArray<ATile*>> GameBoardTile;

	int GetSIZEGRID();

	void GenerateRandomValue();

	int GetCountEmptyTile() const;

private:

	int CountEmptyTile;

	UWorld* World;

	URandomizer* MyRandomizer;

	const int SIZEGRID = 4;

	USceneComponent* BoardRoot;

	UStaticMeshComponent* BoardMesh;
};