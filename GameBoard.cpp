
#include "GameBoard.h"


AGameBoard::AGameBoard()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	BoardRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BoardRoot"));
	RootComponent = BoardRoot;
	BoardRoot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	BoardMesh->SetupAttachment(BoardRoot);

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Game/Shapes/Shape_Plane.Shape_Plane"));
	BoardMesh->SetStaticMesh(CubeMeshAsset.Object);
	BoardMesh->SetWorldScale3D(FVector(16.f, 16.f, 1.f));

	RootTextRenderScore = CreateDefaultSubobject<USceneComponent>(TEXT("RootTextRenderScore"));
	TextRenderScore = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderScore"));
	TextRenderScore->SetupAttachment(RootTextRenderScore);

	RootTextRenderUndoCount = CreateDefaultSubobject<USceneComponent>(TEXT("RootTextRenderUndoCount"));
	TextRenderUndoCount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderUndoCount"));
	TextRenderUndoCount->SetupAttachment(RootTextRenderUndoCount);

	RootTextRenderEndGame = CreateDefaultSubobject<USceneComponent>(TEXT("RootTextRenderEndGame"));
	TextRenderEndGame = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderEndGame"));
	TextRenderEndGame->SetupAttachment(RootTextRenderEndGame);
	
	UMaterialInterface* BoardMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/MyMaterials/Background.Background"));
	if (BoardMaterial)
	{
		BoardMesh->SetMaterial(0, BoardMaterial); // установка материала
	}

	GameBoardTile.SetNum(SIZEGRID);
	
	for (int ROW = 0; ROW < SIZEGRID; ROW++)
	{
		GameBoardTile[ROW].SetNum(SIZEGRID);
	}

	MyRandomizer = NewObject<URandomizer>();
}

void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
	
	World = GetWorld();

	if (World != nullptr)
	{
		CreatingElementsOnTheBoard();
	}
}

// Called every frame
void AGameBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameBoard::CreatingElementsOnTheBoard()
{
	for (int ROW = 0; ROW < SIZEGRID; ROW++)
	{
		for (int COLUMN = 0; COLUMN < SIZEGRID; COLUMN++)
		{
			ATile* newtile = World->SpawnActor<ATile>(ATile::StaticClass(), FVector(-300.f + ROW * 105, 190.f - COLUMN * 105, 2.f), FRotator(0.f, 0.f, 0.f));

			if (newtile != nullptr)
			{
				GameBoardTile[ROW][COLUMN] = newtile;
			}
		}
	}

	SetTextRenderComponent(TextRenderScore, GameBoardTile[0][0]->GetActorLocation(), 50, 80, "0", FColor::White, 40.0f);
	SetTextRenderComponent(TextRenderUndoCount, GameBoardTile[0][SIZEGRID - 1]->GetActorLocation(), 42, -79.5f, "3", FColor::White, 25.0f);
	SetTextRenderComponent(TextRenderEndGame, GameBoardTile[SIZEGRID - 1][0]->GetActorLocation(), 0, -75, "END GAME", FColor::Red, 40.0f);
}

int AGameBoard::GetSIZEGRID() const
{
	return SIZEGRID;
}

void AGameBoard::GenerateRandomValue()
{
	CountEmptyTile = MyRandomizer->GenerateRandomValueForTile(GameBoardTile, SIZEGRID);
}

int AGameBoard::GetCountEmptyTile() const
{
	return CountEmptyTile;
}

void AGameBoard::SetCurrentScore(int NewCurrentScore)
{
	CurrentScore = NewCurrentScore;
}

int AGameBoard::GetCurrentScore() const
{
	return CurrentScore;
}

void AGameBoard::DisplayGameOverMessage()
{
	TextRenderEndGame->SetHiddenInGame(false);
}

void AGameBoard::HideGameOverMessage()
{
	TextRenderEndGame->SetHiddenInGame(true);
}

void AGameBoard::UpdateScore(int newScore)
{
	TextRenderScore->SetText(FString::Printf(TEXT("%d"), newScore));
}

void AGameBoard::UpdateUndoCount(int newUndoCount)
{
	TextRenderUndoCount->SetText(FString::Printf(TEXT("%d"), newUndoCount));
}

void AGameBoard::SetTextRenderComponent(UTextRenderComponent* TextRenderComp, FVector Position, float XPos, float YPos, FString Text, FColor Color,float sizeText)
{
	TextRenderComp->SetTextRenderColor(Color);
	Position.Z += 250;
	Position.Y += YPos;
	Position.X += XPos;
	TextRenderComp->SetRelativeLocation(Position);
	TextRenderComp->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	TextRenderComp->SetWorldSize(sizeText);
	TextRenderComp->SetText(FText::FromString(Text));
}

