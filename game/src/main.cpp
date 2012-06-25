#include <boost/thread.hpp>
#include <boost/property_tree/ptree.hpp> // KILLME
#include <boost/property_tree/json_parser.hpp> // KILLME

#pragma comment(lib, "winmm.lib")

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

#include <air2d/physics/Common.h>
#include <air2d/physics/IShape.h>
#include <air2d/physics/PolygonShape.h>
#include <air2d/physics/IPrimitive.h>
#include <air2d/physics/CompositePrimitive.h>
#include <air2d/physics/World.h>
#include <air2d/engine/IEntityFactory.h>
#include <air2d/engine/IPhysicMaterialTable.h>
#include <air2d/engine/IResourceController.h>
#include <air2d/engine/IGraphicMaterialTable.h>
#include <air2d/engine/IEntity.h>
#include <air2d/engine/ComplexPhysicEntity.h>
#include <air2d/engine/DestructibleEntity.h>
#include <air2d/engine/Scene.h>

#include <air2d/DataLoaders/SceneLoader.h>

float get_time_callback() {
	return timeGetTime() * 0.001f;
}

// R2D
std::auto_ptr<r2d::IRenderContext> contextPtr;
std::auto_ptr<r2d::ICamera> cameraPtr;
e2d::engine::Scene* scene;

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

e2d::engine::DestructibleEntity* destructibleEntity;

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

	//char cCurrentPath[FILENAME_MAX];
	//_getcwd(cCurrentPath, sizeof(cCurrentPath));

	contextPtr = r2d::CreateRenderContext(hWnd);
	contextPtr->Init();
	
	std::auto_ptr<r2d::IFactory> factoryPtr = contextPtr->GetFactory();
	
	cameraPtr = factoryPtr->CreateCamera(Rect(-400.0f, -300.0f, 400.0f, 300.0f));
	scene = new e2d::engine::Scene(factoryPtr);
	
	e2d::loaders::SceneLoader loader(scene);
	/*
	std::ifstream entity1Input("Data/Level/entity1.json");
	std::ifstream entity2Input("Data/Level/entity2.json");
	std::ifstream entity3Input("Data/UnreachableStars/Entities/background-entity.json");
	std::ifstream entity4Input("Data/UnreachableStars/Entities/ground-entity.json");
	std::ifstream entity5Input("Data/UnreachableStars/Entities/foreground-entity.json");
	std::ifstream entity6Input("Data/Level/entity3.json");*/
	std::ifstream entity7Input("Data/Level/character.json");
/*
	std::ifstream graphicMaterialInput1("Data/Level/grass.json");
	std::ifstream graphicMaterialInput2("Data/Level/dummy.json");
	std::ifstream graphicMaterialInput3("Data/Level/grass-alpha.json");
	std::ifstream graphicMaterialInput4("Data/UnreachableStars/Materials/background-material.json");
	std::ifstream graphicMaterialInput5("Data/UnreachableStars/Materials/ground-material.json");
	std::ifstream graphicMaterialInput6("Data/UnreachableStars/Materials/foreground-material.json");*/
	std::ifstream graphicMaterialInput7("Data/Level/character-material.json");
/*
	std::ifstream physicMaterialInput1("Data/Level/rock.json");
*/
	std::ifstream demoLevelInput("Data/DemoLevel/level.json");
	/*
	e2d::engine::IEntity* entity1;
	e2d::engine::IEntity* entity2;
	e2d::engine::IEntity* entity3;
	e2d::engine::IEntity* entity4;
	e2d::engine::IEntity* entity5;
	e2d::engine::IEntity* entity6;*/
	e2d::engine::IEntity* entity8;

	e2d::engine::IEntity* entity7;
	try {
		loader.LoadScene(demoLevelInput);
/*
		loader.LoadGraphicMaterial(graphicMaterialInput1);
		loader.LoadGraphicMaterial(graphicMaterialInput2);
		loader.LoadGraphicMaterial(graphicMaterialInput3);
		loader.LoadGraphicMaterial(graphicMaterialInput4);
		loader.LoadGraphicMaterial(graphicMaterialInput5);
		loader.LoadGraphicMaterial(graphicMaterialInput6);*/
		loader.LoadGraphicMaterial(graphicMaterialInput7);
/*
		loader.LoadPhysicMaterial(physicMaterialInput1);
		
		entity1 = loader.ParseEntity(entity1Input);
		//entity2 = loader.ParseEntity(entity2Input);
		entity3 = loader.ParseEntity(entity3Input);
		entity4 = loader.ParseEntity(entity4Input);
		entity5 = loader.ParseEntity(entity5Input);
		entity6 = loader.ParseEntity(entity6Input);*/
		entity8 = loader.ParseEntity(entity7Input);

		Polygon2d geometry;
		geometry << vec2(0.0f, 0.0f) << vec2(50.0f, 0.0f) << vec2(50.0f, 50.0f) << vec2(0.0f, 50.0f);
		geometry.Center();

		destructibleEntity = new e2d::engine::DestructibleEntity(
			scene->m_world,
			scene,
			"character",
			"rock",
			geometry,
			vec2(100.0f, 100.0f),
			0.0f,
			Rect(0.0f, 0.0f, 0.111111f, 1.0f)
		);
		entity7 = destructibleEntity;
		
		*scene << entity7;
	} catch (boost::property_tree::json_parser_error& e) {
		// TODO: good error messages
		throw std::runtime_error(formatString("can't parse JSON file, error on line '%d', with message '%s'", e.line(), e.what()));
	} catch (const boost::property_tree::ptree_bad_path& e) {
		// TODO: good error messages
		throw std::runtime_error(formatString("can't parse JSON file, node '%s' not found", e.what()));
	}
/*	*scene << entity1;
	*scene << entity3;
	*scene << entity4;
	*scene << entity5;
	*scene << entity6;*/
	*scene << entity8;

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

	delete scene;

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
		scene->Render(*contextPtr, *cameraPtr, true);
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
			//compositeObject.SetPosition(compositeObject.GetPosition() + vec2(0.0f, 2.0f));
			break;
		case VK_DOWN:
			//compositeObject.SetPosition(compositeObject.GetPosition() + vec2(0.0f, -2.0f));
			break;
		case VK_LEFT:
			//compositeObject.SetPosition(compositeObject.GetPosition() + vec2(-2.0f, 0.0f));
			cameraPtr->SetPosition(cameraPtr->GetPosition() + vec2(-5.0f, 0.0f));
			break;
		case VK_RIGHT:
			//compositeObject.SetPosition(compositeObject.GetPosition() + vec2(2.0f, 0.0f));
			cameraPtr->SetPosition(cameraPtr->GetPosition() + vec2(5.0f, 0.0f));
			break;
		case VK_SPACE:
			destructibleEntity->Destruct();
			//compositeObject.SetRotation(compositeObject.GetRotation() - 0.2f);
			break;
		case 0x5A:
			//compositeObject.SetRotation(compositeObject.GetRotation() + 0.2f);
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