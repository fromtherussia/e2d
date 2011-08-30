#ifndef R2D_D3D_FACTORY_H
#define R2D_D3D_FACTORY_H

#include "IFactory.h"

namespace r2d {
	class D3DFactory: public IFactory {
	public:
		D3DFactory(D3DRenderContext& context);
		virtual ~D3DFactory();

		// Factory interface
		virtual ICamera* CreateCamera(const Rect& visibleRect, float zNear = 0.0f, float zFar = 1.0f);
		virtual ITexture* CreateTexture(const string_t& path);
		virtual IEffect* CreateEffect(const string_t& path);
		virtual IMaterial* CreateMaterial(IEffect* effectPtr, uint materialId, MaterialFlags::Flags flags = MaterialFlags::NoFlags);
		virtual IDynamicGeometeryObject* CreateGraphicObject(IMaterialPtr pMaterial, const Polygon2d& geometry, const Rect& uv = Rect(0.0f, 0.0f, 1.0f, 1.0f), int z = 0);
		virtual IDynamicGeometeryObject* CreateGraphicObject(IMaterialPtr pMaterial, const Polygon2d& geometry, const vec2& tileMetrics = vec2(1.0f, 1.0f), int z = 0);

	private:
		D3DRenderContext& m_context;
	};
	DEFPTR(D3DFactory);
}

#endif