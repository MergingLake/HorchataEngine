#include "ECS/SteeringBehaviors.h"
#include "ECS/Actor.h"
#include "ECS/Transform.h"
#include "ECS/ARacer.h" // Incluir la clase específica para acceder a sus métodos

// Implementación de PathFollowing
PathFollowing::PathFollowing(const std::vector<EngineMath::Vector2>& waypoints)
	: m_waypoints(waypoints)
{
}

void PathFollowing::apply(Actor* actor, float deltaTime)
{
	ARacer* racer = dynamic_cast<ARacer*>(actor);
	if (!racer) return;

	EngineUtilities::TSharedPointer<Transform> transform = racer->getComponent<Transform>();
	if (!transform) return;

	EngineMath::Vector2 currentPos = transform->getPosition();
	size_t currentWaypointIndex = racer->getCurrentWaypointIndex();
	EngineMath::Vector2 targetPos = m_waypoints[currentWaypointIndex];

	// Calcular la distancia al waypoint actual
	float distanceToWaypoint = EngineMath::Vector2::distance(currentPos, targetPos);

	// Si el corredor está lo suficientemente cerca del waypoint, avanza al siguiente
	if (distanceToWaypoint < 50.f) {
		currentWaypointIndex = (currentWaypointIndex + 1) % m_waypoints.size();
		racer->setCurrentWaypointIndex(currentWaypointIndex);
		targetPos = m_waypoints[currentWaypointIndex];
	}

	// Comportamiento Seek simple
	EngineMath::Vector2 desiredVelocity = (targetPos - currentPos).normalized() * racer->getMaxSpeed();
	EngineMath::Vector2 steering = desiredVelocity - racer->getVelocity();

	EngineMath::Vector2 newVelocity = racer->getVelocity() + steering * deltaTime;

	// Limitar velocidad máxima
	if (newVelocity.length() > racer->getMaxSpeed()) {
		newVelocity = newVelocity.normalized() * racer->getMaxSpeed();
	}
	racer->setVelocity(newVelocity);

	// Aplicar la velocidad al transform
	transform->setPosition(currentPos + newVelocity * deltaTime);
}

// Implementación de Arrive
Arrive::Arrive(const EngineMath::Vector2& target)
	: m_target(target)
{

}

void Arrive::apply(Actor* actor, float deltaTime)
{
	// Lógica de Arrive
	// ... (la implementación de Arrive se puede añadir aquí si es necesario)
}