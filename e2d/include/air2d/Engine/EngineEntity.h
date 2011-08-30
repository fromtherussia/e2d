#ifndef AIR2D_ENGINE_ENTITY_H
#define AIR2D_ENGINE_ENTITY_H

#include "EngineCommon.h"

namespace air2d {
	namespace physics {
		class IShape;
		PREDECL_CLASS_WITH_PTR(Primitive);
	}
	namespace engine {
		namespace EntityType {
			enum Type;
		}
		class IEntity;
		class IWithNamedPoints;
		/*
			Простая сущность, состоящая из нескольких примитивных форм.
			Соответствует физическому абсолютно жесткому (rigid) телу.
			За счет PrimitiveJoint может динамически соединяться с другими объектами.

			PrimitiveEntity - Статическая сущность.
			KinematicPrimitiveEntity - к PrimitiveEntity добавлена функциональность для использования в качестве кинетической.
			DynamicPrimitiveEntity - к KinematicPrimitiveEntity добавлена функциональность для использования в качестве динамической.
		*/
		class Entity: public IEntity, public IWithNamedPoints {
		public:
			Entity(EntityType::Type type, physics::Primitive* pPhysicsPrimitive);
			virtual ~Entity();
			// Добавление физического примитива
			void AddShape(physics::IShape* shape);
			void AddShape(r2d::IRenderable* shape, vec2 offset);
			void AddShape(physics::IShape* physShape, r2d::IRenderable* graphShape, vec2 offset);
		
			// TMP:
			virtual void Render(r2d::IRenderContext& context, bool isDebug) const;
			virtual void UpdatePosition();
		protected:
			virtual Rect GetGraphicBoundingBox();
			virtual Rect GetPhysicBoundingBox();
			
			// physics::Primitive& GetPhysicPrimitive();

		private:
			physics::PrimitivePtr m_pPhysicsPrimitive;
			r2d::CompositeRenderable m_graphicsPrimitive;

			friend class EntityJoint;
		};
		
		
		class StaticEntity: public Entity, public IStaticEntity {
		public:
			StaticEntity(physics::Primitive* pPhysicsPrimitive);
			virtual ~StaticEntity();
		};

		class KinematicEntity: public Entity, public IKinematicEntity {
		public:
			KinematicEntity(physics::Primitive* pPhysicsPrimitive);
			virtual ~KinematicEntity();
			// IKinematicEntity
			// Position
			virtual vec2 GetPosition();
			virtual bool SetPosition(const vec2& pos);
			virtual bool Move(const vec2& delta);
			// Angle
			virtual float GetAngle();
			virtual bool SetAngle(float angle);
			virtual bool Rotate(float delta);
		
		protected:
			virtual void UpdatePosition();
			virtual Rect GetGraphicBoundingBox();
		};
		
		class DynamicEntity: public Entity, public IDynamicEntity {
		public:
			DynamicEntity(physics::Primitive* pPhysicsPrimitive);
			virtual ~DynamicEntity();
			// IDynamicEntity
			// Interactions
			virtual bool ApplyForce(const vec2& pos, const vec2& force);
			virtual bool ApplyImpulse(const vec2& pos, const vec2& impulse);
		};
	}
}

#endif