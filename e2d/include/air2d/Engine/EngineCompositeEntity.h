#ifndef AIR2D_ENGINE_COMPOSITE_ENTITY_H
#define AIR2D_ENGINE_COMPOSITE_ENTITY_H

#include "EngineCommon.h"

namespace air2d {
	namespace engine {
		/*
			Составная сущность.
			Предназначена для создания сложных, комплексных объектов, физ. структура которых в течение всего времени жизни неизменна.
			"Набросал" внутрь объектов и забыл.
			Например ragdoll без возможности отделять части.
			Всегда является динамической сущностью.
		*/
		class CompositeEntity: public IEntity {
		public:
			CompositeEntity();
			virtual ~CompositeEntity();

			CompositeEntity& operator << (const DynamicPrimitiveEntityPtr& primitive);
			CompositeEntity& operator << (const PrimitiveJointPtr& joint);

		protected:
			virtual void UpdatePosition();
			virtual Rect GetGraphicBoundingBox();
			virtual void Render(const r2d::IRenderContext& context, const r2d::ICamera& camera, bool isDebug);
			virtual EntityType::Type GetType();

		private:
			typedef std::vector<DynamicPrimitiveEntityPtr> PrimitiveEntities;
			typedef std::vector<PrimitiveJointPtr> PrimitiveJoints;
			PrimitiveEntities m_primitives;
			PrimitiveJoints m_joints;
		};
	}
}

#endif