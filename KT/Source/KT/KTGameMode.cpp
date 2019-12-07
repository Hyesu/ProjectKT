// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "KTGameMode.h"
#include "KTCharacter.h"

AKTGameMode::AKTGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AKTCharacter::StaticClass();	
}
