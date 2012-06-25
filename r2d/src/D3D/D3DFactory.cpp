#include <assert.h>

#include <cgl/ITimer.h>
#include <cgl/FrameCounter.h>

#include "r2d/ICamera.h"
#include "r2d/ITexture.h"
#include "r2d/IEffect.h"
#include "r2d/IMaterial.h"
#include "r2d/IDynamicGeometeryObject.h"

#include "r2d/D3D/D3DCommon.h"
#include "r2d/D3D/D3DRenderContext.h"
#include "r2d/D3D/D3DCamera.h"
#include "r2d/D3D/D3DTexture.h"
#include "r2d/D3D/D3DEffect.h"
#include "r2d/D3D/D3DMaterial.h"
#include "r2d/D3D/D3DDynamicGeometeryObject.h"

#include "r2d/D3D/D3DFactory.h"

namespace r2d {
	D3DFactory::D3DFactory(D3DRenderContext& renderContext):
		m_renderContext(renderContext) {
	}

	D3DFactory::~D3DFactory() {

	}
	
	// Factory interface
	
	std::auto_ptr<ICamera> D3DFactory::CreateCamera(const Rect& visibleRect, float zNear, float zFar) const {
		return std::auto_ptr<ICamera>(new D3DCamera(visibleRect, zNear, zFar));
	}

	std::auto_ptr<ITexture> D3DFactory::CreateTexture(const string_t& path) const {
		return std::auto_ptr<ITexture>(new D3DTexture(m_renderContext, path));
	}

	std::auto_ptr<IEffect> D3DFactory::CreateEffect(const string_t& path) const {
		return std::auto_ptr<IEffect>(new D3DEffect(m_renderContext, path));
	}

	std::auto_ptr<IMaterial> D3DFactory::CreateMaterial(std::auto_ptr<IEffect> effectPtr, uint materialId, MaterialFlags::Flags flags) const {
		return std::auto_ptr<IMaterial>(
			new D3DMaterial(m_renderContext, dynamic_auto_ptr_cast<D3DEffect>(effectPtr), materialId, flags)
		);
	}

	std::auto_ptr<IDynamicGeometeryObject> D3DFactory::CreateGraphicObject(IMaterial* materialPtr, const Polygon2d& geometry, const Rect& uv, int z, const AnimationProperties& animationProperties) const {
		return std::auto_ptr<IDynamicGeometeryObject>(
			new D3DDynamicGeometeryObject(
				m_renderContext, materialPtr, geometry, uv, z, animationProperties
			)
		);
	}
}