#ifndef EDITOR_GEOMETRY_PRIMITIVE_EDITOR_H
#define EDITOR_GEOMETRY_PRIMITIVE_EDITOR_H

class GeometryPrimitiveEditor: public IResourceEditor {
public:
	GeometryPrimitiveEditor(Ui::EditorClass& ui);
	virtual ~GeometryPrimitiveEditor();

	virtual bool LoadResource(QString fileName);
	virtual bool SaveChanges(QString fileName);
	virtual bool DiscardChanges();
};

#endif