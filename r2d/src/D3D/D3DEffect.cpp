#include "IRenderContext.h"

#include "D3DCommon.h"
#include "D3DUtils.h"
#include "D3DRenderContext.h"
#include "D3DTexture.h"
#include "D3DEffect.h"

namespace r2d {
	D3DEffect::D3DEffect(D3DRenderContext& context, const string_t& path) {
		ID3DXBuffer* pCompileErrorsBuffer;
		HRESULT creationResult = D3DXCreateEffectFromFileExA(
			context.GetDevice(),
			path.c_str(),
			NULL,
			NULL,
			NULL,
			0,
			NULL,
			&m_effect,
			&pCompileErrorsBuffer
		);

		if (creationResult != D3D_OK) {
			if (pCompileErrorsBuffer) {
				string_t exceptionMessage(static_cast<LPCSTR>(pCompileErrorsBuffer->GetBufferPointer()));
				pCompileErrorsBuffer->Release();
				throw std::logic_error(exceptionMessage);
			}
		}
	}

	D3DEffect::~D3DEffect() {
		m_effect->Release();
	}

	void D3DEffect::SetTextureParam(const string_t& paramName, ITexture* texturePtr) {
		D3DTexture* d3dTexturePtr = dynamic_cast<D3DTexture*>(texturePtr);
		if (m_effect->SetTexture(GetParamName(paramName).c_str(), d3dTexturePtr->GetTexture()) != D3D_OK) {
			throw std::runtime_error("can't set effect param");
		}
	}

	void D3DEffect::SetBoolParam(const string_t& paramName, bool paramValue) {
		if (m_effect->SetBool(GetParamName(paramName).c_str(), paramValue) != D3D_OK) {
			throw std::runtime_error("can't set effect param");
		}
	}

	void D3DEffect::SetIntParam(const string_t& paramName, int paramValue) {
		if (m_effect->SetInt(GetParamName(paramName).c_str(), paramValue) != D3D_OK) {
			throw std::runtime_error("can't set effect param");
		}
	}

	void D3DEffect::SetFloatParam(const string_t& paramName, float paramValue) {
		if (m_effect->SetFloat(GetParamName(paramName).c_str(), paramValue) != D3D_OK) {
			throw std::runtime_error("can't set effect param");
		}
	}

	void D3DEffect::SetMatrixParam(const string_t& paramName, const matrix44& paramValue) {
		D3DXMATRIX matrix = ToMatrixD3D(paramValue);
		if (m_effect->SetMatrix(GetParamName(paramName).c_str(), &matrix) != D3D_OK) {
			throw std::runtime_error("can't set effect param");
		}
	}

	bool D3DEffect::GetBoolParam(const string_t& paramName) {
		// TODO:
		return false;
	}

	int D3DEffect::GetIntParam(const string_t& paramName) {
		// TODO:
		return -1;
	}

	float D3DEffect::GetFloatParam(const string_t& paramName) {
		// TODO:
		return 0.0f;
	}

	matrix44 D3DEffect::GetMatrixParam(const string_t& paramName) {
		// TODO:
		return matrix44();
	}

	LPD3DXEFFECT D3DEffect::GetEffect() {
		return m_effect;
	}

	string_t D3DEffect::GetParamName(const string_t& paramName) {
		return "gmp_" + paramName;
	}
} 
