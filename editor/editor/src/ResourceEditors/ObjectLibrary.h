#ifndef EDITOR_OBJECT_LIBRARY_H
#define EDITOR_OBJECT_LIBRARY_H

#include "Common.h"
#include "QtIncludes.h"
#include "FormIncludes.h"
#include "IResourceEditor.h"

class ObjectLibrary: public QObject {
	Q_OBJECT

	Ui::EditorClass& m_ui;
	QTreeWidget* m_fileTree;
	QTreeWidgetItem* m_currentItem;
	FolderTypes m_folderTypes;
	IResourceEditorPtr m_currentResourceEditor;

	ResourceInfo GetTreeItemData(QTreeWidgetItem* item);
	void SetTreeItemData(QTreeWidgetItem* item, const ResourceInfo& data);

	bool AddSubItems(QTreeWidgetItem* parentItem, const QString& path, ResourceType::Type resourceType);
public:
	ObjectLibrary(Ui::EditorClass& ui, FolderTypes folderTypes);
	~ObjectLibrary();
	bool CreateFolder(const QString& folderName);
	bool CreateResource(const QString& resourceName);
	bool DeleteCurrent();
	ResourceInfo GetCurrentResourceInfo();
	bool RefreshResourceList();
public slots:
	void onItemSelect(QTreeWidgetItem* item, int column);
	void onItemEdit(QTreeWidgetItem* item, int column);
	void onNewFile();
	void onNewFolder();
	void onDeleteSelected();
	void onRefresh();
};

#endif