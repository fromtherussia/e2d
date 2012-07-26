#include <Box2D/Box2D.h>

#include "p2d/Utils.h"

#include "p2d/World.h"

namespace p2d {
	// ContactListener

	class ContactListener: public b2ContactListener {
	public:
		void BeginContact(b2Contact* contactPtr);
		void EndContact(b2Contact* contactPtr);
		void PreSolve(b2Contact* contactPtr, const b2Manifold* oldManifoldPtr);
		void PostSolve(b2Contact* contactPtr, const b2ContactImpulse* impulsePtr);
	};

	void ContactListener::BeginContact(b2Contact* contactPtr) {
		void* bodyUserDataPtr1 = contactPtr->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataPtr2 = contactPtr->GetFixtureB()->GetBody()->GetUserData();
		
		if (bodyUserDataPtr1 == NULL && bodyUserDataPtr2 == NULL) {
			return;
		}

		if (contactPtr->GetManifold()->pointCount == 1) {
			b2WorldManifold worldManifold;
			contactPtr->GetWorldManifold(&worldManifold);
			b2Manifold* localManifoldPtr = contactPtr->GetManifold();

			static_cast<ICollisionListener*>(bodyUserDataPtr1)->ProcessCollisionBegin(
				*static_cast<ICollisionListener*>(bodyUserDataPtr2),
				CollisionParams
				(
					ToGlmVec(localManifoldPtr->points[0].localPoint),
					ToGlmVec(worldManifold.points[0]),
					ToGlmVec(localManifoldPtr->localNormal)
				)
			);
		} else {
			b2WorldManifold worldManifold;
			contactPtr->GetWorldManifold(&worldManifold);
			b2Manifold* localManifoldPtr = contactPtr->GetManifold();

			static_cast<ICollisionListener*>(bodyUserDataPtr1)->ProcessCollisionBegin(
				*static_cast<ICollisionListener*>(bodyUserDataPtr2),
				CollisionParams
				(
					ToGlmVec(localManifoldPtr->points[0].localPoint),
					ToGlmVec(localManifoldPtr->points[1].localPoint),
					ToGlmVec(worldManifold.points[0]),
					ToGlmVec(worldManifold.points[1]),
					ToGlmVec(localManifoldPtr->localNormal)
				)
			);
		}
	}

	void ContactListener::EndContact(b2Contact* contactPtr) {
		void* bodyUserDataPtr1 = contactPtr->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataPtr2 = contactPtr->GetFixtureB()->GetBody()->GetUserData();
		
		if (bodyUserDataPtr1 == NULL && bodyUserDataPtr2 == NULL) {
			return;
		}

		if (contactPtr->GetManifold()->pointCount == 1)
		{
			b2WorldManifold worldManifold;
			contactPtr->GetWorldManifold(&worldManifold);
			b2Manifold* localManifoldPtr = contactPtr->GetManifold();

			static_cast<ICollisionListener*>(bodyUserDataPtr1)->ProcessCollisionEnd(
				*static_cast<ICollisionListener*>(bodyUserDataPtr2),
				CollisionParams
				(
					ToGlmVec(localManifoldPtr->points[0].localPoint),
					ToGlmVec(worldManifold.points[0]),
					ToGlmVec(localManifoldPtr->localNormal)
				)
			);
		} else {
			b2WorldManifold worldManifold;
			contactPtr->GetWorldManifold(&worldManifold);
			b2Manifold* localManifoldPtr = contactPtr->GetManifold();

			static_cast<ICollisionListener*>(bodyUserDataPtr1)->ProcessCollisionEnd(
				*static_cast<ICollisionListener*>(bodyUserDataPtr2),
				CollisionParams
				(
					ToGlmVec(localManifoldPtr->points[0].localPoint),
					ToGlmVec(localManifoldPtr->points[1].localPoint),
					ToGlmVec(worldManifold.points[0]),
					ToGlmVec(worldManifold.points[1]),
					ToGlmVec(localManifoldPtr->localNormal)
				)
			);
		}
	}

