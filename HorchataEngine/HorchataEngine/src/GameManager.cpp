#include "GameManager.h"
#include "ECS/Transform.h"
#include <algorithm>
#include <SFML/Graphics/Image.hpp>

GameManager::GameManager()
{
}

void GameManager::init(EngineUtilities::TSharedPointer<Actor> trackActor, std::vector<EngineMath::Vector2> waypoints)
{
	m_trackActor = trackActor;
	m_waypoints = waypoints;

	// Load the track texture as an image for collision checking
	auto textureComponent = m_trackActor->getComponent<Texture>();
	if (textureComponent) {
		const sf::Texture* texture = &textureComponent->getTexture();

		if (texture) {
			m_trackCollisionImage = texture->copyToImage();
		}
	}
}

void GameManager::update(float deltaTime, std::vector<EngineUtilities::TSharedPointer<ARacer>>& racers, EngineUtilities::TSharedPointer<APlayer>& player)
{
	m_timeInSeconds += deltaTime;

	updateRanks(racers, player);
	checkCollisions(player);

	// Update waypoints for each bot
	for (auto& racer : racers) {
		EngineMath::Vector2 currentPos = racer->getComponent<Transform>()->getPosition();
		EngineMath::Vector2 targetWaypoint = m_waypoints[racer->getCurrentWaypointIndex()];
		float distance = EngineMath::Vector2::distance(currentPos, targetWaypoint);
		if (distance < 50.f) {
			size_t nextIndex = (racer->getCurrentWaypointIndex() + 1) % m_waypoints.size();
			racer->setCurrentWaypointIndex(nextIndex);

			// If the bot has completed a lap
			if (nextIndex == 0) {
				racer->setLapCount(racer->getLapCount() + 1);
			}
		}
	}

	// Similar logic for the player
	EngineMath::Vector2 playerPos = player->getComponent<Transform>()->getPosition();
	EngineMath::Vector2 playerTargetWaypoint = m_waypoints[player->getCurrentWaypointIndex()];
	float playerDistance = EngineMath::Vector2::distance(playerPos, playerTargetWaypoint);
	if (playerDistance < 50.f) {
		size_t nextIndex = (player->getCurrentWaypointIndex() + 1) % m_waypoints.size();
		player->setCurrentWaypointIndex(nextIndex);

		// If the player has completed a lap
		if (nextIndex == 0) {
			player->setLapCount(player->getLapCount() + 1);
		}
	}
}

void GameManager::updateRanks(std::vector<EngineUtilities::TSharedPointer<ARacer>>& racers, EngineUtilities::TSharedPointer<APlayer>& player)
{
	m_leaderboard.clear();

	// Create a list of all racers
	std::vector<std::pair<EngineUtilities::TSharedPointer<Actor>, float>> allRacers;

	allRacers.push_back({ player, player->getLapCount() * m_waypoints.size() + player->getCurrentWaypointIndex() });
	for (auto& racer : racers) {
		allRacers.push_back({ racer, racer->getLapCount() * m_waypoints.size() + racer->getCurrentWaypointIndex() });
	}

	// Sort the list by position on the track (highest to lowest)
	std::sort(allRacers.begin(), allRacers.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});

	// Fill the leaderboard
	for (size_t i = 0; i < allRacers.size(); ++i) {
		m_leaderboard.push_back({ allRacers[i].first->getName(), i + 1 });
	}
}

void GameManager::checkCollisions(EngineUtilities::TSharedPointer<APlayer>& player)
{
	auto transform = player->getComponent<Transform>();
	if (!transform) return;

	// Get the player's position in world coordinates
	EngineMath::Vector2 playerPos = transform->getPosition();

	// Convert the player's position to track image coordinates
	auto trackTransform = m_trackActor->getComponent<Transform>();
	if (!trackTransform) return;

	EngineMath::Vector2 trackOrigin = trackTransform->getOrigin();
	EngineMath::Vector2 trackPosition = trackTransform->getPosition();
	EngineMath::Vector2 trackScale = trackTransform->getScale();
	sf::IntRect trackBounds = trackTransform->getGlobalBounds();

	// Normalize the player's position to the track (coordinates 0-1)
		// sf::FloatRect uses .left, .top, .width, .height in SFML, but if your sf::Rect<float> does not, use .x, .y, .width, .height
	float normalizedX = (playerPos.x - trackBounds.position.x) / trackBounds.size.x;
	float normalizedY = (playerPos.y - trackBounds.position.y) / trackBounds.size.y;

	unsigned int pixelX = static_cast<unsigned int>(normalizedX * m_trackCollisionImage.getSize().x);
	unsigned int pixelY = static_cast<unsigned int>(normalizedY * m_trackCollisionImage.getSize().y);

	if (pixelX < m_trackCollisionImage.getSize().x &&
		pixelY < m_trackCollisionImage.getSize().y)
	{
		sf::Color pixelColor = m_trackCollisionImage.getPixel(sf::Vector2u(pixelX, pixelY));

		// If the pixel is black, it is a "death" zone
		if (pixelColor == sf::Color::Black) {
			size_t lastWaypointIndex = (player->getCurrentWaypointIndex() > 0) ? player->getCurrentWaypointIndex() - 1 : m_waypoints.size() - 1;
			transform->setPosition(m_waypoints[lastWaypointIndex]);
		}
	}
}

void GameManager::renderHUD(EngineUtilities::TSharedPointer<Window>& window)
{
	ImGui::Begin("Game HUD");

	// Stopwatch
	ImGui::Text("Time: %.2f", m_timeInSeconds);

	// Leaderboard
	ImGui::Text("Leaderboard:");
	ImGui::Separator();
	for (const auto& entry : m_leaderboard) {
		ImGui::Text("%d. %s", entry.second, entry.first.c_str());
	}

	ImGui::End();
}