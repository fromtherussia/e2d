#ifndef AIR2D_ENGINE_IENTITY_H
#define AIR2D_ENGINE_IENTITY_H

#include "EngineCommon.h"

namespace air2d {
	namespace engine {
		/*
			������������ ��� ������������� �������� �����.
		*/
		namespace EntityType {
			enum Type {
				etStatic,
				etKinematic,
				etDynamic
			};
		}

		class IWithNamedPoints {
		public:
			IWithNamedPoints() {};
			virtual ~IWithNamedPoints() {};
			// �.� ����� ���������� - ����������� ����� ���������� ���. ������� ���������� ����� ����� ���������� ����.
			void AddNamedPoint(const string_t& applicationPointName, vec2 point);
			vec2 GetNamedPoint(const string_t& applicationPointName);
		
		private:
			typedef std::map<string_t, vec2> NamedPoints;
			NamedPoints m_namedPoints;
		};

		/*
			��������� ������� ��������.
			����������� bounding box ������ ��� ��������������� ����������� ������� ���������.
			���������� � �������� ���� (���� �� ������ ������� �����. Box2D ��� ������������. ��������� �� �������, �������� ����������
			�� ����� ������ ��������� ������� ���������� ��������)
			����� ��������� ����������� ����������� � ������� Render (���������� ������ ���� bounding box �������� � ������� ���������).
		*/
		class IEntity {
		public:
			IEntity(EntityType::Type type);
			virtual ~IEntity();
		
		protected:
			virtual void UpdatePosition() = 0;
			virtual Rect GetGraphicBoundingBox() = 0;
			virtual Rect GetPhysicBoundingBox() = 0;
			virtual void Render(r2d::IRenderContext& context, bool isDebug) const = 0;
			EntityType::Type GetType();

		private:
			EntityType::Type m_type;
		
			friend class Scene;
		};
		DEFPTR(IEntity);

		class IStaticEntity {
		public:
			IStaticEntity();
			virtual ~IStaticEntity();
		};

		class IKinematicEntity {
		public:
			IKinematicEntity();
			virtual ~IKinematicEntity();
			// Position
			virtual vec2 GetPosition() = 0;
			virtual bool SetPosition(const vec2& pos) = 0;
			virtual bool Move(const vec2& delta) = 0;
			// Angle
			virtual float GetAngle() = 0;
			virtual bool SetAngle(float angle) = 0;
			virtual bool Rotate(float delta) = 0;
		};

		class IDynamicEntity {
		public:
			IDynamicEntity();
			virtual ~IDynamicEntity();
			// Interactions
			virtual bool ApplyForce(const vec2& pos, const vec2& force) = 0;
			virtual bool ApplyImpulse(const vec2& pos, const vec2& impulse) = 0;
		};
	}
}

#endif