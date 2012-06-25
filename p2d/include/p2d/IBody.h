#ifndef P2D_IPRIMITIVE_H
#define P2D_IPRIMITIVE_H

#include "p2d/Common.h"

namespace p2d {
	class IStaticBody {
	public:
		IStaticBody() {};
		virtual ~IStaticBody() {};
		virtual vec2 GetPosition() const = 0;
		virtual float GetAngle() const = 0;
		virtual vec2 GetLinearVelocity() const = 0;
		virtual float GetAngularVelocity() const = 0;
	};

	class IKinematicBody {
	public:
		IKinematicBody() {};
		virtual ~IKinematicBody() {};
		virtual void SetPosition(const vec2& pos) = 0;
		virtual void Move(const vec2& delta) = 0;
		virtual void SetAngle(float angle) = 0;
		virtual void Rotate(float delta) = 0;
	};

	class IDynamicBody {
	public:
		IDynamicBody() {};
		virtual ~IDynamicBody() {};
		virtual void ApplyForce(const vec2& pos, const vec2& force) = 0;
		virtual void ApplyImpulse(const vec2& pos, const vec2& impulse) = 0;
	};

	class IBody: public IStaticBody, public IKinematicBody, public IDynamicBody {
	public:
		enum Type {
			ptStatic, // не двигаются, масса - бесконечность, не участвуют в коллизиях с другими статическими и кинематическими объектами.
			ptDynamic, // коллизии со всеми объектами.
			ptKinematic // коллизии только с динамическими объектами.
		};
		IBody(World& world, Type type, const Material& attributes, const BodyInitialMotion& initialMotion);
		virtual ~IBody();
		virtual bool IsActive() const = 0;
		virtual void DebugRender(const DebugRenderer& debugRenderer) = 0;
		
		// IStaticPrimitive
		virtual vec2 GetPosition() const;
		virtual float GetAngle() const;
		virtual vec2 GetLinearVelocity() const;
		virtual float GetAngularVelocity() const;

		// IKinematicPrimitive
		virtual void SetPosition(const vec2& pos);
		virtual void Move(const vec2& delta);
		virtual void SetAngle(float angle);
		virtual void Rotate(float delta);

		// IDynamicPrimitive
		virtual void ApplyForce(const vec2& force, const vec2& point);
		virtual void ApplyImpulse(const vec2& force, const vec2& point);

	protected:
		void AttachShape(IShape* shapePtr);
		b2Body* GetBody();

	private:
		Type m_type;
		b2World& m_world;
		b2Body* m_bodyPtr;

		friend class IJoint;
	};
}

#endif