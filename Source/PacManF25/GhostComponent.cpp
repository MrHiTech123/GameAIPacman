// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostComponent.h"

#include "AI/NavigationSystemBase.h"

// Sets default values for this component's properties
UGhostComponent::UGhostComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// set tile size and destination radius

	State=GhostState::WANDER;

}


// Called when the game starts
void UGhostComponent::BeginPlay()
{
	Super::BeginPlay();

	// get reference to movement component
	MyMovementComponent = GetOwner()->GetComponentByClass<UPacmanMovementComponent>();
	
	
	if (IsValid(MyMovementComponent))
	{
		NextTile=MyMovementComponent->GetCurrentTile();
		
		GetOwner()->SetActorLocation(MyMovementComponent->GetTileCenter(NextTile));
		Destination = MyMovementComponent->GetTileCenter(NextTile);
	}
}


// Called every frame
void UGhostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector location = GetOwner()->GetActorLocation();
	FVector2D movement;
	FVector2D currentTile;
	if (IsValid(MyMovementComponent))
	{
		movement=MyMovementComponent->MovementVector;
		currentTile=MyMovementComponent->GetCurrentTile();
	}
	
	int Key = 0;
	GEngine->AddOnScreenDebugMessage(0,30,FColor::Cyan,
		FString::Printf(
			TEXT("Location: %f %f %f"), location.X, location.Y, location.Z));
	GEngine->AddOnScreenDebugMessage(1,30,FColor::Orange,
		FString::Printf(TEXT("Destination: %f %f %f"),Destination.X, Destination.Y, Destination.Z));
	GEngine->AddOnScreenDebugMessage(2,30,FColor::Green,
		FString::Printf(TEXT("Movement Vector: %f %f"),movement.X, movement.Y));
	
	GEngine->AddOnScreenDebugMessage(3,30,FColor::Cyan,
		FString::Printf(TEXT("Current Tile: %d %d"), (int)currentTile.X, (int)currentTile.Y));

	GEngine->AddOnScreenDebugMessage(4,30,FColor::Yellow,
	FString::Printf(TEXT("Next Tile: %d %d"), (int)NextTile.X, (int)NextTile.Y));

	GEngine->AddOnScreenDebugMessage(5,30,FColor::Yellow,
		FString::Printf(TEXT("Next Direction: %f %f"), NextDirection.X, NextDirection.Y));


		
	if (currentTile == NextTile)
	{
		SelectNewDestinationTile();
	}

	if (IsAtDestination())
	{
		UE_LOG(LogTemp, Display, TEXT("At Destination"));

		// snap to destination

		GetOwner()->SetActorLocation(Destination);
		// // set movement vector to NextDirection
		if (IsValid(MyMovementComponent))
		{
			Destination = MyMovementComponent->GetTileCenter(NextTile);
			UE_LOG(LogTemp, Display, TEXT("New Destination: %f %f"), Destination.X, Destination.Y);
			MyMovementComponent->SetMovementVector(NextDirection);
		}
	}
}


void UGhostComponent::SelectNewDestinationTile()
{
	FVector2D currentTile = MyMovementComponent->GetCurrentTile();
	switch (State)
	{
	case GhostState::WANDER:
		NextDirection = Wander(currentTile);
		break;
	case GhostState::FLEE:
		NextDirection = Wander(currentTile);
	}
	
	NextTile = currentTile + NextDirection;
	UE_LOG(LogTemp, Display, TEXT("Selected destination tile: %f %f"),NextTile.X, NextTile.Y )
}

FVector2D UGhostComponent::Wander (FVector2D currentTile)
{
	// pick random direction
	int direction = FMath::RandRange(0,3);
	FVector2D directionVector(0,0);

	
	switch (direction)
	{
	case 0:
		directionVector.X=1;
		break;
	case 1:
		directionVector.X=-1;
		break;
	case 2:
		directionVector.Y=1;
		break;
	case 3:
		directionVector.Y=-1;
		break;
	}
	
	

	return directionVector;
	
}

FVector2D UGhostComponent::Chase(FVector2D currentTile)
{
	FVector2D directionVector(0,0);
	return directionVector;
}

FVector2D UGhostComponent::Flee(FVector2D currentTile)
{
	FVector2D directionVector(0,0);
	return directionVector;
}

FVector2D UGhostComponent::Patrol(FVector2D currentTile)
{
	FVector2D directionVector(0,0);
	return directionVector;
}

bool UGhostComponent::IsAtDestination()
{ 
	FVector location = GetOwner()->GetActorLocation();
	if (FVector::DistSquared(location, Destination ) < DestinationRadius * DestinationRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}


