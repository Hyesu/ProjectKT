#pragma once

#include "CoreMinimal.h"
#include "ManagerBase.h"
#include "SceneManager.generated.h"

class USceneBase;

UCLASS()
class KT_API USceneManager : public UManagerBase
{
	GENERATED_BODY()

	DECL_SINGLETONE(USceneManager);
	
public:
	void Initialize() final;

	void ChangeScene(const FName& sceneName);

private:
	UPROPERTY()
		USceneBase* _currentScene;
};