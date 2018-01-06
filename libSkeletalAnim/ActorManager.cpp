#include "ActorManager.h"
#include "Logger.h"

namespace SkeletalAnim
{
	ActorManager* ActorManager::m_instance = nullptr;

	ActorManager* ActorManager::GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new ActorManager;

		return m_instance;
	}
	
	void ActorManager::DestroyInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	ActorManager::~ActorManager()
	{
		m_actors.clear();
	}

	ActorManager* GetActorManager()
	{
		return ActorManager::GetInstance();
	}

	bool ActorManager::AddActor(const std::string& atlasPath, const std::string& jsonPath)
	{
		auto actor = std::make_unique<SkeletalAnimActor>(atlasPath, jsonPath);
		if (actor->IsValid() == false)
		{
			Log("AddActor fail: %s", actor->ToString().c_str());
			return false;
		}

		m_actors.emplace_back(std::move(actor));
		return true;
	}

	void ActorManager::Update(float delta)
	{
		for (auto& it : m_actors)
			it->Update(delta);
	}
}