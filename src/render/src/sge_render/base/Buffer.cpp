#pragma once
#include "Buffer.h"


VertexBuffer::VertexBuffer(BufferDesc& desc) : BufferBase(desc)
{
	printf("Create D3D11 Buffer\n");

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = desc.bufferSize;             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	auto* d3d = DirectX11Render::getRenderMethod();
	ID3D11Device* dev = d3d->getDev();
	
	ID3D11Buffer* pVBuffer = getD3DBuffer();
	pVBuffer = nullptr;
	dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer
	_d3dBuffer.reset(pVBuffer);
}

void VertexBuffer::onUploadToGPU(span<const u8> data, size_t offset)
{
	auto* d3d = DirectX11Render::getRenderMethod();
	ID3D11DeviceContext* devcon = d3d->getDevcon();

	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(getD3DBuffer(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);		// map the buffer
	memcpy(ms.pData, data.data(), data.size());									// copy the data
	devcon->Unmap(getD3DBuffer(), NULL);										// unmap the buffer
}
