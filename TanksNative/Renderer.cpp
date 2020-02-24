#include "Renderer.h"
#include "Window.h"

#include <d3dx9.h>
#include <thread>
#include "Math.h"
#include "Scene.h"


namespace Renderer
{
struct Vertex
{
	Vector3 position;
	Vector2 texel;
};

LPDIRECT3D9 direct;
LPDIRECT3DDEVICE9 device;
std::thread thread;
bool enabled;
float width, height;


Vector2 GetSize() {
	return { width, height };
}

void StartRendering() {
	while (enabled)
	{
		device->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff000000, 1.0f, 0);
		device->BeginScene();

		D3DXMATRIX view;
		D3DXMatrixLookAtLH(&view,
			&D3DXVECTOR3{ width / 2, height / 2, 1000.0f },
			&D3DXVECTOR3{ width / 2, height / 2, 0.0f },
			&D3DXVECTOR3{ 0.0f, -1.0f, 0.0f }
		);
		device->SetTransform(D3DTS_VIEW, &view);

		D3DXMATRIX proj;
		D3DXMatrixOrthoLH(&proj, width, height, 1.0f, 10000.0f);
		device->SetTransform(D3DTS_PROJECTION, &proj);

		device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

		Scene::Render();

		device->EndScene();
		device->Present(nullptr, nullptr, nullptr, nullptr);

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

bool Initialize() {
	if (!(direct = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	D3DPRESENT_PARAMETERS pp{ 0 };
	pp.Windowed = true;

	HWND hwnd = Window::GetHandle();
	RECT cr;
	::GetClientRect(hwnd, &cr);

	pp.BackBufferWidth = width = cr.right - cr.left;
	pp.BackBufferHeight = height = cr.bottom - cr.top;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	pp.EnableAutoDepthStencil = TRUE;
	pp.hDeviceWindow = hwnd;
	pp.SwapEffect = D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;

	if (FAILED(direct->CreateDevice(0, D3DDEVTYPE::D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &pp, &device)))
		return false;

	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA);

	enabled = true;
	thread = std::thread(StartRendering);

	return true;
}
void Release() {
	enabled = false;
	if (thread.joinable())
		thread.join();
}
LPDIRECT3DDEVICE9 GetDevice()
{
	return device;
}

void DrawSprite(const Vector2& position, float depth, const Vector2& size, const RectF& rect) {
	Vertex vertices[]{
		{ {position, depth}, rect.TopLeft() },
		{ {position.x + size.x, position.y, depth}, rect.TopRight() },
		{ {position.x + size.x, position.y + size.y, depth}, rect.BottomRight() },
		{ {position.x, position.y + size.y, depth}, rect.BottomLeft() },
	};
	device->DrawPrimitiveUP(D3DPRIMITIVETYPE::D3DPT_TRIANGLEFAN, 2, vertices, sizeof(Vertex));
}

void SetTexture(Microsoft::WRL::ComPtr<IDirect3DTexture9> texture)
{
	device->SetTexture(0, texture.Get());
}

}

