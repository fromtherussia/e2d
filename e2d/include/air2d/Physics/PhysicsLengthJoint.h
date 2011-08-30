#ifndef AIR2D_PHYSICS_LENGTH_JOINT_H
#define AIR2D_PHYSICS_LENGTH_JOINT_H

#include "PhysicsCommon.h"

namespace air2d {
	namespace physics {
		class Primitive;
		class World;

		class LengthJoint: public IJoint {
		public:
			LengthJoint(World& world, Primitive& primitive1, Primitive& primitive2, vec2 anchor1, vec2 anchor2);
			virtual ~LengthJoint();
		
		private:
			RESTRICT_COPY_CTOR(LengthJoint);
			RESTRICT_ASSIGN_OPERATOR(LengthJoint);

			virtual void Render(const r2d::IRenderContext& context);

			b2DistanceJointDef* m_pDistanceJointDef;
		};
	}
}

#endif