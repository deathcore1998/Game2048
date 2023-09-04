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
	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	friend class AManagerGame;
	int getSIZEGRID();
	int getCountEmptyTile() const;
	void generateRandomValue();
	void creatingElementsOnTheBoard();

private:
	UWorld* world;
	URandomizer* myRandomizer;
	USceneComponent* boardRoot;
	UStaticMeshComponent* boardMesh;

	TArray<TArray<ATile*>> gameBoardTile;
	const int SIZEGRID = 4;
	int countEmptyTile;
};