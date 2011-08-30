#ifndef AIR2D_PHYSICS_JOINT_H
#define AIR2D_PHYSICS_JOINT_H

#include "PhysicsCommon.h"

namespace air2d {
	namespace physics {
		class Primitive;
		class World;
		
		class IJoint {
		public:
			virtual ~IJoint();
			void DebugRender(const r2d::IRenderContext& context);
			vec2 GetAnchorA();
			vec2 GetAnchorB();
			
		protected:
			IJoint(World& world, const b2JointDef& jointDef);
			void Construct();
			b2Body* GetPrimitiveBody(Primitive& primitive);
			
		private:
			RESTRICT_COPY_CTOR(IJoint);
			RESTRICT_ASSIGN_OPERATOR(IJoint);

			virtual void Render(const r2d::IRenderContext& context) = 0;

			b2Joint* m_pJoint;
			const b2JointDef& m_jointDef;
			b2World& m_world;
		};
		DEFPTR(IJoint);
	}
}

#endif