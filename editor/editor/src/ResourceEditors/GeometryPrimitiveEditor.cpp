#include "Common.h"
#include "QtIncludes.h"
#include "FormIncludes.h"

#include "IResourceEditor.h"

#include "GeometryPrimitiveEditor.h"

GeometryPrimitiveEditor::GeometryPrimitiveEditor(Ui::EditorClass& ui):
IResourceEditor(ui) {
	QWidget* widget = new QWidget();
	Ui::GeometryPrimitiveEditor form;
	form.setupUi(widget);
	SetPanel(widget);
}

GeometryPrimitiveEditor::~GeometryPrimitiveEditor() {

}

bool GeometryPrimitiveEditor::LoadResource(QString fileName) {
	return true;
}

bool GeometryPrimitiveEditor::SaveChanges(QString fileName) {
	return true;
}

bool GeometryPrimitiveEditor::DiscardChanges() {
	return true;
}