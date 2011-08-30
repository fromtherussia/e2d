#include <assert.h>

#include <Box2D/Box2D.h>

#include <r2d/IRenderable.h>
#include <r2d/CompositeRenderable.h>

#include "PhysicsIShape.h"
#include "PhysicsPrimitive.h"

#include "EngineIEntity.h"
#include "EngineEntity.h"

namespace air2d {
	namespace engine {
		// Entity
		// Public

		Entity::Entity(EntityType::Type type, physics::Primitive* pPhysicsPrimitive):
			IEntity(type),
			m_pPhysicsPrimitive(physics::PrimitivePtr(pPhysicsPrimitive)) {
		}

		Entity::~Entity() {
		}

		void Entity::AddShape(physics::IShape* shape) {
			*m_pPhysicsPrimitive << shape;
		}

		void Entity::AddShape(r2d::IRenderable* shape, vec2 offset) {
			// TODO: support graphics
			m_graphicsPrimitive.AddRenderable(shape, offset);
		}

		void Entity::AddShape(physics::IShape* physShape, r2d::IRenderable* graphShape, vec2 offset) {
			// TODO: support graphics
			*m_pPhysicsPrimitive << physShape;
			m_graphicsPrimitive.AddRenderable(graphShape, offset);
		}

		// Protected

		void Entity::UpdatePosition() {
			m_graphicsPrimitive.SetTransformations(
				m_pPhysicsPrimitive->GetPosition(),
				m_pPhysicsPrimitive->GetAngle()
			);
		}

		Rect Entity::GetGraphicBoundingBox() {
			return Rect();
		}

		Rect Entity::GetPhysicBoundingBox() {
			return Rect();
		}

		void Entity::Render(r2d::IRenderContext& context, bool isDebug) const {
			m_graphicsPrimitive.Render(context);
			if (isDebug) {
				//m_pPhysicsPrimitive->DebugRender(context);
			}
		}

		// StaticEntity
		// Public

		StaticEntity::StaticEntity(physics::Primitive* pPhysicsPrimitive):
			Entity(EntityType::etStatic, pPhysicsPrimitive) {
		}

		StaticEntity::~StaticEntity() {

		}

		// KinematicEntity
		// Public		
		
		KinematicEntity::KinematicEntity(physics::Primitive* pPhysicsPrimitive):
			Entity(EntityType::etKinematic, pPhysicsPrimitive) {

		}

		KinematicEntity::~KinematicEntity() {

		}
	
		// Position
	
		vec2 KinematicEntity::GetPosition() {
			return vec2();
		}

		bool KinematicEntity::SetPosition(const vec2& pos) {
			return true;
		}
		
		bool KinematicEntity::Move(const vec2& delta) {
			return true;
		}
		
		float KinematicEntity::GetAngle() {
			return 0.0f;
		}

		bool KinematicEntity::SetAngle(float angle) {
			return true;
		}

		bool KinematicEntity::Rotate(float delta) {
			return true;
		}

		// Protected

		void KinematicEntity::UpdatePosition() {

		}

		Rect KinematicEntity::GetGraphicBoundingBox() {
			return Rect();
		}
		
		// DynamicEntity
		// Public
		
		DynamicEntity::DynamicEntity(physics::Primitive* pPhysicsPrimitive):
			Entity(EntityType::etDynamic, pPhysicsPrimitive) {
		}

		DynamicEntity::~DynamicEntity() {
		}
		
		// Interactions

		bool DynamicEntity::ApplyForce(const vec2& pos, const vec2& force) {
			return true;
		}

		bool DynamicEntity::ApplyImpulse(const vec2& pos, const vec2& impulse) {
			return true;
		}
	}
}