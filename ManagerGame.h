
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoard.h"
#include "InputManager.h"
#include "Widgets/SWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "ManagerGame.generated.h"

UCLASS()
class GAME2048_API AManagerGame : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AManagerGame();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	void PushUp();

	void PushDown();

	void PushLeft();

	void PushRight();

	void StartGame();

	void SetPreviousBoard();

private:

	void UpdateUndoCount(int UndoCount);

	void UpdateScore(int Score);

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UUserWidget> MainMenu;

	UUserWidget* StartMenuWidget;

	UTextBlock* StartMenuScoreBlock;

	UTextBlock* StartMenuUndoCountText;

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UUserWidget> GameOver;

	UUserWidget* GameOverWidget;

	bool hasMoved;

	void CheckEndGame();

	bool CanCombineWithTile(ATile* const currentTile, int const& ROW, int const& COLUMN);

	void EndGame();

	void SavePreviousBoard();

	void IfHasMoved();

	AGameBoard* gameBoard;

	int currentScore;

	int previousScore;

	int undoCount;

	TArray<TArray<int>> previousBoard;
};
