#ifndef R2D_D3D_MATERIAL_H
#define R2D_D3D_MATERIAL_H

#include "IMaterial.h"

namespace r2d {
	class D3DMaterial: public IMaterial {
	public:
		D3DMaterial(D3DEffect* effectPtr, uint materialId, MaterialFlags::Flags flags = MaterialFlags::NoFlags);
		virtual ~D3DMaterial();

		// Adding texture
		virtual void AddTexture(const string_t& textureName, ITexture* texturePtr);
		
		// Returns number of passes
		uint BeginPasses(D3DRenderContext& context, const string_t& techniqueName);
		bool BeginPass(uint passId);
		bool EndPass();
		bool EndPasses();
		bool SetMatrices(D3DRenderContext& context);

	private:
		bool SetTextures();

		std::vector<ITexturePtr> m_textures;
		D3DEffectPtr m_effect;
		MaterialFlags::Flags m_controlFlags;
	};
	DEFPTR(D3DMaterial);
}

#endif 
