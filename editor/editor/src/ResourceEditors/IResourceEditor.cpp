#include "Common.h"
#include "QtIncludes.h"
#include "FormIncludes.h"

#include "IResourceEditor.h"

IResourceEditor::IResourceEditor(Ui::EditorClass& ui):
	m_ui(ui),
	m_panel(NULL) {	
}

IResourceEditor::~IResourceEditor() {
	//m_ui.resourceEditor_panelAreaWrapper->takeWidget();
}

void IResourceEditor::SetPanel(QWidget* panel) {
	m_ui.resourceEditor_panelAreaWrapper->setWidget(panel);
}