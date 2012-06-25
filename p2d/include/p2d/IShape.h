#ifndef P2D_ISHAPE_H
#define P2D_ISHAPE_H

#include "p2d/Common.h"

namespace p2d {
	class IShape {
	public:
		virtual ~IShape();
		vec2 GetPosition() const;
		float GetAngle() const;
		virtual void GetVertecies(Polygon2d& vertecies) = 0;
		virtual void DebugRender(const DebugRenderer& debugRenderer) = 0;
	
	protected:
		IShape();
		void Construct(const b2Shape* shape, Material& attrs);
		bool AttachToBody(b2Body* body);
		
	private:
		b2Fixture* m_fixturePtr;
		b2FixtureDef* m_fixtureDefPtr;
		b2Body* m_bodyPtr;
		
		friend class IBody;
	};
}

#endif