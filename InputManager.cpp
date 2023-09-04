
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
	managerGame = Cast<AManagerGame>(UGameplayStatics::GetActorOfClass(GetWorld(), AManagerGame::StaticClass()));
}

void AInputManager::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("PushUp", IE_Pressed, this, &AInputManager::pushUp);
	InputComponent->BindAction("PushDown", IE_Pressed, this, &AInputManager::pushDown);
	InputComponent->BindAction("PushLeft", IE_Pressed, this, &AInputManager::pushLeft);
	InputComponent->BindAction("PushRight", IE_Pressed, this, &AInputManager::pushRight);
	InputComponent->BindAction("NewGame",IE_Pressed,this, &AInputManager::startNewGame);
	InputComponent->BindAction("CancelingMove", IE_Pressed, this, &AInputManager::cancelingMove);
}

void AInputManager::pushUp()
{
	managerGame->pushUp();
}

void AInputManager::pushDown()
{
	managerGame->pushDown();
}

void AInputManager::pushLeft()
{
	managerGame->pushLeft();
}

void AInputManager::pushRight()
{
	managerGame->pushRight();
}

void AInputManager::startNewGame()
{
	managerGame->startGame();
}

void AInputManager::cancelingMove()
{
	managerGame->setPreviousBoard();
}