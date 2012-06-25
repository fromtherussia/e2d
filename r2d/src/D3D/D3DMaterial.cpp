#include <sstream>

#include "r2d/ITexture.h"
#include "r2d/IEffect.h"

#include "r2d/D3D/D3DCommon.h"
#include "r2d/D3D/D3DRenderContext.h"
#include "r2d/D3D/D3DTexture.h"
#include "r2d/D3D/D3DEffect.h"
#include "r2d/D3D/D3DMaterial.h"

namespace r2d {
	D3DMaterial::D3DMaterial(D3DRenderContext& renderContext, std::auto_ptr<D3DEffect> effectPtr, uint materialId, MaterialFlags::Flags flags):
		m_renderContext(renderContext),
		m_effectPtr(effectPtr),
		IMaterial(materialId),
		m_controlFlags(flags) {
	}

	D3DMaterial::~D3DMaterial() {

	}

	void D3DMaterial::AddTexture(const string_t& textureName, std::auto_ptr<ITexture> texturePtr) {
		ITexture* tmpTexturePtr = texturePtr.release();
		D3DTexture* tmpD3DTexturePtr = dynamic_cast<D3DTexture*>(tmpTexturePtr);
		CGL_CHECK(tmpD3DTexturePtr);
		m_effectPtr->SetTextureParam(textureName, tmpD3DTexturePtr);
		m_textures.push_back(tmpTexturePtr);
	}
	
	uint D3DMaterial::BeginPasses(const string_t& techniqueName) {
		LPDIRECT3DDEVICE9 d3dDevice = m_renderContext.GetDevice();

		uint passesCount;
		HRESULT result = m_effectPtr->GetEffect()->Begin(&passesCount, 0);
		if (result != D3D_OK) {
			return 0;
		}

		LPD3DXEFFECT effect = m_effectPtr->GetEffect();
		D3DXHANDLE techniqueHandle = effect->GetTechniqueByName(techniqueName.c_str());
		if (!effect->ValidateTechnique(techniqueHandle)) {
			return 0;
		}
		effect->SetTechnique(techniqueHandle);

		return passesCount;
	}

	bool D3DMaterial::BeginPass(uint passId) {
		m_effectPtr->GetEffect()->BeginPass(passId);
		return true;
	}

	bool D3DMaterial::EndPass() {
		m_effectPtr->GetEffect()->EndPass();
		return true;
	}

	bool D3DMaterial::EndPasses() {
		m_effectPtr->GetEffect()->End();
		return true;
	}

	bool D3DMaterial::SetMatrices() {
		LPDIRECT3DDEVICE9 d3dDevice = m_renderContext.GetDevice();
		D3DXMATRIXA16 world;

		d3dDevice->GetTransform(D3DTS_WORLD, &world);

		if (m_controlFlags & MaterialFlags::SetConstMatrixWorld) {
			m_effectPtr->GetEffect()->SetMatrix("gmp_world", &world);
		}

		if (m_controlFlags & MaterialFlags::SetConstMatrixView) {
			m_effectPtr->GetEffect()->SetMatrix("gmp_view", &world);
		}

		if (m_controlFlags & MaterialFlags::SetConstMatrixProjection) {
			m_effectPtr->GetEffect()->SetMatrix("gmp_projection", &world);
		}

		if (m_controlFlags & MaterialFlags::SetConstMatrixVP) {
			D3DXMATRIXA16 view;
			D3DXMATRIXA16 projection;
			d3dDevice->GetTransform(D3DTS_VIEW, &view);
			d3dDevice->GetTransform(D3DTS_PROJECTION, &projection);

			D3DXMATRIXA16 vp = view * projection;
			m_effectPtr->GetEffect()->SetMatrix("gmp_vp", &vp);
		}

		if (m_controlFlags & MaterialFlags::SetConstMatrixWVP) {
			D3DXMATRIXA16 view;
			D3DXMATRIXA16 projection;
			d3dDevice->GetTransform(D3DTS_VIEW, &view);
			d3dDevice->GetTransform(D3DTS_PROJECTION, &projection);

			D3DXMATRIXA16 mvp = world * view * projection;
			m_effectPtr->GetEffect()->SetMatrix("gmp_wvp", &mvp);
		}
		return true;
	}

	void D3DMaterial::SetBoolParam(const string_t& paramName, bool paramValue) {
		m_effectPtr->SetBoolParam(paramName, paramValue);
	}
	
	void D3DMaterial::SetIntParam(const string_t& paramName, int paramValue) {
		m_effectPtr->SetIntParam(paramName, paramValue);
	}
	
	void D3DMaterial::SetFloatParam(const string_t& paramName, float paramValue) {
		m_effectPtr->SetFloatParam(paramName, paramValue);
	}
	
	void D3DMaterial::SetMatrixParam(const string_t& paramName, const matrix44& paramValue) {
		m_effectPtr->SetMatrixParam(paramName, paramValue);
	}
	
	bool D3DMaterial::GetBoolParam(const string_t& paramName) const {
		return m_effectPtr->GetBoolParam(paramName);
	}
	
	int D3DMaterial::GetIntParam(const string_t& paramName) const {
		return m_effectPtr->GetIntParam(paramName);
	}
	
	float D3DMaterial::GetFloatParam(const string_t& paramName) const {
		return m_effectPtr->GetFloatParam(paramName);
	}
	
	matrix44 D3DMaterial::GetMatrixParam(const string_t& paramName) const {
		return m_effectPtr->GetMatrixParam(paramName);
	}
}