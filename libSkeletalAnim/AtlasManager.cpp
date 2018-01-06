#include "AtlasManager.h"
#include "Logger.h"

AtlasManager* AtlasManager::m_instance = nullptr;

AtlasManager* AtlasManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new AtlasManager;

	return m_instance;
}

void AtlasManager::DestroyInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

AtlasManager::~AtlasManager()
{
	m_atlasMap.clear();
}

SkeletalAnim::Atlas* AtlasManager::CreateOrGetAtlas(const std::string& atlasPath)
{
	std::string key = atlasPath; // todo: only atlas name

	auto it = m_atlasMap.find(key);
	if (it != m_atlasMap.end())
		return it->second.get();

	SkeletalAnim::Atlas* atlas = SkeletalAnim::CreateAtlasFromFile(atlasPath);
	if (atlas == nullptr)
	{
		Log("GetSkeletonData: Cannot Open atlas- key[%s], path[%s]", key.c_str(), atlasPath.c_str());
		return nullptr;
	}

	m_atlasMap[key] = std::unique_ptr<SkeletalAnim::Atlas>(atlas);
	return atlas;
}

AtlasManager* GetAtlasManager()
{
	return AtlasManager::GetInstance();
}