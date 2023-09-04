#include "GameBoard.h"

AGameBoard::AGameBoard()
{	
	PrimaryActorTick.bCanEverTick = true;

	boardRoot = CreateDefaultSubobject<USceneComponent>(TEXT("boardRoot"));
	RootComponent = boardRoot;
	boardRoot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	boardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	boardMesh->SetupAttachment(boardRoot);
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMeshAsset(TEXT("/Game/Shapes/Shape_Plane.Shape_Plane"));
	boardMesh->SetStaticMesh(cubeMeshAsset.Object);
	float sideLengthTile = 16.f;
	float heightTile = 1.f;
	boardMesh->SetWorldScale3D(FVector(sideLengthTile, sideLengthTile, heightTile));
	
	UMaterialInterface* boardMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/MyMaterials/Background.Background"));
	if (boardMaterial) {
		boardMesh->SetMaterial(0, boardMaterial); // установка материала
	}

	gameBoardTile.SetNum(SIZEGRID);
	for (int ROW = 0; ROW < SIZEGRID; ROW++) {
		gameBoardTile[ROW].SetNum(SIZEGRID);
	}
	myRandomizer = NewObject<URandomizer>();
}

void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
	
	world = GetWorld();
	if (world != nullptr) {
		creatingElementsOnTheBoard();
	}
}

void AGameBoard::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AGameBoard::creatingElementsOnTheBoard()
{
	float boardMargin = 2.f;
	float verticalOffset = 190.f;
	float blockSpacing = 105.0f;
	float horizontalOffset = -300.f;

	for (int ROW = 0; ROW < SIZEGRID; ROW++)
	{
		for (int COLUMN = 0; COLUMN < SIZEGRID; COLUMN++)
		{
			ATile* newtile = world->SpawnActor<ATile>(ATile::StaticClass(), 
				FVector(horizontalOffset + ROW * blockSpacing, verticalOffset - COLUMN * blockSpacing, boardMargin), FRotator(0.f, 0.f, 0.f));

			if (newtile) {
				gameBoardTile[ROW][COLUMN] = newtile;
			}
		}
	}
}

int AGameBoard::getSIZEGRID() 
{
	return SIZEGRID;
}

void AGameBoard::generateRandomValue()
{
	countEmptyTile = myRandomizer->GenerateRandomValueForTile(gameBoardTile, SIZEGRID);
}

int AGameBoard::getCountEmptyTile() const
{
	return countEmptyTile;
}