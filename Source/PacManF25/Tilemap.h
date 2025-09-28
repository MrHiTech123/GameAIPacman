// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tilemap.generated.h"

/**
 * 
 */
UCLASS()
class PACMANF25_API UTilemap : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	TArray<int32> Data;

	UPROPERTY(VisibleAnywhere)
	int32 NumRows;

	UPROPERTY(VisibleAnywhere)
	int32 NumColumns;

	UTilemap();

	int Load(FString Filename);


	int GetData(int Row, int Column);
	int GetData(FUintVector2 Tile);

	void SetData(int Row, int Column, int Value);
	void SetData(FUintVector2 Tile, int Value);	
};
