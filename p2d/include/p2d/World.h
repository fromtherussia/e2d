#ifndef P2D_WORLD_H
#define P2D_WORLD_H

#include "p2d/Common.h"

namespace p2d {
	class World {
	public:
		World(const vec2& gravity, bool sleepWhenInactive = true);
		~World();
		void Simulate(float frameTime);
		std::auto_ptr<CollisionListeners> QueryPrimitives(const Rect& rect, BodyKind::Kind kind) const;
		std::auto_ptr<RaycastIntersections> QueryPrimitives(const vec2& lineBegin, const vec2& lineEnd, BodyKind::Kind kind, bool findFirst = false) const;
	private:
		std::auto_ptr<b2World> m_worldPtr;

		friend class IBody;
		friend class IJoint;
	};
}

#endif