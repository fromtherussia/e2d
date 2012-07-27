#ifndef R2D_D3D_FACTORY_H
#define R2D_D3D_FACTORY_H

#include "r2d/IFactory.h"

namespace r2d {
	class D3DFactory: public IFactory {
	public:
		D3DFactory(D3DRenderContext& renderContext);
		virtual ~D3DFactory();

		// Factory interface
		virtual std::auto_ptr<ICamera> CreateCamera(const Rect& visibleRect, float zNear, float zFar) const;
		virtual std::auto_ptr<ITexture> CreateTexture(const string_t& path) const;
		virtual std::auto_ptr<IEffect> CreateEffect(const string_t& path) const;
		virtual std::auto_ptr<IMaterial> CreateMaterial(std::auto_ptr<IEffect> effectPtr, uint materialId, MaterialFlags::Flags flags) const;
		virtual std::auto_ptr<IDynamicGeometeryObject> CreateGraphicObject(IMaterial& material, const Polygon2d& geometry, const Rect& uv, int z, const AnimationProperties& animationProperties) const;

	private:
		D3DRenderContext& m_renderContext;
	};
}

#endif