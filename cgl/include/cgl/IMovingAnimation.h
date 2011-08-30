#ifndef CGL_IMOVING_ANIMATION_H
#define CGL_IMOVING_ANIMATION_H

template <typename TrajectoryPointType>
class IMovingAnimation {
public:
	typedef TrajectoryPointType PointType;

	IMovingAnimation() {
	}

	virtual ~IMovingAnimation()	{
	}

	bool AnimateMoving(const PointType& from, const PointType& to, float avgSpeed) {
		if (avgSpeed <= 0.0f) {
			return false;
		}
		m_to = to;
		m_from = from;
		m_avgSpeed = avgSpeed;
		m_timer.Start();
		return true;
	}

	const PointType& GetPosition() {
		if (m_timer.IsActive()) {
			return GetTrajectoryPoint(m_from, m_to, m_avgSpeed, m_timer.TimeElapsed());
		} else {
			return m_to;
		}
	}

	const PointType& Update() {
		m_timer.Update();

		if (GetTrajectoryTime() <= m_timer.TimeElapsed()) {
			m_timer.Stop();
		}

		if (m_timer.IsActive()) {
			return GetTrajectoryPoint(m_timer.TimeElapsed());
		} else {
			return m_to;
		}		
	}

	bool ResetAnimation() {
		m_timer.Reset();
		return m_timer.Start();
	}

	bool IsAnimationEnded() {
		return !m_timer.IsActive();
	}

	virtual const PointType GetTrajectoryPoint (float time) const = 0;

private:
	xStopWatch m_timer;

protected:
	PointType m_to;
	PointType m_from;
	float m_avgSpeed;

	virtual const PointType GetAbsoluteValue(float time) const = 0;
	virtual float GetTrajectoryTime() const = 0;
};

typedef IMovingAnimation<float> IScalarMovingAnimation;

#endif