#include <assert.h>

#include "ICamera.h"
#include "ITexture.h"
#include "IEffect.h"
#include "IMaterial.h"
#include "IDynamicGeometeryObject.h"

#include "D3DCommon.h"
#include "D3DRenderContext.h"
#include "D3DCamera.h"
#include "D3DTexture.h"
#include "D3DEffect.h"
#include "D3DMaterial.h"
#include "D3DDynamicGeometeryObject.h"

#include "D3DFactory.h"

namespace r2d {
	D3DFactory::D3DFactory(D3DRenderContext& context):
		m_context(context) {

	}

	D3DFactory::~D3DFactory() {

	}
	
	// Factory interface
	
	ICamera* D3DFactory::CreateCamera(const Rect& visibleRect, float zNear, float zFar) {
		return new D3DCamera(visibleRect, zNear, zFar);
	}

	ITexture* D3DFactory::CreateTexture(const string_t& path) {
		return new D3DTexture(m_context, path);
	}

	IEffect* D3DFactory::CreateEffect(const string_t& path) {
		return new D3DEffect(m_context, path);
	}

	IMaterial* D3DFactory::CreateMaterial(IEffect* effectPtr, uint materialId, MaterialFlags::Flags flags) {
		return new D3DMaterial(dynamic_cast<D3DEffect*>(effectPtr), materialId, flags);
	}

	IDynamicGeometeryObject* D3DFactory::CreateGraphicObject(IMaterialPtr pMaterial, const Polygon2d& geometry, const Rect& uv, int z) {
		return new D3DDynamicGeometeryObject(pMaterial, m_context, geometry, uv, z);
	}

	IDynamicGeometeryObject* D3DFactory::CreateGraphicObject(IMaterialPtr pMaterial, const Polygon2d& geometry, const vec2& tileMetrics, int z) {
		return new D3DDynamicGeometeryObject(pMaterial, m_context, geometry, tileMetrics, z);
	}
}