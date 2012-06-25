#ifndef R2D_D3D_MATERIAL_H
#define R2D_D3D_MATERIAL_H

#include "r2d/IMaterial.h"

namespace r2d {
	class D3DMaterial: public IMaterial {
	public:
		D3DMaterial(D3DRenderContext& renderContext, std::auto_ptr<D3DEffect> effectPtr, uint materialId, MaterialFlags::Flags flags = MaterialFlags::NoFlags);
		virtual ~D3DMaterial();

		// Adding texture
		virtual void AddTexture(const string_t& textureName, std::auto_ptr<ITexture> texturePtr);
		
		// Returns number of passes
		uint BeginPasses(const string_t& techniqueName);
		bool BeginPass(uint passId);
		bool EndPass();
		bool EndPasses();
		bool SetMatrices();

		// Material params
		virtual void SetBoolParam(const string_t& paramName, bool paramValue);
		virtual void SetIntParam(const string_t& paramName, int paramValue);
		virtual void SetFloatParam(const string_t& paramName, float paramValue);
		virtual void SetMatrixParam(const string_t& paramName, const matrix44& paramValue);
		virtual bool GetBoolParam(const string_t& paramName) const;
		virtual int GetIntParam(const string_t& paramName) const;
		virtual float GetFloatParam(const string_t& paramName) const;
		virtual matrix44 GetMatrixParam(const string_t& paramName) const;

	private:
		bool SetTextures();

		D3DRenderContext& m_renderContext;
		boost::ptr_vector<ITexture> m_textures;
		std::auto_ptr<D3DEffect> m_effectPtr;
		MaterialFlags::Flags m_controlFlags;
	};
}

#endif 
