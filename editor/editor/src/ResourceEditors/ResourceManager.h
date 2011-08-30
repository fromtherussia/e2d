#ifndef EDITOR_RESOURCE_MANAGER_H
#define EDITOR_RESOURCE_MANAGER_H

class ResourceManager {
public:
	static IResourceEditorPtr GetResourceEditorPtr(Ui::EditorClass& ui, ResourceInfo resourceInfo);
};

#endif