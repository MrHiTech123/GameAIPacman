// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanMovementComponent.h"

// Sets default values for this component's properties
UPacmanMovementComponent::UPacmanMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MovementVector = FVector2D(0,0);
	MaxSpeed = 200;

	TileSize = FVector2D(80,80);
	DestinationRadius = 10;
}


// Called when the game starts
void UPacmanMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	PACMAN_INSTANCE = this;
	
}

void UPacmanMovementComponent::SetMovementVector(FVector2D input)
{
	MovementVector = input;
}

FVector2D UPacmanMovementComponent::GetMovementVector() {
	return MovementVector;
}

void UPacmanMovementComponent::UpdateMovement(FVector2D input, bool allowReverse)
{
	AActor* actor = GetOwner();
	FVector location = actor->GetActorLocation();

	// only one axis at a time
	UE_LOG(LogTemp, Display, TEXT("Update Movement Input: %f %f"), input.X, input.Y);
	if (abs(input.Y)>0)
	{
		input.X=0;
	}
	
	int tileX = location.X / TileSize.X;
	int tileY = location.Y / TileSize.Y;

	FVector tileCenter = GetTileCenter(GetCurrentTile());

	if (FVector::DistSquared(location, tileCenter) < DestinationRadius * DestinationRadius)
	{
		MovementVector = input;
	}
	else
	{
		// allow reversing
		if (allowReverse && (input.Dot(MovementVector)==-1))
		{
			MovementVector = input;
		}
	}
}

// Called every frame 
void UPacmanMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* actor = GetOwner();
	FVector location = actor->GetActorLocation();

	FVector move = FVector(MovementVector.X, MovementVector.Y, 0) * MaxSpeed * DeltaTime;
	FVector newLocation = location + move;
	actor->SetActorLocation(newLocation);

	// if moving, orient to direction of movement
	// 
	if (IsMoving())
	{
		float yaw = FMath::Atan2(MovementVector.Y,MovementVector.X);
		actor->SetActorRotation(FRotator(0,FMath::RadiansToDegrees(yaw),0));
	}
	

	
}

FVector UPacmanMovementComponent::GetTileCenter(FVector2D tile)
{
	FVector centerPoint;
	centerPoint.X = tile.X * TileSize.X + (TileSize.X / 2);
	centerPoint.Y = tile.Y * TileSize.Y + (TileSize.Y / 2);
	return centerPoint;
}

FVector2D UPacmanMovementComponent::GetCurrentTile()
{
	FVector location = GetOwner()->GetActorLocation();
	FVector2D tile;
	tile.X = FMath::Floor (location.X / TileSize.X );
	tile.Y = FMath::Floor (location.Y / TileSize.Y );
	return tile;
}


bool UPacmanMovementComponent::IsMoving()
{
	if (MovementVector.SquaredLength() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
