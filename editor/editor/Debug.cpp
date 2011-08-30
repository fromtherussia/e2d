#include <e2d/e2d.h>

#include "src/VisualEditors/DebugRenderer.h"

using namespace air2d::physics;

r2d::D3DRenderContext context;
r2d::D3DCamera camera(Rect(-320.0f, -240.0f, 320.0f, 240.0f));

/*
PolygonEditor polygonEditor;
RectangleEditor rectangleEditor;
RectGraphicPrimitiveEditor rectGraphicPrimitiveEditor;
PolygonGraphicPrimitiveEditor polygonGraphicPrimitiveEditor;
ObjectLibrary* objectLibrary;
CursorMovementModifier cursorMovementModifier;*/

/*
World world(vec2(0.0f, -100.0f));
Primitive* bullet;
Primitive* brick;
Joint* lengthJoint;
Primitive* wall;
std::vector<Primitive*> primitives;*/

DebugRenderer* debugRenderer;
r2d::D3DFont* font;


void OnLeft() {
	camera.Move(vec2(-2.0f, 0.0f));
}

void OnRight() {
	camera.Move(vec2(2.0f, 0.0f));
}

void OnUp() {
	camera.Move(vec2(0.0f, 2.0f));
}

void OnDown() {
	camera.Move(vec2(0.0f, -2.0f));
}

void Init(HWND hWnd) {
	context.Init(hWnd);
	/*
	FolderTypes folderTypes;
	folderTypes[QString::fromLocal8Bit("Формы")] = ResourceInfo("Resources/Forms", ResourceType::Form);
	folderTypes[QString::fromLocal8Bit("Текстуры")] = ResourceInfo("Resources/Textures", ResourceType::Texture);
	folderTypes[QString::fromLocal8Bit("Эффекты")] = ResourceInfo("Resources/Effects", ResourceType::Effect);
	folderTypes[QString::fromLocal8Bit("Звуки")] = ResourceInfo("Resources/Audio", ResourceType::Sound);
	folderTypes[QString::fromLocal8Bit("Материалы")] = ResourceInfo("Resources/Materials", ResourceType::Material);
	folderTypes[QString::fromLocal8Bit("Физ. примитивы")] = ResourceInfo("Resources/PhysPrimitives", ResourceType::PhysPrimitive);
	folderTypes[QString::fromLocal8Bit("Граф. примитивы")] = ResourceInfo("Resources/GraphPrimitives", ResourceType::GraphPrimitive);
	folderTypes[QString::fromLocal8Bit("Звук. примитивы")] = ResourceInfo("Resources/AudioPrimitives", ResourceType::SoundPrimitive);
	objectLibrary = new ObjectLibrary(ui, folderTypes);*/

	debugRenderer = new DebugRenderer(context);

	r2d::FontAttributes fontAttributes;
	fontAttributes.height = 14;
	fontAttributes.width = 0;
	fontAttributes.weight = FW_NORMAL;
	fontAttributes.isItalic = false;
	fontAttributes.charset = DEFAULT_CHARSET;
	fontAttributes.precision = OUT_TT_ONLY_PRECIS; // OUT_TT_ONLY_PRECIS TrueType
	fontAttributes.quality = ANTIALIASED_QUALITY;
	fontAttributes.familyIndex = DEFAULT_PITCH | FF_DONTCARE;
	fontAttributes.fontFace = "Arial";
	font = new r2d::D3DFont(context, fontAttributes);

	/*
	wall = new Primitive(world, Primitive::typeStatic);
	*wall << IShapePtr(new PolygonShape(Polygon2d(Rect(-300.0f, -200.0f, 300.0f, -190.0f)), ShapePhysicsAttributes()));
	*wall << IShapePtr(new PolygonShape(Polygon2d(Rect(300.0f, -190.0f, 310.0f, 200.0f)), ShapePhysicsAttributes()));

	brick = new Primitive(world, Primitive::typeDynamic, PrimitivePhysicsAttributes(), PrimitiveInitialMotion(vec2(-300.0f, 70.0f)));
	*brick << IShapePtr(new CircleShape(Circle(10.0f, vec2()), ShapePhysicsAttributes(1.0f)));

	bullet = new Primitive(world, Primitive::typeDynamic, PrimitivePhysicsAttributes(), PrimitiveInitialMotion(vec2(-200.0f, 70.0f)));
	*bullet << IShapePtr(new CircleShape(Circle(10.0f, vec2()), ShapePhysicsAttributes(100.0f)));

	lengthJoint = new LengthJoint(world, *bullet, *brick, vec2(vec2(-200.0f, 70.0f)), vec2(-300.0f, 70.0f));

	float xInitial = 0.0f;
	float x = 0.0f;
	float y = -190.0f;
	for (int i = 8; i > 0; --i) {
	for (float x = xInitial, j = 0; j <= i; x += 10.0f, ++j) {
	Primitive* p;
	p = new Primitive(world, Primitive::typeDynamic);
	*p << IShapePtr(new PolygonShape(Polygon2d(Rect(x, y, x + 10.0f, y + 10.0f)), ShapePhysicsAttributes()));
	primitives.push_back(p);
	}
	y += 10.0f;
	xInitial += 5.0f;
	}*/
}

void Deinit() {
	context.Deinit();
}

void Render(vec2 cursorPos) {
/*	world.Simulate(1.0f / 60.0f);
	wall->DebugRender(context);
	bullet->DebugRender(context);
	brick->DebugRender(context);
	lengthJoint->DebugRender(context);
	for (int i = 0; i < primitives.size(); ++i) {
		primitives[i]->DebugRender(context);
	}
	bullet->ApplyForce(vec2(4000000.0f, 10.0f), bullet->GetPosition());
*/
	context.BeginScene();
	context.ApplyCamera(camera);

	//font->Render(context, camera, "SomeText", vec2(20.0f, 20.0f), ivec3(0xFF, 0xFF, 0xFF), VerticalAlign::Right, HorisontalAlign::Bottom, vec2(10.0f, 10.0f));

	debugRenderer->RenderBoundaries(Rect(10.0f, 10.0f, 200.0f, 100.0f), camera.GetVisibleRect());
	debugRenderer->RenderRules(15.0f, camera.GetVisibleRect());

	context.RenderPoint(cursorPos, ivec3(0xFF, 0, 0), 2.0f);

	context.EndScene();
}