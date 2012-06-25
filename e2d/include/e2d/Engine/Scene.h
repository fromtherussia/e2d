#ifndef E2D_ENGINE_SCENE_H
#define E2D_ENGINE_SCENE_H

#include "e2d/Engine/GraphicMaterialTable.h"
#include "e2d/Engine/PhysicMaterialTable.h"
#include "e2d/Engine/IResourceController.h"

namespace e2d {
	namespace engine {
		/*
			Идея следующая:
			Карта должна создаваться автоматом из ресурсов, неинтерактивные объекты не имеют игровых оберток.
			Интерактивные имеют и внутри игрового объекта содержится:
			PrimitiveEntity, KinematicPrimitiveEntity, DynamicPrimitiveEntity, CompositeEntity, PrimitiveJoint, итд.
			Но все объекты добавляются в сцену и обсчитываются централизованно.
		*/


		class Scene: 
			public IResourceController {
			//public IEntityFactory, 
		public:
			Scene(r2d::IRenderContext& renderContext, const vec2& gravity = vec2(0.0f, -10.0f));
			~Scene();
			void Render(const r2d::ICamera& camera, bool isDebug);
			Scene& operator << (std::auto_ptr<IEntity> entityPtr);

			// Resource controller interface
			// virtual IEntityFactory& GetEntitiesFactory();
			virtual r2d::IFactory& GetGraphicObjectsFactory();
			virtual GraphicMaterialTable& GetGraphicMaterialTable();
			virtual PhysicMaterialTable& GetPhysicMaterialTable();
			
			// Factory interface
			//ComplexPhysicEntity* CreateComplexPhysicEntity(const vec2& initialPos = vec2(), p2d::IBody::Type type = p2d::IBody::ptStatic, const string_t& primitiveMaterialName = string_t(""));

			
		private:
			r2d::IRenderContext& m_renderContext;

			// Resource controller data
			std::auto_ptr<r2d::IFactory> m_graphicFactoryPtr;
			GraphicMaterialTable m_graphicMaterialTable;
			PhysicMaterialTable m_physicMaterialTable;
			
			// Physics
			p2d::World m_world;

			// Scene data
			boost::ptr_vector<IEntity> m_entities;
			
		};
	}
}

#endif