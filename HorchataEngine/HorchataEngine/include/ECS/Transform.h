#pragma once
#include "Component.h"
#include "../Prerequisites.h"
#include "Window.h"

class
	Transform : public Component {
public:
	/**
	 * @brief Default constructor.
	 */
	Transform() : Component(ComponentType::TRANSFORM),
								m_position(0.0f, 0.0f),
								m_rotation(0.0f),
								m_scale(1.0f, 1.0f) {}
	
	/**
	 * @brief Default destructor.
	 */
	virtual ~Transform() = default;
	
	/**
	 * @brief Initializes the transform component.
	 */
	void
		beginplay() override {}
	
	/**
	 * @brief Updates the transform component.
	 * @param deltaTime Time since the last frame.
	 */
	void
		update(float deltaTime) override {}
	
	/**
	 * @brief Renders the transform component.
	 * @param window The window to render to.
	 */
	void
	render(const EngineUtilities::TSharedPointer<Window>& window) override {}

	/**
	 * @brief Cleans up the transform component.
	 */
	void
		destroy() {}

	void
		seek(const EngineMath::Vector2& targetPosition,
				 float speed,
				 float deltaTime,
				 float range) {
			// Implement seeking behavior towards the target position
			EngineMath::Vector2 direction = targetPosition - m_position;
			float length = EngineMath::sqrt(direction.x * direction.x + direction.y * direction.y);

			if (length > range) {
				direction /= length;
				m_position += direction * speed * deltaTime;
			}
		}

	/**
	* @brief Sets the position of the transform.
	* @param position The new position.
	*/
	void
	setPosition(const EngineMath::Vector2& position) {
			m_position = position;
	}

	/**
	* @brief Gets the position of the transform.
	* @return The current position.
	*/
	EngineMath::Vector2&
	getPosition() {
			return m_position;
	}

	/**
	 * @brief Sets the rotation of the transform.
	 * @param rotation The new rotation angle in degrees.
	 */
	void
	setRotation(float rotation) {
			m_rotation = rotation;
	}
	
	/**
	 * @brief Gets the rotation of the transform.
	 * @return The current rotation angle in degrees.
	 */
	float
		getRotation() {
			return m_rotation;
	}

	/**
	 * @brief Sets the scale of the transform.
	 * @param scale The new scale factor.
	 */
	void
		setScale(const EngineMath::Vector2& scale) {
			m_scale = scale;
	}

	/**
	 * @brief Gets the scale of the transform.
	 * @return The current scale factor.
	 */
	EngineMath::Vector2&
		getScale() {
			return m_scale;
	}

private:
	  /**< Position of the transform. */
		EngineMath::Vector2 m_position; /**< Position of the transform. */
		float m_rotation; /**< Rotation angle in degrees. */
		EngineMath::Vector2 m_scale; /**< Scale factor for the transform. */
};