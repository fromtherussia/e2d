#ifndef EDITOR_IRESOURCE_EDITOR_H
#define EDITOR_IRESOURCE_EDITOR_H

namespace ResourceType {
	enum Type {
		Category = 1000,
		Form = 1001,
		Texture = 1002,
		Effect = 1003,
		Sound = 1004,
		Material = 1005,
		PhysPrimitive = 1006,
		GraphPrimitive = 1007,
		SoundPrimitive = 1008
	};
}

struct ResourceInfo {
	ResourceInfo(){};
	ResourceInfo(QString path, ResourceType::Type type):m_path(path), m_type(type){}
	~ResourceInfo(){}
	QString m_path;
	ResourceType::Type m_type;
};

typedef ResourceInfo ResourcesLocationInfo;
typedef QMap<QString, ResourcesLocationInfo> FolderTypes;

class IResourceEditor {
	Ui::EditorClass& m_ui;
	QWidget* m_panel;
public:
	IResourceEditor(Ui::EditorClass& ui);
	virtual ~IResourceEditor();
	void SetPanel(QWidget* panel);

	virtual bool LoadResource(QString fileName) = 0;
	virtual bool SaveChanges(QString fileName) = 0;
	virtual bool DiscardChanges() = 0;
};

typedef boost::shared_ptr<IResourceEditor> IResourceEditorPtr;

#endif