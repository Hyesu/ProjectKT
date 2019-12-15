#include "KTWorldLibrary.h"

#include "Manager/SceneManager.h"

void UKTWorldLibrary::ChangeScene(FName sceneName)
{
	USceneManager::Get()->ChangeScene(sceneName);
}