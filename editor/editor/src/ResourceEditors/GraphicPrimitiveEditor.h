#ifndef EDITOR_GRAPHIC_PRIMITIVE_EDITOR_H
#define EDITOR_GRAPHIC_PRIMITIVE_EDITOR_H

class GraphicPrimitiveEditor: public IResourceEditor {
public:
	GraphicPrimitiveEditor(Ui::EditorClass& ui);
	virtual ~GraphicPrimitiveEditor();

	virtual bool LoadResource(QString fileName);
	virtual bool SaveChanges(QString fileName);
	virtual bool DiscardChanges();
};

#endif