#pragma once
#include "Component.h"
#include "../Prerequisites.h"

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

	void
		destroy() {}

	void
	setPosition(const sf::Vector2f& position) {
			m_position = position;
	}

	sf::Vector2f&
	getPosition() {
			return m_position;
	}

	void
	setRotation(float rotation) {
			m_rotation = rotation;
	}
	
	float
		getRotation() {
			return m_rotation;
	}

	void
		setScale(const sf::Vector2f& scale) {
			m_scale = scale;
	}

	sf::Vector2f&
		getScale() {
			return m_scale;
	}

private:
		sf::Vector2f m_position; /**< Position of the transform. */
		float m_rotation; /**< Rotation angle in degrees. */
		sf::Vector2f m_scale; /**< Scale factor for the transform. */
};