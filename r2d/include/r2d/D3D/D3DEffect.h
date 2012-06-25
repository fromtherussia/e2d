#ifndef R2D_D3D_EFFECT_H
#define R2D_D3D_EFFECT_H

#include "r2d/IEffect.h"

namespace r2d {
	class D3DEffect: public IEffect {
	public:
		D3DEffect(D3DRenderContext& renderContext, const string_t& path);
		virtual ~D3DEffect();
		
		// Effect params
		virtual void SetBoolParam(const string_t& paramName, bool paramValue);
		virtual void SetIntParam(const string_t& paramName, int paramValue);
		virtual void SetFloatParam(const string_t& paramName, float paramValue);
		virtual void SetMatrixParam(const string_t& paramName, const matrix44& paramValue);
		virtual bool GetBoolParam(const string_t& paramName) const;
		virtual int GetIntParam(const string_t& paramName) const;
		virtual float GetFloatParam(const string_t& paramName) const;
		virtual matrix44 GetMatrixParam(const string_t& paramName) const;

	private:
		void SetTextureParam(const string_t& paramName, D3DTexture* texturePtr);
		string_t GetParamName(const string_t& paramName) const;
		LPD3DXEFFECT GetEffect();

		LPD3DXEFFECT m_effect;
		D3DEffect(const D3DEffect&);

		friend class D3DTexture;
		friend class D3DMaterial;
	};
};

#endif 
