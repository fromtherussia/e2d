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
		Фильтр коллизий
	*/
	struct CollisionFilter {
		CollisionFilter():
			m_categoryBits(0),
			m_maskBits(~0),
			m_groupIndex(0) {
		}
		uint m_categoryBits; // 16 бит для определения категории объекта.
		uint m_maskBits; // 16 битная маска применяемая к categoryBits объекта.
		uint m_groupIndex; // 16 битный индекс группы. Объекты одной группы не участвуют в коллизиях для определения пересекаются ли объекты разных групп используются categoryBits.
	};

	/*
		Также:
		- Статические объекты не участвуют в коллизиях со статическими объектами
		- Формы(b2Fixture) не проверяются на коллизии внутри одного объекта(b2Body),
		за исключением случаев, когда они соединены джоинтом и коллизии принудительно разрешены
	*/
	struct Material {
		Material(float destiny = 5.0f, float friction = 2.0f, float restitution = 0.5f, const CollisionFilter& filter = CollisionFilter(), bool isSensor = false): 
			// Физические свойства формы
			m_density(destiny),
			m_friction(friction),
			m_restitution(restitution),
			m_filter(filter),
			m_isSensor(isSensor),
			// Физические свойства тела
			m_linearDamping(0.1f),
			m_angularDamping(0.0f),
			m_allowSleep(true),
			m_fixedRotation(false),
			m_bullet(false),
			m_active(true),
			m_awake(true) {
		}
		// Физические свойства формы
		float m_density; // Плотность кг/кв.метр.
		float m_friction; // Трение 0 - нет трения, 1 - максимальное трение.
		float m_restitution; // Упругость удара 0 - абсолютно неупругий, 1 - абсолютно упругий.
		CollisionFilter m_filter; // См. выше.
		bool m_isSensor; // Объекты пересекаются но коллизии не происходит.
		// Физические свойства тела
		float m_linearDamping; // Линейное "сопротивление воздуха", предназначено для постепенного замедления. Рекомендуемые значения 0 - 0.1. 0 - нет замедления.
		float m_angularDamping; // Угловое сопротивление. Рекомендуемые значения 0 - 0.1.
		bool m_allowSleep; // Разрешить объекту становиться неактивным, когда он перестал двигаться и перешел в состояние покоя.
		bool m_fixedRotation; // Запрещено вращение.
		bool m_bullet; // Использовать ли CCD (continuous collision detection). Т.е. предотвращать тунельный эффект.
		bool m_active; // Активен ли объект. Активность объекта - это его возможность участвовать в физ процессах.
		bool m_awake; // Если true сразу после добавления в сцену объект при наличии сил начнет движение.
	};

	/*
		Начальное положение и ускорения.
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