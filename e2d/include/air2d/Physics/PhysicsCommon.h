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
			Фильтр коллизий
		*/
		struct CollisionFilter {
			CollisionFilter():
				categoryBits(0),
				maskBits(~0),
				groupIndex(0) {
			}
			uint categoryBits; // 16 бит для определения категории объекта.
			uint maskBits; // 16 битная маска применяемая к categoryBits объекта.
			uint groupIndex; // 16 битный индекс группы. Объекты одной группы не участвуют в коллизиях для определения пересекаются ли объекты разных групп используются categoryBits.
		};

		/*
			Также:
			- Статические объекты не участвуют в коллизиях со статическими объектами
			- Формы(b2Fixture) не проверяются на коллизии внутри одного объекта(b2Body),
			за исключением случаев, когда они соединены джоинтом и коллизии принудительно разрешены
		*/
		struct Material {
			Material(float destiny = 5.0f, float friction = 2.0f, float restitution = 0.5f, CollisionFilter filter = CollisionFilter(), bool isSensor = false): 
				m_density(destiny),
				m_friction(friction),
				m_restitution(restitution),
				m_filter(filter),
				m_isSensor(isSensor) {
			}
			float m_density; // Плотность кг/кв.метр.
			float m_friction; // Трение 0 - нет трения, 1 - максимальное трение.
			float m_restitution; // Упругость удара 0 - абсолютно неупругий, 1 - абсолютно упругий.
			CollisionFilter m_filter; // См. выше.
			bool m_isSensor; // Объекты пересекаются но коллизии не происходит.

		};

		/*
			Начальное положение и ускорения.
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
			Физические атрибуты примитива.
			Используются при конструировании. После нужно пользоваться соответствующими методами объекта.
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
			float m_linearDamping; // Линейное "сопротивление воздуха", предназначено для постепенного замедления. Рекомендуемые значения 0 - 0.1. 0 - нет замедления.
			float m_angularDamping; // Угловое сопротивление. Рекомендуемые значения 0 - 0.1.
			bool m_allowSleep; // Разрешить объекту становиться неактивным, когда он перестал двигаться и перешел в состояние покоя.
			bool m_fixedRotation; // Запрещено вращение.
			bool m_bullet; // Использовать ли CCD (continuous collision detection). Т.е. предотвращать тунельный эффект.
			bool m_active; // Активен ли объект. Активность объекта - это его возможность участвовать в физ процессах.
			bool m_awake; // Если true сразу после добавления в сцену объект при наличии сил начнет движение.
			float m_inertiaScale; // Experimental, not documented.
		};
	}
}

#endif