#ifndef AIR2D_ENGINE_SCENE_H
#define AIR2D_ENGINE_SCENE_H

namespace air2d {
	namespace physics {
		class World;
	}
	namespace engine {
		/*
			���� ���������:
			����� ������ ����������� ��������� �� ��������, ��������������� ������� �� ����� ������� �������.
			������������� ����� � ������ �������� ������� ����������:
			PrimitiveEntity, KinematicPrimitiveEntity, DynamicPrimitiveEntity, CompositeEntity, PrimitiveJoint, ���.
			�� ��� ������� ����������� � ����� � ������������� ���������������.
		*/
		class StaticEntity;
		class KinematicEntity;
		class DynamicEntity;
		PREDECL_CLASS_WITH_PTR(IEntity);

		class Scene {
		public:
			Scene(const vec2& gravity = vec2(0.0f, -10.0f));
			~Scene();
			void Render(r2d::IRenderContext& context, const r2d::ICamera& camera, bool isDebug);
			Scene& operator << (IEntity* entityPtr);
			// Factory interface
			StaticEntity* CreateStaticEntity(const vec2& initialPos = vec2(), const string_t& primitiveMaterialName = string_t(""));
			KinematicEntity* CreateKinematicEntity(const vec2& initialPos = vec2(), const string_t& primitiveMaterialName = string_t(""));
			DynamicEntity* CreateDynamicEntity(const vec2& initialPos = vec2(), const string_t& primitiveMaterialName = string_t(""));

		private:
			physics::PrimitiveAttributes GetAttributes(const string_t& primitiveMaterialName) const;

			std::vector<IEntityPtr> m_entities;
			physics::World m_world;
		};
	}
}

#endif