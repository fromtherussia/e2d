#include "Common.h"
#include "QtIncludes.h"
#include "FormIncludes.h"

#include "IResourceEditor.h"
#include "GraphicPrimitiveEditor.h"
#include "GeometryPrimitiveEditor.h"

#include "ResourceManager.h"

IResourceEditorPtr ResourceManager::GetResourceEditorPtr(Ui::EditorClass& ui, ResourceInfo resourceInfo) {
	switch (resourceInfo.m_type) {
		case ResourceType::Texture:
			return IResourceEditorPtr(new GraphicPrimitiveEditor(ui));
		case ResourceType::Form:
			return IResourceEditorPtr(new GeometryPrimitiveEditor(ui));
	}
	throw std::logic_error("editor isnt supported");
}