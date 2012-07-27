#ifndef R2D_IGRAPHIC_OBJECT_H
#define R2D_IGRAPHIC_OBJECT_H

#include "r2d/IRenderable.h"

namespace r2d {
	class IDynamicGeometeryObject: public IRenderable {
	public:
		IDynamicGeometeryObject(IMaterial& material): 
			IRenderable(material) {
		};
		virtual ~IDynamicGeometeryObject() {};
		// Geometry data access
		virtual Polygon2d& GetGeometry() = 0;
		virtual Rect& GetUv() = 0;
		virtual int& GetDepth() = 0;
		virtual void SynchronizeWithGpu() = 0;
		// Animation
		virtual void StartAnimation() = 0;
		virtual void StopAnimation() = 0;
		virtual void PauseAnimation() = 0;
		virtual void UnpauseAnimation() = 0;
		virtual bool IsAnimationRunning() const = 0;
	};
}

#endif