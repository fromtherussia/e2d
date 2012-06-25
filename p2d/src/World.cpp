#include <Box2D/Box2D.h>

#include "p2d/Utils.h"

#include "p2d/World.h"

namespace p2d {
	World::World(const vec2& gravity, bool sleepWhenInactive):
		m_worldPtr(new b2World(ToBox2Vec(gravity))) {
	}
	
	World::~World() {
	}

	void World::Simulate(float frameTime) {
		m_worldPtr->Step(frameTime, 6, 2);
	}
}