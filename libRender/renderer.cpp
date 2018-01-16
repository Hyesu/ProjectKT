#include "renderer.h"
#include "ActorManager.h"
#include "Logger.h"

IMPL_SINGLETONE(Renderer);

HRESULT Renderer::InitD3D(HWND hWnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if (nullptr == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Constants
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 900;

	// Set up the structure used to create the D3DDevice.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


	// check device capability for hardware vertex processing
	D3DCAPS9 caps;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int nVertexProcessingType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	// Create the Direct3D device.
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		nVertexProcessingType,
		&d3dpp, &m_d3dDevice))) 
	{
		return E_FAIL;
	}
	
	m_window = hWnd;

	// init viewspace
	D3DXVECTOR3 targetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMATRIX viewMatrix;
	D3DXVECTOR3 vCameraPosition = D3DXVECTOR3(0.0f, 0.0f, -15.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &vCameraPosition, &targetPosition, &upVector);
	m_d3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
		
	// set projection
	D3DXMATRIX projectionMatrix;

	// perspective
	/*D3DXMatrixPerspectiveFovLH(&projectionMatrix,
		D3DX_PI * 0.25f,
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		1000.0f);*/

	// orthogonal
	D3DXMatrixOrthoLH(&projectionMatrix, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT, 1.0f, 1000.0f);	
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	// set render state
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	
	return S_OK;
}

void Renderer::Cleanup()
{
	if (m_d3dDevice != nullptr)
		m_d3dDevice->Release();

	if (m_pD3D != nullptr)
		m_pD3D->Release();

	if (m_vertexBuffer != nullptr)
		m_vertexBuffer->Release();

	if (m_indexBuffer != nullptr)
		m_indexBuffer->Release();
}

void Renderer::Draw(VERTEX_VEC& vertexVec, INDEX_VEC& indexVec, IDirect3DTexture9* texture)
{	
	SetTexture(0, texture);

	if (SetVertexBuffer(vertexVec) == false)
		return;

	if (SetIndexBuffer(indexVec) == false)
		return;

	DrawPrimitives((int)vertexVec.size(), (int)indexVec.size());
}

void Renderer::Render()
{
	if (nullptr == m_d3dDevice)
		return;
		
	static const D3DCOLOR BACKGOUND_COLOR = D3DCOLOR_XRGB(255, 255, 255);
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BACKGOUND_COLOR, 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(m_d3dDevice->BeginScene())) 
	{	
		m_d3dDevice->SetFVF(GLOBAL_FVF);
		
		GetActorManager()->Draw();

		// End the scene
		m_d3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	m_d3dDevice->Present(NULL, NULL, NULL, NULL);

	ValidateRect(m_window, nullptr);
}

bool Renderer::SetVertexBuffer(const VERTEX_VEC& v)
{
	if (m_vertexBuffer == nullptr || m_vertexBufferSize < v.size())
	{
		if (m_vertexBuffer != nullptr)
			m_vertexBuffer->Release();

		if (FAILED(m_d3dDevice->CreateVertexBuffer(
			(UINT)v.size() * sizeof(Vertex),
			D3DUSAGE_WRITEONLY,
			D3DFVF_XYZ | D3DFVF_DIFFUSE,
			D3DPOOL_MANAGED,
			&m_vertexBuffer,
			0)))
			return false;
		
		m_vertexBufferSize = v.size();
	}
	
	// set vertex buffer
	Vertex* vertices = nullptr;
	UINT size = (UINT)v.size() * sizeof(Vertex);
	m_vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	memcpy_s(vertices, size, &v[0], size);


	/*int i = 0;
	for (auto& it : v)
		vertices[i++] = Vertex(it.x, it.y);
*/
	m_vertexBuffer->Unlock();
	m_d3dDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Vertex));

	return true;
}

bool Renderer::SetIndexBuffer(const INDEX_VEC& v) 
{
	if (m_indexBuffer == nullptr || m_indexBufferSize < v.size()) 
	{
		if (m_indexBuffer != nullptr)
			m_indexBuffer->Release();

		if (FAILED(m_d3dDevice->CreateIndexBuffer(
			(UINT)v.size() * sizeof(WORD),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&m_indexBuffer,
			0)))
			return false;
		
		m_indexBufferSize = v.size();
	}
	
	// Set indices
	WORD* pIndices = nullptr;
	UINT size = (UINT)v.size() * sizeof(WORD);
	m_indexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	memcpy_s(pIndices, size, &v[0], size);

	/*int i = 0;
	for (auto& it : v)
		pIndices[i++] = it;
*/
	m_indexBuffer->Unlock();

	m_d3dDevice->SetIndices(m_indexBuffer);
	return true;
}

void Renderer::SetWolrdTransform(const POINT2D& p)
{
	D3DXMATRIX worldMatrix;
	D3DXVECTOR3 position(p.x, p.y, Z_VALUE);
	D3DXMatrixTranslation(&worldMatrix, position.x, position.y, position.z);
	m_d3dDevice->SetTransform(D3DTS_WORLD, &worldMatrix);	
}

void Renderer::DrawPrimitives(const int numVertices, const int numIndices)
{
	m_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numIndices / 3);
}

Renderer* GetRenderer()
{
	return Renderer::GetInstance();
}

void Renderer::LoadTexture(IDirect3DTexture9** texture, const char* filePath)
{	
	D3DXCreateTextureFromFileA(m_d3dDevice, filePath, texture);
}

IDirect3DTexture9* Renderer::LoadTexture(const char* filePath)
{
	IDirect3DTexture9* texture;
	D3DXCreateTextureFromFileA(m_d3dDevice, filePath, &texture);
	return texture;
}

void Renderer::SetTexture(DWORD stage, IDirect3DTexture9* texture)
{
	m_d3dDevice->SetTexture(0, texture);
}