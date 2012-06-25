#ifndef EDITOR_EDITOR_H
#define EDITOR_EDITOR_H

#include <cgl/cgl.h>
#include "Common.h"
#include "QtIncludes.h"
#include "FormIncludes.h"

class Editor: public QMainWindow {
	Q_OBJECT
public:
	Editor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Editor();
public slots:
	void onActivateHandler();
public:
	void Run();
	vec2 GetCursorPos();
	vec2 GetCursorDelta();
	void ShowItemPicker();
	void ShowFormEditor();

private:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void wheelEvent(QWheelEvent* event);

	vec2 oldPosition;
	bool done;
	boost::thread* mainEditorThread;

	Ui::EditorClass ui;
};

#endif