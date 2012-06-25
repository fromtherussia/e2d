#ifndef P2D_COMPOSITE_PRIMITIVE_H
#define P2D_COMPOSITE_PRIMITIVE_H

#include "p2d/IBody.h"

namespace p2d {
	/*
		Составное физическое тело из нескольких форм не движущихся относительно друг друга
	*/
	class CompositeBody: public IBody {
	public:
		CompositeBody(World& world, IBody::Type m_type, const Material& attrs = Material(), const BodyInitialMotion& initialMotion = BodyInitialMotion());
		virtual ~CompositeBody();
		CompositeBody& operator << (std::auto_ptr<IShape> shape);
		IShape& operator [] (uint index);
		size_t CountShapes() const;
		void RemoveShapes();
		// IBody
		virtual bool IsActive() const;
		virtual void DebugRender(const DebugRenderer& debugRenderer);

	private:
		boost::ptr_vector<IShape> m_shapes;
	};
}

#endif