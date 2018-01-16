#pragma once
#include <vector>
#include <d3d9.h>

// macro
#define SAFE_DELETE(x) { \
	if(x != nullptr) { \
		delete x; \
		x = nullptr; \
	} \
}

#define DECL_SINGLETONE(x)	\
public: \
	static x* GetInstance(); \
	static void DestroyInstance(); \
private: \
	x() {} \
	~x() {} \
	static x* m_instance;

#define IMPL_SINGLETONE(x) \
x* x::m_instance = nullptr; \
x* x::GetInstance() { \
	if(m_instance == nullptr) \
		m_instance = new x(); \
	return m_instance; \
} \
void x::DestroyInstance() { \
	SAFE_DELETE(m_instance); \
}

// constant
const DWORD GLOBAL_FVF = D3DFVF_XYZ | D3DFVF_TEX1; // for color: D3DFVF_DIFFUSE
static const float Z_VALUE = 1.0f;

// struct
struct POINT2D 
{
	float x;
	float y;

	POINT2D() : x(0.0f), y(0.0f) {}
	POINT2D(float _x, float _y) : x(_x), y(_y) {}
};

struct Vertex 
{
	Vertex() {}
	Vertex(float x, float y)
		: _x(x), _y(y) {}
	Vertex(float x, float y, float u, float v)
		: _x(x), _y(y), _u(u), _v(v) {}
	/*Vertex(float x, float y, float z = 0.0f, D3DCOLOR color = D3DCOLOR_XRGB(0, 0, 255))
	: _x(x), _y(y), _z(z), _color(color) {}*/

	float _x = 0.0f, _y = 0.0f;
	float _z = 0.0f;
	float _u = 0.0f, _v = 0.0f;
	//D3DCOLOR _color = 0; // 32bit color:ARGB
};

struct SCALE 
{
	unsigned int width;
	unsigned int height;

	SCALE() : width(100), height(100) {}
	SCALE(unsigned int w, unsigned int h) : width(w), height(h) {}
};

// type def
typedef std::vector<Vertex> VERTEX_VEC;
typedef std::vector<WORD> INDEX_VEC;