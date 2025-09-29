// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeTemp.h"

// Sets default values
AMazeTemp::AMazeTemp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileSize=FVector2D(80,80);

	LoadTileset();
	TilemapFilename = "Data/MazeRedo.csv";
	USceneComponent* Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Scene);

}

void AMazeTemp::Generate()
{
	if (!IsValid(Tilemap))
	{
		UE_LOG(LogTemp, Error, TEXT("Tilemap is invalid"));
		return;
	}
	
	for (int Row=0;Row<Tilemap->NumRows;Row++)
	{
		for (int Column=0;Column<Tilemap->NumColumns;Column++)
		{
			int TileValue = Tilemap->GetData(Row,Column);
			if (TileValue<0)
			{
				UE_LOG(LogTemp, Error, TEXT("invalid data at %d, %d"), Row,Column);
				
			}
			else if (TileValue<TileMeshes.Num() && IsValid(TileMeshes[TileValue]))
			{
				FString MeshName = FString::Printf(TEXT("Tile_%d_%d"), Row, Column);
				UE_LOG(LogTemp,Display,TEXT("Add mesh component (%d,%d) = %d"), Row, Column, TileValue);
				UStaticMeshComponent* MeshComponent=NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), *MeshName);
				MeshComponent->RegisterComponent();
				//TileComponents[MeshComponentIndex]=CreateDefaultSubobject<UStaticMeshComponent>(*MeshName);
				
				MeshComponent->SetStaticMesh(TileMeshes[TileValue]);
				MeshComponent->SetupAttachment(RootComponent);
				MeshComponent->SetRelativeLocation(FVector(Row * TileSize.X, Column * TileSize.Y,0));

				TileComponents.Add(MeshComponent);
			}
			else
			{
				UE_LOG(LogTemp,Error,TEXT("Couldn't add mesh component (%d,%d) = %d"), Row, Column, TileValue);
			}
		}
	
	}
}

void AMazeTemp::LoadTileset()
{
	TilesetSize=21;
	TileMeshes.SetNum(TilesetSize);
	
	for (int i=0;i<TilesetSize;i++)
	{
		FString assetPath = FString::Printf(TEXT("/Game/MazeSet2/tile_t_%d.tile_t_%d"),i,i);
		
		ConstructorHelpers::FObjectFinder<UStaticMesh> asset (*assetPath);
		if (asset.Succeeded())
		{
			TileMeshes[i] = asset.Object;
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Could not load %s"),*assetPath);
		}
	}
}

int AMazeTemp::LoadTilemap()
{
	
	int result = Tilemap->Load(TilemapFilename);
	return result; 
}

// Called when the game starts or when spawned
void AMazeTemp::BeginPlay()
{
	Super::BeginPlay();
	Tilemap = NewObject<UTilemap>();
	if (LoadTilemap())
	{
		UE_LOG(LogTemp, Display, TEXT("Tilemap size: %d %d"),Tilemap->NumRows, Tilemap->NumColumns);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load tilemap"));
	}

	Generate();
}

// Called every frame
void AMazeTemp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AMazeTemp::GetData(int row, int col) {
	return Tilemap->GetData(row, col);
}

