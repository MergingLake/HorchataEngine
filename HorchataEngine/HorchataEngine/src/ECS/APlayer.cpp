#include "ECS/APlayer.h"

APlayer::APlayer(const std::string& name) : Actor(name)
{
	
}

void APlayer::update(float deltaTime)
{
	handleInput(deltaTime);
	Actor::update(deltaTime);
}

void APlayer::handleInput(float deltaTime)
{
	EngineUtilities::TSharedPointer<Transform> transform = getComponent<Transform>();
	if (!transform) return;

	// Apply friction for smooth deceleration
	m_velocity.x *= m_friction;
	m_velocity.y *= m_friction;

	// Accelerate and decelerate with the arrow keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		m_velocity.y -= m_acceleration * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		m_velocity.y += m_acceleration * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		m_velocity.x -= m_acceleration * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		m_velocity.x += m_acceleration * deltaTime;
	}

	// Limit the speed
	float currentSpeed = m_velocity.length();
	if (currentSpeed > m_maxSpeed) {
		m_velocity = m_velocity.normalized() * m_maxSpeed;
	}

	// Move the player
	EngineMath::Vector2 currentPos = transform->getPosition();
	transform->setPosition(currentPos + m_velocity * deltaTime);
}

void APlayer::setCurrentWaypointIndex(size_t index)
{
	m_currentWaypointIndex = index;
}

size_t APlayer::getCurrentWaypointIndex() const
{
	return m_currentWaypointIndex;
}

void APlayer::setLapCount(int laps)
{
	m_lapCount = laps;
}

int APlayer::getLapCount() const
{
	return m_lapCount;
}