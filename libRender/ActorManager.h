#pragma once
#include "defines.h"
#include "Actor.h"
#include <memory>
#include <list>

class ActorManager {
	DECL_SINGLETONE(ActorManager);

public:
	void Draw();
	void CreateActor();

private:
	std::list<std::unique_ptr<Actor>> m_actors;
};

ActorManager* GetActorManager();
