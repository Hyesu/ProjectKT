#pragma once
#include "defines.h"

class Actor {
public:
	Actor() = delete;
	Actor(const SCALE& scale);
	virtual ~Actor();

	void Init();
	void Draw();

private:
	void BuildVertices();
	void BuildIndices();

	POINT2D m_pos;
	SCALE m_scale;
	VERTEX_VEC m_vertices;
	INDEX_VEC m_indices;

	LPDIRECT3DTEXTURE9 m_texture = nullptr;
};
