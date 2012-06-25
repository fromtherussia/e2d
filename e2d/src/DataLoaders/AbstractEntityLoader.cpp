/*#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <cgl/Rect.h>
#include <cgl/Polygon.h>
#include <cgl/Utils.h>
#include <cgl/TypesParser.h>

#include <r2d/CompositeRenderable.h>

#include "Physics/Common.h"
#include "Physics/IPrimitive.h"

#include "Engine/IEntity.h"
#include "Engine/IResourceController.h"
#include "Engine/IEntityFactory.h"
#include "Engine/ComplexPhysicEntity.h"

#include "DataLoaders/Common.h"
#include "DataLoaders/Utils.h"
#include "DataLoaders/IEntityLoader.h"
#include "DataLoaders/IGraphicShapeLoader.h"
#include "DataLoaders/IPhysicShapeLoader.h"
#include "DataLoaders/ComplexPhysicEntityLoader.h"
#include "DataLoaders/SceneLoader.h"

using namespace boost::property_tree;

namespace e2d {
	namespace loaders {

		engine::IEntity* ComplexPhysicEntityLoader::Load(ptree& parsedEntity, engine::IResourceController* resourceController, SceneLoader* sceneLoader) const {
			ptree& entityNode = parsedEntity.get_child("entity");

			LOAD_TYPED_PARAM_FROM_SUBNODE(entityNode, string_t, physicsType, "physics_type", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(entityNode, vec2, offset, vec2(), "offset", TypesParser::GetType, TypesParser::ParseVec2, CglTypes::ctVec2);

			// Creating entity
			engine::ComplexPhysicEntity* entity;
			p2d::IBody::Type type;
			if (physicsType == "dynamic") {
				type = p2d::IBody::ptDynamic;
			} else if (physicsType == "static") {
				type = p2d::IBody::ptStatic;
			} else if (physicsType == "kinematic") {
				type = p2d::IBody::ptKinematic;
			}
			entity = resourceController->GetEntitiesFactory()->CreateComplexPhysicEntity(offset, type);

			// Loading graphic shapes
			if (HAS_CHILD(parsedEntity, "entity.graphics.shapes")) {
				ptree& graphicShapesNode = parsedEntity.get_child("entity.graphics.shapes");
				BOOST_FOREACH(ptree::value_type& shapeNode, graphicShapesNode) {
					string_t shapeType = shapeNode.second.get<string_t>("type", "");
					LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(shapeNode.second, vec2, shapeOffset, vec2(), "offset", TypesParser::GetType, TypesParser::ParseVec2, CglTypes::ctVec2);
					entity->AddShape(
						sceneLoader->GetGraphicShapeLoader(shapeType)->Load(shapeNode.second, resourceController),
						shapeOffset
					);
				}
			}

			// Loading physic shapes
			if (HAS_CHILD(parsedEntity, "entity.physics.shapes")) {
				ptree& physicShapesNode = parsedEntity.get_child("entity.physics.shapes");
				BOOST_FOREACH(ptree::value_type& shapeNode, physicShapesNode) {
					string_t shapeType = shapeNode.second.get<string_t>("type", "");
					entity->AddShape(
						sceneLoader->GetPhysicShapeLoader(shapeType)->Load(shapeNode.second, resourceController)
					);
				}
			}
			return entity;
		}

	}
}*/