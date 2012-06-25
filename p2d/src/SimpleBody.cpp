#include <Box2D/Box2D.h>

#include "p2d/DebugRenderer.h"
#include "p2d/Utils.h"
#include "p2d/IShape.h"

#include "p2d/SimpleBody.h"

namespace p2d {
	SimpleBody::SimpleBody(World& world, std::auto_ptr<IShape> shapePtr, IBody::Type type, const Material& attrs, const BodyInitialMotion& initialMotion):
		IBody(world, type, attrs, initialMotion),
		m_shapePtr(shapePtr) {
		AttachShape(m_shapePtr.get());
	}

	SimpleBody::~SimpleBody() {
	}

	bool SimpleBody::IsActive() const {
		return false; 
	}

	void SimpleBody::DebugRender(const DebugRenderer& debugRenderer) {
		debugRenderer.SetWorldTransform(GetPosition(), GetAngle());
		m_shapePtr->DebugRender(debugRenderer);
		debugRenderer.RenderWorldAxises();
		debugRenderer.ResetWorldTransform();
	}
}