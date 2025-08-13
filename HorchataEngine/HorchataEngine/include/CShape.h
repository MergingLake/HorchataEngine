#pragma once
#include "Prerequisites.h"
#include "ECS\Component.h"
#include "ECS\Texture.h"

class Window;
//class Texture;

/**
 * @class CShape
 * @brief Component responsible for managing and rendering a 2D shape.
 *
 * Provides methods for creating, updating, and rendering shapes, as well as
 * modifying their position, color, rotation, and scale.
 */
class 
  CShape : public Component {
public:
  /**
   * @brief Default constructor.
   */
  CShape() = default;

  /**
   * @brief Constructor with shape type.
   * @param shapeType Type of the shape to create.
   */
  CShape(ShapeType shapeType) : m_shapePtr(nullptr),
                                m_shapeType(ShapeType::EMPTY),
                                Component(ComponentType::SHAPE) { }

  /**
   * @brief Default destructor.
   */
  virtual
  ~CShape() = default;

  /**
   * @brief Creates a new shape based on the given type.
   * @param shapeType The type of shape to create.
   * @return Pointer to the created shape.
   */
  void
		createShape(ShapeType shapeType);

	void 
    beginplay() override;

  /**
   * @brief Updates the shape state.
   * @param deltaTime Time elapsed since last update.
   */
  void
    update(float deltaTime) override;

  /**
   * @brief Renders the shape to the given window.
   * @param window The window where the shape is rendered.
   */
  void
    render(const EngineUtilities::TSharedPointer<Window>& window) override;

	void 
    destroy() override;

  /**
   * @brief Sets the position of the shape.
   * @param x X coordinate.
   * @param y Y coordinate.
   */
  void
    setPosition(float x, float y);

  /**
   * @brief Sets the position of the shape using a vector.
   * @param position A vector specifying the position.
   */
  void
    setPosition(const EngineMath::Vector2& position);

  /**
   * @brief Sets the fill color of the shape.
   * @param color The color to apply.
   */
  void
    setFillColor(const sf::Color& color);

  /**
   * @brief Sets the rotation of the shape.
   * @param angle Rotation angle in degrees.
   */
  void
    setRotation(const EngineMath::Vector2& rot);

  /**
   * @brief Sets the scale of the shape.
   * @param scl The scale vector to apply.
   */
  void
    setScale(const EngineMath::Vector2& scl);

  void
    setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

private:
	EngineUtilities::TSharedPointer<sf::Shape> m_shapePtr; /**< Shared pointer to the SFML shape. */
  //sf::Shape* m_shape;  /**< Pointer to the SFML shape.*/
  ShapeType m_shapeType;  /**< Type of the shape.*/
  sf::VertexArray* m_line;  /**< Optional line representation (if any).*/
};
