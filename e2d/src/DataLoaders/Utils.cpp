#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <cgl/Rect.h>
#include <cgl/Polygon.h>
#include <cgl/TypesParser.h>
#include <cgl/Utils.h>

#include "e2d/DataLoaders/Common.h"
#include "e2d/DataLoaders/Utils.h"

using namespace boost::property_tree;

namespace e2d {
	namespace loaders {
		bool IsParamExists(ptree& node, const string_t& attributeName) {
			return node.find(attributeName) != node.not_found();
		}

		bool HasChild(boost::property_tree::ptree& node, const string_t& childPath) {
			return node.get_child_optional(childPath) != NULL;
		}

		void LoadPolygon(ptree& polygonNode, Polygon2d& polygon) {
			BOOST_FOREACH(ptree::value_type& child, polygonNode) {
				LOAD_TYPED_PARAM_FROM_NODE(child, vec2, vertex, TypesParser::GetType, TypesParser::ParseVec2, CglTypes::ctVec2);
				polygon << vertex;
			}
			polygon.Center();
		}
	}
}