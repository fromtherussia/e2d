#ifndef E2D_ENGINE_DESTRUCTIBLE_ENTITY_H
#define E2D_ENGINE_DESTRUCTIBLE_ENTITY_H

namespace r2d {
	PREDECL_CLASS_WITH_PTR(IRenderable);
	class IRenderContext;
}

namespace e2d {
	namespace p2d {
		class World;
		PREDECL_CLASS_WITH_PTR(SimpleBody);
	}
	namespace engine {
		class IEntity;
		class IWithNamedPoints;
		class IBody;

		/*
			Разрушаемая сущность
		*/
		class DestructibleEntity: public IEntity {
		public:
			DestructibleEntity(
				p2d::World& world,
				IResourceController* resourceController,
				const string_t& graphicMaterialName,
				const string_t& physicMaterialName,
				const Polygon2d& geometry,
				const vec2& origin,
				float z,
				const Rect& uv
			);
			virtual ~DestructibleEntity();
			virtual void Render(r2d::IRenderContext& context, bool isDebug) const;
			virtual void UpdatePosition();
			void Destruct();
		
		protected:
			virtual Rect GetGraphicBoundingBox();
			virtual Rect GetPhysicBoundingBox();

		private:
			void AddPhysicShape(const Polygon2d& geometry, const p2d::BodyInitialMotion& initialMotion);
			void AddGraphicShape(const Polygon2d& geometry, const Rect& uv);

			Rect CalculateInnerUvForInnerRect(const Rect& outerRect, const Rect& innerRect, const Rect& outerUv);

			typedef std::vector<p2d::SimplePrimitivePtr> PhysicPrimitives;
			typedef std::vector<r2d::IRenderablePtr> GraphicPrimitives;
			PhysicPrimitives m_physicPrimitives;
			GraphicPrimitives m_graphicPrimitives;
			bool m_isDestructed;
			
			p2d::World& m_world;
			IResourceController* m_pResourceController;
			string_t m_graphicMaterialName;
			string_t m_physicMaterialName;
			Polygon2d m_sourceGeometry;
			float m_z;
			Rect m_uv;
			
			friend class EntityJoint;
		};
	}
}

#endif