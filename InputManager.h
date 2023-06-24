
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputManager.generated.h"

class AManagerGame;

UCLASS()
class GAME2048_API AInputManager : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AInputManager();

	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void PushUp();

	void PushDown();

	void PushLeft();

	void PushRight();

	void StartNewGame();

	void CancelingMove();
private:
	AManagerGame* ManagerGame;
};
