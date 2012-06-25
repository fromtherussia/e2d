#ifndef E2D_ENGINE_IENTITY_H
#define E2D_ENGINE_IENTITY_H

#include "e2d/Engine/Common.h"

namespace e2d {
	namespace engine {
		/*
			Интерфейс игровой сущности.
			Графический bounding box служит для высокоуровневой оптимизации области видимости.
			Физический в возможно тоже (Пока не совсем понятно зачем. Box2D сам оптимизирует. Оставлено на будущее, например выкидывать
			из сцены далеко улетевшие осколки ломающихся объектов)
			Более детальная оптимизация выполняется в функции Render (вызывается только если bounding box попадает в область видимости).
		*/
		class IEntity {
		public:
			IEntity(EntityType::Type type): m_type(type) {};
			virtual ~IEntity() {};
			virtual void SetPosition(const vec2& pos) = 0;
			virtual void Move(const vec2& delta) = 0;
			virtual vec2 GetPosition() const = 0;
			virtual void SetAngle(float angle) = 0;
			virtual void Rotate(float delta) = 0;
			virtual float GetAngle() const = 0;
		
		protected:
			virtual void UpdatePosition() = 0;
			virtual Rect GetGraphicBoundingBox() const = 0;
			virtual void Render() const = 0;
			EntityType::Type GetType() { return m_type; };

		private:
			EntityType::Type m_type;
		
			friend class Scene;
		};

		class IPhysicEntity {
		public:
			IPhysicEntity() {};
			virtual ~IPhysicEntity() {};
			// Static
			virtual vec2 GetLinearVelocity() const = 0;
			virtual float GetAngularVelocity() const = 0;
			// Dynamic
			virtual void ApplyForce(const vec2& pos, const vec2& force) = 0;
			virtual void ApplyImpulse(const vec2& pos, const vec2& impulse) = 0;
			// Named points
			// Именованные места приложения сил. Удобнее ограничить число точек приложения силы.
			void AddNamedPoint(const string_t& applicationPointName, const vec2& point);
			vec2 GetNamedPoint(const string_t& applicationPointName);

		protected:
			virtual Rect GetPhysicBoundingBox() const = 0;

		private:
			typedef std::map<string_t, vec2> NamedPoints;
			NamedPoints m_namedPoints;

			friend class Scene;
		};
	}
}

#endif