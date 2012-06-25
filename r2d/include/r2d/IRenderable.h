#ifndef R2D_IRENDERABLE_H
#define R2D_IRENDERABLE_H

#include "r2d/Common.h"

namespace r2d {
	/*
		Интерфейс объекта, который может быть добавлен
		в очередь объектов для рендеринга.

		Объекты в очереди сортируются сначала по альфа-каналу,
		выводятся в первую очередь объекты не имеющие альфа-канала,
		затем оставшиеся сортируются по глубине.

		Все выводимые объекты перед выводом сортируются по материалу.
	*/
	class IRenderable {
	public:
		IRenderable(IMaterial* materialPtr);
		virtual ~IRenderable() {};
		// Transformations
		virtual void ApplyTransformations() const = 0;
		virtual void IdentityTransformation() const = 0;
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
		virtual int GetMaterialId() const;
		IMaterial* GetMaterial() const {
			return m_materialPtr;
		}
		// Rendering
		virtual void AddToRenderQueue() const = 0;
		virtual void Render() const = 0;
		virtual void RenderWire() const = 0;

	protected:
		vec2 m_rotationOrigin;
		bool m_isRotationOriginSet;
		
	private:
		IMaterial* m_materialPtr;
	};
}

#endif