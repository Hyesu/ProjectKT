#pragma once
#include "defines.h"
#include <d3dx9.h>

struct POINT2D;

class Renderer {
	DECL_SINGLETONE(Renderer);

public:
	HRESULT InitD3D(HWND hWnd);
	void Cleanup();
	void Render();

	bool SetVertexBuffer(const VERTEX_VEC& v);
	bool SetIndexBuffer(const INDEX_VEC& v);
	void SetWolrdTransform(const POINT2D& p);
	void SetTexture(DWORD stage, LPDIRECT3DTEXTURE9& texture);

	void DrawPrimitives(const int numVertices, const int numIndices);

	void LoadTexture(LPDIRECT3DTEXTURE9& texture, LPCWSTR filePath);

private:
	HWND m_window;
	LPDIRECT3D9 m_pD3D = nullptr; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9 m_d3dDevice = nullptr; // rendering device
	IDirect3DVertexBuffer9* m_vertexBuffer = nullptr;
	IDirect3DIndexBuffer9* m_indexBuffer = nullptr;

	size_t m_vertexBufferSize = 0;
	size_t m_indexBufferSize = 0;
	float m_cameraAngle = 0.0f;
};

Renderer* GetRenderer();