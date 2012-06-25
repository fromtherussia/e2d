#ifndef E2D_DATA_LOADERS_SCENE_LOADER_H
#define E2D_DATA_LOADERS_SCENE_LOADER_H

namespace r2d {
	class IMaterial;
}

namespace e2d {
	namespace p2d {
		struct Material;
	}
	namespace engine {
		class Scene;
		class IEntity;
	}
	namespace loaders {
		PREDECL_CLASS_WITH_PTR(IGraphicShapeLoader);
		PREDECL_CLASS_WITH_PTR(IPhysicShapeLoader);
		PREDECL_CLASS_WITH_PTR(IEntityLoader);

		class SceneLoader {
		public:
			SceneLoader(engine::Scene* scene);
			~SceneLoader();
			
			void LoadScene(std::istream& inputStream);
			engine::IEntity* ParseEntity(std::istream& inputStream);
			r2d::IMaterial* LoadGraphicMaterial(std::istream& inputStream);
			p2d::Material* LoadPhysicMaterial(std::istream& inputStream);

			const IGraphicShapeLoader* GetGraphicShapeLoader(const string_t& shapeTypeName);
			const IPhysicShapeLoader* GetPhysicShapeLoader(const string_t& shapeTypeName);
			const IEntityLoader* GetEntityLoader(const string_t& entityTypeName);

		private:
			void AddGraphicShapeLoader(const string_t& shapeTypeName, IGraphicShapeLoader* pLoader);
			void AddPhysicShapeLoader(const string_t& shapeTypeName, IPhysicShapeLoader* pLoader);
			void AddEntityLoader(const string_t& shapeTypeName, IEntityLoader* pLoader);

			engine::Scene* scene;
			std::map<string_t, IGraphicShapeLoaderPtr> m_graphicShapeLoaders;
			std::map<string_t, IPhysicShapeLoaderPtr> m_physicShapeLoaders;
			std::map<string_t, IEntityLoaderPtr> m_entityLoaders;
		};
	}
}

#endif