
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
	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	friend class AInputManager;
	void pushUp();
	void pushDown();
	void pushLeft();
	void pushRight();
	void startGame();
	void setPreviousBoard();

	void updateUndoCount(int countUndo);
	void updateScore(int score);
	void checkEndGame();
	bool canCombineWithTile(ATile* const currentTile, int const& ROW, int const& COLUMN);
	void endGame();
	void savePreviousBoard();
	void ifHasMoved();

private:
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UUserWidget> mainMenu;
	UUserWidget* startMenuWidget;
	UTextBlock* startMenuScoreBlock;
	UTextBlock* startMenuUndoCountText;

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<UUserWidget> gameOver;
	UUserWidget* gameOverWidget;

	TArray<TArray<int>> previousBoard;
	AGameBoard* gameBoard;
	bool hasMoved;
	int currentScore;
	int previousScore;
	int undoCount;
};