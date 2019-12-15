#include "SceneManager.h"
#include "Scene/SceneBase.h"
#include "Kismet/GameplayStatics.h"

IMPL_SINGLETONE(USceneManager);

void USceneManager::Initialize()
{
	USceneManager::_instance = this;
}

void USceneManager::ChangeScene(const FName& sceneName)
{
	if (_currentScene != nullptr) {
		_currentScene->Finalize();
	}

	// todo: get scene by scene name

	UGameplayStatics::OpenLevel(this, "Stage01");
}