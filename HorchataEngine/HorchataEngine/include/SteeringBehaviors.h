#pragma once

#include "Prerequisites.h"

class Actor;

/**
 * @class SteeringBehavior
 * @brief Abstract base class for steering behaviors applied to actors.
 */
class SteeringBehavior
{
public:

  /**
   * @brief Virtual destructor for the steering behavior.
   */
  virtual ~SteeringBehavior() = default;

  /**
   * @brief Applies the steering behavior to the given actor.
   * @param actor Pointer to the actor to apply the behavior to.
   * @param deltaTime Time elapsed since the last update.
   */
  virtual void apply(Actor* actor, float deltaTime) = 0;
};

/**
 * @class PathFollowing
 * @brief Steering behavior for following a series of waypoints.
 */
class PathFollowing : public SteeringBehavior
{
public:

  /**
   * @brief Constructs a PathFollowing behavior with a list of waypoints.
   * @param waypoints Vector of waypoints to follow.
   */
  PathFollowing(const std::vector<EngineMath::Vector2>& waypoints);

  /**
   * @brief Applies the path following behavior to the given actor.
   * @param actor Pointer to the actor to apply the behavior to.
   * @param deltaTime Time elapsed since the last update.
   */
  void apply(Actor* actor, float deltaTime) override;

private:

  /**
   * @brief List of waypoints for the path following behavior.
   */
  std::vector<EngineMath::Vector2> m_waypoints;
};

/**
 * @class Arrive
 * @brief Steering behavior for arriving smoothly at a target position.
 */
class Arrive : public SteeringBehavior
{
public:

  /**
   * @brief Constructs an Arrive behavior with a target position.
   * @param target The target position to arrive at.
   */
  Arrive(const EngineMath::Vector2& target);

  /**
   * @brief Applies the arrive behavior to the given actor.
   * @param actor Pointer to the actor to apply the behavior to.
   * @param deltaTime Time elapsed since the last update.
   */
  void apply(Actor* actor, float deltaTime) override;

private:

  /**
   * @brief The target position to arrive at.
   */
  EngineMath::Vector2 m_target;

  /**
   * @brief The radius within which the actor starts to slow down.
   */
  float m_slowingRadius = 150.f;
};