#pragma once
#include <unordered_map>
#include <memory>
#include "SkeletalAnim.h"

class SkeletonManager
{
public:
	static SkeletonManager* GetInstance();
	static void DestroyInstance();

	std::shared_ptr<SkeletalAnim::SkeletonData> CreateOrGetSkeletonData(SkeletalAnim::SkeletonJson& json, const std::string& jsonPath);

private:
	SkeletonManager() {}
	~SkeletonManager();

	static SkeletonManager* m_instance;
	std::unordered_map<std::string, std::shared_ptr<SkeletalAnim::SkeletonData>> m_skeletonMap;
};

SkeletonManager* GetSkeletonManager();