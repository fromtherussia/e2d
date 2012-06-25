#include "r2d/IRenderContext.h"

#include "r2d/D3D/D3DCommon.h"
#include "r2d/D3D/D3DUtils.h"
#include "r2d/D3D/D3DRenderContext.h"
#include "r2d/D3D/D3DTexture.h"
#include "r2d/D3D/D3DEffect.h"

namespace r2d {
	D3DEffect::D3DEffect(D3DRenderContext& renderContext, const string_t& path) {
		ID3DXBuffer* compileErrorsBufferPtr;
		HRESULT creationResult = D3DXCreateEffectFromFileExA(
			renderContext.GetDevice(),
			path.c_str(),
			NULL,
			NULL,
			NULL,
			0,
			NULL,
			&m_effect,
			&compileErrorsBufferPtr
		);

		if (creationResult != D3D_OK) {
			if (compileErrorsBufferPtr) {
				string_t exceptionMessage(static_cast<LPCSTR>(compileErrorsBufferPtr->GetBufferPointer()));
				compileErrorsBufferPtr->Release();
				throw std::logic_error(exceptionMessage);
			}
		}
	}

	D3DEffect::~D3DEffect() {
		m_effect->Release();
	}

	void D3DEffect::SetTextureParam(const string_t& paramName, D3DTexture* texturePtr) {
		CGL_CHECK(m_effect->SetTexture(GetParamName(paramName).c_str(), texturePtr->GetTexture()) != D3D_OK);
	}

	void D3DEffect::SetBoolParam(const string_t& paramName, bool paramValue) {
		CGL_CHECK(m_effect->SetBool(GetParamName(paramName).c_str(), paramValue) != D3D_OK);
	}

	void D3DEffect::SetIntParam(const string_t& paramName, int paramValue) {
		CGL_CHECK(m_effect->SetInt(GetParamName(paramName).c_str(), paramValue) != D3D_OK);
	}

	void D3DEffect::SetFloatParam(const string_t& paramName, float paramValue) {
		CGL_CHECK(m_effect->SetFloat(GetParamName(paramName).c_str(), paramValue) != D3D_OK);
	}

	void D3DEffect::SetMatrixParam(const string_t& paramName, const matrix44& paramValue) {
		D3DXMATRIX matrix = ToMatrixD3D(paramValue);
		CGL_CHECK(m_effect->SetMatrix(GetParamName(paramName).c_str(), &matrix) != D3D_OK);
	}

	bool D3DEffect::GetBoolParam(const string_t& paramName) const {
		// TODO:
		return false;
	}

	int D3DEffect::GetIntParam(const string_t& paramName) const {
		// TODO:
		return -1;
	}

	float D3DEffect::GetFloatParam(const string_t& paramName) const {
		// TODO:
		return 0.0f;
	}

	matrix44 D3DEffect::GetMatrixParam(const string_t& paramName) const {
		// TODO:
		return matrix44();
	}

	LPD3DXEFFECT D3DEffect::GetEffect() {
		return m_effect;
	}

	string_t D3DEffect::GetParamName(const string_t& paramName) const {
		return "gmp_" + paramName;
	}
} 
