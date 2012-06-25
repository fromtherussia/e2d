#ifndef R2D_COMMON_H
#define R2D_COMMON_H

#include <cgl/MathTypes.h>

namespace r2d {
	#define TILE_METRICS_TO_UV(boundingRect, tileMetrics) \
		Rect(0.0f, 0.0f, boundingRect.Width() / tileMetrics.x, boundingRect.Height() / tileMetrics.y)

	struct AnimationProperties {
		bool m_useAnimation;
		float m_step;
		float m_frameTime;
		int m_framesCount;

		AnimationProperties(bool useAnimation = false, float step = 0.04f, float frameTime = 0.04f, int framesCount = 25):
			m_useAnimation(useAnimation),
			m_step(step),
			m_frameTime(frameTime),
			m_framesCount(framesCount) {
		}
		
		~AnimationProperties() {
		}
		
		float GetCycleTime() const {
			return m_frameTime * m_framesCount;
		}
	};

	class MaterialFlags {
	public:
		enum Flags {
			NoFlags = 0x0000,
			SetConstMatrixWorld = 0x0001,
			SetConstMatrixView = 0x0002,
			SetConstMatrixProjection = 0x0004,
			SetConstMatrixWVP = 0x0008,
			SetConstMatrixVP = 0x0010
		};
	};

	class ITexture;
	class IEffect;
	class IMaterial;
	class IFont;
	class IRenderable;
	class IDynamicGeometeryObject;
	class ICamera;
	class IRenderContext;
	class IFactory;
	class DebugRenderer;
}

#endif