// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tilemap.h"
#include "MazeTemp.generated.h"

UCLASS()
class PACMANF25_API AMazeTemp : public AActor
{
	GENERATED_BODY()
	
public:	


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TilesetSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TileSize;
	
	UPROPERTY(VisibleAnywhere)
	UTilemap* Tilemap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TilemapFilename;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> TileMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> TileComponents;

	// Sets default values for this actor's properties
	AMazeTemp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void Generate();
	
	int LoadTilemap();
	int GetData(int row, int col);
	void LoadTileset();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
