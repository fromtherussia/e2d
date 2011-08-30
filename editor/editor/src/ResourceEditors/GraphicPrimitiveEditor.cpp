#include "Common.h"
#include "QtIncludes.h"
#include "FormIncludes.h"

#include "IResourceEditor.h"

#include "GraphicPrimitiveEditor.h"

GraphicPrimitiveEditor::GraphicPrimitiveEditor(Ui::EditorClass& ui):
	IResourceEditor(ui) {
	QWidget* widget = new QWidget();
	Ui::GraphicPrimitiveEditor form;
	form.setupUi(widget);
	SetPanel(widget);
}

GraphicPrimitiveEditor::~GraphicPrimitiveEditor() {

}

bool GraphicPrimitiveEditor::LoadResource(QString fileName) {
	return true;
}

bool GraphicPrimitiveEditor::SaveChanges(QString fileName) {
	return true;
}

bool GraphicPrimitiveEditor::DiscardChanges() {
	return true;
}