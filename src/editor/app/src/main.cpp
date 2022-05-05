#include <sge_editor.h>

namespace sge {

class MainWin : public NativeUIWindow {
public:
	virtual void onCloseButton() override {
		NativeUIApp::current()->quit(0);
	}
};

class EditorApp : public NativeUIApp {
	using Base = NativeUIApp;
public:
	virtual void onCreate(CreateDesc& desc) override {
		Base::onCreate(desc);

		NativeUIWindow::CreateDesc winDesc;
		winDesc.isMainWindow = true;
		_mainWin.create(winDesc);
		_mainWin.setWindowTitle("SGE Editor");

		_renderer.create(_mainWin);
		PostQuitMessage(0);
	}

	void RenderFrame() { _renderer.RenderFrame(); }
	void setCurrentRender(int i) { _renderer.setCurrentRender(i); }
	void createMesh(int mesh) { _renderer.createMesh(mesh); }
private:
	MainWin		_mainWin;
	Renderer	_renderer;
};

}


int main() {
	sge::EditorApp app;
	sge::EditorApp::CreateDesc desc;
	app.run(desc);

	MSG msg;

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);
			// send the message to the WindowProc function
			DispatchMessage(&msg);
			// check to see if it's time to quit
			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			// Run game code here
			int renderMethod;
			int meshName;
			printf("Your Render Method: ");
			scanf("%i",&renderMethod);
			app.setCurrentRender(renderMethod);
			printf("Your Render mesh: ");
			scanf("%i", &meshName);
			app.createMesh(meshName);
			app.RenderFrame();
			printf("\n");
		}
	}

	return msg.wParam;
}
