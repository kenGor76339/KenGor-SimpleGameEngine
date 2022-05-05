#pragma once

#include <sge_render/DirectX11/DirectX11.h>
#include <sge_render/OpenGL/OpenGL.h>
#include <sge_render/base/RenderCmd.h>
#include <EASTL/string.h>

class Renderer {
public:
	DirectX11Render directXrender;
	//OpenGLRender openGLrender;
	
	void create(sge::NativeUIWindow& win) {
		directXrender.create(win); 
		//openGLrender.create(win);
	}

	void RenderFrame() { 
		
		RenderCmd_Draw cmd;
		cmd.primitivetype = renderMesh.getPrimitiveType();
		cmd.mesh = &renderMesh;
		cmd.vertexbuffer = renderMesh.getVertexBuffer();
		cmd.shader = &shader;
		cmd.vertexCount = renderMesh.getVertexCount();
		createLayoutDesc(cmd);
		
		switch (currentRenderTarget)
		{
			//case 0:openGLrender.RenderFrame(); break;
			case 1:directXrender.draw(cmd); break;
			default:
				break;
		}
		
	}
	void setCurrentRender(int i) { currentRenderTarget = i; }
	void createMesh(int mesh) {

		switch(mesh){
			case 0:
			{
				Mesh mesh;
				mesh.pos.emplace_back(tuple3f{ 0.0f, 0.5f, 0.0f });
				mesh.pos.emplace_back(tuple3f{ 0.45f, -0.5, 0.0f });
				mesh.pos.emplace_back(tuple3f{ -0.45f, -0.5f, 0.0f });

				mesh.color.emplace_back(Color4b{ 1, 0, 0, 1 });
				mesh.color.emplace_back(Color4b{ 0, 1, 0, 1 });
				mesh.color.emplace_back(Color4b{ 0, 0, 1, 1 });

				renderMesh.create(mesh);
				renderMesh.setPrimitiveType(PrimitiveType::triangles);
				renderMesh.setVertexCount(3);
				break;
			}
			case 1: {
				Mesh mesh;
				mesh.pos.emplace_back(tuple3f{ -0.5f , 0.5f , 0.0f });
				mesh.pos.emplace_back(tuple3f{  0.5f , -0.5  , 0.0f });
				mesh.pos.emplace_back(tuple3f{  0.5f ,  0.5f , 0.0f });
				mesh.pos.emplace_back(tuple3f{ -0.5f , -0.5f , 0.0f });

				mesh.color.emplace_back(Color4b{ 1, 0, 0, 1 });
				mesh.color.emplace_back(Color4b{ 0, 0, 1, 1 });
				mesh.color.emplace_back(Color4b{ 0, 1, 0, 1 });
				mesh.color.emplace_back(Color4b{ 1, 0, 1, 1 });

				renderMesh.create(mesh);
				renderMesh.setPrimitiveType(PrimitiveType::square);
				renderMesh.setVertexCount(4);
				break;
			}
			default:
				break;
		}

	}

	void createLayoutDesc(RenderCmd_Draw& cmd) {
		cmd.layout = new VertexLayoutDesc();
		cmd.layout->element = 
		{
			{VertexSemantic::POS, 0, RenderDataType::float3, 0, 0, InputClassFication::INPUT_PER_VERTEX_DATA, 0},
			{VertexSemantic::Color, 0, RenderDataType::float4, 0, 12, InputClassFication::INPUT_PER_VERTEX_DATA, 0},
		};
	}
private:
	int currentRenderTarget = 0;

	RenderMesh renderMesh;
	Shader shader;
};