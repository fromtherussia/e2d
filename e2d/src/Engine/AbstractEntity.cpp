#include <r2d/IRenderable.h>
#include <p2d/IBody.h>

#include "e2d/Engine/AbstractEntity.h"

namespace e2d {
	namespace engine {
		AbstractEntity::AbstractEntity(std::auto_ptr<r2d::IRenderable> graphicsPrimitivePtr, std::auto_ptr<p2d::IBody> physicsPrimitivePtr):
			IEntity(EntityType::etAbstract),
			m_graphicsPrimitivePtr(graphicsPrimitivePtr),
			m_physicsPrimitivePtr(physicsPrimitivePtr) {
			CGL_CHECK(m_graphicsPrimitivePtr.get());
			CGL_CHECK(m_physicsPrimitivePtr.get());
		}

		AbstractEntity::~AbstractEntity() {
		}

		void AbstractEntity::UpdatePosition() {
			m_graphicsPrimitivePtr->SetTransformations(
				m_physicsPrimitivePtr->GetPosition(),
				m_physicsPrimitivePtr->GetAngle()
			);
		}
		
		vec2 AbstractEntity::GetPosition() const {
			return m_physicsPrimitivePtr->GetPosition();
		}
		
		float AbstractEntity::GetAngle() const {
			return m_physicsPrimitivePtr->GetAngle();
		}
		
		vec2 AbstractEntity::GetLinearVelocity() const {
			return m_physicsPrimitivePtr->GetLinearVelocity();
		}
		
		float AbstractEntity::GetAngularVelocity() const {
			return m_physicsPrimitivePtr->GetAngularVelocity();
		}

		void AbstractEntity::SetPosition(const vec2& pos) {
			return m_physicsPrimitivePtr->SetPosition(pos);
		}
		
		void AbstractEntity::Move(const vec2& delta) {
			return m_physicsPrimitivePtr->Move(delta);
		}
		
		void AbstractEntity::SetAngle(float angle) {
			return m_physicsPrimitivePtr->SetAngle(angle);
		}

		void AbstractEntity::Rotate(float delta) {
			return m_physicsPrimitivePtr->Rotate(delta);
		}

		void AbstractEntity::ApplyForce(const vec2& pos, const vec2& force) {
			return m_physicsPrimitivePtr->ApplyForce(pos, force);
		}
		
		void AbstractEntity::ApplyImpulse(const vec2& pos, const vec2& impulse) {
			return m_physicsPrimitivePtr->ApplyImpulse(pos, impulse);
		}

		Rect AbstractEntity::GetGraphicBoundingBox() const {
			return m_graphicsPrimitivePtr->GetBoundingRect();
		}

		Rect AbstractEntity::GetPhysicBoundingBox() const {
			// TODO:
			return Rect();
		}

		void AbstractEntity::Render() const {
			m_graphicsPrimitivePtr->AddToRenderQueue();
		}
	}
}