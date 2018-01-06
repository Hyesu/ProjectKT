#pragma once
#include "SkeletalAnim.h"

#include <unordered_map>
#include <memory>

class AtlasManager 
{
public:
	static AtlasManager* GetInstance();
	static void DestroyInstance();

	SkeletalAnim::Atlas* CreateOrGetAtlas(const std::string& atlasPath);

private:
	AtlasManager() {}
	~AtlasManager();

	static AtlasManager* m_instance;
	std::unordered_map<std::string, std::unique_ptr<SkeletalAnim::Atlas>> m_atlasMap;
};

AtlasManager* GetAtlasManager();