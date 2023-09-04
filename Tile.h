#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Tile.generated.h"

struct RefTileMaterial// Структура для хранения ссылок на метериалы
{
	UMaterial* tileMaterial_Base;
	UMaterial* tileMaterial_2;
	UMaterial* tileMaterial_4;
	UMaterial* tileMaterial_8;
	UMaterial* tileMaterial_16;
	UMaterial* tileMaterial_32;
	UMaterial* tileMaterial_64;
	UMaterial* tileMaterial_128;
	UMaterial* tileMaterial_256;
	UMaterial* tileMaterial_512;
	UMaterial* tileMaterial_1024;
	UMaterial* tileMaterial_2048;
	UMaterial* tileMaterial_4096;
	UMaterial* tileMaterial_8192;
	UMaterial* tileMaterial_16384;
	UMaterial* tileMaterial_default;

	RefTileMaterial();
};

UCLASS()
class GAME2048_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATile();
	int getValue();

private:
	friend class AManagerGame;
	friend class URandomizer;
	void setColor(); // Установка цвета блока
	void setValue(int newValue); // Установка значения блока
	void updateAppearance(); // Функция для обновления надписи на блоке и его цвета

private:
	int tileValue;
	USceneComponent* tileRoot;
	UStaticMeshComponent* blockMeshTile;
	UTextRenderComponent* textComponentForValue;
	RefTileMaterial* material;
};
