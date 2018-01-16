#pragma once
#include "SkeletalAnim.h"
#include <string>
#include <memory>

class SkeletalAnimActor
{
public:
	SkeletalAnimActor() = delete;
	SkeletalAnimActor(const std::string& atlasPath, const std::string& jsonPath);
	~SkeletalAnimActor();

	void Update(float delta);
	void Render();

	bool IsValid() const;

	const std::string ToString();

private:
	std::shared_ptr<SkeletalAnim::SkeletonData> m_skeletonData;
	std::unique_ptr<SkeletalAnim::AnimationState> m_animState;
	std::unique_ptr<SkeletalAnim::Skeleton> m_skeleton;
};