	void ContactListener::PreSolve(b2Contact* contactPtr, const b2Manifold* oldManifoldPtr) {
	}

	void ContactListener::PostSolve(b2Contact* contactPtr, const b2ContactImpulse* impulsePtr) {
	}

	// RectQueryCallback

	class RectQueryCallback: public b2QueryCallback
	{
	public:
		RectQueryCallback(BodyKind::Kind kind);
		bool ReportFixture(b2Fixture* fixturePtr);
		std::auto_ptr<CollisionListeners> GetCollisionListeners();
	private:
		BodyKind::Kind kind;
		std::auto_ptr<CollisionListeners> collisionListenersPtr;
	};

	RectQueryCallback::RectQueryCallback(BodyKind::Kind kind):
		kind(kind),
		collisionListenersPtr(new CollisionListeners()) {
	}

	bool RectQueryCallback::ReportFixture(b2Fixture* fixturePtr) {
		b2Body* bodyPtr = fixturePtr->GetBody();

		if (ToBodyKind(bodyPtr->GetType()) != kind) {
			return true;
		}

		void* userDataPtr = bodyPtr->GetUserData();
		if (userDataPtr == NULL) {
			return true;
		}

		collisionListenersPtr->push_back(static_cast<ICollisionListener*>(userDataPtr));
		return true;
	}

	std::auto_ptr<CollisionListeners> RectQueryCallback::GetCollisionListeners() {
		return collisionListenersPtr;
	}

	// RayQueryCallback

	class RayQueryCallback: public b2RayCastCallback {
	public:
		RayQueryCallback(BodyKind::Kind kind, bool findFirst = false);
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
		std::auto_ptr<RaycastIntersections> GetRaycastIntersections();
	private:
		bool findFirst;
		BodyKind::Kind kind;
		std::auto_ptr<RaycastIntersections> raycastIntersectionsPtr;
	};

	RayQueryCallback::RayQueryCallback(BodyKind::Kind kind, bool findFirst):
		kind(kind),
		findFirst(findFirst),
		raycastIntersectionsPtr(new RaycastIntersections()) {
	}

	float32 RayQueryCallback::ReportFixture(b2Fixture* fixturePtr, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
		b2Body* bodyPtr = fixturePtr->GetBody();

		if (ToBodyKind(bodyPtr->GetType()) != kind) {
			return -1.0f;
		}

		void* userDataPtr = bodyPtr->GetUserData();
		
		if (userDataPtr == NULL) {
			return -1.0f;
		}

		raycastIntersectionsPtr->push_back(
			RaycastIntersection(
				static_cast<ICollisionListener*>(userDataPtr),
				ToGlmVec(point),
				ToGlmVec(normal)
			)
		);

		return findFirst ? 0.0f : fraction;
	}

	std::auto_ptr<RaycastIntersections> RayQueryCallback::GetRaycastIntersections() {
		return raycastIntersectionsPtr;
	}

	// World

	World::World(const vec2& gravity, bool sleepWhenInactive):
		m_worldPtr(new b2World(ToBox2dVec(gravity))) {
	}
	
	World::~World() {
	}

	void World::Simulate(float frameTime) {
		m_worldPtr->Step(frameTime, 6, 2);
	}

	std::auto_ptr<CollisionListeners> World::QueryPrimitives(const Rect& rect, BodyKind::Kind kind) const
	{
		b2AABB aabb;
		aabb.lowerBound.Set(rect.x1, rect.y1);
		aabb.upperBound.Set(rect.x2, rect.y2);

		RectQueryCallback callback(kind);
		m_worldPtr->QueryAABB(&callback, aabb);

		return callback.GetCollisionListeners();
	}

	std::auto_ptr<RaycastIntersections> World::QueryPrimitives(const vec2& lineBegin, const vec2& lineEnd, BodyKind::Kind kind, bool findFirst) const
	{
		RayQueryCallback callback(kind, findFirst);
		m_worldPtr->RayCast(&callback, ToBox2dVec(lineBegin), ToBox2dVec(lineEnd));

		return callback.GetRaycastIntersections();
	}
}