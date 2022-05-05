#pragma once

#include <sge_render/base/RenderCmd.h>
#include <sge_render/base/Buffer.h>

void RenderMesh::create(const Mesh& mesh)
{
	int bSize = mesh.pos.size() * (sizeof(tuple3f) + sizeof(Color4b));
	fixed_vector<u8,1024> fv;
	fv.resize(bSize);
	u8* pData = fv.data();
	for (int i = 0, index = 0; i < mesh.pos.size(); ++i) {
		if (index > 1024) {
			printf("index of out bound");
			break;
		}
		*reinterpret_cast<tuple3f*>(pData) = mesh.pos[i];
		int stride = sizeof(tuple3f);
		pData += stride;
		index += stride;
		*reinterpret_cast<Color4b*>(pData) = mesh.color[i];
		stride = sizeof(Color4b);
		pData += stride;
		index += stride;
	}

	BufferDesc desc;
	desc.type = BufferType::Vertex;
	desc.bufferSize = bSize;
	VertexBuffer* newBuf = new VertexBuffer(desc); 
	if(vertexBuffer.get() != nullptr)delete vertexBuffer.get();
	vertexBuffer.reset(newBuf);
	vertexBuffer->uploadToGPU(fv);
}