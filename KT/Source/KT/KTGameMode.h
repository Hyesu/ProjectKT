// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KTCommonDefine.h"
#include "KTGameMode.generated.h"

class UManagerBase;
UCLASS(minimalapi)
class AKTGameMode : public AGameModeBase
{
	GENERATED_BODY()

	DECL_SINGLETONE(AKTGameMode);

public:
	AKTGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UClass* GetDefaultPawnClassForController_Implementation(AController* InController);

private:
	void InitManager();

	UPROPERTY()
		TMap<UClass*, UManagerBase*> _managers;
};