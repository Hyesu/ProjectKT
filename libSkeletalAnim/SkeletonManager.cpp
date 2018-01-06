#include "SkeletonManager.h"
#include "Logger.h"

SkeletonManager* SkeletonManager::m_instance = nullptr;
SkeletonManager* SkeletonManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new SkeletonManager;

	return m_instance;
}

void SkeletonManager::DestroyInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

std::shared_ptr<SkeletalAnim::SkeletonData> SkeletonManager::CreateOrGetSkeletonData(SkeletalAnim::SkeletonJson& json, const std::string& jsonPath)
{
	std::string key = jsonPath; // todo: only json file name
	auto it = m_skeletonMap.find(key);
	if (it != m_skeletonMap.end())
		return it->second;

	SkeletalAnim::SkeletonData* skeletonData = json.readSkeletonDataFile(jsonPath);
	if (skeletonData == nullptr)
	{
		Log("CreateOrGetSkeletonData: Cannot Open json - key[%s], path[%s]", key.c_str(), jsonPath.c_str());
		return nullptr;
	}
	auto _skeletonData = std::shared_ptr<SkeletalAnim::SkeletonData>(skeletonData);
	m_skeletonMap[key] = _skeletonData;
	return _skeletonData;
}

SkeletonManager::~SkeletonManager()
{
	m_skeletonMap.clear();
}

SkeletonManager* GetSkeletonManager()
{
	return SkeletonManager::GetInstance();
}