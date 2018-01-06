#include "SkeletalAnimActor.h"

SkeletalAnimActor::SkeletalAnimActor(const std::string& atlasPath, const std::string& jsonPath)
{
	m_skeletonData = SkeletalAnim::GetSkeletonData(atlasPath, jsonPath);
	m_skeleton = std::make_unique<SkeletalAnim::Skeleton>(*m_skeletonData);
	m_animState = std::move(SkeletalAnim::GetAnimationState(m_skeletonData.get()));
}

SkeletalAnimActor::~SkeletalAnimActor()
{
}

void SkeletalAnimActor::Update(float delta)
{
	SkeletalAnim::UpdateAnimationState(m_animState.get(), delta);
	SkeletalAnim::ApplySkeletonToAnimationState(m_animState.get(), m_skeleton.get());
}

bool SkeletalAnimActor::IsValid() const
{
	if (m_skeletonData == nullptr
		|| m_skeleton == nullptr
		|| m_animState == nullptr)
		return false;

	return true;
}

const std::string SkeletalAnimActor::ToString()
{
	char temp[1024];
	sprintf_s(temp, "%s: skelData[%p], skeleton[%p], animState[%p]", typeid(this).name(), m_skeletonData, m_skeleton, m_animState);
	return temp;
}