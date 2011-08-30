#ifndef AIR2D_PHYSICS_PRIMITIVE_H
#define AIR2D_PHYSICS_PRIMITIVE_H

#include "PhysicsCommon.h"

namespace air2d {
	namespace physics {
		class World;
		PREDECL_CLASS_WITH_PTR(IShape);

		class Primitive {
		public:
			enum Type {
				ptStatic, // �� ���������, ����� - �������������, �� ��������� � ��������� � ������� ������������ � ��������������� ���������.
				ptDynamic, // �������� �� ����� ���������.
				ptKinematic // �������� ������ � ������������� ���������.
			};
		
			Primitive(World& world, Type m_type, const PrimitiveAttributes& attrs = PrimitiveAttributes(), const PrimitiveInitialMotion& initialMotion = PrimitiveInitialMotion());
			~Primitive();
			// ��� ����� �������������� � ������ ��������� ������� �� ����� �������� ��������� ������������ ���� �����.
			Primitive& operator << (IShape* shape);
			IShape& operator [] (uint index);
			void ApplyForce(vec2 force, vec2 point);
			void ApplyImpulse(vec2 force, vec2 point);
			vec2 GetPosition() const;
			float GetAngle() const;
			void DebugRender(const r2d::IRenderContext& context);
			bool IsActive() const;
			size_t CountShapes() const;

		private:
			RESTRICT_COPY_CTOR(Primitive);
			RESTRICT_ASSIGN_OPERATOR(Primitive);

			b2Body* m_pBody;
			b2World& m_world;
			std::vector<IShapePtr> m_shapes;

			friend class IJoint;
		};
		DEFPTR(Primitive);
	}
}

#endif