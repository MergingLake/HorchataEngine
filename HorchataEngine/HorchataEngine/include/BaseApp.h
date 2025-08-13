#pragma once
#include <Prerequisites.h>
#include "Window.h"
#include "CShape.h"
#include "ECS/Actor.h"
#include "ECS/APlayer.h"
#include "ECS/ARacer.h"
#include "EngineGUI.h"
#include "GameManager.h"
#include "SteeringBehaviors.h"

/**
 * @class BaseApp
 * @brief Main application class that controls the lifecycle of the program.
 *
 * Handles initialization, frame updates, rendering, and cleanup. It owns the
 * main window and other graphical elements needed for the application.
 */
class 
  BaseApp {
public:
  /**
   * @brief Default constructor.
   */
  BaseApp() = default;

  /**
   * @brief Destructor.
   */
  ~BaseApp();

  /**
   * @brief Runs the main application loop.
   * @return Application exit status code.
   */
  int
    run();

  /**
   * @brief Initializes the application resources and window.
   * @return True if initialization is successful, false otherwise.
   */
  bool
    init();

  /**
   * @brief Updates the application logic on each frame.
   */
  void
    update();

  /**
   * @brief Renders the current frame to the screen.
   */
  void
    render();

  /**
   * @brief Cleans up and releases resources before exiting.
   */
  void
    destroy();

private:
	std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors; /**< Vector of actors in the scene. */
	
  EngineUtilities::TSharedPointer<Window> m_windowPtr;

	EngineUtilities::TSharedPointer<APlayer> m_Aplayer; /**< Pointer to the actor component for managing entities. */
	EngineUtilities::TSharedPointer<Actor> m_ATrack; /**< Pointer to the circle shape component for rendering. */
	std::vector<EngineUtilities::TSharedPointer<ARacer>> m_Aracers; /**< Vector of AI racers in the game. */

	EngineUtilities::TSharedPointer<GameManager> m_gameManager; /**< Pointer to the GameManager for high-level game logic. */
  std::vector<EngineMath::Vector2> m_waypoints;

	EngineGUI m_engineGUI; /**< Instance of the EngineGUI for rendering ImGui elements. */
};
