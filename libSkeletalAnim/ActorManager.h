#pragma once
#include "SkeletalAnimActor.h"
#include <vector>
#include <memory>

namespace SkeletalAnim
{
	class ActorManager
	{
	public:
		static ActorManager* GetInstance();
		static void DestroyInstance();

		bool AddActor(const std::string& atlasPath, const std::string& jsonPath);
		void Update(float delta);

	private:
		ActorManager() {}
		~ActorManager();

		static ActorManager* m_instance;
		std::vector<std::unique_ptr<SkeletalAnimActor>> m_actors;
	};

	ActorManager* GetActorManager();
}