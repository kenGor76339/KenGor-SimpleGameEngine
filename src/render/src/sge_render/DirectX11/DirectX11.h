#pragma once

#include <sge_render/base/RenderBase.h>
#ifdef _WIN32

#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#endif

class DirectX11Render : public RenderBase {
public:
	~DirectX11Render() { destroy(); }
	void onCreate(sge::NativeUIWindow& win) override;
	void onRenderFrame() override;

	// function prototypes
	void InitD3D(HWND hWnd);     // sets up and initializes Direct3D
	void CleanD3D();         // closes Direct3D and releases memory
	void InitPipeline();
	void InitGraphics();

	void destroy() {
		if (m_rc) { CleanD3D();	m_rc = nullptr; }
		if (m_dc) { ReleaseDC(m_hwnd, m_dc);	m_dc = nullptr; }
		if (m_hwnd) { DestroyWindow(m_hwnd);	m_hwnd = nullptr; }
		PostQuitMessage(0);
	}
	void swapBuffers() {
		if (swapchain)
			swapchain->Present(0, 0);
	}


private:
	IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
	ID3D11Device* dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon;           // the pointer to our Direct3D device context
	ID3D11VertexShader* pVS = nullptr;               // the vertex shader
	ID3D11PixelShader* pPS = nullptr;                // the pixel shader
	ID3D11InputLayout* pLayout;
	struct VERTEX { FLOAT X, Y, Z; float Color[4]; };    // a struct to define a vertex
	ID3D11Buffer* pVBuffer;                            // the vertex buffer
	ID3D11RenderTargetView* backbuffer;
};