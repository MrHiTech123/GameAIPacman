// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MazeTemp.h"

#include "PacmanMovementComponent.h"
#include "GhostComponent.generated.h"

UENUM(BlueprintType)
enum class GhostState : uint8 {
	WANDER = 0 UMETA(DisplayName = "Wander"),
	PATROL = 1  UMETA(DisplayName = "Patrol"),
	CHASE = 2     UMETA(DisplayName = "Chase"),
	FLEE = 3 UMETA(DisplayName = "Flee")
};

UENUM(BlueprintType)
enum class GhostType : uint8 {
	BLINKY = 0 UMETA(DisplayName = "Blinky"),
	CLYDE = 1 UMETA(DisplayName = "Clyde"),
	PINKY = 2 UMETA(DisplayName = "Pinky"),
	INKY = 3 UMETA(DisplayName = "Inky")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PACMANF25_API UGhostComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UGhostComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	GhostState State;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	GhostType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D NextTile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DestinationRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D NextDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Home;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Pacman;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Blinky;
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPacmanMovementComponent* MyMovementComponent;
	AMazeTemp* mazeTemp;
	
	const int EMPTY_TILE = 0;
	const int TIME_UNTIL_CHASE = 5;
	
	float timePassed = 0;
	
	bool ValidTurn(FVector2D futureVector, FVector2D turn, bool allowReverse);
public:
	
	UFUNCTION()
	void SelectNewDestinationTile();

	UFUNCTION()
	bool IsAtDestination();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector2D Wander(FVector2D currentTile);  
	FVector2D Chase(FVector2D currentTile);
    FVector2D ChaseBlinkyStyle(FVector2D currentTile);
    FVector2D ChaseClydeStyle(FVector2D currentTile);
    FVector2D ChasePinkyStyle(FVector2D currentTile);
    FVector2D ChaseInkyStyle(FVector2D currentTile);
	
	FVector2D Patrol(FVector2D currentTile);
	FVector2D ChaseTile(FVector2D currentTile, FVector2D targetTile);
	FVector2D Respawn();
	FVector2D Flee(FVector2D currentTile);
	
	AMazeTemp* GetMazeTemp();
};
