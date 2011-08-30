#ifndef AIR2D_PHYSICS_COMMON_H
#define AIR2D_PHYSICS_COMMON_H

#include <cgl/MathTypes.h>
#include <r2d/IRenderContext.h>

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

namespace air2d {
	namespace physics {
		/*
			������ ��������
		*/
		struct CollisionFilter {
			CollisionFilter():
				categoryBits(0),
				maskBits(~0),
				groupIndex(0) {
			}
			uint categoryBits; // 16 ��� ��� ����������� ��������� �������.
			uint maskBits; // 16 ������ ����� ����������� � categoryBits �������.
			uint groupIndex; // 16 ������ ������ ������. ������� ����� ������ �� ��������� � ��������� ��� ����������� ������������ �� ������� ������ ����� ������������ categoryBits.
		};

		/*
			�����:
			- ����������� ������� �� ��������� � ��������� �� ������������ ���������
			- �����(b2Fixture) �� ����������� �� �������� ������ ������ �������(b2Body),
			�� ����������� �������, ����� ��� ��������� �������� � �������� ������������� ���������
		*/
		struct Material {
			Material(float destiny = 5.0f, float friction = 2.0f, float restitution = 0.5f, CollisionFilter filter = CollisionFilter(), bool isSensor = false): 
				m_density(destiny),
				m_friction(friction),
				m_restitution(restitution),
				m_filter(filter),
				m_isSensor(isSensor) {
			}
			float m_density; // ��������� ��/��.����.
			float m_friction; // ������ 0 - ��� ������, 1 - ������������ ������.
			float m_restitution; // ��������� ����� 0 - ��������� ���������, 1 - ��������� �������.
			CollisionFilter m_filter; // ��. ����.
			bool m_isSensor; // ������� ������������ �� �������� �� ����������.

		};

		/*
			��������� ��������� � ���������.
		*/
		struct PrimitiveInitialMotion {
			PrimitiveInitialMotion(vec2 position = vec2(), float angle = 0.0f, vec2 linearVelocity = vec2(), float angularVelocity = 0.0f):
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

		/*
			���������� �������� ���������.
			������������ ��� ���������������. ����� ����� ������������ ���������������� �������� �������.
		*/
		struct PrimitiveAttributes {
			PrimitiveAttributes():
				m_linearDamping(0.1f),
				m_angularDamping(0.0f),
				m_allowSleep(true),
				m_fixedRotation(false),
				m_bullet(false),
				m_active(true),
				m_awake(true),
				m_inertiaScale(0.0f) {
			}
			float m_linearDamping; // �������� "������������� �������", ������������� ��� ������������ ����������. ������������� �������� 0 - 0.1. 0 - ��� ����������.
			float m_angularDamping; // ������� �������������. ������������� �������� 0 - 0.1.
			bool m_allowSleep; // ��������� ������� ����������� ����������, ����� �� �������� ��������� � ������� � ��������� �����.
			bool m_fixedRotation; // ��������� ��������.
			bool m_bullet; // ������������ �� CCD (continuous collision detection). �.�. ������������� ��������� ������.
			bool m_active; // ������� �� ������. ���������� ������� - ��� ��� ����������� ����������� � ��� ���������.
			bool m_awake; // ���� true ����� ����� ���������� � ����� ������ ��� ������� ��� ������ ��������.
			float m_inertiaScale; // Experimental, not documented.
		};
	}
}

#endif