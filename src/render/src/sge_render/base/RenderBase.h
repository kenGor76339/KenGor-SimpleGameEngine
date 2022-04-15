#pragma once

#include <sge_core/native_ui/NativeUI.h>

class RenderBase {

public:

	void create(sge::NativeUIWindow& win) { onCreate(win);}
	virtual void onCreate(sge::NativeUIWindow& win) {}
	void RenderFrame() { onRenderFrame();}
	virtual void onRenderFrame() {}

	int canvasWidth() const { return m_canvasWidth; }
	int canvasHeight() const { return m_canvasHeight; }


protected:
	HWND	m_hwnd = nullptr;
	HDC		m_dc = nullptr;
	HGLRC	m_rc = nullptr;

	int m_canvasWidth = 100;
	int m_canvasHeight = 100;
};
