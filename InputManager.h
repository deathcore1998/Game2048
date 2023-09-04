
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputManager.generated.h"

class AManagerGame;

UCLASS()
class GAME2048_API AInputManager : public APlayerController
{
	GENERATED_BODY()
public:
	AInputManager();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void pushUp();
	void pushDown();
	void pushLeft();
	void pushRight();
	void startNewGame();
	void cancelingMove();

private:
	AManagerGame* managerGame;
};
