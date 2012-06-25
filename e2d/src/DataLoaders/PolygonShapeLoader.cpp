#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <cgl/Rect.h>
#include <cgl/Polygon.h>
#include <cgl/Utils.h>
#include <cgl/TypesParser.h>

#include <p2d/PolygonShape.h>

#include "e2d/Engine/PhysicMaterialTable.h"
#include "e2d/Engine/IResourceController.h"

#include "e2d/DataLoaders/Common.h"
#include "e2d/DataLoaders/Utils.h"
#include "e2d/DataLoaders/IPhysicShapeLoader.h"

#include "e2d/DataLoaders/PolygonShapeLoader.h"

using namespace boost::property_tree;

namespace e2d {
	namespace loaders {
		std::auto_ptr<p2d::IShape> PolygonShapeLoader::Load(boost::property_tree::ptree& shapeNode, engine::IResourceController& resourceController) const {
			ptree& verticesNode = shapeNode.get_child("vertices");

			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(shapeNode, vec2, offset, vec2(), "offset", TypesParser::GetType, TypesParser::ParseVec2, CglTypes::ctVec2);
			LOAD_TYPED_PARAM_FROM_SUBNODE(shapeNode, string_t, materialName, "material", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
			LOAD_POLYGON_FROM_NODE(verticesNode, Polygon2d, geometry);
			geometry += offset;
			
			return std::auto_ptr<p2d::IShape>(
				new p2d::PolygonShape(
					geometry,
					*resourceController.GetPhysicMaterialTable().GetPhysicMaterial(materialName)
				)
			);
		}
	}
}