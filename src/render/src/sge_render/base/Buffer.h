#pragma once
#include <sge_render/DirectX11/DirectX11.h>

enum class BufferType {
	None,
	Vertex,
	Index,
	Const
};

struct BufferDesc {
	BufferType type = BufferType::None;
	size_t bufferSize = 0;
	size_t stride = 16;
};

class BufferBase {
public:
	BufferBase(BufferDesc& desc) : _desc(desc) {}

	void uploadToGPU(span<const u8> data, size_t offset = 0) {
		if (data.size() + offset > _desc.bufferSize) {
			throw SGE_ERROR("out of range");
		}
		onUploadToGPU(data,offset);
	}
protected:
	virtual void onUploadToGPU(span<const u8> data, size_t offset = 0) = 0;
	BufferDesc _desc;
};

class VertexBuffer : public BufferBase {
public:
	VertexBuffer(BufferDesc& desc);
	void onUploadToGPU(span<const u8> data, size_t offset = 0) override;
	ID3D11Buffer* getD3DBuffer() { return _d3dBuffer.get(); }
private:
	shared_ptr<ID3D11Buffer> _d3dBuffer;
};

class IndexBuffer : public BufferBase {

};
