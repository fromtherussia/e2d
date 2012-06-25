#ifndef E2D_ENGINE_COMMON_H
#define E2D_ENGINE_COMMON_H

#include <cgl/MathTypes.h>
#include <r2d/IRenderContext.h>

#include <r2d/Common.h>
#include <p2d/Common.h>

namespace e2d {
	namespace engine {
		namespace EntityType {
			enum Type {
				etAbstract,
				etPhysic,
				etComplex
			};
		}

		namespace DeferredDataKind {
			enum Kind {
				ddkGraphics,
				ddkPhysics,
				ddkLogic
			};
		};

		class IEntityFactory;
		class IResourceController;
		class GraphicMaterialTable;
		class PhysicMaterialTable;
		class ComplexPhysicEntity;
		class Scene;
	}
}

#endif