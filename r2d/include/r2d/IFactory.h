#ifndef R2D_IFACTORY_H
#define R2D_IFACTORY_H

#include "r2d/Common.h"

namespace r2d {
	class IFactory {
	public:
		IFactory() {};
		virtual ~IFactory() {};
		// Factory interface
		virtual std::auto_ptr<ICamera> CreateCamera(const Rect& visibleRect, float zNear = 0.0f, float zFar = 1.0f) const = 0;
		virtual std::auto_ptr<ITexture> CreateTexture(const string_t& path) const = 0;
		virtual std::auto_ptr<IEffect> CreateEffect(const string_t& path) const = 0;
		virtual std::auto_ptr<IMaterial> CreateMaterial(std::auto_ptr<IEffect> effectPtr, uint materialId, MaterialFlags::Flags flags = MaterialFlags::NoFlags) const = 0;
		virtual std::auto_ptr<IDynamicGeometeryObject> CreateGraphicObject(IMaterial& material, const Polygon2d& geometry, const Rect& uv = Rect(0.0f, 0.0f, 1.0f, 1.0f), int z = 0, const AnimationProperties& animationProperties = AnimationProperties()) const = 0;
	};
}

#endif