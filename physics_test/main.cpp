#include <boost/thread.hpp>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Box2d.lib")

#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <direct.h> // KILLME
#include <fstream>
#include <iostream>

#include <Box2D/Box2D.h>

#include <cgl/Types.h>
#include <cgl/Utils.h>
#include <cgl/FrameTimeCounter.h>

#include <r2d/ICamera.h>
#include <r2d/ITexture.h>
#include <r2d/IEffect.h>
#include <r2d/IMaterial.h>
#include <r2d/IRenderable.h>
#include <r2d/IDynamicGeometeryObject.h>
#include <r2d/IFactory.h>
#include <r2d/ContextFactory.h>
#include <r2d/IRenderContext.h>
#include <r2d/CompositeRenderable.h>

#include <p2d/DebugRenderer.h>
#include <p2d/PolygonShape.h>
#include <p2d/CircleShape.h>
#include <p2d/ChainShape.h>
#include <p2d/CompositeBody.h>
#include <p2d/SimpleBody.h>
#include <p2d/LengthJoint.h>
#include <p2d/World.h>

float get_time_callback() {
	return timeGetTime() * 0.001f;
}

// R2D
std::auto_ptr<r2d::IRenderContext> contextPtr;
std::auto_ptr<r2d::ICamera> cameraPtr;
std::auto_ptr<r2d::IFactory> factoryPtr;

std::auto_ptr<p2d::World> physicsWorld(new p2d::World(vec2(0.0f, -10.0f), true));
boost::ptr_vector<p2d::IBody> physicsBodies;
boost::ptr_vector<p2d::IJoint> physicsJoints;


