#pragma once

#include "CoreMinimal.h"
#include "KTCommonDefine.h"
#include "ManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class KT_API UManagerBase : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Initialize() {};
	virtual void Finalize() {};
};