#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <cgl/Rect.h>
#include <cgl/Polygon.h>
#include <cgl/Utils.h>
#include <cgl/TypesParser.h>

#include <r2d/ITexture.h>
#include <r2d/IEffect.h>
#include <r2d/IMaterial.h>
#include <r2d/IFactory.h>
#include <r2d/IDynamicGeometeryObject.h>

#include "e2d/Engine/GraphicMaterialTable.h"
#include "e2d/Engine/IResourceController.h"

#include "e2d/DataLoaders/Common.h"
#include "e2d/DataLoaders/Utils.h"
#include "e2d/DataLoaders/IGraphicShapeLoader.h"

#include "e2d/DataLoaders/DynamicGeometryObjectLoader.h"

using namespace boost::property_tree;

namespace e2d {
	namespace loaders {
		std::auto_ptr<r2d::IRenderable> DynamicGeometryObjectLoader::Load(ptree& shapeNode, engine::IResourceController& resourceController) const {
			r2d::IFactory& graphicObjectsFactory = resourceController.GetGraphicObjectsFactory();
			engine::GraphicMaterialTable& graphicMaterialsTable = resourceController.GetGraphicMaterialTable();

			ptree& verticesNode = shapeNode.get_child("vertices");

			LOAD_TYPED_PARAM_FROM_SUBNODE(shapeNode, string_t, materialName, "material", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
			LOAD_TYPED_PARAM_FROM_SUBNODE(shapeNode, int, depth, "depth", TypesParser::GetType, TypesParser::ParseInt, CglTypes::ctInt);
			LOAD_POLYGON_FROM_NODE(verticesNode, Polygon2d, geometry);

			r2d::AnimationProperties animationProperties;
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(shapeNode, bool, isAnimated, false, "is_animated", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			if (isAnimated) {
				LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(shapeNode, float, frameTime, false, "frame_time", TypesParser::GetType, TypesParser::ParseFloat, CglTypes::ctFloat);
				LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(shapeNode, float, step, false, "step", TypesParser::GetType, TypesParser::ParseFloat, CglTypes::ctFloat);
				LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(shapeNode, int, framesCount, false, "frames_count", TypesParser::GetType, TypesParser::ParseInt, CglTypes::ctInt);
				animationProperties.m_useAnimation = true;
				animationProperties.m_step = step;
				animationProperties.m_frameTime = frameTime;
				animationProperties.m_framesCount = framesCount;
			}
			
			if (IS_PARAM_EXISTS(shapeNode, "uv")) {
				LOAD_TYPED_PARAM_FROM_SUBNODE(shapeNode, Rect, uv, "uv", TypesParser::GetType, TypesParser::ParseRect, CglTypes::ctRect);
				
				return graphicObjectsFactory.CreateGraphicObject(
					graphicMaterialsTable.GetGraphicMaterial(materialName),
					geometry,
					uv,
					0.0f,
					animationProperties
				);

			} else if (IS_PARAM_EXISTS(shapeNode, "pixel_per_uv")) {
				LOAD_TYPED_PARAM_FROM_SUBNODE(shapeNode, vec2, pixelPerUv, "pixel_per_uv", TypesParser::GetType, TypesParser::ParseVec2, CglTypes::ctVec2);
				Rect boundingRect = geometry.GetBoundingRect();
				
				return graphicObjectsFactory.CreateGraphicObject(
					graphicMaterialsTable.GetGraphicMaterial(materialName),
					geometry,
					TILE_METRICS_TO_UV(boundingRect, pixelPerUv)					
				);
			} else {
				throw std::runtime_error("uv not set");
			}
		}

	}
}