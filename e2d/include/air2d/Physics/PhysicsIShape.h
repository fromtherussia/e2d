#ifndef AIR2D_PHYSICS_ISHAPE_H
#define AIR2D_PHYSICS_ISHAPE_H

#include "PhysicsCommon.h"

namespace air2d {
	namespace physics {
		class IShape {
		public:
			virtual ~IShape();
			void DebugRender(const r2d::IRenderContext& context) const;
			vec2 GetPosition() const;
			float GetAngle() const;
		
		protected:
			IShape();
			void Construct(const b2Shape* shape, Material& attrs);
			bool AttachToBody(b2Body* body);
			virtual void Render(const r2d::IRenderContext& context) const = 0;
		
		private:
			RESTRICT_COPY_CTOR(IShape);
			RESTRICT_ASSIGN_OPERATOR(IShape);

			b2Fixture* m_pFixture;
			b2FixtureDef m_fixtureDef;
			b2Body* m_pBody;
			
			friend class Primitive;
		};
		DEFPTR(IShape);
	}
}

#endif