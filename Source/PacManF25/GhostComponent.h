// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

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
	FVector2D NextTile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DestinationRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D NextDirection;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPacmanMovementComponent* MyMovementComponent;
public:
	
	UFUNCTION()
	void SelectNewDestinationTile();

	UFUNCTION()
	bool IsAtDestination();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector2D Wander(FVector2D currentTile);  
	FVector2D Chase(FVector2D currentTile);
	FVector2D Patrol(FVector2D currentTile);
	FVector2D Respawn();
	FVector2D Flee(FVector2D currentTile);
};
