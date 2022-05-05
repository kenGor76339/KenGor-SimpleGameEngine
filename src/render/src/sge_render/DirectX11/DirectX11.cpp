#include "DirectX11.h"
#include "DirectX11adapter.h"
#include "sge_render/base/Buffer.h"

void DirectX11Render::onCreate(sge::NativeUIWindow& win)
{
	if (!win._hwnd)
		printf("CreateWindow");

	InitD3D(win._hwnd);
}


void DirectX11Render::onDraw(RenderCmd_Draw& cmd) {
	printf("DirectX onDraw!\n");

	(void)cmd;
	auto* vertexBuffer = cmd.vertexbuffer;
	devcon->IASetPrimitiveTopology(DirectX11adapter::getD3DPrimitive(cmd.primitivetype));
	InitPipeline(cmd);

	UINT stride = (UINT)cmd.stride;
	UINT offset = 0;
	ID3D11Buffer* pVBuffer = vertexBuffer->getD3DBuffer();
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

	printf("vertex count %i",cmd.vertexCount);
	devcon->Draw(cmd.vertexCount, 0);
	
	swapBuffers();
}

void DirectX11Render::InitD3D(HWND hWnd)
{
	printf("InitD3D\n");
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferDesc.Width = canvasWidth();                    // set the back buffer width
	scd.BufferDesc.Height = canvasHeight();                  // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWnd;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);

	// get the address of the back buffer
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = canvasWidth();
	viewport.Height = canvasHeight();

	devcon->RSSetViewports(1, &viewport);
}

void DirectX11Render::CleanD3D()
{
	swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

// close and release all existing COM objects
	pVS->Release();
	pPS->Release();
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}

void DirectX11Render::InitPipeline(RenderCmd_Draw cmd)
{
	printf("InitPipeline\n");
	// load and compile the two shaders
	ID3D10Blob* VS, * PS;

	HRESULT tmp = D3DCompileFromFile(L"../../../../../src/shaders/Shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &VS, 0);
	HRESULT tmp1 = D3DCompileFromFile(L"../../../../../src/shaders/Shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &PS, 0);

	// encapsulate both shaders into shader objects
	dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	// set the shader objects
	devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);

	// create the input layout object
	
	/*{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};*/
	if (cmd.layout == nullptr || cmd.layout->element.empty()) {
		printf("element is empty\n");
		return;
	}
	D3D11_INPUT_ELEMENT_DESC* ied = DirectX11adapter::getD3DDesc(cmd.layout).data();
	dev->CreateInputLayout(ied, cmd.layout->element.size(), VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	devcon->IASetInputLayout(pLayout);
}
