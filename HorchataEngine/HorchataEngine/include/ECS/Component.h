#pragma once
#include "../Prerequisites.h"

class Window;

enum
	ComponentType {
	NONE = 0,
	TRANSFORM = 1,
	SPRITE = 2,
	RENDERER = 3,
	PHYSICS = 4,
	AUDIOSOURCE = 5,
	SHAPE = 6,
	TEXTURE = 7
};

class 
	Component {
public:
	/*
	 * @brief Default constructor for the component.
	 */
	Component() = default; // Default constructor

	/*
	 * @brief Constructs a component with a specific type.
	 * @param type The type of the component.
	 */
	Component(const ComponentType type) : m_type(type) {} // Constructor with type

	/*
	 * @brief Destroys the component and frees any resources.
	 */
	virtual 
	~Component() = default; // Virtual destructor for proper cleanup

	/*
	 * @brief Initializes the component at the start of the game.
	 * @param deltaTime Time since the last frame, used for initialization logic.
	 * This function is called once at the beginning of the game to set up the component.
	 * It is a pure virtual function, meaning derived classes must implement it.
	 */
	virtual void
		beginplay() = 0; // Pure virtual function for initialization

	/*
	 * @brief Updates the component every frame.
	 * @param deltaTime Time since the last frame, used for update logic.
	 * This function is called once per frame to update the component.
	 * It is a pure virtual function, meaning derived classes must implement it.
	 */
	virtual void
		update(float deltaTime) = 0; // Pure virtual function for updating the component

	/*
	 * @brief Renders the component.
	 * @param window The window to render the component to.
	 * This function is called once per frame to render the component.
	 * It is a pure virtual function, meaning derived classes must implement it.
	 */
	virtual void
		render(const EngineUtilities::TSharedPointer<Window>& window) = 0; // Pure virtual function for rendering the component

	/*
	 * @brief Destroys the component and frees any resources.
	 */
	virtual void
		destroy() = 0; // Pure virtual function for cleanup

	/*
	 * @brief Gets the type of the component.
	 * @return The type of the component.
	 */
	ComponentType
		getType() const {return m_type;}

protected:
	ComponentType m_type;
};