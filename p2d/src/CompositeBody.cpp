#include <Box2D/Box2D.h>

#include "p2d/DebugRenderer.h"
#include "p2d/Utils.h"
#include "p2d/IShape.h"

#include "p2d/CompositeBody.h"

namespace p2d {
	CompositeBody::CompositeBody(World& world, IBody::Type type, const Material& attrs, const BodyInitialMotion& initialMotion):
		IBody(world, type, attrs, initialMotion) {
	}
	
	CompositeBody::~CompositeBody() {
		m_shapes.clear();
	}

	CompositeBody& CompositeBody::operator << (std::auto_ptr<IShape> shapePtr) {
		AttachShape(shapePtr.get());
		m_shapes.push_back(shapePtr.release());
		return *this;
	}

	IShape& CompositeBody::operator [] (uint index) {
		if (index >= m_shapes.size()) {
			throw std::logic_error("index is out of range");
		}
		return m_shapes[index];
	}

	bool CompositeBody::IsActive() const {
		return false; 
	}

	size_t CompositeBody::CountShapes() const {
		return m_shapes.size();
	}

	void CompositeBody::RemoveShapes() {
		m_shapes.clear();
	}

	void CompositeBody::DebugRender(const DebugRenderer& debugRenderer) {
		debugRenderer.SetWorldTransform(GetPosition(), GetAngle());
		for (size_t i = 0; i < m_shapes.size(); ++i) {
			m_shapes[i].DebugRender(debugRenderer);
		}
		debugRenderer.RenderWorldAxises();
		debugRenderer.ResetWorldTransform();
	}
}