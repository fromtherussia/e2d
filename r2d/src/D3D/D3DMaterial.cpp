#include <sstream>

#include "ITexture.h"
#include "IEffect.h"

#include "D3DCommon.h"
#include "D3DRenderContext.h"
#include "D3DTexture.h"
#include "D3DEffect.h"
#include "D3DMaterial.h"

namespace r2d
{
	D3DMaterial::D3DMaterial(D3DEffect* effectPtr, uint materialId, MaterialFlags::Flags flags):
		IMaterial(materialId),
		m_effect(effectPtr),
		m_controlFlags(flags) {
	}

	D3DMaterial::~D3DMaterial() {

	}

	void D3DMaterial::AddTexture(const string_t& textureName, ITexture* texturePtr) {
		m_effect->SetTextureParam(textureName, texturePtr);
		m_textures.push_back(ITexturePtr(texturePtr));
	}
	
	uint D3DMaterial::BeginPasses(D3DRenderContext& context, const string_t& techniqueName) {
		LPDIRECT3DDEVICE9& d3dDevice = context.GetDevice();

		uint passesCount;
		HRESULT result = m_effect->GetEffect()->Begin(&passesCount, 0);
		if (result != D3D_OK) {
			return 0;
		}

		LPD3DXEFFECT effect = m_effect->GetEffect();
		D3DXHANDLE techniqueHandle = effect->GetTechniqueByName(techniqueName.c_str());
		if (!effect->ValidateTechnique(techniqueHandle)) {
			return 0;
		}
		effect->SetTechnique(techniqueHandle);

		return passesCount;
	}

	bool D3DMaterial::BeginPass(uint passId) {
		m_effect->GetEffect()->BeginPass(passId);
		return true;
	}

	bool D3DMaterial::EndPass() {
		m_effect->GetEffect()->EndPass();
		return true;
	}

	bool D3DMaterial::EndPasses() {
		m_effect->GetEffect()->End();
		return true;
	}

	bool D3DMaterial::SetMatrices(D3DRenderContext& context) {
		LPDIRECT3DDEVICE9& d3dDevice = context.GetDevice();
		D3DXMATRIXA16 world;

		d3dDevice->GetTransform(D3DTS_WORLD, &world);

		if (m_controlFlags & MaterialFlags::SetConstMatrixWorld) {
			m_effect->GetEffect()->SetMatrix("gmp_world", &world);
		}

		if (m_controlFlags & MaterialFlags::SetConstMatrixWVP) {
			D3DXMATRIXA16 view;
			D3DXMATRIXA16 projection;
			d3dDevice->GetTransform(D3DTS_VIEW, &view);
			d3dDevice->GetTransform(D3DTS_PROJECTION, &projection);

			D3DXMATRIXA16 mvp = world * view * projection;
			m_effect->GetEffect()->SetMatrix("gmp_wvp", &mvp);
		}
		return true;
	}
} 
