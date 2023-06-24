
#include "InputManager.h"
#include "Kismet/GameplayStatics.h"
#include "ManagerGame.h"

AInputManager::AInputManager()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AInputManager::BeginPlay()
{
	Super::BeginPlay();
	ManagerGame = Cast<AManagerGame>(UGameplayStatics::GetActorOfClass(GetWorld(), AManagerGame::StaticClass()));
}

void AInputManager::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("PushUp", IE_Pressed, this, &AInputManager::PushUp);
	InputComponent->BindAction("PushDown", IE_Pressed, this, &AInputManager::PushDown);
	InputComponent->BindAction("PushLeft", IE_Pressed, this, &AInputManager::PushLeft);
	InputComponent->BindAction("PushRight", IE_Pressed, this, &AInputManager::PushRight);
	InputComponent->BindAction("NewGame",IE_Pressed,this, &AInputManager::StartNewGame);
	InputComponent->BindAction("CancelingMove", IE_Pressed, this, &AInputManager::CancelingMove);
}

void AInputManager::PushUp()
{
	ManagerGame->PushUp();
}

void AInputManager::PushDown()
{
	ManagerGame->PushDown();
}

void AInputManager::PushLeft()
{
	ManagerGame->PushLeft();
}

void AInputManager::PushRight()
{
	ManagerGame->PushRight();
}

void AInputManager::StartNewGame()
{
	ManagerGame->StartGame();
}

void AInputManager::CancelingMove()
{
	ManagerGame->SetPreviousBoard();
}