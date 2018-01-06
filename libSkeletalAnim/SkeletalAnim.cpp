#include "SkeletalAnim.h"
#include "AtlasManager.h"
#include "SkeletonManager.h"
#include "Logger.h"

namespace SkeletalAnim
{
	Atlas* CreateAtlasFromFile(const std::string& atlasPath)
	{
		return spine::Atlas::createFromFile(atlasPath.c_str(), nullptr);
	}

	std::shared_ptr<SkeletonData> GetSkeletonData(const std::string& atlasPath, const std::string& jsonPath) 
	{
		Atlas* atlas = GetAtlasManager()->CreateOrGetAtlas(atlasPath);
		if (atlas == nullptr)
			return nullptr;

		AtlasAttachmentLoader atlasAttachmentLoader = AtlasAttachmentLoader(*atlas);
		SkeletonJson skeletonJson = SkeletonJson(atlasAttachmentLoader);
		return GetSkeletonManager()->CreateOrGetSkeletonData(skeletonJson, jsonPath);
	}

	std::unique_ptr<AnimationState> GetAnimationState(SkeletonData* skeletonData)
	{
		ASSERT(skeletonData != nullptr);
		AnimationStateData animStateData = AnimationStateData(*skeletonData);
		auto animState = std::unique_ptr<AnimationState>(new AnimationState(animStateData));
		return std::move(animState);
	}

	void UpdateAnimationState(AnimationState* animState, float delta)
	{
		animState->update(delta);
	}

	void ApplySkeletonToAnimationState(AnimationState* animState, Skeleton* skeleton)
	{
		animState->apply(*skeleton);		
	}
};