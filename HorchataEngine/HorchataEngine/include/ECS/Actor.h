#pragma once
#include "../Prerequisites.h"
#include "Entity.h"
#include "Cshape.h"
#include "Transform.h"

class 
Actor : Entity
{
public:
	/**
	 * @brief Default constructor for the Actor class.
	 */
	Actor() = default;

	/**
	 * @brief Constructor for the Actor class with a name
	 * @param actorName The name of the actor.
	 */
	Actor(const std::string& actorName);

	/**
	 * @brief Default destructor for the Actor class.
	 */
	virtual 
	~Actor() = default;

	/**
	 * @brief Adds a component to the actor.
	 * @param component The component to add.
	 */
	void 
	beginplay() override {};

	/**
	 * @brief Updates the actor's components.
	 * @param deltaTime Time since the last frame.
	 */
	void
	update(float deltaTime) override;

	/**
	 * @brief Renders the actor's components to the window.
	 * @param window The window to render to.
	 */
	void
	render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/**
	 * @brief Destroys the actor and its components.
	 */
	void
	destroy() override {};

	void
		setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

	/**
	 * @brief Adds a component to the actor.
	 * @param component The component to add.
	 */
	template <typename T>
	EngineUtilities::TSharedPointer<T>
	getComponent();


private:
	/**
	 * @brief name of the actor.
	 */
	std::string m_name = "Actor";
};

/**
 * @brief Adds a component to the actor.
 * @param component The component to add.
 */
template <typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
	for (auto& component : components) {
		EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
		if (specificComponent) {
			return specificComponent;
		}
	}
	return EngineUtilities::TSharedPointer<T>();
}