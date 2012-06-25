#ifndef R2D_IMATERIAL_H
#define R2D_IMATERIAL_H

#include "r2d/Common.h"

namespace r2d {
	class IMaterial {
	public:
		IMaterial(uint materialId):
			m_materialId(materialId) {
		};
		virtual ~IMaterial() {
		};
		// Adding texture
		virtual void AddTexture(const string_t& textureName, std::auto_ptr<ITexture> texturePtr) = 0;
		// Unique material id
		int GetMaterialId() const {
			return m_materialId;
		};
		// Effect params
		virtual void SetBoolParam(const string_t& paramName, bool paramValue) = 0;
		virtual void SetIntParam(const string_t& paramName, int paramValue) = 0;
		virtual void SetFloatParam(const string_t& paramName, float paramValue) = 0;
		virtual void SetMatrixParam(const string_t& paramName, const matrix44& paramValue) = 0;
		virtual bool GetBoolParam(const string_t& paramName) const = 0;
		virtual int GetIntParam(const string_t& paramName) const = 0;
		virtual float GetFloatParam(const string_t& paramName) const = 0;
		virtual matrix44 GetMatrixParam(const string_t& paramName) const = 0;
	private:
		uint m_materialId;
	};
}

#endif