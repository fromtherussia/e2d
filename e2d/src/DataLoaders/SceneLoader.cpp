#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <cgl/Rect.h>
#include <cgl/Utils.h>
#include <cgl/TypesParser.h>

#include <r2d/ITexture.h>
#include <r2d/IEffect.h>
#include <r2d/IMaterial.h>
#include <r2d/IFactory.h>
#include <r2d/CompositeRenderable.h>

#include "Physics/Common.h"
#include "Physics/IPrimitive.h"

#include "Engine/IGraphicMaterialTable.h"
#include "Engine/IPhysicMaterialTable.h"
#include "Engine/IEntityFactory.h"
#include "Engine/IResourceController.h"
#include "Engine/IEntity.h"
#include "Engine/ComplexPhysicEntity.h"
// <KILLME>
#include "Physics/World.h"
// </KILLME>
#include "Engine/Scene.h"

#include "DataLoaders/Common.h"
#include "DataLoaders/Utils.h"
#include "DataLoaders/ResourceLoader.h"
#include "DataLoaders/IGraphicShapeLoader.h"
#include "DataLoaders/IPhysicShapeLoader.h"
#include "DataLoaders/IEntityLoader.h"
#include "DataLoaders/PolygonShapeLoader.h"
#include "DataLoaders/CircleShapeLoader.h"
#include "DataLoaders/DynamicGeometryObjectLoader.h"
#include "DataLoaders/ComplexPhysicEntityLoader.h"
#include "DataLoaders/SceneLoader.h"

using namespace boost::property_tree;

namespace e2d {
	namespace loaders {
		
		// Public
		
		SceneLoader::SceneLoader(engine::Scene* scene):
			scene(scene) {
			this->AddGraphicShapeLoader("polygon_shape", new DynamicGeometryObjectLoader());
			this->AddPhysicShapeLoader("polygon_shape", new PolygonShapeLoader());
			this->AddPhysicShapeLoader("circle_shape", new CircleShapeLoader());
			this->AddEntityLoader("complex_physic_entity", new ComplexPhysicEntityLoader());
		}
		
		SceneLoader::~SceneLoader() {

		}

