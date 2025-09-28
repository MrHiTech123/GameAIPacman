// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PacmanMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PACMANF25_API UPacmanMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPacmanMovementComponent();

    UPROPERTY(EditAnywhere)
    FVector2D MovementVector;
    
    UPROPERTY(EditAnywhere)
    float MaxSpeed;

	UPROPERTY(EditAnywhere)
	FVector2D TileSize;

	UPROPERTY(EditAnywhere)
	float DestinationRadius;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	FVector GetTileCenter(FVector2D tile);

	UFUNCTION()
	FVector2D GetCurrentTile ();

	UFUNCTION(BlueprintCallable, Category="Movement")
	void SetMovementVector (FVector2D input);
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void UpdateMovement(FVector2D input, bool allowReverse);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsMoving();
};
