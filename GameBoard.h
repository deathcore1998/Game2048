
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

	friend class AManagerGame;
	int GetSIZEGRID();

	int GetCountEmptyTile() const;

	void GenerateRandomValue();

	TArray<TArray<ATile*>> GameBoardTile;

	void CreatingElementsOnTheBoard();
public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	int CountEmptyTile;

	UWorld* World;

	URandomizer* MyRandomizer;

	const int SIZEGRID = 4;

	USceneComponent* BoardRoot;

	UStaticMeshComponent* BoardMesh;
};