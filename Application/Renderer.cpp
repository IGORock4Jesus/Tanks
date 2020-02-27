#include "Renderer.h"
#include <exception>
#include "Window.h"
#include <d3dx9.h>
#include <Mathematics/Vector3.h>

struct Vertex
{
	Vector3 position;
	Vector2 texel;
};

class RendererImpl {
	LPDIRECT3D9 direct;
	LPDIRECT3DDEVICE9 device;

public:
	RendererImpl(Window* window)
	{
		if (!(direct = Direct3DCreate9(D3D_SDK_VERSION)))
			throw std::exception("Direct3DCreate9() - failed");

		D3DPRESENT_PARAMETERS pp{ 0 };
		pp.Windowed = true;

		HWND hwnd = window->GetHandle();
		RECT cr;
		::GetClientRect(hwnd, &cr);

		pp.BackBufferWidth = cr.right - cr.left;
		pp.BackBufferHeight = cr.bottom - cr.top;
		pp.BackBufferFormat = D3DFMT_A8R8G8B8;
		pp.AutoDepthStencilFormat = D3DFMT_D24S8;
		pp.EnableAutoDepthStencil = TRUE;
		pp.hDeviceWindow = hwnd;
		pp.SwapEffect = D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;

		if (FAILED(direct->CreateDevice(0, D3DDEVTYPE::D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &pp, &device)))
			throw std::exception("IDirect3D9::CreateDevice() - failed");

		device->SetRenderState(D3DRS_LIGHTING, FALSE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA);
	}

	~RendererImpl()
	{
		device->Release();
		direct->Release();
	}

	void BeginScene()
	{
		device->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff000000, 1.0f, 0);
		device->BeginScene();
	}

	void EndScene() {
		device->EndScene();
		device->Present(nullptr, nullptr, nullptr, nullptr);
	}

	void DrawSprite(const RectF& rect, float depth, const RectF& texCoords)
	{
		Vertex vertices[]{
			   { { rect.TopLeft(), depth}, rect.TopLeft() },
			   { { rect.TopRight(), depth}, rect.TopRight() },
			   { { rect.BottomRight(), depth}, rect.BottomRight() },
			   { { rect.BottomLeft(), depth}, rect.BottomLeft() },
		};
		device->DrawPrimitiveUP(D3DPRIMITIVETYPE::D3DPT_TRIANGLEFAN, 2, vertices, sizeof(Vertex));
	}

	void SetTexture(LPDIRECT3DTEXTURE9 texture)
	{
		//device->SetTexture(0, texture.Get());
	}

	LPDIRECT3DDEVICE9 GetDevice() { return device; }
};

Renderer::Renderer(Window* window)
{
	impl = new RendererImpl(window);
}

Renderer::~Renderer()
{
	delete impl;
}

void Renderer::Update()
{
	impl->BeginScene();

	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view,
		&D3DXVECTOR3{ width / 2.0f, height / 2.0f, 1000.0f },
		&D3DXVECTOR3{ width / 2.0f, height / 2.0f, 0.0f },
		&D3DXVECTOR3{ 0.0f, -1.0f, 0.0f }
	);

	auto device = impl->GetDevice();

	device->SetTransform(D3DTS_VIEW, &view);

	D3DXMATRIX proj;
	D3DXMatrixOrthoLH(&proj, width, height, 1.0f, 10000.0f);
	device->SetTransform(D3DTS_PROJECTION, &proj);

	device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	Rendering(this);

	impl->EndScene();
}

void Renderer::DrawSprite(const RectF& rect, float depth, const RectF& texCoords)
{
	impl->DrawSprite(rect, depth, texCoords);
}