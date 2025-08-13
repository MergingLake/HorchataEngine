#include "ECS/ARacer.h"

ARacer::ARacer(const std::string& name) : Actor(name)
{

}

void ARacer::update(float deltaTime)
{
	// Apply all Steering Behaviors
	for (const auto& behavior : m_steeringBehaviors) {
		if (behavior) {
			behavior->apply(this, deltaTime);
		}
	}
	Actor::update(deltaTime);
}

void ARacer::setPlace(int newPlace)
{
	m_place = newPlace;
}

int ARacer::getPlace() const
{
	return m_place;
}

void ARacer::addSteeringBehavior(EngineUtilities::TSharedPointer<SteeringBehavior> behavior)
{
	m_steeringBehaviors.push_back(behavior);
}

void ARacer::setNextWaypoint(const EngineMath::Vector2& nextWaypoint)
{
	m_nextWaypoint = nextWaypoint;
}

const EngineMath::Vector2& ARacer::getNextWaypoint() const
{
	return m_nextWaypoint;
}

void ARacer::setVelocity(const EngineMath::Vector2& velocity)
{
	m_velocity = velocity;
}

const EngineMath::Vector2& ARacer::getVelocity() const
{
	return m_velocity;
}

void ARacer::setMaxSpeed(float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

float ARacer::getMaxSpeed() const
{
	return m_maxSpeed;
}

void ARacer::setCurrentWaypointIndex(size_t index)
{
	m_currentWaypointIndex = index;
}

size_t ARacer::getCurrentWaypointIndex() const
{
	return m_currentWaypointIndex;
}

void ARacer::setLapCount(int laps)
{
	m_lapCount = laps;
}

int ARacer::getLapCount() const
{
	return m_lapCount;
}