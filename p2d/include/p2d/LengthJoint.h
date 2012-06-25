#ifndef P2D_LENGTH_JOINT_H
#define P2D_LENGTH_JOINT_H

#include "p2d/IJoint.h"

namespace p2d {
	class LengthJoint: public IJoint {
	public:
		LengthJoint(World& world, IBody& primitive1, IBody& primitive2, const vec2& anchor1, const vec2& anchor2);
		virtual ~LengthJoint();
	};
}

#endif