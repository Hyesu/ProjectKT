#include "SkeletalAnimActor.h"
#include "Logger.h"
#include "defines.h"

SkeletalAnimActor::SkeletalAnimActor(const std::string& atlasPath, const std::string& jsonPath)
{
	m_skeletonData = SkeletalAnim::GetSkeletonData(atlasPath, jsonPath);
	m_skeleton = std::make_unique<SkeletalAnim::Skeleton>(*m_skeletonData);

	PlayAnimation("flying");
}

SkeletalAnimActor::~SkeletalAnimActor()
{
}

void SkeletalAnimActor::Update(float delta)
{
	SkeletalAnim::UpdateSkeleton(m_skeleton.get(), delta);
	SkeletalAnim::ApplyAnimation(m_animation, m_skeleton.get(), m_totalAniTime, delta, true);
	SkeletalAnim::UpdateAnimationState(m_animState.get(), delta);
	SkeletalAnim::ApplySkeletonToAnimationState(m_animState.get(), m_skeleton.get());
	SkeletalAnim::UpdateWorldTransform(m_skeleton.get());
	
	m_totalAniTime += delta;
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
	sprintf_s(temp, "%s: skelData[%p], skeleton[%p], animState[%p]", typeid(this).name(), m_skeletonData.get(), m_skeleton.get(), m_animState.get());
	return temp;
}

void SkeletalAnimActor::Render()
{
	if (m_skeleton == nullptr)
		return;

	size_t slotSize = m_skeleton->slots.size();
	for (size_t i = 0; i < slotSize; ++i)
	{
		SkeletalAnim::Slot* slot = SkeletalAnim::GetSlotByDrawOrder(m_skeleton.get(), i);
		ASSERT(slot != nullptr);

		VERTEX_VEC vertexVec;
		INDEX_VEC indexVec;
		IDirect3DTexture9* texture = nullptr;
		switch (SkeletalAnim::GetAttachmentType(slot))
		{
		case SkeletalAnim::AttachmentType::REGION:
			SkeletalAnim::ComputeWorldVertices_Region(slot, vertexVec, indexVec, texture);
			break;
		case SkeletalAnim::AttachmentType::MESH:
			SkeletalAnim::ComputeWorldVertices_Mesh(slot, vertexVec, indexVec, texture);
			break;
		default:
			Log("--- Not Supported Attachment Type[%d]\n", SkeletalAnim::GetAttachmentType(slot));
			break;
		}
		GetRenderer()->Draw(vertexVec, indexVec, texture);
	}
}

void SkeletalAnimActor::PlayAnimation(const std::string& animName)
{
	m_animState.reset();
	m_animState = std::move(SkeletalAnim::GetAnimationState(m_skeletonData.get()));
	m_totalAniTime = 0.0f;
	m_animation = const_cast<SkeletalAnim::Animation*>(SkeletalAnim::FindAnimation(m_skeletonData.get(), animName));
}