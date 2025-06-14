#pragma once
#include "Prerequisites.h"

/**
 * @class Window
 * @brief Wrapper class for managing an SFML RenderWindow.
 *
 * Provides window creation, event handling, drawing, and resource cleanup.
 */
class 
  Window {
public:
  /**
   * @brief Default constructor.
   */
  Window() = default;

  /**
   * @brief Constructs a window with specified dimensions and title.
   * @param width Width of the window in pixels.
   * @param height Height of the window in pixels.
   * @param title Window title as a string.
   */
  Window(int width, int height, const std::string& title);

  /**
   * @brief Destructor, destroys the window and releases resources.
   */
  ~Window();

  /**
   * @brief Handles window events (input, close, etc.).
   */
  void
    handleEvents();

  /**
   * @brief Checks if the window is still open.
   * @return True if window is open, false otherwise.
   */
  bool
    isOpen() const;

  /**
   * @brief Clears the window with a given color.
   * @param color The clear color, defaults to opaque black.
   */
  void
    clear(const sf::Color& color = sf::Color(0, 0, 0, 255));

  /**
   * @brief Draws a drawable object to the window.
   * @param drawable The SFML drawable object to draw.
   * @param states Render states to apply, default is none.
   */
  void
    draw(const sf::Drawable& drawable,
      const sf::RenderStates& states = sf::RenderStates::Default);

  /**
   * @brief Displays the rendered frame on the screen.
   */
  void
    display();

  /**
   * @brief Destroys the window and releases allocated resources.
   */
  void
    destroy();

private:
  sf::RenderWindow* m_window; /**< Pointer to the SFML RenderWindow. */
};
