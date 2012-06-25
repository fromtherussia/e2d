#ifndef E2D_ENGINE_ABSTRACT_ENTITY_H
#define E2D_ENGINE_ABSTRACT_ENTITY_H

#include "e2d/Engine/IEntity.h"

namespace e2d {
	namespace engine {
		/*
			Обобщенная сущность, содержащая физику, графику, звук.
		*/
		class AbstractEntity: public IEntity, public IPhysicEntity {
		public:
			AbstractEntity(std::auto_ptr<r2d::IRenderable> graphicsPrimitivePtr, std::auto_ptr<p2d::IBody> physicsPrimitivePtr);
			virtual ~AbstractEntity();
			// IEntity
			virtual void SetPosition(const vec2& pos);
			virtual vec2 GetPosition() const;
			virtual void Move(const vec2& delta);
			virtual float GetAngle() const;
			virtual void SetAngle(float angle);
			virtual void Rotate(float delta);

			// IPhysicEntity
			// Static
			virtual vec2 GetLinearVelocity() const;
			virtual float GetAngularVelocity() const;
			// Dynamic
			virtual void ApplyForce(const vec2& pos, const vec2& force);
			virtual void ApplyImpulse(const vec2& pos, const vec2& impulse);

		protected:
			// IEntity
			virtual void UpdatePosition();
			virtual Rect GetGraphicBoundingBox() const;
			virtual Rect GetPhysicBoundingBox() const;
			virtual void Render() const;

		private:
			std::auto_ptr<p2d::IBody> m_physicsPrimitivePtr;
			std::auto_ptr<r2d::IRenderable> m_graphicsPrimitivePtr;
		};
	}
}

#endif