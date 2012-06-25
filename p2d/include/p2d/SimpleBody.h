#ifndef P2D_SIMPLE_PRIMITIVE_H
#define P2D_SIMPLE_PRIMITIVE_H

#include "p2d/IBody.h"

namespace p2d {
	/*
		Простое физическое тело из 1 формы.
	*/
	class SimpleBody: public IBody {
	public:
		SimpleBody(World& world, std::auto_ptr<IShape> shapePtr, IBody::Type type, const Material& attributes = Material(), const BodyInitialMotion& initialMotion = BodyInitialMotion());
		virtual ~SimpleBody();
		// IBody
		virtual bool IsActive() const;
		virtual void DebugRender(const DebugRenderer& debugRenderer);

	private:
		std::auto_ptr<IShape> m_shapePtr;
	};
}

#endif