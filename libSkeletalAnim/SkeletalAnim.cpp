#include "SkeletalAnim.h"
#include "AtlasManager.h"
#include "SkeletonManager.h"
#include "Logger.h"
#include <fstream>

namespace spine
{
	void AtlasPage_disposeTexture(spine::Atlas::Page& page)
	{
		IDirect3DTexture9* texture = (IDirect3DTexture9*)page.rendererObject;
		texture->Release();
		page.rendererObject = nullptr;
	}

	void AtlasPage_createTexture(spine::Atlas::Page& page, const char* path)
	{
		IDirect3DTexture9* texture = nullptr;
		GetRenderer()->LoadTexture(&texture, path);
		page.rendererObject = texture;
	}

	std::string Util_readFile(const std::string& path)
	{
		return std::string(std::istreambuf_iterator<char>(std::ifstream(path)), std::istreambuf_iterator<char>());
	}
}

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

		AtlasAttachmentLoader* atlasAttachmentLoader = GetAtlasManager()->CreateOrGetAtlasAttachmentLoader(atlasPath, atlas);
		if (atlasAttachmentLoader == nullptr)
			return nullptr;

		SkeletonJson skeletonJson = SkeletonJson(*atlasAttachmentLoader);
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

	void UpdateSkeleton(Skeleton* skeleton, float delta)
	{
		skeleton->update(delta);
	}

	void UpdateWorldTransform(Skeleton* skeleton)
	{
		skeleton->updateWorldTransform();
	}

	size_t GetSlotSize(Skeleton* skeleton)
	{
		return skeleton->slots.size();
	}

	Slot* GetSlotByDrawOrder(Skeleton* skeleton, size_t index)
	{
		if (index < GetSlotSize(skeleton))
			return skeleton->drawOrder[index];

		return nullptr;
	}

	AttachmentType GetAttachmentType(Slot* slot)
	{
		auto attachment = slot->getAttachment();
		if (attachment->type == Attachment::Type::Region)
			return AttachmentType::REGION;
		else if (attachment->type == Attachment::Type::Mesh)
			return AttachmentType::MESH;

		return AttachmentType::NOT_SUPPORT;
	}

	void ComputeWorldVertices_Region(Slot* slot, VERTEX_VEC& vertices, INDEX_VEC& indices, LPDIRECT3DTEXTURE9& texture)
	{
		const RegionAttachment* attachment = (const RegionAttachment*)slot->getAttachment();

		// get vertex
		static const int NUM_REGION_VERTEX = 8;
		float tempVertices[NUM_REGION_VERTEX];
		attachment->computeWorldVertices(slot->bone, tempVertices);

		for (int i = 0; i < 4; ++i)
		{
			float x = tempVertices[i * 2];
			float y = tempVertices[i * 2 + 1];
			vertices.emplace_back(x, y);

			vertices[i]._u = attachment->uvs[i].x;
			vertices[i]._v = attachment->uvs[i].y;
		}
		
		// get index
		indices.reserve(6);
		indices = {0, 1, 2, 2, 3, 0};

		// get texture
		auto region = (Atlas::Region*)attachment->rendererObject;
		texture = (LPDIRECT3DTEXTURE9)region->page.rendererObject;
	}

	void ComputeWorldVertices_Mesh(Slot* slot, VERTEX_VEC& vertices, INDEX_VEC& indices, LPDIRECT3DTEXTURE9& texture)
	{
		const MeshAttachment* attachment = (const MeshAttachment*)slot->getAttachment();

		// get vertex
		float tempVertices[1024];
		attachment->computeWorldVertices(*slot, tempVertices);		
		int worldVerticesCount = attachment->worldVerticesCount;
		for (int i = 0; i < worldVerticesCount; i += 2)
			vertices.emplace_back(tempVertices[i], tempVertices[i + 1], attachment->uvs[i / 2].x, attachment->uvs[i / 2].y);

		// get index
		indices.assign(attachment->triangles.begin(), attachment->triangles.end());		

		// get texture
		auto region = (Atlas::Region*)attachment->rendererObject;
		texture = (LPDIRECT3DTEXTURE9)region->page.rendererObject;
	}
};