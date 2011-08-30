#include <assert.h>

#include <Box2D/Box2D.h>

#include <cgl/FrameTimeCounter.h>
#include <r2d/CompositeRenderable.h>

#include "PhysicsPrimitive.h"
#include "PhysicsWorld.h"

#include "EngineIEntity.h"
#include "EngineEntity.h"

#include "EngineScene.h"

namespace air2d {
	namespace engine {
		// Public

		Scene::Scene(const vec2& gravity):
			m_world(gravity) {
		}

		Scene::~Scene() {
			m_entities.clear();
		}

		void Scene::Render(r2d::IRenderContext& context, const r2d::ICamera& camera, bool isDebug) {
			// Calculating frame time
			static FrameTimeCounter counter;
			float lastFrameTime = counter.GetFrameTime() == 0.0f ? 1.0f / 60.0f : counter.GetFrameTime();
			lastFrameTime *= 2.0f;
			counter.BeginCounting();

			// Simulate physics
			m_world.Simulate(lastFrameTime);

			
			if (isDebug) {
				context.RenderWorldAxises(vec2(0.0f, 0.0f), 0.0f);
			}

			// Render graphics
			context.BeginScene();
			context.ApplyCamera(camera);
			for (size_t i = 0; i < m_entities.size(); ++i) {
				m_entities[i]->UpdatePosition();
				m_entities[i]->Render(context, isDebug);
			}
			context.RenderQueuedObjects(false);
			context.EndScene();

			counter.EndCounting();
		}

		Scene& Scene::operator << (IEntity* entityPtr) {
			m_entities.push_back(IEntityPtr(entityPtr));
			return *this;
		}
		
		// Factory interface
		
		StaticEntity* Scene::CreateStaticEntity(const vec2& initialPos, const string_t& primitiveMaterialName) {
			return new StaticEntity(
				new physics::Primitive(
					m_world,
					physics::Primitive::ptStatic,
					GetAttributes(primitiveMaterialName),
					physics::PrimitiveInitialMotion(initialPos)
				)
			);
		}

		KinematicEntity* Scene::CreateKinematicEntity(const vec2& initialPos, const string_t& primitiveMaterialName) {
			return new KinematicEntity(
				new physics::Primitive(
					m_world,
					physics::Primitive::ptKinematic,
					GetAttributes(primitiveMaterialName),
					physics::PrimitiveInitialMotion(initialPos)
				)
			);
		}

		DynamicEntity* Scene::CreateDynamicEntity(const vec2& initialPos, const string_t& primitiveMaterialName) {
			return new DynamicEntity(
				new physics::Primitive(
					m_world,
					physics::Primitive::ptDynamic,
					GetAttributes(primitiveMaterialName),
					physics::PrimitiveInitialMotion(initialPos)
				)
			);
		}

		// Private
		physics::PrimitiveAttributes Scene::GetAttributes(const string_t& primitiveMaterialName) const {
			// TODO:
			return physics::PrimitiveAttributes();
		}
	}
}