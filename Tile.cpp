#include "Tile.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;

	material = new RefTileMaterial();
	tileValue = 0;
	// Создания RootComponent для блока
	tileRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TileRoot"));
	RootComponent = tileRoot;
	// Создания визуального отображения блока
	blockMeshTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("blockMeshTile"));
	blockMeshTile->SetupAttachment(tileRoot);
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/Shapes/Shape_Plane.Shape_Plane"));
	blockMeshTile->SetStaticMesh(meshAsset.Object);
	// Создания надписи на блоке, для отображения значения TileValue и ее настройка 
	textComponentForValue = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponentForValue"));
	textComponentForValue->SetupAttachment(blockMeshTile);
	textComponentForValue->SetTextRenderColor(FColor::Black);
	textComponentForValue->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	textComponentForValue->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	textComponentForValue->SetWorldSize(50.f);
	textComponentForValue->SetText(FString::FromInt(tileValue));
	textComponentForValue->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	FVector newLocationText = tileRoot->GetRelativeLocation();
	newLocationText.Z += 5;
	textComponentForValue->SetRelativeLocation(newLocationText);
}

void ATile::setColor()
{
	switch (tileValue)// В зависимости от значения TileValue устанавливается цвет ячейки
	{
	case 0:
		blockMeshTile->SetMaterial(0, material->tileMaterial_Base);
		break;

	case 2:
		blockMeshTile->SetMaterial(0, material->tileMaterial_2);
		break;

	case 4:
		blockMeshTile->SetMaterial(0, material->tileMaterial_4);
		break;

	case 8:
		blockMeshTile->SetMaterial(0, material->tileMaterial_8);
		break;

	case 16:
		blockMeshTile->SetMaterial(0, material->tileMaterial_16);
		break;

	case 32:
		blockMeshTile->SetMaterial(0, material->tileMaterial_32);
		break;

	case 64:
		blockMeshTile->SetMaterial(0, material->tileMaterial_64);
		break;

	case 128:
		blockMeshTile->SetMaterial(0, material->tileMaterial_128);
		break;

	case 256:
		blockMeshTile->SetMaterial(0, material->tileMaterial_256);
		break;

	case 512:
		blockMeshTile->SetMaterial(0, material->tileMaterial_512);
		break;

	case 1024:
		blockMeshTile->SetMaterial(0, material->tileMaterial_1024);
		break;

	case 2048:
		blockMeshTile->SetMaterial(0, material->tileMaterial_2048);
		break;

	case 4096:
		blockMeshTile->SetMaterial(0, material->tileMaterial_4096);
		break;

	case 8192:
		blockMeshTile->SetMaterial(0, material->tileMaterial_8192);
		break;

	case 16384:
		blockMeshTile->SetMaterial(0, material->tileMaterial_16384);
		break;

	default:
		blockMeshTile->SetMaterial(0, material->tileMaterial_default);
		break;
	}
}

void ATile::setValue(int newValue)
{
	tileValue = newValue;
	updateAppearance();
}

void ATile::updateAppearance() // обновление внешнего вида блока после его изменения
{
	if (tileValue == 0) {
		textComponentForValue->SetText(TEXT(""));
	}
	else{
		textComponentForValue->SetText(FString::FromInt(tileValue));
	}	
	setColor();
}

int ATile::getValue()
{
	return tileValue;
}

RefTileMaterial::RefTileMaterial()// Получение ссылок на материалы, для ячеек
{
	tileMaterial_Base = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_Base.TileMaterial_Base")).Get();
	tileMaterial_2 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_2.TileMaterial_2")).Get();
	tileMaterial_4 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_4.TileMaterial_4")).Get();
	tileMaterial_8 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_8.TileMaterial_8")).Get();
	tileMaterial_16 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_16.TileMaterial_16")).Get();
	tileMaterial_32 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_32.TileMaterial_32")).Get();
	tileMaterial_64 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_64.TileMaterial_64")).Get();
	tileMaterial_128 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_128.TileMaterial_128")).Get();
	tileMaterial_256 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_256.TileMaterial_256")).Get();
	tileMaterial_512 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_512.TileMaterial_512")).Get();
	tileMaterial_1024 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_1024.TileMaterial_1024")).Get();
	tileMaterial_2048 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_2048.TileMaterial_2048")).Get();
	tileMaterial_4096 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_4096.TileMaterial_4096")).Get();
	tileMaterial_8192 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_8192.TileMaterial_8192")).Get();
	tileMaterial_16384 = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_16384.TileMaterial_16384")).Get();
	tileMaterial_default = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/MyMaterials/TileMaterial_32768.TileMaterial_32768")).Get();
}