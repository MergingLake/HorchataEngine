#include "CShape.h"
#include "Window.h"

sf::Shape*
CShape::createShape(ShapeType shapeType) 
{
	m_shapeType = shapeType;
	switch (shapeType) 
	{
	case ShapeType::CIRCLE:
		sf::CircleShape* circle = new sf::CircleShape(10.f); //Example radius
		circle->setFillColor(sf::Color::White);
		m_shape = circle;
		return circle;

	case ShapeType::RECTANGLE:
		sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(100.f, 50.f)); //Example size
		m_shape = rectangle;
		return rectangle;

	case ShapeType::TRIANGLE:
		sf::ConvexShape* triangle = new sf::ConvexShape(3);
		triangle->setPoint(0, sf::Vector2f(0.f, 0.f));
		triangle->setPoint(1, sf::Vector2f(50.f, 100.f));
		triangle->setPoint(2, sf::Vector2f(100.f, 0.f));
		triangle->setFillColor(sf::Color::White);
		m_shape = triangle;
		return triangle;

	case ShapeType::POLYGON:
		sf::ConvexShape* polygon = new sf::ConvexShape(5); //Example with 5 points
		polygon->setPoint(0, sf::Vector2f(0.f, 0.f));
		polygon->setPoint(1, sf::Vector2f(50.f, 100.f));
		polygon->setPoint(2, sf::Vector2f(100.f, 0.f));
		polygon->setPoint(3, sf::Vector2f(75.f, -50.f));
		polygon->setPoint(4, sf::Vector2f(-25.f, -50.f));
		polygon->setFillColor(sf::Color::White);
		m_shape = polygon;
		return polygon;
	}
}