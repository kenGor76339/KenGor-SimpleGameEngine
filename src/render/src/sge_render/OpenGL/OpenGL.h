#pragma once

#include <sge_render/base/RenderBase.h>

#ifdef _WIN32
	#include <conio.h>

	#include <GL/gl.h>
	#include <GL/glu.h>
	#pragma comment(lib, "Opengl32.lib")

	#undef max
	#undef min
#endif

class OpenGLRender : public RenderBase {
public:
	~OpenGLRender() { destroy(); }
	void onCreate(sge::NativeUIWindow& win) override;
	void onRenderFrame() override;

	void makeCurrent() {
		if(m_rc)
			wglMakeCurrent(m_dc, m_rc);
	}
	void destroy() {
		if (m_rc) { wglDeleteContext(m_rc);	m_rc = nullptr; }
		if (m_dc) { ReleaseDC(m_hwnd, m_dc);	m_dc = nullptr; }
		if (m_hwnd) { DestroyWindow(m_hwnd);	m_hwnd = nullptr; }
		PostQuitMessage(0);
	}
	void swapBuffers(){
		if (m_dc)
			::SwapBuffers(m_dc);
	}


};