		void SceneLoader::LoadScene(std::istream& inputStream) {
			ptree parsedEntity;
			read_json(inputStream, parsedEntity);

			ptree& graphicMaterialsNode = parsedEntity.get_child("graphic_materials");
			ptree& physicMaterialsNode = parsedEntity.get_child("physic_materials");
			ptree& entityPrototypesNode = parsedEntity.get_child("entity_prototypes");

			BOOST_FOREACH(ptree::value_type& graphicMaterialNode, graphicMaterialsNode) {
				LOAD_TYPED_PARAM_FROM_NODE(graphicMaterialNode, string_t, fileName, TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
				istream_ptr materialInputStream = ResourceLoader::GetResourceFileStream(fileName, ResourceLoader::GRAPHIC_MATERIAL);
				LoadGraphicMaterial(*materialInputStream);
			}

			BOOST_FOREACH(ptree::value_type& physicMaterialNode, physicMaterialsNode) {
				LOAD_TYPED_PARAM_FROM_NODE(physicMaterialNode, string_t, fileName, TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
				istream_ptr materialInputStream = ResourceLoader::GetResourceFileStream(fileName, ResourceLoader::PHYSIC_MATERIAL);
				LoadPhysicMaterial(*materialInputStream);
			}

			BOOST_FOREACH(ptree::value_type& entityPrototypeNode, entityPrototypesNode) {
				LOAD_TYPED_PARAM_FROM_NODE(entityPrototypeNode, string_t, fileName, TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
				istream_ptr entityInputStream = ResourceLoader::GetResourceFileStream(fileName, ResourceLoader::ENTITY_PROTOTYPE);
				*scene << ParseEntity(*entityInputStream);
			}
		}
		
		engine::IEntity* SceneLoader::ParseEntity(std::istream& inputStream) {
			ptree parsedEntity;
			read_json(inputStream, parsedEntity);
			
			ptree& entityNode = parsedEntity.get_child("entity");
			LOAD_TYPED_PARAM_FROM_SUBNODE(entityNode, string_t, entityType, "type", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);

			return GetEntityLoader(entityType)->Load(parsedEntity, scene, this);
		}

		r2d::IMaterial* SceneLoader::LoadGraphicMaterial(std::istream& inputStream) {
			ptree parsedEntity;
			read_json(inputStream, parsedEntity);
			
			ptree& materialNode = parsedEntity.get_child("material");
			ptree& effectNode = parsedEntity.get_child("material.effect");
			ptree& texturesNode = parsedEntity.get_child("material.textures");
			
			// Loading material properties
			LOAD_TYPED_PARAM_FROM_SUBNODE(materialNode, int, materialId, "id", TypesParser::GetType, TypesParser::ParseInt, CglTypes::ctInt);
			LOAD_TYPED_PARAM_FROM_SUBNODE(materialNode, string_t, materialName, "name", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, passProjectionMatrix, false, "pass_projection_matrix", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, passViewMatrix, false, "pass_view_matrix", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, passWorldMatrix, false, "pass_world_matrix", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, passVPMatrix, false, "pass_vp_matrix", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, passWVPMatrix, false, "pass_wvp_matrix", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_PARAM_FROM_SUBNODE(effectNode, string_t, effectSrc, "src", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);

			int flags = 0;
			if (passProjectionMatrix) {
				flags |= r2d::MaterialFlags::SetConstMatrixProjection;
			}
			if (passViewMatrix) {
				flags |= r2d::MaterialFlags::SetConstMatrixView;
			}
			if (passWorldMatrix) {
				flags |= r2d::MaterialFlags::SetConstMatrixWorld;
			}
			if (passVPMatrix) {
				flags |= r2d::MaterialFlags::SetConstMatrixVP;
			}
			if (passWVPMatrix) {
				flags |= r2d::MaterialFlags::SetConstMatrixWVP;
			}
			if (flags == 0) {
				throw std::runtime_error("no material flags set");
			}
			
			// Creating material
			r2d::IFactory* factoryPtr = scene->GetGraphicObjectsFactory();
			std::auto_ptr<r2d::IMaterial> materialPtr = factoryPtr->CreateMaterial(
				factoryPtr->CreateEffect(effectSrc),
				materialId,
				(r2d::MaterialFlags::Flags)flags
			);

			// Loading material textures
			BOOST_FOREACH(ptree::value_type& textureNode, texturesNode) {
				LOAD_TYPED_PARAM_FROM_SUBNODE(textureNode.second, string_t, textureSrc, "src", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
				LOAD_TYPED_PARAM_FROM_SUBNODE(textureNode.second, string_t, textureName, "name", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
				materialPtr->AddTexture(
					textureName, 
					factoryPtr->CreateTexture(textureSrc)
				);
			}

			// Adding material to material table
			scene->GetGraphicMaterialTable()->AddGraphicMaterial(materialName, materialPtr.release());
			return materialPtr;
		}
		
		p2d::Material* SceneLoader::LoadPhysicMaterial(std::istream& inputStream) {
			ptree parsedEntity;
			read_json(inputStream, parsedEntity);

			ptree& materialNode = parsedEntity.get_child("material");
			
			// Loading material properties
			LOAD_TYPED_PARAM_FROM_SUBNODE(materialNode, string_t, materialName, "name", TypesParser::GetType, TypesParser::ParseString, CglTypes::ctString);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, float, density, 5.0f, "density", TypesParser::GetType, TypesParser::ParseFloat, CglTypes::ctFloat);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, float, friction, 2.0f, "friction", TypesParser::GetType, TypesParser::ParseFloat, CglTypes::ctFloat);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, float, restitution, 0.5f, "restitution", TypesParser::GetType, TypesParser::ParseFloat, CglTypes::ctFloat);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, float, linearDamping, 0.1f, "linear_damping", TypesParser::GetType, TypesParser::ParseFloat, CglTypes::ctFloat);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, float, angularDamping, 0.0f, "angular_damping", TypesParser::GetType, TypesParser::ParseFloat, CglTypes::ctFloat);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, isSensor, false, "is_sensor", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, isBullet, false, "is_bullet", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, isActive, true, "is_active", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, isAwake, true, "is_awake", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, allowSleep, true, "allow_sleep", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);
			LOAD_TYPED_OPTIONAL_PARAM_FROM_SUBNODE(materialNode, bool, isRotationDisabled, false, "is_rotation_disabled", TypesParser::GetType, TypesParser::ParseBool, CglTypes::ctBool);

			// Creating material
			p2d::Material* pMaterial = new p2d::Material();
			pMaterial->m_density = density;
			pMaterial->m_friction = friction;
			pMaterial->m_restitution = restitution;
			pMaterial->m_linearDamping = linearDamping;
			pMaterial->m_angularDamping = angularDamping;
			pMaterial->m_isSensor = isSensor;
			pMaterial->m_bullet = isBullet;
			pMaterial->m_active = isActive;
			pMaterial->m_awake = isAwake;
			pMaterial->m_allowSleep = allowSleep;
			pMaterial->m_fixedRotation = isRotationDisabled;

			scene->GetPhysicMaterialTable()->AddPhysicMaterial(materialName, pMaterial);

			return pMaterial;
		}
		
		// Private

		void SceneLoader::AddGraphicShapeLoader(const string_t& shapeTypeName, IGraphicShapeLoader* pLoader) {
			m_graphicShapeLoaders[shapeTypeName] = IGraphicShapeLoaderPtr(pLoader);
		}

		void SceneLoader::AddPhysicShapeLoader(const string_t& shapeTypeName, IPhysicShapeLoader* pLoader) {
			m_physicShapeLoaders[shapeTypeName] = IPhysicShapeLoaderPtr(pLoader);
		}

		void SceneLoader::AddEntityLoader(const string_t& shapeTypeName, IEntityLoader* pLoader) {
			m_entityLoaders[shapeTypeName] = IEntityLoaderPtr(pLoader);
		}

		const IGraphicShapeLoader* SceneLoader::GetGraphicShapeLoader(const string_t& shapeTypeName) {
			if (m_graphicShapeLoaders.count(shapeTypeName) == 0) {
				throw std::runtime_error(formatString("can't find loader for graphic shape with type '%s'", shapeTypeName.c_str()));
			}
			return m_graphicShapeLoaders[shapeTypeName].get();
		}

		const IPhysicShapeLoader* SceneLoader::GetPhysicShapeLoader(const string_t& shapeTypeName) {
			if (m_physicShapeLoaders.count(shapeTypeName) == 0) {
				throw std::runtime_error(formatString("can't find loader for physic shape with type '%s'", shapeTypeName.c_str()));
			}
			return m_physicShapeLoaders[shapeTypeName].get();
		}

		const IEntityLoader* SceneLoader::GetEntityLoader(const string_t& entityTypeName) {
			if (m_entityLoaders.count(entityTypeName) == 0) {
				throw std::runtime_error(formatString("can't find loader for entity with type '%s'", entityTypeName.c_str()));
			}
			return m_entityLoaders[entityTypeName].get();
		}

	}
}