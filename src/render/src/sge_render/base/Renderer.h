#pragma once

#include <sge_render/DirectX11/DirectX11.h>
#include <sge_render/OpenGL/OpenGL.h>
//#include <sge_core/native_ui/NativeUI.h>

class Renderer {
public:
	DirectX11Render directXrender;
	OpenGLRender openGLrender;
	
	void create(sge::NativeUIWindow& win) {
		directXrender.create(win); 
		openGLrender.create(win);
	}

	void RenderFrame() { 
		switch (currentRender)
		{
		case 0:openGLrender.RenderFrame(); break;
		case 1:directXrender.RenderFrame(); break;
		default:
			break;
		}
		
	}
	void setCurrentRender(int i) { currentRender = i; }

private:
	int currentRender = 0;
};