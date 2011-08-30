#ifndef R2D_IRENDERABLE_H
#define R2D_IRENDERABLE_H

#include "Common.h"

namespace r2d {
	/*
		Интерфейс объекта, который может быть добавлен
		в очередь объектов для рендеринга.

		Объекты в очереди сортируются сначала по альфа-каналу,
		выводятся в первую очередь объекты не имеющие альфа-канала,
		затем оставшиеся сортируются по глубине.

		Все выводимые объекты перед выводом сортируются по материалу.
	*/
	class IRenderContext;
	PREDECL_CLASS_WITH_PTR(IMaterial);
	
	class IRenderable {
	public:
		IRenderable(const IMaterialPtr& pMaterial);
		virtual ~IRenderable() {};
		const IMaterial* GetMaterial() const;
		// Transformations
		virtual void ApplyTransformations(IRenderContext& context) const = 0;
		virtual void IdentityTransformation(IRenderContext& context) const = 0;
		virtual void SetTransformations(const vec2& position, float angle) = 0;
		virtual void SetPosition(const vec2& position) = 0;
		virtual vec2 GetPosition() const = 0;
		virtual void SetRotation(float angle) = 0;
		virtual float GetRotation() const = 0;
		void SetRotationOrigin(const vec2& rotationOrigin);
		vec2 GetRotationOrigin() const;
		virtual void ResetTransformations() = 0;
		// Invisible objects optimization
		virtual Rect GetBoundingRect() const = 0;
		// Sorting
		virtual bool HasAlpha() const = 0;
		virtual int GetZ() const = 0;
		virtual int GetMaterialId() const = 0;
		// Rendering
		virtual void Render(IRenderContext& context) const = 0;
		virtual void RenderWire(IRenderContext& context) const = 0;

	protected:
		vec2 m_rotationOrigin;
		bool m_isRotationOriginSet;
		
	private:
		IMaterialPtr m_pMaterial;
	};
	DEFPTR(IRenderable);
}

#endif