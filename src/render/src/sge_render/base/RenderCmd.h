#pragma once

#include <sge_render/base/Shader.h>

using namespace eastl;
using namespace sge;

class VertexBuffer;

struct RenderCmdBase {
	enum class CmdTypes {
		None,
		Draw,
		SetViewport,
		Clear
	};
public:
	CmdTypes type;
};

enum class VertexSemantic {
	POS,
	UV0,
	UV1,
	UV2,
	Color
};

enum class RenderDataType {
	float1,
	float2,
	float3,
	float4,
	int1,
	int2,
	int3,
	int4
};

enum class InputClassFication {
	INPUT_PER_VERTEX_DATA = 0,
	INPUT_PER_INSTANCE_DATA = 1
};

struct VertexLayoutDesc {

	struct Element {
		VertexSemantic semantic;
		int SemanticIndex;
		RenderDataType datatype;
		int inputslot;
		int AlignedByteOffset;
		InputClassFication InputSlotClass;
		int InstanceDataStepRate;
	};
	
	vector<Element> element;
};

struct Color4b {
	u8 r, g, b, a;
};

template <class T>
struct tuple3
{
	T x, y, z;
};

using tuple3f = tuple3<float>;
using tuple3d = tuple3<double>;

struct Vertex_PosColor {
	tuple3f pos;
	Color4b color;

	static VertexLayoutDesc* layout;
};

enum class PrimitiveType {
	None = 0,
	triangles = 4,
	square = 1,
	circle = 3,
	line = 2,
};

class Mesh {
public:
	static const int kMaxUv = 8;

	vector<tuple3f> pos;
	vector<tuple3f> uv[kMaxUv];
	vector<Color4b> color;

};
class RenderMesh {
public:

	void create(const Mesh& mesh);
	size_t getVertexCount() { return vertexCount; }
	void setVertexCount(size_t count) { vertexCount = count; }
	PrimitiveType getPrimitiveType() { return primitivetype; }
	void setPrimitiveType(PrimitiveType type) { primitivetype = type; }
	VertexBuffer* getVertexBuffer() { return vertexBuffer.get(); }
private:
	PrimitiveType primitivetype = PrimitiveType::None;
	shared_ptr<class VertexBuffer> vertexBuffer;
	shared_ptr<class IndexBuffer> indexBuffer;
	size_t vertexCount = 0;
};

class RenderCmd_Draw : public RenderCmdBase {
public:
	PrimitiveType primitivetype = PrimitiveType::None;

	VertexLayoutDesc* layout = nullptr;

	class VertexBuffer* vertexbuffer = nullptr;
	class IndexBuffer* indexbuffer = nullptr;

	Shader* shader = nullptr;
	RenderMesh* mesh = nullptr;
	size_t vertexCount = 0;
	int stride = 0;
};

