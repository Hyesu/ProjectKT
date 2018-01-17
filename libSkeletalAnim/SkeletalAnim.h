#pragma once
#include <spinecpp/Skeleton.h>
#include <spinecpp/SkeletonData.h>
#include <spinecpp/SkeletonJson.h>
#include <spinecpp/Atlas.h>
#include <spinecpp/AtlasAttachmentLoader.h>
#include <spinecpp/AnimationState.h>
#include <spinecpp/AnimationStateData.h>
#include <spinecpp/Animation.h>
#include <spinecpp/Slot.h>
#include <spinecpp/Attachment.h>
#include <spinecpp/RegionAttachment.h>
#include <spinecpp/MeshAttachment.h>

#include "renderer.h"
#include <memory>

// spine-cpp implement
namespace spine
{
	void AtlasPage_disposeTexture(spine::Atlas::Page& page);
	void AtlasPage_createTexture(spine::Atlas::Page& page, const char* path);
	std::string Util_readFile(const std::string& path);
}

namespace SkeletalAnim
{
	typedef spine::Skeleton Skeleton;
	typedef spine::SkeletonData SkeletonData;
	typedef spine::SkeletonJson SkeletonJson;
	typedef spine::Atlas Atlas;
	typedef spine::AtlasAttachmentLoader AtlasAttachmentLoader;
	typedef spine::AnimationState AnimationState;
	typedef spine::Animation Animation;
	typedef spine::AnimationStateData AnimationStateData;
	typedef spine::Slot Slot;
	typedef spine::Attachment Attachment;
	typedef spine::RegionAttachment RegionAttachment;
	typedef spine::MeshAttachment MeshAttachment;

	enum class AttachmentType
	{
		REGION,
		MESH,
		NOT_SUPPORT,
	};

	// atlas
	Atlas* CreateAtlasFromFile(const std::string& atlasPath);

	// skeleton
	std::shared_ptr<SkeletonData> GetSkeletonData(const std::string& atlasPathconst, const std::string& jsonPath);
	void ApplySkeletonToAnimationState(AnimationState* animState, Skeleton* skeleton);
	void UpdateSkeleton(Skeleton* skeleton, float delta);
	void UpdateWorldTransform(Skeleton* skeleton);

	// slot
	size_t GetSlotSize(Skeleton* skeleton);
	Slot* GetSlotByDrawOrder(Skeleton* skeleton, size_t index);
	AttachmentType GetAttachmentType(Slot* slot);
	void ComputeWorldVertices_Region(Slot* slot, VERTEX_VEC& vertices, INDEX_VEC& indices, LPDIRECT3DTEXTURE9& texture);
	void ComputeWorldVertices_Mesh(Slot* slot, VERTEX_VEC& vertices, INDEX_VEC& indices, LPDIRECT3DTEXTURE9& texture);

	// animation
	std::unique_ptr<AnimationState> GetAnimationState(SkeletonData* skeletonData);
	void UpdateAnimationState(AnimationState* animState, float delta);
	const Animation* FindAnimation(SkeletonData* skeletonData, const std::string& animName);
	void ApplyAnimation(Animation* anim, Skeleton* skeleton, float lastTime, float deltaTime, bool loop);
};