#pragma once
#include <Prerequisites.h>
#include "Window.h"
#include "CShape.h"

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
	EngineUtilities::TSharedPointer<Window> m_windowPtr;
	EngineUtilities::TSharedPointer<CShape> m_shapePtr; /**< Pointer to the shape component for rendering. */
  //Window* m_window;  /**< Pointer to the application window wrapper. */
  //sf::CircleShape* m_circle; /**< Pointer to the circle shape for rendering.  */
};
