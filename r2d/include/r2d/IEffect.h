#ifndef R2D_IEFFECT_H
#define R2D_IEFFECT_H

#include "Common.h"

namespace r2d {
	class IEffect {
	public:
		IEffect() {};
		virtual ~IEffect() {};
		
		// Effect params
		virtual void SetTextureParam(const string_t& paramName, ITexture* texturePtr) = 0;
		virtual void SetBoolParam(const string_t& paramName, bool paramValue) = 0;
		virtual void SetIntParam(const string_t& paramName, int paramValue) = 0;
		virtual void SetFloatParam(const string_t& paramName, float paramValue) = 0;
		virtual void SetMatrixParam(const string_t& paramName, const matrix44& paramValue) = 0;
		virtual bool GetBoolParam(const string_t& paramName) = 0;
		virtual int GetIntParam(const string_t& paramName) = 0;
		virtual float GetFloatParam(const string_t& paramName) = 0;
		virtual matrix44 GetMatrixParam(const string_t& paramName) = 0;

	};
	DEFPTR(IEffect);
};

#endif