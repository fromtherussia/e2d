#ifndef P2D_WORLD_H
#define P2D_WORLD_H

#include "p2d/Common.h"

namespace p2d {
	class World {
	public:
		World(const vec2& gravity, bool sleepWhenInactive = true);
		~World();
		void Simulate(float frameTime);

	private:
		std::auto_ptr<b2World> m_worldPtr;

		friend class IBody;
		friend class IJoint;
	};
}

#endif