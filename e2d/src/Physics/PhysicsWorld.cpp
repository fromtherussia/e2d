#include <Box2D/Box2D.h>

#include "PhysicsUtils.h"

#include "PhysicsWorld.h"

namespace air2d {
	namespace physics {
		// Public

		World::World(vec2 gravity, bool sleepWhenInactive) {
			m_pWorld = new b2World(ToBox2Vec(gravity), sleepWhenInactive);
		}
		
		World::~World() {
			delete m_pWorld;
		}

		void World::Simulate(float frameTime) {
			m_pWorld->Step(frameTime, 6, 2);
		}
	}
}