class p2dDebugRenderer: public p2d::DebugRenderer {
public:
	p2dDebugRenderer() {};
	virtual ~p2dDebugRenderer() {};
	virtual void SetWorldTransform(const vec2& position, float angle) const {
		contextPtr->SetWorldTransform(position, angle);
	}
	virtual void ResetWorldTransform() const {
		contextPtr->ResetWorldTransform();
	}
	virtual void RenderPoint(const vec2& point, const ivec3& color = DEFAULT_COLOR_RGB, float pointSize = 1.0f) const {
		contextPtr->RenderPoint(point, color, pointSize);
	}
	virtual void RenderPolygonalChain(const PolygonalChain2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const {
		contextPtr->RenderPolygonalChain(p, color);
	}
	virtual void RenderLine(const vec2& point1, const vec2& point2, const ivec3& color = DEFAULT_COLOR_RGB) const {
		contextPtr->RenderLine(point1, point2, color);
	}
	virtual void RenderWireRectangle(const Rect& geometry, const ivec3& color = DEFAULT_COLOR_RGB) const {
		contextPtr->RenderWireRectangle(geometry, color);
	}
	virtual void RenderSolidRectangle(const Rect& geometry, const ivec3& color = DEFAULT_COLOR_RGB) const {
		contextPtr->RenderSolidRectangle(geometry, color);
	}
	virtual void RenderWireCircle(const Circle& c, const ivec3& color = DEFAULT_COLOR_RGB) const {
		contextPtr->RenderWireCircle(c, color);
	}
	virtual void RenderSolidCircle(const Circle& c, const ivec3& color = DEFAULT_COLOR_RGB) const {
		contextPtr->RenderSolidCircle(c, color);
	}
	virtual void RenderWirePolygon(const Polygon2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const {
		contextPtr->RenderWirePolygon(p, color);
	}
	virtual void RenderSolidPolygon(const Polygon2d& p, const ivec3& color = DEFAULT_COLOR_RGB) const {
		contextPtr->RenderSolidPolygon(p, color);
	}
	virtual void RenderWorldAxises() const {
		contextPtr->RenderWorldAxises();
	}
};

p2dDebugRenderer debugRenderer;

// The main window class name.
static TCHAR szWindowClass[] = _T("air2dgame");
// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("air2d based game");
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hWnd;

bool complete = false;
void renderScene();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Creating window
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex)) {
		return 1;
	}
	hInst = hInstance;
	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if (!hWnd) {
		return 1;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Win32 init finished

	contextPtr = r2d::CreateRenderContext(hWnd);
	contextPtr->Init();

	factoryPtr = contextPtr->GetFactory();
	cameraPtr = factoryPtr->CreateCamera(Rect(-400.0f, -300.0f, 400.0f, 300.0f));


	// Init physics
	p2d::Material material;
	p2d::BodyInitialMotion motion;

	Polygon2d polygon1(Rect(-300.0f, -50.0f, 300.0f, 0.0f));
	;
	Polygon2d polygon2;

	polygon2 << vec2(-200.0f, -200.0f) << vec2(-180.0f, -300.0f) << vec2(-100.0f, -250.0f) << vec2(0.0f, -300.0f) << vec2(100.0f, -100.0f) << vec2(200.0f, -250.0f);

	polygon2 += vec2(-200.0f, 90.0f);
	
	motion.m_angle = 0.2f;
	physicsBodies.push_back(
		std::auto_ptr<p2d::IBody>(new p2d::SimpleBody(
			*physicsWorld,
			std::auto_ptr<p2d::IShape>(new p2d::PolygonShape(polygon1, material)),
			p2d::IBody::ptStatic,
			material,
			motion
		))
	);
	motion.m_angle = 0.0f;

	physicsBodies.push_back(
			std::auto_ptr<p2d::IBody>(new p2d::SimpleBody(
			*physicsWorld,
			std::auto_ptr<p2d::IShape>(new p2d::ChainShape(polygon2, material)),
			p2d::IBody::ptStatic,
			material,
			motion
		))
	);

	material.m_restitution = 0.5f;
	motion.m_position = vec2(0.0f, 300.0f);
	physicsBodies.push_back(
		std::auto_ptr<p2d::IBody>(new p2d::SimpleBody(
			*physicsWorld,
			std::auto_ptr<p2d::IShape>(new p2d::CircleShape(Circle(40.0f, vec2(0.0f, 0.0f)), material)),
			p2d::IBody::ptDynamic,
			material,
			motion
		))
	);

	material.m_restitution = 1.0f;
	motion.m_position = vec2(100.0f, 300.0f);
	physicsBodies.push_back(
		std::auto_ptr<p2d::IBody>(new p2d::SimpleBody(
		*physicsWorld,
		std::auto_ptr<p2d::IShape>(new p2d::CircleShape(Circle(10.0f, vec2(0.0f, 0.0f)), material)),
		p2d::IBody::ptDynamic,
		material,
		motion
		))
	);

	physicsJoints.push_back(
		std::auto_ptr<p2d::IJoint>(new p2d::LengthJoint(
			*physicsWorld,
			physicsBodies[2],
			physicsBodies[3],
			physicsBodies[2].GetPosition() + vec2(0.0f, 15.0f),
			physicsBodies[3].GetPosition() + vec2(0.0f, 5.0f)
		))
	);
	//



	//
	boost::thread* renderThread = new boost::thread(renderScene);
	// Dispatching messages
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	complete = true;
	renderThread->join();
	
	contextPtr->Deinit();


	// Exit
	return (int) msg.wParam;
}

void renderScene() {
	FrameTimeCounter counter;
	int avgFps = 0;
	int iterations = 0;
	while (!complete) {
		counter.BeginCounting();
		
		physicsWorld->Simulate(1.0f / 10.0f);
		
		contextPtr->BeginScene();
		contextPtr->ApplyCamera(*cameraPtr);
		//contextPtr->RenderLine(vec2(0.0f, 0.0f), vec2(100.0f, 100.0f));
		for (int i = 0; i < physicsBodies.size(); ++i) {
			physicsBodies[i].DebugRender(debugRenderer);
		}

		for (int i = 0; i < physicsJoints.size(); ++i) {
			physicsJoints[i].DebugRender(debugRenderer);
		}

		contextPtr->EndScene();



		counter.EndCounting();

		avgFps += counter.GetFps();
		iterations++;
		if (iterations > 10) {
			SetWindowTextA(hWnd, formatString("fps: %d", avgFps / iterations).c_str());	
			iterations = 0;
			avgFps = 0;
		}
	}
}

void HandleKeyDown(WPARAM wParam) {
	switch(wParam) {
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_SPACE:
			break;
		case 0x5A:
			break;
	}
}
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_KEYDOWN:
			HandleKeyDown(wParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}