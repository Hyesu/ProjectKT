#pragma once
#include "defines.h"
#include "SkeletalAnimActor.h"

class Actor 
{
public:
	Actor() = delete;
	Actor(const SCALE& scale);
	virtual ~Actor();

	void Init();
	void InitSkeletalAnim(const std::string& atlasPath, const std::string& jsonPath);

	void Draw();

private:
	void BuildVertices();
	void BuildIndices();

	POINT2D m_pos;
	SCALE m_scale;
	VERTEX_VEC m_vertices;
	INDEX_VEC m_indices;

	IDirect3DTexture9* m_texture = nullptr;

	std::unique_ptr<SkeletalAnimActor> m_skeletalAnimActor = nullptr;
};
