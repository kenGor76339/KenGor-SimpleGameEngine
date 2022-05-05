#include "OpenGL.h"
#include <sge_core.h>

void OpenGLRender::onCreate(sge::NativeUIWindow& win)
{

    if (!win._hwnd)
        printf("CreateWindow");
	

	m_dc = GetDC(win._hwnd);
	if (!m_dc)
		printf("GetDC");
	

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pf = ChoosePixelFormat(m_dc, &pfd);
	if (pf == 0)
		printf("ChoosePixelFormat");

	if (!SetPixelFormat(m_dc, pf, &pfd))
		printf("SetPixelFormat");

	m_rc = wglCreateContext(m_dc);
	if (!m_rc)
		printf("wglCreateContext");

	makeCurrent();

}

void OpenGLRender::onRenderFrame()
{
	printf("OpenGL Rendering\n");
	glViewport(0, 0, canvasWidth(), canvasHeight());

	glClearColor(0.2f, 0.5f, 0.6f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float d = 0.5f;
	glBegin(GL_QUADS);
	glColor4f(1, 0, 0, 1);	glVertex3f(-d, -d, 0);
	glColor4f(0, 0, 1, 1);	glVertex3f(d, -d, 0);
	glColor4f(0, 1, 0, 1);	glVertex3f(d, d, 0);
	glColor4f(1, 0, 1, 1);	glVertex3f(-d, d, 0);
	glEnd();

	swapBuffers();
}
