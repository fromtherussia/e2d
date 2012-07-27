#ifndef E2D_DATA_LOADERS_SCENE_LOADER_H
#define E2D_DATA_LOADERS_SCENE_LOADER_H

#include "e2d/DataLoaders/Common.h"

namespace e2d {
	namespace loaders {
		class SceneLoader {
		public:
			SceneLoader(engine::IResourceController& resourceController);
			~SceneLoader();
			
			void LoadScene(std::istream& inputStream);

			std::auto_ptr<engine::IEntity> LoadEntity(std::istream& inputStream);
			r2d::IMaterial& LoadGraphicMaterial(std::istream& inputStream);
			p2d::Material& LoadPhysicMaterial(std::istream& inputStream);

			const IGraphicShapeLoader& GetGraphicShapeLoader(const string_t& shapeTypeName);
			const IPhysicShapeLoader& GetPhysicShapeLoader(const string_t& shapeTypeName);
			const IEntityLoader& GetEntityLoader(const string_t& entityTypeName);

		private:
			void AddGraphicShapeLoader(const string_t& shapeTypeName, std::auto_ptr<IGraphicShapeLoader> loaderPtr);
			void AddPhysicShapeLoader(const string_t& shapeTypeName, std::auto_ptr<IPhysicShapeLoader> loaderPtr);
			void AddEntityLoader(const string_t& shapeTypeName, std::auto_ptr<IEntityLoader> loaderPtr);

			engine::IResourceController& m_resourceController;

			typedef boost::shared_ptr<IGraphicShapeLoader> IGraphicShapeLoaderPtr;
			typedef boost::shared_ptr<IPhysicShapeLoader> IPhysicShapeLoaderPtr;
			typedef boost::shared_ptr<IEntityLoader> IEntityLoaderPtr;

			std::map<string_t, IGraphicShapeLoaderPtr> m_graphicShapeLoaders;
			std::map<string_t, IPhysicShapeLoaderPtr> m_physicShapeLoaders;
			std::map<string_t, IEntityLoaderPtr> m_entityLoaders;
		};
	}
}

#endif