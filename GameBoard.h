

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

	int GetSIZEGRID() const;

	void GenerateRandomValue();

	int GetCountEmptyTile() const;

	void SetCurrentScore(int NewCurrentScore);

	int GetCurrentScore() const;

	void DisplayGameOverMessage();

	void HideGameOverMessage();

	void UpdateScore(int newScore);

	void UpdateUndoCount(int newUndoCount);

private:

	int CountEmptyTile;

	UWorld* World;

	URandomizer* MyRandomizer;

	const int SIZEGRID = 4;

	int CurrentScore;

	USceneComponent* BoardRoot;

	UStaticMeshComponent* BoardMesh;

	USceneComponent* RootTextRenderScore;

	UTextRenderComponent* TextRenderScore;

	USceneComponent* RootTextRenderUndoCount;

	UTextRenderComponent* TextRenderUndoCount;

	USceneComponent* RootTextRenderEndGame;

	UTextRenderComponent* TextRenderEndGame;

	void SetTextRenderComponent(UTextRenderComponent* TextRenderComp, FVector Position, float XPos, float YPos,  FString Text, FColor Color,float sizeText);
};
