#ifndef P2D_COMMON_H
#define P2D_COMMON_H

#include <cgl/MathTypes.h>

class b2World;
class b2Fixture;
struct b2FixtureDef;
class b2Shape;
class b2CircleShape;
class b2PolygonShape;
class b2Body;
class b2Joint;
struct b2JointDef;
struct b2DistanceJointDef;

namespace p2d {
	/*
		������ ��������
	*/
	struct CollisionFilter {
		CollisionFilter():
			m_categoryBits(0),
			m_maskBits(~0),
			m_groupIndex(0) {
		}
		uint m_categoryBits; // 16 ��� ��� ����������� ��������� �������.
		uint m_maskBits; // 16 ������ ����� ����������� � categoryBits �������.
		uint m_groupIndex; // 16 ������ ������ ������. ������� ����� ������ �� ��������� � ��������� ��� ����������� ������������ �� ������� ������ ����� ������������ categoryBits.
	};

	/*
		�����:
		- ����������� ������� �� ��������� � ��������� �� ������������ ���������
		- �����(b2Fixture) �� ����������� �� �������� ������ ������ �������(b2Body),
		�� ����������� �������, ����� ��� ��������� �������� � �������� ������������� ���������
	*/
	struct Material {
		Material(float destiny = 5.0f, float friction = 2.0f, float restitution = 0.5f, const CollisionFilter& filter = CollisionFilter(), bool isSensor = false): 
			// ���������� �������� �����
			m_density(destiny),
			m_friction(friction),
			m_restitution(restitution),
			m_filter(filter),
			m_isSensor(isSensor),
			// ���������� �������� ����
			m_linearDamping(0.1f),
			m_angularDamping(0.0f),
			m_allowSleep(true),
			m_fixedRotation(false),
			m_bullet(false),
			m_active(true),
			m_awake(true) {
		}
		// ���������� �������� �����
		float m_density; // ��������� ��/��.����.
		float m_friction; // ������ 0 - ��� ������, 1 - ������������ ������.
		float m_restitution; // ��������� ����� 0 - ��������� ���������, 1 - ��������� �������.
		CollisionFilter m_filter; // ��. ����.
		bool m_isSensor; // ������� ������������ �� �������� �� ����������.
		// ���������� �������� ����
		float m_linearDamping; // �������� "������������� �������", ������������� ��� ������������ ����������. ������������� �������� 0 - 0.1. 0 - ��� ����������.
		float m_angularDamping; // ������� �������������. ������������� �������� 0 - 0.1.
		bool m_allowSleep; // ��������� ������� ����������� ����������, ����� �� �������� ��������� � ������� � ��������� �����.
		bool m_fixedRotation; // ��������� ��������.
		bool m_bullet; // ������������ �� CCD (continuous collision detection). �.�. ������������� ��������� ������.
		bool m_active; // ������� �� ������. ���������� ������� - ��� ��� ����������� ����������� � ��� ���������.
		bool m_awake; // ���� true ����� ����� ���������� � ����� ������ ��� ������� ��� ������ ��������.
	};

	/*
		��������� ��������� � ���������.
	*/
	struct BodyInitialMotion {
		BodyInitialMotion(const vec2& position = vec2(), float angle = 0.0f, const vec2& linearVelocity = vec2(), float angularVelocity = 0.0f):
			m_position(position),
			m_angle(angle),
			m_linearVelocity(linearVelocity),
			m_angularVelocity(angularVelocity) {
		}
		vec2 m_position;
		float m_angle;
		vec2 m_linearVelocity;
		float m_angularVelocity;
	};

	namespace BodyKind {
		enum Kind {
			bkStatic,
			bkKinematic,
			bkDynamic
		};
	};

	class IJoint;
	class LengthJoint;
	class IBody;
	class SimpleBody;
	class IShape;
	class CircleShape;
	class PolygonShape;
	class ChainShape;
	class CompositeBody;
	class World;
	class DebugRenderer;

	struct CollisionParams {
		CollisionParams(const vec2& localPoint1, const vec2& localPoint2, const vec2& globalPoint1, const vec2& globalPoint2, const vec2& normal):
			isTwoPoints(true),
			localPoint1(localPoint1),
			localPoint2(localPoint2),
			globalPoint1(globalPoint1),
			globalPoint2(globalPoint2),
			normal(normal) {
		}

		CollisionParams(const vec2& localPoint1, const vec2& globalPoint1, const vec2& normal):
			isTwoPoints(false),
			localPoint1(localPoint1),
			globalPoint1(globalPoint1),
			normal(normal) {
		}

		bool isTwoPoints;
		vec2 localPoint1;
		vec2 localPoint2;
		vec2 globalPoint1;
		vec2 globalPoint2;
		vec2 normal;
	};

	class ICollisionListener {
	public:
		virtual void ProcessCollisionBegin(ICollisionListener& entity, const CollisionParams& collisionParams) = 0;
		virtual void ProcessCollisionEnd(ICollisionListener& entity, const CollisionParams& collisionParams) = 0;
	};

	typedef std::vector<ICollisionListener*> CollisionListeners;

	struct RaycastIntersection {
		RaycastIntersection(ICollisionListener* collisionListenerPtr, const vec2& position, const vec2& normal):
			collisionListenerPtr(collisionListenerPtr),
			position(position),
			normal(normal) {
		}

		ICollisionListener* collisionListenerPtr;
		vec2 position;
		vec2 normal;
	};
	typedef std::vector<RaycastIntersection> RaycastIntersections;
}

#endif