#pragma once

#include <sge_core/native_ui/NativeUI.h>
#include <sge_render/base/RenderCmd.h>


class RenderBase {

public:
	RenderBase() {
		_renderMethod = this;
	}
	virtual ~RenderBase() {
		_renderMethod = nullptr;
	}
	void create(sge::NativeUIWindow& win) { onCreate(win);}
	virtual void onCreate(sge::NativeUIWindow& win) {}
	void RenderFrame() { onRenderFrame();}
	virtual void onRenderFrame() {}

	void draw(RenderCmd_Draw& cmd) { onDraw(cmd); }
	virtual void onDraw(RenderCmd_Draw& cmd){}

	int canvasWidth() const { return m_canvasWidth; }
	int canvasHeight() const { return m_canvasHeight; }


protected:
	HWND	m_hwnd = nullptr;
	HDC		m_dc = nullptr;
	HGLRC	m_rc = nullptr;

	int m_canvasWidth = 100;
	int m_canvasHeight = 100;

	static RenderBase* _renderMethod;
};
