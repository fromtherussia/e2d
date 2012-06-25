#ifndef P2D_PULLEY_JOINT_H
#define P2D_PULLEY_JOINT_H

#include "p2d/IJoint.h"

namespace p2d {
	class PulleyJoint: public IJoint {
	public:
		PulleyJoint(World& world, IBody& primitive1, IBody& primitive2, const vec2& anchor1, const vec2& anchor2, float raito, float minLenght, float maxLength);
		virtual ~PulleyJoint();
	};
}

#endif