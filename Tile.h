// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Tile.generated.h"


struct RefTileMaterial// Структура для хранения ссылок на метериалы
{
	UMaterial* TileMaterial_Base;
	UMaterial* TileMaterial_2;
	UMaterial* TileMaterial_4;
	UMaterial* TileMaterial_8;
	UMaterial* TileMaterial_16;
	UMaterial* TileMaterial_32;
	UMaterial* TileMaterial_64;
	UMaterial* TileMaterial_128;
	UMaterial* TileMaterial_256;
	UMaterial* TileMaterial_512;
	UMaterial* TileMaterial_1024;
	UMaterial* TileMaterial_2048;
	UMaterial* TileMaterial_4096;
	UMaterial* TileMaterial_8192;
	UMaterial* TileMaterial_16384;
	UMaterial* TileMaterial_default;

	RefTileMaterial();
};

UCLASS()
class GAME2048_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	

	ATile();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void SetColor(); // Установка цвета блока

	void SetValue(int NewValue); // Установка значения блока

	void UpdateAppearance(); // Функция для обновления надписи на блоке и его цвета

	int GetValue();

private:

	int TileValue;

	USceneComponent* TileRoot;

	UStaticMeshComponent* BlockMeshTile;

	UTextRenderComponent* TextComponentForValue;

	RefTileMaterial* Material;
};
