#include "stdafx.h"
#include "renderer.h"
#include "Actor.h"

void Actor::BuildVertices() {
	static const int NUM_VERTICES = 4;
	m_vertices.clear();
	m_vertices.reserve(NUM_VERTICES);

	m_vertices.emplace_back(m_pos.x, m_pos.y + m_scale.height, 0.0f, 0.0f);
	m_vertices.emplace_back(m_pos.x + m_scale.width, m_pos.y + m_scale.height, 1.0f, 0.0f);
	m_vertices.emplace_back(m_pos.x, m_pos.y, 0.0f, 1.0f);
	m_vertices.emplace_back(m_pos.x + m_scale.width, m_pos.y, 1.0f, 1.0f);
}

void Actor::BuildIndices() {
	static const int NUM_INDICES = 6;
	m_indices.clear();
	m_indices.reserve(NUM_INDICES);

	m_indices.emplace_back(0);
	m_indices.emplace_back(1);
	m_indices.emplace_back(2);

	m_indices.emplace_back(2);
	m_indices.emplace_back(1);
	m_indices.emplace_back(3);
}

void Actor::Draw() {
	GetRenderer()->SetTexture(0, m_texture);

	BuildVertices();
	if (GetRenderer()->SetVertexBuffer(m_vertices) == false)
		return;
	
	BuildIndices();
	if (GetRenderer()->SetIndexBuffer(m_indices) == false)
		return;

	GetRenderer()->SetWolrdTransform(m_pos);
	GetRenderer()->DrawPrimitives((int) m_vertices.size(), (int)m_indices.size());
}

void Actor::Init() {
	GetRenderer()->LoadTexture(m_texture, L"../data/image/example_01.jpg");
}

Actor::Actor(const SCALE& scale)
	: m_scale(scale) {
	Init();
}

Actor::~Actor() {
	if (m_texture != nullptr) {
		m_texture->Release();
	}
}