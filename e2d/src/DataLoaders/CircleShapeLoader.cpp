#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <cgl/Rect.h>
#include <cgl/Circle.h>
#include <cgl/Utils.h>
#include <cgl/TypesParser.h>

#include <p2d/CircleShape.h>

#include "e2d/Engine/PhysicMaterialTable.h"
#include "e2d/Engine/IResourceController.h"

#include "e2d/DataLoaders/Common.h"
#include "e2d/DataLoaders/Utils.h"
#include "e2d/DataLoaders/IPhysicShapeLoader.h"

#include "e2d/DataLoaders/CircleShapeLoader.h"

using namespace boost::property_tree;

namespace e2d {
	namespace loaders {
		std::auto_ptr<p2d::IShape> CircleShapeLoader::Load(boost::property_tree::ptree& shapeNode, engine::IResourceController& resourceController) const {
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(shapeNode, vec2, offset, vec2(), "offset", TypesParser::GetType, TypesParser::ParseVec2, CglTypes::ctVec2);
			LOAD_TYPED_PARAM_FROM_SUBNODE(shapeNode, string_t, materialName, "material", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
			LOAD_TYPED_PARAM_FROM_SUBNODE(shapeNode, float, radius, "radius", TypesParser::GetType, TypesParser::ParseFloat, CglTypes::ctFloat);

			return std::auto_ptr<p2d::IShape>(
				new p2d::CircleShape(
					Circle(radius, offset),
					*resourceController.GetPhysicMaterialTable().GetPhysicMaterial(materialName)
				)
			);
		}
	}
}