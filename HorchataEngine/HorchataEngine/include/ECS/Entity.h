#pragma once
#include "../Prerequisites.h"
#include "Component.h"

class Window;

class 
Entity {
public:
	/**
	 * @brief Default constructor for the entity.
	 */
	virtual 
		~Entity() = default; // Virtual destructor for proper cleanup

	/*
	* @brief Begin play function for the entity.
	* @param deltaTime Time elapsed since the last update.
	*/
	virtual void
		beginplay() = 0; // Pure virtual function for initialization

	/**
	* @brief Update function for the entity.
	* @param deltaTime Time elapsed since the last update.
	*/
	virtual void
		update(float deltaTime) = 0; // Pure virtual function for updating

	/**
	* @brief Render function for the entity.
	* @param window Pointer to the window to render the entity in.
	*/
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0; // Pure virtual function for rendering

	/*
	 * @brief Cleanup function for the entity.
	 * @param component Pointer to the component to add.
	 */
	virtual void
		destroy() = 0; // Pure virtual function for cleanup

	template <typename T>
	void addComponent(EngineUtilities::TSharedPointer<T> component) {
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		components.push_back(component.template dynamic_pointer_cast<Component>());
	}

	template <typename T>
	EngineUtilities::TSharedPointer<T> 
	getComponent() {
		for(auto& component : components) {
			EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
			if(specificComponent) {
				return specificComponent;
			}
		}

		return EngineUtilities::TSharedPointer<T>();
	}

protected:
	bool isActive;
	uint32_t id;
	std::vector<EngineUtilities::TSharedPointer<Component>> components;
};