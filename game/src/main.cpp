#include <boost/thread.hpp>

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <direct.h> // KILLME

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

#include <air2d/physics/PhysicsWorld.h>
#include <air2d/physics/PhysicsIShape.h>
#include <air2d/physics/PhysicsPolygonShape.h>
#include <air2d/physics/PhysicsPrimitive.h>
#include <air2d/engine/EngineIEntity.h>
#include <air2d/engine/EngineEntity.h>
#include <air2d/engine/EngineScene.h>

#include <rapidxml/rapidxml.hpp>

#include <cgl/TypesParser.h >

#include <fstream>
#include <iostream>

#include <air2d/DataLoaders/ResourceXmlLoader.h>

float get_time_callback() {
	return timeGetTime() * 0.001f;
}

// R2D
r2d::IRenderContextPtr contextPtr;
r2d::ICameraPtr cameraPtr;
air2d::engine::Scene scene;

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

	//////////////////////////////////////////////////////////////////////////
	// XML


	std::ifstream xmlInput("Data/Level/entity1.xml");
	string_t data;

	std::istream_iterator<string_t> DataBegin(xmlInput);
	std::istream_iterator<string_t> DataEnd;


	while (DataBegin != DataEnd) {
		data += *DataBegin;
		DataBegin++;
	}

	e2d::loaders::EngineObjectsXmlLoader loader;

	loader.AddGraphicShapeLoader("dynamic_geometry", new e2d::loaders::DynamicGeometryObjectXmlLoader());

	loader.ParseEntity(data);

	/*string_t sampleXml("<?xml version=\"1.0\" encoding=\"UTF-8\"?><entity src=\"123\" dst=\"1234\"></entity>");
	
	rapidxml::xml_document<char> doc;
	doc.parse<0>((char*)sampleXml.c_str());

	rapidxml::xml_node<>* node = doc.first_node("entity");

	for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
		char* attrName = attr->name();
		attrName[0] = '\0';
	}*/
	//////////////////////////////////////////////////////////////////////////
	char cCurrentPath[FILENAME_MAX];
	_getcwd(cCurrentPath, sizeof(cCurrentPath));

	contextPtr = r2d::CreateRenderContext(hWnd);
	
	r2d::IFactoryPtr factoryPtr;
	r2d::ITexture* texturePtr;
	r2d::IEffect* effectPtr;
	r2d::IMaterialPtr materialPtr;
	
	
	contextPtr->Init();
	factoryPtr = r2d::IFactoryPtr(contextPtr->GetFactory());
	
	cameraPtr = r2d::ICameraPtr(factoryPtr->CreateCamera(Rect(-400.0f, -300.0f, 400.0f, 300.0f)));
	texturePtr = factoryPtr->CreateTexture("Data/Image.jpg");
	effectPtr = factoryPtr->CreateEffect("Data/Shader.fx");
	materialPtr = r2d::IMaterialPtr(factoryPtr->CreateMaterial(effectPtr, 1, r2d::MaterialFlags::SetConstMatrixWVP));
	materialPtr->AddTexture("texture1", texturePtr);
	
	Polygon2d polygon;
	polygon << vec2(0.0f, 0.0f) << vec2(60.0f, 0.0f) << vec2(60.0f, 60.0f) << vec2(0.0f, 60.0f);
	polygon.Center();

	Polygon2d ground;
	ground << vec2(-200.0f, -100.0f) << vec2(200.0f, -100.0f) << vec2(200.0f, -80.0f) << vec2(-200.0f, -80.0f);
	ground.Center();

	
	
	air2d::engine::Entity* entity1 = scene.CreateDynamicEntity();
	entity1->AddShape(
		new air2d::physics::PolygonShape(
			polygon,
			air2d::physics::Material()
		),
		factoryPtr->CreateGraphicObject(materialPtr, polygon, vec2(30.0f, 30.0f)),
		vec2(0.0f, 0.0f)
	);

	air2d::engine::Entity* entity2 = scene.CreateDynamicEntity(vec2(37.0f, 80.0f));
	entity2->AddShape(
		new air2d::physics::PolygonShape(
			polygon,
			air2d::physics::Material()
		),
		factoryPtr->CreateGraphicObject(materialPtr, polygon, vec2(30.0f, 30.0f)),
		vec2(0.0f, 0.0f)
	);

	air2d::engine::Entity* entity4 = scene.CreateDynamicEntity(vec2(-37.0f, 70.0f));
	entity4->AddShape(
		new air2d::physics::PolygonShape(
		polygon,
		air2d::physics::Material()
		),
		factoryPtr->CreateGraphicObject(materialPtr, polygon, vec2(30.0f, 30.0f)),
		vec2(0.0f, 0.0f)
		);
	
	air2d::engine::Entity* entity3 = scene.CreateStaticEntity(vec2(0.0f, -90.0f));
	entity3->AddShape(
		new air2d::physics::PolygonShape(
			ground,
			air2d::physics::Material()
		),
		factoryPtr->CreateGraphicObject(materialPtr, ground, vec2(30.0f, 30.0f)),
		vec2(0.0f, 0.0f)
	);


	scene << entity1 << entity2 << entity3 << entity4;

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

	//font->Render(context, camera, "SomeText", vec2(20.0f, 20.0f), ivec3(0xFF, 0xFF, 0xFF), VerticalAlign::Right, HorisontalAlign::Bottom, vec2(10.0f, 10.0f));
	//debugRenderer->RenderBoundaries(Rect(10.0f, 10.0f, 200.0f, 100.0f), camera.GetVisibleRect());
	//debugRenderer->RenderRules(15.0f, camera.GetVisibleRect());
	//context.RenderPoint(cursorPos, ivec3(0xFF, 0, 0), 2.0f);
	//contextPtr->RenderLine(vec2(0.0f, 0.0f), vec2(100.0f, 100.0f));
	//compositeObject.Render(*contextPtr);


	// Exit
	return (int) msg.wParam;
}

void renderScene() {
	FrameTimeCounter counter;
	int avgFps = 0;
	int iterations = 0;
	while (!complete) {
		counter.BeginCounting();
		scene.Render(*contextPtr, *cameraPtr, true);
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
	/*switch(wParam) {
		case VK_UP:
			compositeObject.SetPosition(compositeObject.GetPosition() + vec2(0.0f, 2.0f));
			break;
		case VK_DOWN:
			compositeObject.SetPosition(compositeObject.GetPosition() + vec2(0.0f, -2.0f));
			break;
		case VK_LEFT:
			compositeObject.SetPosition(compositeObject.GetPosition() + vec2(-2.0f, 0.0f));
			break;
		case VK_RIGHT:
			compositeObject.SetPosition(compositeObject.GetPosition() + vec2(2.0f, 0.0f));
			break;
		case 0x41:
			compositeObject.SetRotation(compositeObject.GetRotation() - 0.2f);
			break;
		case 0x5A:
			compositeObject.SetRotation(compositeObject.GetRotation() + 0.2f);
			break;
	}*/
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