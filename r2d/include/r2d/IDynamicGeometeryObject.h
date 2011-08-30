#ifndef R2D_IGRAPHIC_OBJECT_H
#define R2D_IGRAPHIC_OBJECT_H

#include "Common.h"
#include "IRenderable.h"

namespace r2d {
	class IDynamicGeometeryObject: public IRenderable {
	public:
		IDynamicGeometeryObject(IMaterialPtr pMaterial): 
			IRenderable(pMaterial) {

		};
		virtual ~IDynamicGeometeryObject() {};

		// Geometry data access
		virtual Polygon2d& GetGeometry() = 0;
		virtual Rect& GetUv() = 0;
		virtual int& GetDepth() = 0;
		virtual void SynchronizeWithGpu(IRenderContext& context) = 0;
	};
	DEFPTR(IDynamicGeometeryObject);
}

#endif