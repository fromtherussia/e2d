#ifndef P2D_JOINT_H
#define P2D_JOINT_H

#include "p2d/Common.h"

namespace p2d {
	class IJoint {
	public:
		virtual ~IJoint();
		vec2 GetAnchorA();
		vec2 GetAnchorB();
		void DebugRender(const DebugRenderer& debugRenderer);
		
	protected:
		IJoint(World& world);
		void Construct(const b2JointDef& jointDefPtr);
		b2Body* GetPrimitiveBody(IBody& primitive);
		
	private:
		b2Joint* m_jointPtr;
		b2World& m_world;
	};
}

#endif