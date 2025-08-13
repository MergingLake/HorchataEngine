#include "SteeringBehaviors.h"
#include "ECS/Actor.h"
#include "ECS/Transform.h"
#include "ECS/ARacer.h"

// Implementation of PathFollowing
PathFollowing::PathFollowing(const std::vector<EngineMath::Vector2>& waypoints)
	: m_waypoints(waypoints)
{
}

void PathFollowing::apply(Actor* actor, float deltaTime)
{
	ARacer* racer = dynamic_cast<ARacer*>(actor);
	if (!racer) return;

	EngineUtilities::TSharedPointer<Transform> transform = racer->getComponent<Transform>();
	if (!transform) return;

	EngineMath::Vector2 currentPos = transform->getPosition();
	size_t currentWaypointIndex = racer->getCurrentWaypointIndex();

	// If we are close to the current waypoint, advance to the next one
	EngineMath::Vector2 targetPos = m_waypoints[currentWaypointIndex];
	float distanceToWaypoint = EngineMath::Vector2::distance(currentPos, targetPos);
	if (distanceToWaypoint < 50.f) { // Threshold of 50.f to detect arrival at the waypoint
		currentWaypointIndex = (currentWaypointIndex + 1) % m_waypoints.size();
		racer->setCurrentWaypointIndex(currentWaypointIndex);
		targetPos = m_waypoints[currentWaypointIndex];
	}

	// More detailed "Seek" behavior to follow the path
	EngineMath::Vector2 desiredVelocity = targetPos - currentPos;
	float length = desiredVelocity.length();

	// If the bot is close to the target, reduce speed ("Arrive" behavior)
	if (length < 200.0f) {
		desiredVelocity = desiredVelocity.normalized() * (racer->getMaxSpeed() * (length / 200.0f));
	}
	else {
		desiredVelocity = desiredVelocity.normalized() * racer->getMaxSpeed();
	}

	EngineMath::Vector2 steering = desiredVelocity - racer->getVelocity();
	EngineMath::Vector2 newVelocity = racer->getVelocity() + steering * deltaTime;

	// Limit maximum speed
	if (newVelocity.length() > racer->getMaxSpeed()) {
		newVelocity = newVelocity.normalized() * racer->getMaxSpeed();
	}
	racer->setVelocity(newVelocity);

	// Apply velocity to the transform
	transform->setPosition(currentPos + newVelocity * deltaTime);
}

// Implementation of Arrive methods
Arrive::Arrive(const EngineMath::Vector2& target)
	: m_target(target)
{
	// The slowing radius is initialized in the header
}

void Arrive::apply(Actor* actor, float deltaTime)
{
	ARacer* racer = dynamic_cast<ARacer*>(actor);
	if (!racer) return;

	EngineUtilities::TSharedPointer<Transform> transform = racer->getComponent<Transform>();
	if (!transform) return;

	EngineMath::Vector2 currentPos = transform->getPosition();
	EngineMath::Vector2 desiredVelocity = m_target - currentPos;
	float distance = desiredVelocity.length();

	if (distance > 0)
	{
		// If the distance is less than the slowing radius, Arrive
		if (distance < m_slowingRadius)
		{
			float desiredSpeed = racer->getMaxSpeed() * (distance / m_slowingRadius);
			desiredVelocity = desiredVelocity.normalized() * desiredSpeed;
		}
		else // Otherwise, act as Seek (maximum speed)
		{
			desiredVelocity = desiredVelocity.normalized() * racer->getMaxSpeed();
		}

		// Calculate steering force
		EngineMath::Vector2 steering = desiredVelocity - racer->getVelocity();
		EngineMath::Vector2 newVelocity = racer->getVelocity() + steering * deltaTime;

		// Limit maximum speed
		if (newVelocity.length() > racer->getMaxSpeed())
		{
			newVelocity = newVelocity.normalized() * racer->getMaxSpeed();
		}
		racer->setVelocity(newVelocity);

		// Apply velocity to the transform
		transform->setPosition(currentPos + newVelocity * deltaTime);
	}
	else
	{
		// Stop the racer if it is already at the target
		racer->setVelocity({ 0, 0 });
	}
}