#pragma once
#include <sge_render/DirectX11/DirectX11.h>
#include <wrl.h>

class DirectX11adapter {
public:
	static D3D_PRIMITIVE_TOPOLOGY getD3DPrimitive(PrimitiveType type) {
		switch (type)
		{
		case PrimitiveType::triangles:return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case PrimitiveType::line:return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		case PrimitiveType::square:return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;
		default:
			return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
			break;
		}
	}


	static vector<D3D11_INPUT_ELEMENT_DESC> getD3DDesc(VertexLayoutDesc* desc) {

		vector<D3D11_INPUT_ELEMENT_DESC> inputLayout(desc->element.size());
		for (int i = 0; i < desc->element.size(); ++i) {
			auto& e = desc->element[i];
			auto& element = inputLayout[i];
			element.SemanticName = getSemanticName(e.semantic);
			element.SemanticIndex = e.SemanticIndex;
			element.Format = getFormat(e.datatype);
			element.InputSlot = e.inputslot;
			element.AlignedByteOffset = e.AlignedByteOffset;
			element.InputSlotClass = getInputClass(e.InputSlotClass);
			element.InstanceDataStepRate = e.InstanceDataStepRate;
		}

		return inputLayout;
	}

private:
	static LPCSTR getSemanticName(VertexSemantic semantic) {
		switch (semantic)
		{
		case VertexSemantic::POS:return "POSITION";
			break;
		case VertexSemantic::Color:return "COLOR";
			break;
		default:
			abort();
			break;
		}
	}

	static DXGI_FORMAT getFormat(RenderDataType dataType) {
		switch (dataType)
		{
		case RenderDataType::float3:return DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case RenderDataType::float4:return DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		default:
			abort();
			break;
		}
	}

	static D3D11_INPUT_CLASSIFICATION getInputClass(InputClassFication inputClass) {
		switch (inputClass)
		{
		case InputClassFication::INPUT_PER_VERTEX_DATA:return D3D11_INPUT_PER_VERTEX_DATA;
			break;
		case InputClassFication::INPUT_PER_INSTANCE_DATA:return D3D11_INPUT_PER_INSTANCE_DATA;
			break;
		default:
			abort();
			break;
		}
	}
};