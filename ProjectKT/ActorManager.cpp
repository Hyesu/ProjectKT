#include "stdafx.h"
#include "ActorManager.h"

IMPL_SINGLETONE(ActorManager);

void ActorManager::Draw() {
	for (auto& it : m_actors)
		it->Draw();
}

ActorManager* GetActorManager() {
	return ActorManager::GetInstance();
}

void ActorManager::CreateActor() {
	auto actor = std::make_unique<Actor>(SCALE());
	m_actors.emplace_back(std::move(actor));
}