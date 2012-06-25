#include <Box2D/Box2D.h>

#include <cgl/MathTypes.h>

#include <r2d/CompositeRenderable.h>

#include <p2d/IPrimitive.h>
#include <p2d/IShape.h>
#include <p2d/PolygonShape.h>
#include <p2d/SimplePrimitive.h>
#include <p2d/World.h>

//KILLME
#include <r2d/ITexture.h>
#include <r2d/IEffect.h>
#include <r2d/IMaterial.h>
#include <r2d/IFactory.h>
#include <r2d/IDynamicGeometeryObject.h>
#include <r2d/CompositeRenderable.h>

#include "Engine/IPolygonDestructor.h"
#include "Engine/SimplePolygonDestructor.h"

#include "Engine/IGraphicMaterialTable.h"
#include "Engine/IPhysicMaterialTable.h"
#include "Engine/IEntityFactory.h"
#include "Engine/IResourceController.h"

//KILLME

#include "Engine/Common.h"
#include "Engine/IEntity.h"
#include "Engine/ComplexPhysicEntity.h"
#include "Engine/DestructibleEntity.h"

namespace e2d {
	namespace engine {

		DestructibleEntity::DestructibleEntity(
			p2d::World& world,
			IResourceController* resourceController,
			const string_t& graphicMaterialName,
			const string_t& physicMaterialName,
			const Polygon2d& geometry,
			const vec2& origin,
			float z,
			const Rect& uv
		):
			IEntity(EntityType::etComplex),
			m_world(world),
			m_isDestructed(false),
			m_sourceGeometry(geometry),
			m_pResourceController(resourceController),
			m_graphicMaterialName(graphicMaterialName),
			m_physicMaterialName(physicMaterialName),
			m_z(z),
			m_uv(uv) {
			AddPhysicShape(geometry, p2d::BodyInitialMotion(origin));
			AddGraphicShape(geometry, uv);
		}

		DestructibleEntity::~DestructibleEntity() {
		}

		void DestructibleEntity::Destruct() {
			if (m_isDestructed) {
				return;
			}
			assert(m_physicPrimitives.size() == 1);

			// Getting initial motion params
			p2d::SimplePrimitivePtr& pSourcePrimitive = m_physicPrimitives[0];
			vec2 origin = pSourcePrimitive->GetPosition();
			float angle = pSourcePrimitive->GetAngle();
			vec2 linearVelocity = pSourcePrimitive->GetLinearVelocity();
			float angularVelocity = pSourcePrimitive->GetAngularVelocity();
			
			// Geometry destruction
			Rect sourceGeometryBoundingRect = m_sourceGeometry.GetBoundingRect();
			std::vector<Polygon2d> polygonParts;
			SimplePolygonDestructor().Destruct(m_sourceGeometry, vec2(), vec2(), polygonParts);
			
			// Removing old primitives
			m_graphicPrimitives.clear();
			m_physicPrimitives.clear();
			
			// Adding new primitives
			for (size_t i = 0; i < polygonParts.size(); ++i) {
				Rect polygonPartBoundingRect = polygonParts[i].GetBoundingRect();
				AddPhysicShape(
					polygonParts[i],
					p2d::BodyInitialMotion(polygonParts[i].Center() + origin, angle, linearVelocity, angularVelocity)
				);
				AddGraphicShape(
					polygonParts[i],
					CalculateInnerUvForInnerRect(
						sourceGeometryBoundingRect,
						polygonPartBoundingRect,
						m_uv
					)
				);
			}
			m_isDestructed = true;
		}

		void DestructibleEntity::UpdatePosition() {
			for (size_t i = 0; i < m_physicPrimitives.size(); ++i) {
				p2d::SimplePrimitivePtr& physicPrimitive = m_physicPrimitives[i];
				m_graphicPrimitives[i]->SetTransformations(
					physicPrimitive->GetPosition(),
					physicPrimitive->GetAngle()
				);
			}
		}

		void DestructibleEntity::AddPhysicShape(const Polygon2d& geometry, const p2d::BodyInitialMotion& initialMotion) {
			p2d::MaterialPtr pMaterial = m_pResourceController->GetPhysicMaterialTable()->GetPhysicMaterial(m_physicMaterialName);
			m_physicPrimitives.push_back(
				p2d::SimplePrimitivePtr(
					new p2d::SimpleBody(
						m_world,
						new p2d::PolygonShape(geometry, *pMaterial),
						p2d::IBody::ptDynamic,
						*pMaterial,
						initialMotion
					)
				)
			);
		}
		
		void DestructibleEntity::AddGraphicShape(const Polygon2d& geometry, const Rect& uv) {
			m_graphicPrimitives.push_back(
				r2d::IRenderablePtr(
					m_pResourceController->GetGraphicObjectsFactory()->CreateGraphicObject(
						m_pResourceController->GetGraphicMaterialTable()->GetGraphicMaterial(m_graphicMaterialName),
						geometry,
						uv
					)
				)
			);
		}

		Rect DestructibleEntity::GetGraphicBoundingBox() {
			return Rect();
		}

		Rect DestructibleEntity::GetPhysicBoundingBox() {
			return Rect();
		}

		void DestructibleEntity::Render(r2d::IRenderContext& context, bool isDebug) const {
			for (size_t i = 0; i < m_graphicPrimitives.size(); ++i) {
				if (isDebug) {
					m_physicPrimitives[i]->DebugRender(context);
				} else {
					context.AddToRenderingQueue(m_graphicPrimitives[i].get());
				}
			}
		}

		Rect DestructibleEntity::CalculateInnerUvForInnerRect(const Rect& outerRect, const Rect& innerRect, const Rect& outerUv) {
			float uScale1 = (innerRect.x1 - outerRect.x1) / outerRect.Width();
			float vScale1 = (innerRect.y1 - outerRect.y1) / outerRect.Height();
			float uScale2 = (innerRect.x2 - outerRect.x1) / outerRect.Width();
			float vScale2 = (innerRect.y2 - outerRect.y1) / outerRect.Height();
			
			return Rect(
				outerUv.x1 + uScale1 * outerUv.Width(),
				outerUv.y1 + vScale1 * outerUv.Height(),
				outerUv.x1 + uScale2 * outerUv.Width(),
				outerUv.y1 + vScale2 * outerUv.Height()
			);
		}

	}
}