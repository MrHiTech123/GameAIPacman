// Fill out your copyright notice in the Description page of Project Settings.


#include "Tilemap.h"
#include "Misc/Paths.h"
#include "Misc/CString.h"
#include "Misc/Paths.h"
UTilemap::UTilemap()
{
	NumRows=0;
	NumColumns=0;
}

int UTilemap::GetData(FUintVector2 Tile)
{
	return GetData(Tile.X, Tile.Y);
}

int UTilemap::GetData(int Row, int Column)
{
	int Index = Row * NumColumns + Column;
	if (Index < Data.Num())
	{
		return Data[Index];
	}
	else
	{
		return -1;	// error 
	}
}

void UTilemap::SetData(FUintVector2 Tile, int Value)
{
	SetData(Tile.X, Tile.Y, Value);
}

void UTilemap::SetData(int Row, int Column, int Value)
{
	int Index = Row * NumColumns + Column;
	if (Index < Data.Num())
	{
		Data[Index] = Value;
	}
}

int UTilemap::Load(FString Filename)
{
	TArray<FString> Lines;
	FString FullPath = FPaths::Combine(FPaths::ProjectContentDir(), Filename);
	
	if (!FFileHelper::LoadFileToStringArray(Lines, *FullPath))
	{
		UE_LOG(LogTemp, Error, TEXT("UTilemap::Load(): Failed to load file %s"), *FullPath);
		return false;
	}
	
	NumRows=Lines.Num();
	if (NumRows<1)
	{
		UE_LOG(LogTemp, Error, TEXT("UTilemap::Load():File is empty"));
		return false;
	}

	TArray<FString> Tokens;
	Lines[0].ParseIntoArray(Tokens,TEXT(","));
	NumColumns=Tokens.Num();

	Data.SetNum(NumRows*NumColumns);

	for (int Row=0;Row<NumRows; Row++)
	{
		Lines[Row].ParseIntoArray(Tokens,TEXT(","));
		for (int Column=0;Column<NumColumns;Column++)
		{
			int Value;
			FString Token = Tokens[Column];
			Value=FCString::Atoi(*Token);
			SetData(Row,Column,Value);
		}
	}
	return true;
}




