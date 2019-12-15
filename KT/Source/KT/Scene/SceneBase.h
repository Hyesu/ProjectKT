#pragma once

#include "CoreMinimal.h"
#include "SceneBase.generated.h"

/**
 * 
 */
UCLASS()
class KT_API USceneBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize();
	virtual void Finalize();
};