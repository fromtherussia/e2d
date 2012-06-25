/*#include <assert.h>

#include <Box2D/Box2D.h>

#include <cgl/Utils.h>
#include <cgl/FrameTimeCounter.h>
#include <r2d/IMaterial.h>
#include <r2d/IFactory.h>
#include <r2d/CompositeRenderable.h>*/

//#include <p2d/CompositeBody.h>
#include <r2d/IFactory.h>
#include <r2d/IRenderContext.h>

#include <p2d/World.h>

/*
#include "Engine/IEntityFactory.h"
#include "Engine/IGraphicMaterialTable.h"
#include "Engine/IPhysicMaterialTable.h"
#include "Engine/IResourceController.h"

#include "Engine/ComplexPhysicEntity.h"
*/
#include "e2d/Engine/IEntity.h"

#include "e2d/Engine/Scene.h"

namespace e2d {
	namespace engine {
		Scene::Scene(r2d::IRenderContext& renderContext, const vec2& gravity):
			m_renderContext(renderContext),
			m_world(gravity),
			m_graphicFactoryPtr(renderContext.GetFactory()) {
		}

		Scene::~Scene() {
			m_entities.clear();
		}

		void Scene::Render(const r2d::ICamera& camera, bool isDebug) {
			// Calculating frame time
			//static FrameTimeCounter counter;
			float lastFrameTime = 1.0f / 60.0f; //counter.GetFrameTime() == 0.0f ? 1.0f / 60.0f : counter.GetFrameTime();
			lastFrameTime *= 2.0f;
			//counter.BeginCounting();

			// Simulate physics
			m_world.Simulate(lastFrameTime);

			
			if (isDebug) {
				m_renderContext.RenderWorldAxises();
			}

			// Render graphics
			m_renderContext.BeginScene();
			m_renderContext.ApplyCamera(camera);
			for (size_t i = 0; i < m_entities.size(); ++i) {
				m_entities[i].UpdatePosition();
				m_entities[i].Render();
			}
			m_renderContext.RenderQueuedObjects(false);
			
			/*
			if (isDebug) {
				for (size_t i = 0; i < m_entities.size(); ++i) {
					m_entities[i].UpdatePosition();
					m_entities[i].Render(true);
				}
			}*/
			m_renderContext.EndScene();

			//counter.EndCounting();
		}

		Scene& Scene::operator << (std::auto_ptr<IEntity> entityPtr) {
			m_entities.push_back(entityPtr.release());
			return *this;
		}

		// Getting factories and material tables
		
		/*IEntityFactory* Scene::GetEntitiesFactory() {
			return this;
		}*/
		
		r2d::IFactory& Scene::GetGraphicObjectsFactory() {
			return *m_graphicFactoryPtr;
		}
		
		GraphicMaterialTable& Scene::GetGraphicMaterialTable() {
			return m_graphicMaterialTable;
		}
		
		PhysicMaterialTable& Scene::GetPhysicMaterialTable() {
			return m_physicMaterialTable;
		}
		
		
		// Factory interface

		/*ComplexPhysicEntity* Scene::CreateComplexPhysicEntity(const vec2& initialPos, p2d::IBody::Type type, const string_t& primitiveMaterialName) {
			return new ComplexPhysicEntity(
				new p2d::CompositeBody(m_world, type, GetAttributes(primitiveMaterialName), p2d::BodyInitialMotion(initialPos))
			);
		}*/

		
	}
}