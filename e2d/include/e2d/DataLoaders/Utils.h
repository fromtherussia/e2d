#ifndef E2D_DATA_LOADERS_UTILS_H
#define E2D_DATA_LOADERS_UTILS_H

class Polygon2d;

namespace e2d {
	namespace loaders {
		#define LOAD_TYPED_PARAM_FROM_SUBNODE(node, variableType, variable, paramName, typeCheckFunction, parseFunction, type) \
		variableType variable; \
		{ \
			string_t stringValue = node.get<string_t>(paramName, ""); \
			if (typeCheckFunction(stringValue) != type) { \
				throw std::runtime_error(formatString("%s attribute should be %s", paramName, #type)); \
			} \
			variable = parseFunction(stringValue); \
		}

		#define LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(node, variableType, variable, defaultValue, paramName, typeCheckFunction, parseFunction, type) \
		variableType variable = defaultValue; \
		if (IS_PARAM_EXISTS(node, paramName)) { \
			string_t stringValue = node.get<string_t>(paramName, ""); \
			if (typeCheckFunction(stringValue) != type) { \
				throw std::runtime_error(formatString("%s attribute should be %s", paramName, #type)); \
			} \
			variable = parseFunction(stringValue); \
		}

		#define LOAD_TYPED_PARAM_FROM_NODE(node, variableType, variable, typeCheckFunction, parseFunction, type) \
		variableType variable; \
		{ \
			string_t stringValue = node.second.data(); \
			if (typeCheckFunction(stringValue) != type) { \
				throw std::runtime_error(formatString("%s attribute should be %s", #type)); \
			} \
			variable = parseFunction(stringValue); \
		}

		#define LOAD_POLYGON_FROM_NODE(node, variableType, variable) \
			variableType variable; \
			LoadPolygon(node, variable);

		#define LOAD_POLYGONAL_CHAIN_FROM_NODE(node, variableType, variable) \
			variableType variable; \
			LoadPolygonalChain(node, variable);

		#define IS_PARAM_EXISTS(node, paramName) IsParamExists(node, paramName)

		#define HAS_CHILD(node, childPath) HasChild(node, childPath)

		bool IsParamExists(boost::property_tree::ptree& node, const string_t& attributeName);
		bool HasChild(boost::property_tree::ptree& node, const string_t& childPath);
		void LoadPolygon(boost::property_tree::ptree& polygonNode, Polygon2d& polygon);
		void LoadPolygonalChain(boost::property_tree::ptree& polygonNode, PolygonalChain2d& polygonalChain);
	}
}

#endif