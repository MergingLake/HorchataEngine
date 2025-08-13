#pragma once

#include "Actor.h"
#include "SteeringBehaviors.h"
#include <vector>

/**
 * @class ARacer
 * @brief Represents a racing actor controlled by AI or logic in the game.
 */
class
	ARacer : public Actor
{
public:

	/**
	 * @brief Constructs a racer actor with the given name.
	 * @param name The name of the racer.
	 */
	ARacer(const std::string& name);

	/**
	 * @brief Destructor for the racer actor.
	 */
	~ARacer() override = default;

	/**
	 * @brief Updates the racer actor.
	 * @param deltaTime Time elapsed since the last update.
	 */
	void
		update(float deltaTime) override;

	/**
	 * @brief Sets the current place (rank) of the racer.
	 * @param newPlace The new place value.
	 */
	void
		setPlace(int newPlace);

	/**
	 * @brief Gets the current place (rank) of the racer.
	 * @return The current place value.
	 */
	int
		getPlace() const;

	/**
	 * @brief Adds a steering behavior to the racer.
	 * @param behavior Shared pointer to the steering behavior to add.
	 */
	void
		addSteeringBehavior(EngineUtilities::TSharedPointer<SteeringBehavior> behavior);

	/**
	 * @brief Sets the next waypoint for the racer.
	 * @param nextWaypoint The position of the next waypoint.
	 */
	void
		setNextWaypoint(const EngineMath::Vector2& nextWaypoint);

	/**
	 * @brief Gets the next waypoint for the racer.
	 * @return The position of the next waypoint.
	 */
	const EngineMath::Vector2&
		getNextWaypoint() const;

	/**
	 * @brief Sets the velocity of the racer.
	 * @param velocity The velocity vector to set.
	 */
	void
		setVelocity(const EngineMath::Vector2& velocity);

	/**
	 * @brief Gets the current velocity of the racer.
	 * @return The velocity vector.
	 */
	const EngineMath::Vector2&
		getVelocity() const;

	/**
	 * @brief Sets the maximum speed of the racer.
	 * @param maxSpeed The maximum speed value.
	 */
	void
		setMaxSpeed(float maxSpeed);

	/**
	 * @brief Gets the maximum speed of the racer.
	 * @return The maximum speed value.
	 */
	float
		getMaxSpeed() const;

	/**
	 * @brief Sets the current waypoint index for the racer.
	 * @param index The waypoint index to set.
	 */
	void
		setCurrentWaypointIndex(size_t index);

	/**
	 * @brief Gets the current waypoint index for the racer.
	 * @return The current waypoint index.
	 */
	size_t
		getCurrentWaypointIndex() const;

	/**
	 * @brief Sets the lap count for the racer.
	 * @param laps The number of laps to set.
	 */
	void
		setLapCount(int laps);

	/**
	 * @brief Gets the lap count for the racer.
	 * @return The current lap count.
	 */
	int
		getLapCount() const;

private:

	/**
	 * @brief The current place (rank) of the racer.
	 */
	int m_place = 0;

	/**
	 * @brief The current waypoint index for the racer.
	 */
	size_t m_currentWaypointIndex = 0;

	/**
	 * @brief The position of the next waypoint.
	 */
	EngineMath::Vector2 m_nextWaypoint;

	/**
	 * @brief The maximum speed of the racer.
	 */
	float m_maxSpeed = 250.f;

	/**
	 * @brief The current velocity of the racer.
	 */
	EngineMath::Vector2 m_velocity;

	/**
	 * @brief The current lap count for the racer.
	 */
	int m_lapCount = 0;

	/**
	 * @brief List of steering behaviors applied to the racer.
	 */
	std::vector<EngineUtilities::TSharedPointer<SteeringBehavior>> m_steeringBehaviors;
};