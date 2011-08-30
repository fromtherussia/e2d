#include "Common.h"
#include "QtIncludes.h"
#include "FormIncludes.h"

#include "IResourceEditor.h"
#include "ResourceManager.h"

#include "ObjectLibrary.h"

// Private

ResourceInfo ObjectLibrary::GetTreeItemData(QTreeWidgetItem* item) {
	ResourceInfo info;
	info.m_path = item->data(0, Qt::ItemDataRole::UserRole).toString();
	info.m_type = (ResourceType::Type)item->type();
	return info;
}

void ObjectLibrary::SetTreeItemData(QTreeWidgetItem* item, const ResourceInfo& data) {
	item->setData(0, Qt::ItemDataRole::UserRole, QVariant(data.m_path));
}

bool ObjectLibrary::AddSubItems(QTreeWidgetItem* parentItem, const QString& path, ResourceType::Type resourceType) {
	try {
		QDirIterator it(path);
		QVector<QString> files;
		do {
			it.next();
			QString fileName(it.fileName());
			if (it.fileInfo().isDir()) {
				if (fileName != "." && fileName != "..") {
					QString newPath(path + "/" + it.fileName());
					QTreeWidgetItem* item = new QTreeWidgetItem(parentItem, QStringList() << fileName, (int)resourceType);
					item->setIcon(0, QIcon("Images/folder.png"));
					SetTreeItemData(item, ResourceInfo(newPath, resourceType));

					AddSubItems(item, newPath, resourceType);
				}
			} else {
				files.push_back(fileName);
			}
		}
		while(it.hasNext());

		for (int i = 0; i < files.count(); ++i) {
			QString newPath(path + "/" + files[i]);
			QTreeWidgetItem* item = new QTreeWidgetItem(parentItem, QStringList() << files[i], (int)resourceType);
			item->setIcon(0, QIcon("Images/file.png"));
			SetTreeItemData(item, ResourceInfo(newPath, resourceType));
		}
	} catch(...) {
		return false;
	}

	return true;
}

// Public

ObjectLibrary::ObjectLibrary(Ui::EditorClass& ui, FolderTypes folderTypes):
	m_folderTypes(folderTypes),
	m_currentItem(NULL),
	m_ui(ui) {
	
	m_fileTree = ui.objectLibrary_objectTree;
	QObject::connect(m_fileTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onItemSelect(QTreeWidgetItem*, int)));
	QObject::connect(m_fileTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onItemEdit(QTreeWidgetItem*, int)));
	QObject::connect(ui.objectLibrary_newFile, SIGNAL(clicked()), this, SLOT(onNewFile()));
	QObject::connect(ui.objectLibrary_newFolder, SIGNAL(clicked()), this, SLOT(onNewFolder()));
	QObject::connect(ui.objectLibrary_deleteSelected, SIGNAL(clicked()), this, SLOT(onDeleteSelected()));
	QObject::connect(ui.objectLibrary_refresh, SIGNAL(clicked()), this, SLOT(onRefresh()));

	RefreshResourceList();
}

ObjectLibrary::~ObjectLibrary() {

}

bool ObjectLibrary::CreateFolder(const QString& folderName) {
	if (m_currentItem == NULL) {
		return false;
	}
	ResourceInfo info =	GetTreeItemData(m_currentItem);
	
	QString newPath(info.m_path + "/" + folderName);
	QTreeWidgetItem* item = new QTreeWidgetItem(m_currentItem, QStringList() << folderName, (int)info.m_type);
	item->setIcon(0, QIcon("Images/folder.png"));
	SetTreeItemData(item, ResourceInfo(newPath, info.m_type));

	QString str = QDir::currentPath();
	QDir::current().mkdir(newPath);

	return true;
}

bool ObjectLibrary::CreateResource(const QString& resourceName) {
	if (m_currentItem == NULL) {
		return false;
	}
//	QTreeWidgetItem* item = new QTreeWidgetItem(parentItem, QStringList() << resourceName, (int)resourceType);
	return true;
}

bool ObjectLibrary::DeleteCurrent() {
	if (m_currentItem == NULL) {
		return false;
	}
	ResourceInfo info =	GetTreeItemData(m_currentItem);
	QFileInfo fileInfo(info.m_path);
	if (!fileInfo.exists()) {
		return false;
	} 
	bool success = false;
	if (!fileInfo.isDir()) {
		success = QFile::remove(info.m_path);
	}
	if (success) {
		QTreeWidgetItem* itemParent = m_currentItem->parent();
		itemParent->removeChild(m_currentItem);
	}
	return true;
}

ResourceInfo ObjectLibrary::GetCurrentResourceInfo() {
	ResourceInfo i;
	return i;
}


bool ObjectLibrary::RefreshResourceList() {
	// Clearing tree
	m_fileTree->clear();
	m_currentItem = NULL;

	for (FolderTypes::iterator foldersIt = m_folderTypes.begin(); foldersIt != m_folderTypes.end(); ++foldersIt) {
		QString folderDisplayName(foldersIt.key());
		QString resourcesPathPrefix(foldersIt->m_path);
		ResourceType::Type resourcesType(foldersIt->m_type);

		QTreeWidgetItem* item = new QTreeWidgetItem(m_fileTree, QStringList() << folderDisplayName, (int)ResourceType::Category);
		item->setIcon(0, QIcon("Images/category.png"));
		SetTreeItemData(item, ResourceInfo(resourcesPathPrefix, resourcesType));
		m_fileTree->setItemWidget(item, 0, new QWidget());

		if(!AddSubItems(item, resourcesPathPrefix, resourcesType)) {
			return false;
		}
	}
	return true;
}

void ObjectLibrary::onItemSelect(QTreeWidgetItem* item, int column) {
	m_currentItem = item;
}

void ObjectLibrary::onItemEdit(QTreeWidgetItem* item, int column) {
	m_currentItem = item;
	ResourceInfo info = GetTreeItemData(item);
	//if (info.m_type)
	m_ui.toolBox->setCurrentIndex(1);
	m_currentResourceEditor = ResourceManager::GetResourceEditorPtr(m_ui, info);
}


void ObjectLibrary::onNewFile() {

}

void ObjectLibrary::onNewFolder() {
	if (m_currentItem == NULL) {
		return;
	}
	QDialog dialog;
	Ui::NewFolderDialog newFolderDialog;
	newFolderDialog.setupUi(&dialog);
	dialog.exec();
	if (dialog.result() == QDialog::Accepted) {
		QString folderName = newFolderDialog.lineEdit->text();
		if (folderName.length() > 0) {
			CreateFolder(folderName);
		}
	}
}

void ObjectLibrary::onDeleteSelected() {
	if (m_currentItem == NULL) {
		return;
	}
	QMessageBox messageBox;
	messageBox.setText("Realy delete selected element?");
	messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	messageBox.setDefaultButton(QMessageBox::Cancel);
	if (messageBox.exec() == QMessageBox::Ok) {
		DeleteCurrent();
	}
}

void ObjectLibrary::onRefresh() {
	RefreshResourceList();
}