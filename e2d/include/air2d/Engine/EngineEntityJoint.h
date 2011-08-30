#ifndef AIR2D_ENGINE_ENTITY_JOINT_H
#define AIR2D_ENGINE_ENTITY_JOINT_H

namespace air2d {
	namespace engine {
		/*
			Соединитель сущностей.
		*/
		class EntityJoint {
			physics::JointPtr m_jointPtr;
			PrimitiveEntityPtr m_primitivePtr1;
			PrimitiveEntityPtr m_primitivePtr2;
			EntityJoint(const PrimitiveEntityPtr& primitive1, const string_t& name1, const PrimitiveEntityPtr& primitive2, const string_t& name2);
		public:
			~EntityJoint();

			virtual void Render(const r2d::IRenderContext& context, const r2d::ICamera& camera, bool isDebug);
			// Фабричные методы для создания Joints
			// static PrimitiveJointPtr JoinByLength();
			// и т.д.
		};
		DEFPTR(EntityJoint);
	}
}

#endif