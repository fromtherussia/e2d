#ifndef AIR2D_RESOURCE_XML_LOADER_H
#define AIR2D_RESOURCE_XML_LOADER_H

#include "DataLoadersCommon.h"

namespace e2d {
	namespace loaders {

		bool IsAttributeExists(rapidxml::xml_node<>* node, const string_t& attributeName);

		#define LOAD_TYPED_ATTRIBUTE_VALUE(node, variableName, attributeName, parseFunction, type) \
			rapidxml::xml_attribute<>* p##variableName##Attribute = node->first_attribute(attributeName); \
			if (p##variableName##Attribute != NULL) { \
				string_t attributeStringValue = p##variableName##Attribute->value(); \
				if (TypesParser::GetType(attributeStringValue) != type) { \
					throw std::runtime_error(formatString("%s attribute should be %s", attributeName, #type)); \
				} \
				variableName = TypesParser::parseFunction(attributeStringValue); \
			}

		Polygon2d ParsePolygon(rapidxml::xml_node<>* node);

		class IGraphicShapeXmlLoader {
		public:
			virtual r2d::IRenderable* Load(rapidxml::xml_node<>* node) const = 0;
		};
		DEFPTR(IGraphicShapeXmlLoader);

		class IPhysicShapeXmlLoader {
		public:
			virtual physics::IShape* Load(rapidxml::xml_node<>* node) const = 0;
		};
		DEFPTR(IPhysicShapeXmlLoader);

		/*
			uv and pixel_per_uv at the same time do not work
			uv has higher priority
		*/
		class DynamicGeometryObjectXmlLoader: public IGraphicShapeXmlLoader {
		public:
			virtual r2d::IRenderable* Load(rapidxml::xml_node<>* node) const;
		};

		class EngineObjectsXmlLoader {
		public:
			engine::IEntity* ParseEntity(const string_t& xmlText);
			
			void AddGraphicShapeLoader(const string_t& shapeTypeName, IGraphicShapeXmlLoader* pLoader);
			void AddPhysicShapeLoader(const string_t& shapeTypeName, IPhysicShapeXmlLoader* pLoader);

		private:
			r2d::IRenderable* LoadGraphicShape(rapidxml::xml_node<>* node);
			physics::IShape* LoadPhysicShape(rapidxml::xml_node<>* node);
			const IGraphicShapeXmlLoader* GetGraphicShapeLoader(const string_t& shapeTypeName);
			const IPhysicShapeXmlLoader* GetPhysicShapeLoader(const string_t& shapeTypeName);

			std::map<string_t, IGraphicShapeXmlLoaderPtr> m_graphicShapeLoaders;
			std::map<string_t, IPhysicShapeXmlLoaderPtr> m_physicShapeLoaders;
		};
	}
}

#endif