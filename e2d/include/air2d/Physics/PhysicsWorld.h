#ifndef AIR2D_PHYSICS_WORLD_H
#define AIR2D_PHYSICS_WORLD_H

#include "PhysicsCommon.h"

namespace air2d {
	namespace physics {
		class World {
		public:
			World(vec2 gravity, bool sleepWhenInactive = true);
			~World();
			void Simulate(float frameTime);

		private:
			RESTRICT_COPY_CTOR(World);
			RESTRICT_ASSIGN_OPERATOR(World);

			b2World* m_pWorld;

			friend class Primitive;
			friend class IJoint;
		};
	}
}

#endif