#include <windows.h>
#include <cgl/cgl.h>
#include "Debug.h"

#include "editor.h"

Editor::Editor(QWidget *parent, Qt::WFlags flags):
	QMainWindow(parent, flags),
	done(false),
	oldPosition(-1, -1)
{
	ui.setupUi(this);

	setMouseTracking(true);
	ui.centralWidget->setMouseTracking(true);
	ui.widget->setMouseTracking(true);

	/*
	cursorMovementModifier.SetGridSize(20.0f);
	cursorMovementModifier.TurnOnGrid();*/

	// Задание начальных позиций элементам
	onActivateHandler();

	// Инициализация контекста рендеринга
	HWND contextWindow = ui.widget->winId();
	Init(contextWindow);
	// Запуск основного потока рендеринга
	mainEditorThread = new boost::thread(boost::bind(&Editor::Run, this));
}

Editor::~Editor() {
	done = true;
	// Ожидание завершения потока рендеринга
	mainEditorThread->join();
	// Debug::deinit
	Deinit();
	// Уничтожение контекста
	//context.Deinit();
}

void Editor::ShowItemPicker() {
	ui.toolBox->hide();
}

void Editor::ShowFormEditor() {
	ui.toolBox->show();
}

void Editor::onActivateHandler() {
}

vec2 Editor::GetCursorPos() {
	QPoint cursorPos = ui.widget->mapFromGlobal(QCursor::pos());
	vec2 pos = vec2(cursorPos.x() - 320, 240 - cursorPos.y());
	//cursorMovementModifier.ModifyCursorPos(pos);
	return pos;
}

vec2 Editor::GetCursorDelta() {
	vec2 currentPos = GetCursorPos();
	vec2 delta = currentPos - oldPosition;
	//cursorMovementModifier.ModifyCursorDelta(delta);
	return delta;
}

void Editor::mousePressEvent(QMouseEvent* event) {
	oldPosition = GetCursorPos();
	//polygonGraphicPrimitiveEditor.HandleLeftPress(GetCursorPos());
	//rectGraphicPrimitiveEditor.HandleLeftPress(GetCursorPos());
}

void Editor::mouseReleaseEvent(QMouseEvent* event) {
	//polygonGraphicPrimitiveEditor.HandleLeftRelease(GetCursorPos());
	//rectGraphicPrimitiveEditor.HandleLeftRelease(GetCursorPos());
}

void Editor::mouseDoubleClickEvent(QMouseEvent* event) {
	//polygonGraphicPrimitiveEditor.HandleLeftDoubleClick(GetCursorPos());
	//rectGraphicPrimitiveEditor.HandleLeftDoubleClick(GetCursorPos());
}

void Editor::mouseMoveEvent(QMouseEvent* event) {
	vec2 currentPosition = GetCursorPos();
	//polygonGraphicPrimitiveEditor.HandlePositionChange(currentPosition, GetCursorDelta());
	//rectGraphicPrimitiveEditor.HandlePositionChange(currentPosition, GetCursorDelta());
	oldPosition = currentPosition;
}
void Editor::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_A) {
		OnLeft();
	}
	if (event->key() == Qt::Key_D) {
		OnRight();
	}
	if (event->key() == Qt::Key_W) {
		OnUp();
	}
	if (event->key() == Qt::Key_S) {
		OnDown();
	}
	/*if (event->key() == Qt::Key_Shift) {
		cursorMovementModifier.HandleKeyPress(KeyboardKey::Shift);	
	}
	if (event->key() == Qt::Key_Control) {
		cursorMovementModifier.HandleKeyPress(KeyboardKey::Ctrl);	
	}
	if (event->key() == Qt::Key_G) {
		if (cursorMovementModifier.IsGridOn()) {
			cursorMovementModifier.TurnOffGrid();
		} else {
			cursorMovementModifier.TurnOnGrid();
		}
	}
	if (event->key() == Qt::Key_T) {
		polygonGraphicPrimitiveEditor.HandleKeyPress(KeyboardKey::Key_T);
		rectGraphicPrimitiveEditor.HandleKeyPress(KeyboardKey::Key_T);
	}
	if (event->key() == Qt::Key_Delete) {
		polygonGraphicPrimitiveEditor.HandleKeyPress(KeyboardKey::Delete);
		rectGraphicPrimitiveEditor.HandleKeyPress(KeyboardKey::Delete);
	}*/
}
void Editor::keyReleaseEvent(QKeyEvent* event) {
	/*if (event->key() == Qt::Key_Shift) {
		cursorMovementModifier.HandleKeyRelease(KeyboardKey::Shift);	
	}
	if (event->key() == Qt::Key_Control) {
		cursorMovementModifier.HandleKeyRelease(KeyboardKey::Ctrl);	
	}*/
}

void Editor::wheelEvent(QWheelEvent* event) {
}

void Editor::Run()
{
	/*
	R2D::D3DMaterial material
	(
		R2D::D3DTexturePtr(new R2D::D3DTexture(context, "Data//Image.jpg")),
		R2D::D3DEffectPtr(new R2D::D3DEffect(context, "Data//Shader.fx")),
		R2D::D3DMaterialFlags::SetConstMatrixWVP
	);*/

	/*
	Polygon2d geom1;
	geom1 << vec2(0.0f, 0.0f) << vec2(80.0f, 0.0f) << vec2(80.0f, 80.0f);

	R2D::D3DStaticPolygon poly(context, geom1, Rect(0.0f, 0.0f, 1.0f, 1.0f));
	R2D::D3DStaticRectangle rectangle(context, Rect(-55.0f, -40.0f, 55.0f, 40.0f));
	
	polygonGraphicPrimitiveEditor.SetPolygon(&poly);
	rectGraphicPrimitiveEditor.SetRectangle(&rectangle);*/

	// cursorMovementModifier.Render(context, camera);
	// poly.Render(context, texture);
	// polygonGraphicPrimitiveEditor.Render(context);
	// rectangle.Render(context, texture);
	// rectGraphicPrimitiveEditor.Render(context);
	
	while (!done) {			
		Render(GetCursorPos());
	}
}