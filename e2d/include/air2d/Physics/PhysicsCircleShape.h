#ifndef AIR2D_PHYSICS_CIRCLE_SHAPE_H
#define AIR2D_PHYSICS_CIRCLE_SHAPE_H

#include "PhysicsCommon.h"

namespace air2d {
	namespace physics {
		class CircleShape: public IShape {
		public:
			CircleShape(const Circle& circle, Material& attrs);
			virtual ~CircleShape();
		
		private:
			RESTRICT_COPY_CTOR(CircleShape);
			RESTRICT_ASSIGN_OPERATOR(CircleShape);

			virtual void Render(const r2d::IRenderContext& context) const;
			
			Circle m_circle;
			b2CircleShape* m_pCircleShape;
		};
	}
}

#endif