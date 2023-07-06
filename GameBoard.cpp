
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

	float sideLengthTile = 16.f;
	float heightTile = 1.f;
	BoardMesh->SetWorldScale3D(FVector(sideLengthTile, sideLengthTile, heightTile));
	
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
	float boardMargin = 2.f;
	float verticalOffset = 190.f;
	float blockSpacing = 105.0f;
	float horizontalOffset = -300.f;

	for (int ROW = 0; ROW < SIZEGRID; ROW++)
	{
		for (int COLUMN = 0; COLUMN < SIZEGRID; COLUMN++)
		{
			ATile* newtile = World->SpawnActor<ATile>(ATile::StaticClass(), 
				FVector(horizontalOffset + ROW * blockSpacing, verticalOffset - COLUMN * blockSpacing, boardMargin), FRotator(0.f, 0.f, 0.f));

			if (newtile != nullptr)
			{
				GameBoardTile[ROW][COLUMN] = newtile;
			}
		}
	}
}

int AGameBoard::GetSIZEGRID() 
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

