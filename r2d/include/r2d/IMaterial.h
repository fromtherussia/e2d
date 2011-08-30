#ifndef R2D_IMATERIAL_H
#define R2D_IMATERIAL_H

#include "Common.h"

namespace r2d {
	class MaterialFlags {
	public:
		enum Flags {
			NoFlags = 0x0000,
			SetConstMatrixWorld = 0x0001,
			SetConstMatrixView = 0x0002,
			SetConstMatrixProjection = 0x0004,
			SetConstMatrixWVP = 0x0008,
			SetConstMatrixVP = 0x0010
		};
	};

	PREDECL_CLASS_WITH_PTR(ITexture);
	PREDECL_CLASS_WITH_PTR(IEffect);

	class IMaterial {
	public:
		IMaterial(uint materialId):
			m_materialId(materialId) {
		}

		virtual ~IMaterial() {
		}

		// Adding texture
		virtual void AddTexture(const string_t& textureName, ITexture* texturePtr) = 0;
		
		// Unique material id
		int GetMaterialId() const {
			return m_materialId;
		}

	private:
		uint m_materialId;
	};
	DEFPTR(IMaterial);
}

#endif