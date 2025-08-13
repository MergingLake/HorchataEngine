#pragma once

#include <vector>
#include "ECS/APlayer.h"
#include "ECS/ARacer.h"
#include "ECS/Actor.h"
#include "CShape.h"
#include "Prerequisites.h"

/**
 * @class GameManager
 * @brief Manages the main game logic, including track, waypoints, racers, player, and HUD.
 */
class GameManager
{
public:

  /**
   * @brief Constructs a GameManager instance.
   */
  GameManager();

  /**
   * @brief Initializes the game manager with the track actor and waypoints.
   * @param trackActor Shared pointer to the track actor.
   * @param waypoints Vector of waypoint positions for the track.
   */
  void
    init(EngineUtilities::TSharedPointer<Actor> trackActor, std::vector<EngineMath::Vector2> waypoints);

  /**
   * @brief Updates the game state, including racers and player.
   * @param deltaTime Time elapsed since the last update.
   * @param racers Vector of shared pointers to ARacer objects.
   * @param player Shared pointer to the player object.
   */
  void
    update(float deltaTime, std::vector<EngineUtilities::TSharedPointer<ARacer>>& racers, EngineUtilities::TSharedPointer<APlayer>& player);

  /**
   * @brief Renders the HUD (Heads-Up Display) to the window.
   * @param window Shared pointer to the window where the HUD will be rendered.
   */
  void
    renderHUD(EngineUtilities::TSharedPointer<Window>& window);

private:

  /**
   * @brief Updates the ranking of racers and player for the leaderboard.
   * @param racers Vector of shared pointers to ARacer objects.
   * @param player Shared pointer to the player object.
   */
  void updateRanks(std::vector<EngineUtilities::TSharedPointer<ARacer>>& racers, EngineUtilities::TSharedPointer<APlayer>& player);

  /**
   * @brief Checks for collisions between the player and the track.
   * @param player Shared pointer to the player object.
   */
  void checkCollisions(EngineUtilities::TSharedPointer<APlayer>& player);

  /**
   * @brief Shared pointer to the track actor.
   */
  EngineUtilities::TSharedPointer<Actor> m_trackActor;

  /**
   * @brief Vector of waypoint positions for the track.
   */
  std::vector<EngineMath::Vector2> m_waypoints;

  /**
   * @brief Game clock for tracking elapsed time.
   */
  sf::Clock m_gameClock;

  /**
   * @brief Elapsed time in seconds since the start of the game.
   */
  float m_timeInSeconds = 0.f;

  /**
   * @brief Leaderboard containing pairs of racer/player names and their ranks.
   */
  std::vector<std::pair<std::string, int>> m_leaderboard;

  /**
   * @brief Image used for track collision detection.
   */
  sf::Image m_trackCollisionImage;
};