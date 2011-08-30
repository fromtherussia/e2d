#include <cgl/Rect.h>
#include <cgl/Utils.h>
#include <cgl/TypesParser.h>

#include "EngineIEntity.h"

#include "ResourceXmlLoader.h"

namespace e2d {
	namespace loaders {

		// MOVEME:
rapidxml::xml_document<char> document;
		
		r2d::IRenderable* DynamicGeometryObjectXmlLoader::Load(rapidxml::xml_node<>* node) const {
			// TODO: add Rect(const vec4&) ctor or kinda that

			rapidxml::xml_node<>* optionsNode = node->first_node("options");
			vec2 offset = vec2(); // default vec2(0.0f, 0.0f)
			int depth = 0; // default 0

			LOAD_TYPED_ATTRIBUTE_VALUE(optionsNode, offset, "offset", ParseVec2, CglTypes::ctVec2);
			LOAD_TYPED_ATTRIBUTE_VALUE(optionsNode, depth, "depth", ParseInt, CglTypes::ctInt);

			rapidxml::xml_node<>* pVerticesNode = node->first_node("vertices");
			if (pVerticesNode == NULL) {
				throw std::runtime_error("vertices section not found");
			}
			Polygon2d geometry = ParsePolygon(pVerticesNode);

			if (IsAttributeExists(node, "uv")) {
				Rect uv = Rect();
				LOAD_TYPED_ATTRIBUTE_VALUE(optionsNode, uv, "uv", ParseRect, CglTypes::ctRect);
				// return ...;
				return NULL;

			} else if (IsAttributeExists(node, "pixel_per_uv")) {
				vec2 pixelPerUv = vec2();
				LOAD_TYPED_ATTRIBUTE_VALUE(optionsNode, pixelPerUv, "pixel_per_uv", ParseVec2, CglTypes::ctVec2);
				// return ...;
				return NULL;
			} else {
				throw std::runtime_error("uv not set");
			}
		}

		// MOVEME

		bool IsAttributeExists(rapidxml::xml_node<>* node, const string_t& attributeName) {
			return node->first_attribute(attributeName.c_str()) != NULL;
		}

		Polygon2d ParsePolygon(rapidxml::xml_node<>* node) {
			Polygon2d resultPolygon;
			for (rapidxml::xml_node<>* vertexNode = node->first_node("vertex"); vertexNode; vertexNode = vertexNode->next_sibling("vertex")) {
				char* vecStringValue = vertexNode->value();
				CglTypes::Type type = TypesParser::GetType(vecStringValue);
				if (type != CglTypes::ctVec2) {
					throw std::runtime_error("");
				}
				resultPolygon << TypesParser::ParseVec2(vecStringValue);
			}
			return resultPolygon;
		}

		// Public
		
		engine::IEntity* EngineObjectsXmlLoader::ParseEntity(const string_t& xmlText) {
			char* xmlTextBuffer = new char[xmlText.length() + 1];
			strncpy(xmlTextBuffer, xmlText.c_str(), xmlText.length() + 1);
try {
			
	document.parse<rapidxml::parse_full | rapidxml::parse_validate_closing_tags>(xmlTextBuffer);

			rapidxml::xml_node<>* node = 
				document.first_node("entity")
					->first_node("graphics")
					->first_node("shapes");

			
			for (rapidxml::xml_node<>* shapeNode = node->first_node(); shapeNode; shapeNode = shapeNode->next_sibling()) {
				LoadGraphicShape(shapeNode);
			}
			} catch (rapidxml::parse_error & e) {
				char* w = e.where<char>();
				const char * ex = e.what();
				w[0] = 0;
			}
				
			/*document.first_node("entity")
					
					
					
					->first_node("vertecies");
*/
			//Polygon2d poly = ParsePolygon(node);

			return NULL;
		}

		void EngineObjectsXmlLoader::AddGraphicShapeLoader(const string_t& shapeTypeName, IGraphicShapeXmlLoader* pLoader) {
			m_graphicShapeLoaders[shapeTypeName] = IGraphicShapeXmlLoaderPtr(pLoader);
		}

		void EngineObjectsXmlLoader::AddPhysicShapeLoader(const string_t& shapeTypeName, IPhysicShapeXmlLoader* pLoader) {
			m_physicShapeLoaders[shapeTypeName] = IPhysicShapeXmlLoaderPtr(pLoader);
		}

		// Private

		r2d::IRenderable* EngineObjectsXmlLoader::LoadGraphicShape(rapidxml::xml_node<>* node) {
			string_t nodeName = node->name();
			size_t nameSize = node->name_size();
			return GetGraphicShapeLoader(nodeName)->Load(node);
			
		}

		physics::IShape* EngineObjectsXmlLoader::LoadPhysicShape(rapidxml::xml_node<>* node) {
			return GetPhysicShapeLoader(node->name())->Load(node);
		}

		const IGraphicShapeXmlLoader* EngineObjectsXmlLoader::GetGraphicShapeLoader(const string_t& shapeTypeName) {
			if (m_graphicShapeLoaders.count(shapeTypeName) == 0) {
				throw std::runtime_error(formatString("can't find loader for graphic shape with type '%s'", shapeTypeName.c_str()));
			}
			return m_graphicShapeLoaders[shapeTypeName].get();
		}

		const IPhysicShapeXmlLoader* EngineObjectsXmlLoader::GetPhysicShapeLoader(const string_t& shapeTypeName) {
			if (m_physicShapeLoaders.count(shapeTypeName) == 0) {
				throw std::runtime_error(formatString("can't find loader for physic shape with type '%s'", shapeTypeName.c_str()));
			}
			return m_physicShapeLoaders[shapeTypeName].get();
		}
	}
}