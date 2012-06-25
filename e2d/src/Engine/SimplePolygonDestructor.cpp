#include "e2d/Engine/SimplePolygonDestructor.h"

namespace e2d {
	namespace engine {
		void SimplePolygonDestructor::Destruct(const Polygon2d& sourcePolygon, const vec2& destructionPoint, const vec2& destructionVector, std::vector<Polygon2d>& resultPolygones) {
			// Игнорируем все параметры для разрушения
			vec2 sourcePolygonCenter = sourcePolygon.GetCenter();
			for (size_t i = 0; i < sourcePolygon.VerteciesCount() - 1; ++i) {
				Polygon2d polygon;
				polygon << sourcePolygonCenter << sourcePolygon[i] << sourcePolygon[i + 1];
				resultPolygones.push_back(polygon);
			}
			if (sourcePolygon.VerteciesCount() > 2) {
				Polygon2d polygon;
				polygon << sourcePolygonCenter << sourcePolygon[sourcePolygon.VerteciesCount() - 1] << sourcePolygon[0];
				resultPolygones.push_back(polygon);
			}
		}
	}
}