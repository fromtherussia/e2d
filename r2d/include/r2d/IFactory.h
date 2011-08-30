#ifndef R2D_IFACTORY_H
#define R2D_IFACTORY_H

#include "Common.h"

namespace r2d {
	PREDECL_CLASS_WITH_PTR(ICamera);
	PREDECL_CLASS_WITH_PTR(ITexture);
	PREDECL_CLASS_WITH_PTR(IEffect);
	PREDECL_CLASS_WITH_PTR(IMaterial);
	PREDECL_CLASS_WITH_PTR(IDynamicGeometeryObject);

	class IFactory {
	public:
		IFactory() {};
		virtual ~IFactory() {};

		// Factory interface
		virtual ICamera* CreateCamera(const Rect& visibleRect, float zNear = 0.0f, float zFar = 1.0f) = 0;
		virtual ITexture* CreateTexture(const string_t& path) = 0;
		virtual IEffect* CreateEffect(const string_t& path) = 0;
		virtual IMaterial* CreateMaterial(IEffect* effectPtr, uint materialId, MaterialFlags::Flags flags = MaterialFlags::NoFlags) = 0;
		virtual IDynamicGeometeryObject* CreateGraphicObject(IMaterialPtr pMaterial, const Polygon2d& geometry, const Rect& uv = Rect(0.0f, 0.0f, 1.0f, 1.0f), int z = 0) = 0;
		virtual IDynamicGeometeryObject* CreateGraphicObject(IMaterialPtr pMaterial, const Polygon2d& geometry, const vec2& tileMetrics = vec2(1.0f, 1.0f), int z = 0) = 0;
	};
	DEFPTR(IFactory);
}

#endif