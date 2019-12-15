// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "KTGameMode.h"
#include "KTCharacter.h"

#include "Manager/SceneManager.h"

IMPL_SINGLETONE(AKTGameMode);

AKTGameMode::AKTGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AKTCharacter::StaticClass();	
}

UClass* AKTGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return nullptr;
}

void AKTGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	AKTGameMode::_instance = this;

	InitManager();
}

void AKTGameMode::InitManager()
{
	_managers.Emplace(USceneManager::StaticClass(), NewObject<USceneManager>(this));

	for (auto& it : _managers) {
		it.Value->Initialize();
	}
}