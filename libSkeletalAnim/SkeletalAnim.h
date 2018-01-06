#pragma once
#include <spinecpp/Skeleton.h>
#include <spinecpp/SkeletonData.h>
#include <spinecpp/SkeletonJson.h>
#include <spinecpp/Atlas.h>
#include <spinecpp/AtlasAttachmentLoader.h>
#include <spinecpp/AnimationState.h>
#include <spinecpp/AnimationStateData.h>

#include <memory>

namespace SkeletalAnim
{
	typedef spine::Skeleton Skeleton;
	typedef spine::SkeletonData SkeletonData;
	typedef spine::SkeletonJson SkeletonJson;
	typedef spine::Atlas Atlas;
	typedef spine::AtlasAttachmentLoader AtlasAttachmentLoader;
	typedef spine::AnimationState AnimationState;
	typedef spine::AnimationStateData AnimationStateData;

	Atlas* CreateAtlasFromFile(const std::string& atlasPath);

	std::shared_ptr<SkeletonData> GetSkeletonData(const std::string& atlasPathconst, const std::string& jsonPath);
	std::unique_ptr<AnimationState> GetAnimationState(SkeletonData* skeletonData);

	void UpdateAnimationState(AnimationState* animState, float delta);
	void ApplySkeletonToAnimationState(AnimationState* animState, Skeleton* skeleton);
};