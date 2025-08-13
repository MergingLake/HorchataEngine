#pragma once

#include "Actor.h"
#include <SFML/Window/Keyboard.hpp>

/**
 * @class APlayer
 * @brief Represents a player-controlled actor in the game.
 */
class
	APlayer : public Actor
{
public:

	/**
	 * @brief Constructs a player actor with the given name.
	 * @param name The name of the player.
	 */
	APlayer(const std::string& name);

	/**
	 * @brief Destructor for the player actor.
	 */
	~APlayer() override = default;

	/**
	 * @brief Updates the player actor.
	 * @param deltaTime Time elapsed since the last update.
	 */
	void
		update(float deltaTime) override;

	/**
	 * @brief Handles player input and updates movement.
	 * @param deltaTime Time elapsed since the last update.
	 */
	void
		handleInput(float deltaTime);

	/**
	 * @brief Sets the current waypoint index for the player.
	 * @param index The waypoint index to set.
	 */
	void
		setCurrentWaypointIndex(size_t index);

	/**
	 * @brief Gets the current waypoint index for the player.
	 * @return The current waypoint index.
	 */
	size_t
		getCurrentWaypointIndex() const;

	/**
	 * @brief Sets the lap count for the player.
	 * @param laps The number of laps to set.
	 */
	void
		setLapCount(int laps);

	/**
	 * @brief Gets the lap count for the player.
	 * @return The current lap count.
	 */
	int
		getLapCount() const;

private:

	/**
	 * @brief Maximum speed of the player.
	 */
	float m_maxSpeed = 300.f;

	/**
	 * @brief Acceleration value for the player.
	 */
	float m_acceleration = 500.f;

	/**
	 * @brief Friction applied to the player's movement.
	 */
	float m_friction = 0.98f;

	/**
	 * @brief Current velocity of the player.
	 */
	EngineMath::Vector2 m_velocity;

	/**
	 * @brief Current waypoint index for waypoint logic (managed by GameManager).
	 */
	size_t m_currentWaypointIndex = 0;

	/**
	 * @brief Current lap count for waypoint logic (managed by GameManager).
	 */
	int m_lapCount = 0;
};