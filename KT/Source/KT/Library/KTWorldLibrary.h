#pragma once

#include "CoreMinimal.h"
#include "KTWorldLibrary.generated.h"

/**
 * 
 */
UCLASS()
class KT_API UKTWorldLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		static void ChangeScene(FName sceneName);
};
