
#include "Tile.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;

	Material = new RefTileMaterial();

	TileValue = 0;

	// Создания RootComponent для блока
	TileRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TileRoot"));
	RootComponent = TileRoot;

	// Создания визуального отображения блока
	BlockMeshTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMeshTile"));
	BlockMeshTile->SetupAttachment(TileRoot);
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Shapes/Shape_Plane.Shape_Plane"));
	BlockMeshTile->SetStaticMesh(MeshAsset.Object);

	// Создания надписи на блоке, для отображения значения TileValue и ее настройка 
	TextComponentForValue = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponentForValue"));
	TextComponentForValue->SetupAttachment(BlockMeshTile);
	TextComponentForValue->SetTextRenderColor(FColor::Black);
	TextComponentForValue->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TextComponentForValue->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	TextComponentForValue->SetWorldSize(50.f);
	TextComponentForValue->SetText(FString::FromInt(TileValue));
	TextComponentForValue->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	FVector NewLocationText = TileRoot->GetRelativeLocation();
	NewLocationText.Z += 5;
	TextComponentForValue->SetRelativeLocation(NewLocationText);
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetColor()
{
	switch (TileValue)// В зависимости от значения TileValue устанавливается цвет ячейки
	{
	case 0:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_Base);
		break;

	case 2:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_2);
		break;

	case 4:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_4);
		break;

	case 8:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_8);
		break;

	case 16:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_16);
		break;

	case 32:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_32);
		break;

	case 64:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_64);
		break;

	case 128:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_128);
		break;

	case 256:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_256);
		break;

	case 512:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_512);
		break;

	case 1024:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_1024);
		break;

	case 2048:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_2048);
		break;

	case 4096:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_4096);
		break;

	case 8192:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_8192);
		break;

	case 16384:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_16384);
		break;

	default:
		BlockMeshTile->SetMaterial(0, Material->TileMaterial_default);
		break;
	}
}

void ATile::SetValue(int NewValue)
{
	TileValue = NewValue;
	UpdateAppearance();
}

void ATile::UpdateAppearance()
{
	// обновление внешнего вида блока после его изменения
	if (TileValue == 0)
	{
		TextComponentForValue->SetText(TEXT(""));
	}
	else
	{
		TextComponentForValue->SetText(FString::FromInt(TileValue));
	}	
	SetColor();
}

int ATile::GetValue()
{
	return TileValue;
}


RefTileMaterial::RefTileMaterial()// Получение ссылок на материалы, для ячеек
{
	TileMaterial_Base = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_Base.TileMaterial_Base")).Get();
	TileMaterial_2 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_2.TileMaterial_2")).Get();
	TileMaterial_4 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_4.TileMaterial_4")).Get();
	TileMaterial_8 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_8.TileMaterial_8")).Get();
	TileMaterial_16 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_16.TileMaterial_16")).Get();
	TileMaterial_32 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_32.TileMaterial_32")).Get();
	TileMaterial_64 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_64.TileMaterial_64")).Get();
	TileMaterial_128 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_128.TileMaterial_128")).Get();
	TileMaterial_256 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_256.TileMaterial_256")).Get();
	TileMaterial_512 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_512.TileMaterial_512")).Get();
	TileMaterial_1024 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_1024.TileMaterial_1024")).Get();
	TileMaterial_2048 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_2048.TileMaterial_2048")).Get();
	TileMaterial_4096 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_4096.TileMaterial_4096")).Get();
	TileMaterial_8192 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_8192.TileMaterial_8192")).Get();
	TileMaterial_16384 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_16384.TileMaterial_16384")).Get();
	TileMaterial_default = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_32768.TileMaterial_32768")).Get();
}