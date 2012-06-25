#ifndef CGL_PARABOLIC_MOVING_H
#define CGL_PARABOLIC_MOVING_H

#include "IMovingAnimation.h"

class ParabolicScalarMoving: public IScalarMovingAnimation {
public:
	ParabolicScalarMoving(float a, float b, float c):
		m_a(a),
		m_b(b),
		m_c(c) {
	}
	  
	virtual ~ParabolicScalarMoving() {
	}

	virtual const float GetTrajectoryPoint (float time) const {
		float trajectoryLength = m_to - m_from;
		float valueTrajectoryEnd = GetAbsoluteValue(trajectoryLength / m_avgSpeed);

		return m_from + trajectoryLength * GetAbsoluteValue(time) / valueTrajectoryEnd;
	}
protected:
	virtual const float GetAbsoluteValue (float time) const {
		return time * (time * m_a + m_b) + m_c;
	}
	virtual float GetTrajectoryTime () const {
		return (m_to - m_from) / m_avgSpeed;
	}
private:
	float m_averageSpeed;
	float m_a;
	float m_b;
	float m_c;
};
#define PARABOLIC_SPEED_FAST 1.0f,-5.0f,0.0f

#endif